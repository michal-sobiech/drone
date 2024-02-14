#pragma once


struct EngineSpeeds {
    float fr_speed;
    float fl_speed;
    float bl_speed;
    float br_speed;

    EngineSpeeds operator+(const EngineSpeeds& speeds) const {
        return EngineSpeeds{
            fr_speed + speeds.fr_speed,
            fl_speed + speeds.fl_speed,
            bl_speed + speeds.bl_speed,
            br_speed + speeds.br_speed
        };
    }
};