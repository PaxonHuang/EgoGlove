/*
 * hand_skeleton.c — Hand Token v2 canonical-20 forward kinematics.
 */
#include "hand_skeleton.h"

#include <math.h>
#include <stddef.h>

const int8_t hand_skeleton_parent[HAND_SKELETON_JOINT_COUNT] = {
    -1, 0, 1, 2,
     0, 4, 5, 6,
     0, 8, 9, 10,
     0, 12, 13, 14,
     0, 16, 17, 18
};

static int supported_model(uint16_t model_id)
{
    return model_id == HAND_REST_MODEL_CANONICAL_HUMAN ||
           model_id == HAND_REST_MODEL_MANO_ALIGNED ||
           model_id == HAND_REST_MODEL_OPENXR_ALIGNED;
}

static int zero_vec3(const float v[3])
{
    return v[0] == 0.0f && v[1] == 0.0f && v[2] == 0.0f;
}

static int normalize_quat(const float in[4], float out[4])
{
    float norm2 = in[0] * in[0] + in[1] * in[1] +
                  in[2] * in[2] + in[3] * in[3];
    if (!isfinite(norm2) || norm2 <= 0.0f) return 0;
    float inv = 1.0f / sqrtf(norm2);
    for (int i = 0; i < 4; ++i) out[i] = in[i] * inv;
    return 1;
}

static void quat_mul(const float a[4], const float b[4], float out[4])
{
    out[0] = a[0] * b[0] - a[1] * b[1] - a[2] * b[2] - a[3] * b[3];
    out[1] = a[0] * b[1] + a[1] * b[0] + a[2] * b[3] - a[3] * b[2];
    out[2] = a[0] * b[2] - a[1] * b[3] + a[2] * b[0] + a[3] * b[1];
    out[3] = a[0] * b[3] + a[1] * b[2] - a[2] * b[1] + a[3] * b[0];
}

static void quat_rotate(const float q[4], const float v[3], float out[3])
{
    float u[3] = {q[1], q[2], q[3]};
    float uv[3] = {
        u[1] * v[2] - u[2] * v[1],
        u[2] * v[0] - u[0] * v[2],
        u[0] * v[1] - u[1] * v[0]
    };
    float uuv[3] = {
        u[1] * uv[2] - u[2] * uv[1],
        u[2] * uv[0] - u[0] * uv[2],
        u[0] * uv[1] - u[1] * uv[0]
    };
    for (int i = 0; i < 3; ++i) out[i] = v[i] + 2.0f * (q[0] * uv[i] + uuv[i]);
}

hand_skeleton_status_t hand_skeleton_fk21(
    const hand_skeleton_t *skeleton,
    float out_landmarks[HAND_MEDIAPIPE_LANDMARK_COUNT][3])
{
    if (!skeleton || !out_landmarks) return HAND_SKELETON_INVALID_ARGUMENT;
    if (!supported_model(skeleton->model_id)) return HAND_SKELETON_UNSUPPORTED_MODEL;
    if (skeleton->revision == 0) return HAND_SKELETON_INVALID_REVISION;
    if (!zero_vec3(skeleton->offsets[0])) return HAND_SKELETON_INVALID_WRIST_OFFSET;
    for (int offset = 1; offset < HAND_SKELETON_OFFSET_COUNT; ++offset) {
        for (int component = 0; component < 3; ++component) {
            if (!isfinite(skeleton->offsets[offset][component])) {
                return HAND_SKELETON_INVALID_ARGUMENT;
            }
        }
    }

    float global_q[HAND_SKELETON_JOINT_COUNT][4];
    float global_p[HAND_SKELETON_JOINT_COUNT][3] = {{0}};
    for (int joint = 0; joint < HAND_SKELETON_JOINT_COUNT; ++joint) {
        float local_q[4];
        if (!normalize_quat(skeleton->quat[joint], local_q)) {
            return HAND_SKELETON_INVALID_ARGUMENT;
        }
        int parent = hand_skeleton_parent[joint];
        if (parent < 0) {
            for (int k = 0; k < 4; ++k) global_q[joint][k] = local_q[k];
            continue;
        }
        quat_mul(global_q[parent], local_q, global_q[joint]);
        float rotated[3];
        quat_rotate(global_q[parent], skeleton->offsets[joint], rotated);
        for (int k = 0; k < 3; ++k) global_p[joint][k] = global_p[parent][k] + rotated[k];
    }

    static const int canonical_for_mediapipe[HAND_MEDIAPIPE_LANDMARK_COUNT] = {
        0, 1, 2, 3, -1,
        5, 6, 7, -1,
        9, 10, 11, -1,
        13, 14, 15, -1,
        17, 18, 19, -1
    };
    static const int distal_for_tip[5] = {3, 7, 11, 15, 19};
    static const int tip_output[5] = {4, 8, 12, 16, 20};

    for (int i = 0; i < HAND_MEDIAPIPE_LANDMARK_COUNT; ++i) {
        int joint = canonical_for_mediapipe[i];
        if (joint >= 0) {
            for (int k = 0; k < 3; ++k) out_landmarks[i][k] = global_p[joint][k];
        }
    }
    for (int finger = 0; finger < 5; ++finger) {
        int distal = distal_for_tip[finger];
        int output = tip_output[finger];
        float rotated[3];
        quat_rotate(global_q[distal], skeleton->offsets[20 + finger], rotated);
        for (int k = 0; k < 3; ++k) out_landmarks[output][k] = global_p[distal][k] + rotated[k];
    }
    return HAND_SKELETON_OK;
}
