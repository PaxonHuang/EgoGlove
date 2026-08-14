#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "madgwick.h"

static float qnorm(const float q[4]) {
    return sqrtf(q[0]*q[0]+q[1]*q[1]+q[2]*q[2]+q[3]*q[3]);
}

static void test_static_no_drift(void) {
    madgwick_t m;
    madgwick_init(&m, 0.1f);
    for (int i = 0; i < 6000; i++) {          /* 60 s @ 100 Hz */
        madgwick_update(&m, 0,0,0, 0,0,1, 0.01f);
    }
    float q[4]; madgwick_get_quat(&m, q);
    assert(fabsf(q[0] - 1.0f) < 1e-3f);
    assert(fabsf(q[1]) < 1e-3f && fabsf(q[2]) < 1e-3f && fabsf(q[3]) < 1e-3f);
}

static void test_converge_from_perturbation(void) {
    /* tilt (q1,q2) is corrected by gravity; yaw (q3) is unobservable from
       accel alone and must stay bounded, not diverge. */
    madgwick_t m;
    madgwick_init(&m, 0.1f);
    float q0[4] = {0.9990f, 0.02f, 0.02f, 0.02f};
    madgwick_set_quat(&m, q0);
    for (int i = 0; i < 6000; i++) {
        madgwick_update(&m, 0,0,0, 0,0,1, 0.01f);
    }
    float q[4]; madgwick_get_quat(&m, q);
    assert(fabsf(q[0] - 1.0f) < 1e-2f);
    assert(fabsf(q[1]) < 1e-2f && fabsf(q[2]) < 1e-2f);  /* tilt corrected */
    assert(fabsf(q[3]) < 0.03f);                         /* yaw bounded */
}

static void test_rotate_90_deg_x(void) {
    madgwick_t m;
    madgwick_init(&m, 0.0f);                   /* feedback off: pure integration */
    const float deg90 = 1.5707963f;            /* 90 deg/s about x */
    for (int i = 0; i < 100; i++) {            /* 1.0 s */
        madgwick_update(&m, deg90, 0, 0, 0,0,1, 0.01f);
    }
    float q[4]; madgwick_get_quat(&m, q);
    assert(fabsf(q[0] - 0.7071f) < 0.05f);
    assert(fabsf(q[1] - 0.7071f) < 0.05f);
    assert(fabsf(q[2]) < 0.05f && fabsf(q[3]) < 0.05f);
    assert(fabsf(qnorm(q) - 1.0f) < 1e-3f);
}

static void test_converge_gravity_neg_y(void) {
    /* gravity along -y (device rolled -90deg about x) converges to q = -90deg
       about x. 2026-08-11: previous assertion (q[1] -> +0.7071) codified a
       gradient sign bug (see decision record); physical truth is
       q = (cos45, -sin45, 0, 0). */
    madgwick_t m;
    madgwick_init(&m, 0.1f);
    for (int i = 0; i < 2000; i++) {           /* 20 s */
        madgwick_update(&m, 0,0,0, 0,-1,0, 0.01f);
    }
    float q[4]; madgwick_get_quat(&m, q);
    /* q should be ~(cos45, -sin45, 0, 0) = rotation -90deg about x */
    assert(fabsf(q[0] - 0.7071f) < 0.05f);
    assert(fabsf(q[1] + 0.7071f) < 0.05f);
    assert(fabsf(q[2]) < 0.05f && fabsf(q[3]) < 0.05f);
}

static void test_converge_flip_180_no_ambiguity_guard(void) {
    /* Sign preservation: at roll +90 with gravity -y, the correction step s is
       collinear with q (s || q), so discrete normalize(q - eps*s_hat) is a fixed
       point. Accel alone cannot resolve the +/-180 sign without gyro history
       (no magnetometer); the filter stays at +90 instead of jumping to -90.
       This is expected physics, not a bug. */
    madgwick_t m;
    madgwick_init(&m, 0.1f);
    float q0[4] = {0.7071f, 0.7071f, 0.0f, 0.0f};  /* already 90deg about x */
    madgwick_set_quat(&m, q0);
    for (int i = 0; i < 1000; i++) {
        madgwick_update(&m, 0,0,0, 0,-1,0, 0.01f); /* gravity -y in body */
    }
    float q[4]; madgwick_get_quat(&m, q);
    assert(fabsf(q[0] - 0.7071f) < 0.02f);
    assert(fabsf(q[1] - 0.7071f) < 0.02f);
}

int main(void) {
    test_static_no_drift();
    test_converge_from_perturbation();
    test_rotate_90_deg_x();
    test_converge_gravity_neg_y();
    test_converge_flip_180_no_ambiguity_guard();
    printf("MADGWICK: all tests PASS\n");
    return 0;
}
