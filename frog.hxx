#pragma once

#include "game_config.hxx"

#include <ge211.hxx>

#include <iostream>

using Position = ge211::Posn<float>;

struct Frog {

    Frog(Game_config const&);

    void dead_frog(Game_config const&);

    int lives;
    Position frog_posn;
};