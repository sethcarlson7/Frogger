#pragma once

#include <ge211.hxx>
#include "game_config.hxx"
#include <vector>
#include "lane.hxx"
#include "frog.hxx"



struct Model
{
    explicit Model(Game_config const& config = Game_config());

    void on_frame(double dt);

    void detect_collision();

    bool water_lane();

    Game_config const config;
    Frog frog;
    float time_since_start;
    std::vector<Lane> lanes_vec;
    std::vector<bool> danger_tiles;

};
