#pragma once

#include "game_config.hxx"

#include <ge211.hxx>



struct Lane
{

    Lane(float x_velocity, int view_posn, std::string lane_objects);

    float x_velocity;
    int view_posn;
    std::string lane_objects;
};
