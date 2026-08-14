#include "madgwick.h"
#include <math.h>

void madgwick_init(madgwick_t *m, float beta) {
    m->beta = beta;
    m->q0 = 1.0f; m->q1 = 0.0f; m->q2 = 0.0f; m->q3 = 0.0f;
}

void madgwick_get_quat(const madgwick_t *m, float out[4]) {
    out[0] = m->q0; out[1] = m->q1; out[2] = m->q2; out[3] = m->q3;
}

void madgwick_set_quat(madgwick_t *m, const float q[4]) {
    m->q0 = q[0]; m->q1 = q[1]; m->q2 = q[2]; m->q3 = q[3];
}

static float rsqrt_(float x) { return 1.0f / sqrtf(x); }

/*
 * Madgwick 6-axis gradient-descent AHRS (accel + gyro; no magnetometer).
 * Convention: identity quat <=> sensor +z aligned with gravity (up).
 *   ghat = q (x) (0,0,0,1) (x) q*   -- estimated gravity in body frame
 *   f    = ghat - a                 -- residual vs measured (normalised) accel
 *   s    = J^T f                    -- gradient of ||f||^2 wrt quaternion
 *   qdot = 0.5*q(x)w - beta*s       -- gyro rate + corrective step
 */
void madgwick_update(madgwick_t *m,
                     float gx, float gy, float gz,
                     float ax, float ay, float az,
                     float dt) {
    float q0 = m->q0, q1 = m->q1, q2 = m->q2, q3 = m->q3;
    float beta = m->beta;
    float qDot1, qDot2, qDot3, qDot4;
    float s0, s1, s2, s3, sn;
    float f0, f1, f2;
    float rn;

    /* Rate of change of quaternion from gyroscope (rad/s) */
    qDot1 = 0.5f * (-q1*gx - q2*gy - q3*gz);
    qDot2 = 0.5f * ( q0*gx + q2*gz - q3*gy);
    qDot3 = 0.5f * ( q0*gy - q1*gz + q3*gx);
    qDot4 = 0.5f * ( q0*gz + q1*gy - q2*gx);

    /* Feedback only if accelerometer measurement is valid */
    if (!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f))) {
        rn = rsqrt_(ax*ax + ay*ay + az*az);
        ax *= rn; ay *= rn; az *= rn;

        /* Estimated gravity in body frame (half-vector form) */
        f0 = 2.0f*(q1*q3 - q0*q2) - ax;
        f1 = 2.0f*(q0*q1 + q2*q3) - ay;
        f2 = (q0*q0 - q1*q1 - q2*q2 + q3*q3) - az;

        /* s = J^T f, J = dghat/dq  (2026-08-11: f1 Jacobian coeffs corrected
           from -2q1/-2q0 to +2q1/+2q0 per true J = dghat/dq; see decision
           record above) */
        /* f2 Jacobian is the FULL ∂f2/∂q = (2q0,-2q1,-2q2,2q3), not the
           published constraint-substituted 2(0.5-q1²-q2²); same residuals and
           fixed points, slightly different descent path — do NOT "correct" it. */
        s0 = f0*(-2.0f*q2) + f1*( 2.0f*q1) + f2*( 2.0f*q0);
        s1 = f0*( 2.0f*q3) + f1*( 2.0f*q0) + f2*(-2.0f*q1);
        s2 = f0*(-2.0f*q0) + f1*( 2.0f*q3) + f2*(-2.0f*q2);
        s3 = f0*( 2.0f*q1) + f1*( 2.0f*q2) + f2*( 2.0f*q3);
        /* Guard |s|==0 (no accel residual): rsqrt(0)=inf would turn 0*inf into NaN */
        {
            float ss = s0*s0 + s1*s1 + s2*s2 + s3*s3;
            if (ss > 1e-12f) { sn = rsqrt_(ss); s0 *= sn; s1 *= sn; s2 *= sn; s3 *= sn; }
        }

        /* Corrective step */
        qDot1 -= beta * s0;
        qDot2 -= beta * s1;
        qDot3 -= beta * s2;
        qDot4 -= beta * s3;
    }

    /* Integrate */
    q0 += qDot1 * dt;
    q1 += qDot2 * dt;
    q2 += qDot3 * dt;
    q3 += qDot4 * dt;

    /* Normalise — guarded like the s-normalize above: a degenerate zero/NaN
       norm must never reach rsqrt(0)→NaN; leave q as-is instead. Valid inputs
       (identity start, unit-norm integration) keep the exact original path. */
    float n2 = q0*q0 + q1*q1 + q2*q2 + q3*q3;
    if (n2 > 1e-12f) {
        rn = rsqrt_(n2);
        m->q0 = q0*rn; m->q1 = q1*rn; m->q2 = q2*rn; m->q3 = q3*rn;
    }
}
