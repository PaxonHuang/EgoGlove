/*
 * hand_skeleton.h — Hand Token v2 canonical-20 skeleton and FK contract.
 * Portable C11; no platform dependencies.
 */
#ifndef ECHOGLOVE_HAND_SKELETON_H
#define ECHOGLOVE_HAND_SKELETON_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define HAND_SKELETON_JOINT_COUNT 20
#define HAND_SKELETON_OFFSET_COUNT 25
#define HAND_MEDIAPIPE_LANDMARK_COUNT 21

#define HAND_REST_MODEL_CANONICAL_HUMAN 0u
#define HAND_REST_MODEL_MANO_ALIGNED    1u
#define HAND_REST_MODEL_OPENXR_ALIGNED  2u

typedef struct {
    float quat[HAND_SKELETON_JOINT_COUNT][4];
    float offsets[HAND_SKELETON_OFFSET_COUNT][3];
    uint16_t model_id;
    uint16_t revision;
} hand_skeleton_t;

typedef enum {
    HAND_SKELETON_OK = 0,
    HAND_SKELETON_INVALID_ARGUMENT,
    HAND_SKELETON_INVALID_WRIST_OFFSET,
    HAND_SKELETON_UNSUPPORTED_MODEL,
    HAND_SKELETON_INVALID_REVISION
} hand_skeleton_status_t;

extern const int8_t hand_skeleton_parent[HAND_SKELETON_JOINT_COUNT];

hand_skeleton_status_t hand_skeleton_fk21(
    const hand_skeleton_t *skeleton,
    float out_landmarks[HAND_MEDIAPIPE_LANDMARK_COUNT][3]);

#ifdef __cplusplus
}
#endif

#endif /* ECHOGLOVE_HAND_SKELETON_H */
