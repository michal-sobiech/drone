#pragma once


class PID {
public:
    PID() = default;
    // Calculates the control output
    float calc_y(float y_sp);
protected:
    float k_p;
    float k_i;
    float k_d;
    float last_error;
    float integral;
};