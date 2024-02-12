#pragma once


class PID {
public:
    PID();
    // Calculates the control output
    float calc_u(float y_sp, float prev_y);
protected:
    float _k_p;
    float _k_i;
    float _k_d;
    float _last_error;
    float _integral;
    float _dt;
};