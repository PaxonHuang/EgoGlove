#ifndef ECHOGLOVE_MADGWICK_H
#define ECHOGLOVE_MADGWICK_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    float beta;
    float q0, q1, q2, q3;  /* w, x, y, z */
} madgwick_t;

void madgwick_init(madgwick_t *m, float beta);
void madgwick_update(madgwick_t *m,
                     float gx, float gy, float gz,   /* rad/s */
                     float ax, float ay, float az,   /* g */
                     float dt);                      /* s */
void madgwick_get_quat(const madgwick_t *m, float out[4]);
void madgwick_set_quat(madgwick_t *m, const float q[4]);

#ifdef __cplusplus
}
#endif
#endif
