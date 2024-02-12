#include "PID.hpp"


PID::PID() {
    _integral = 0;
};


float PID::calc_u(float y_sp, float prev_y) {
    float e = y_sp - prev_y;

    float p_term = _k_p * e;

    _integral += _dt * e;
    float i_term = _k_i * _integral;

    float d_term = _k_d * (y_sp - prev_y) / _dt;

    return p_term + i_term + d_term;
};