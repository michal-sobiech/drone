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


void PID::set_k_p(float k_p) {
    _k_p = k_p;
}


void PID::set_k_i(float k_i) {
    _k_i = k_i;
}


void PID::set_k_d(float k_d) {
    _k_d = k_d;
}


float PID::get_k_p() {
    return _k_p;
}


float PID::get_k_i() {
    return _k_i;
}


float PID::get_k_d() {
    return _k_d;
}