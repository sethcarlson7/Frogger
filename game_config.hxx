#pragma once

#include <ge211.hxx>


struct Game_config {
    //Constructs an instance with default parameters
    Game_config();

    ge211::Dims<int> scene_dims;
    int lane_width;
    int cell_size;
    ge211::Dims<int> cell_dims;
    ge211::Posn<float> starting_posn;
};
