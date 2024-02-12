#pragma once


class PID {
public:
    PID();
    // Calculates the control output
    float calc_u(float y_sp, float prev_y);
    void set_k_p(float k_p);
    void set_k_i(float k_i);
    void set_k_d(float k_d);
    float get_k_p();
    float get_k_i();
    float get_k_d();
protected:
    float _k_p;
    float _k_i;
    float _k_d;
    float _last_error;
    float _integral;
    float _dt;
};