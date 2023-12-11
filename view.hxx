#pragma once

#include "model.hxx"


class View
{
public:
    explicit View(Model const& model);

    void draw(ge211::Sprite_set& set);

private:
    Model const& model_;
    ge211::Rectangle_sprite const grass_sprite;
    ge211::Rectangle_sprite const water_sprite;
    ge211::Rectangle_sprite const road_sprite;
    ge211::Rectangle_sprite const car_sprite;
    ge211::Rectangle_sprite const bus_sprite;
    ge211::Rectangle_sprite const log_sprite;
    ge211::Rectangle_sprite const wall_sprite;
    //temporary
    ge211::Rectangle_sprite const frog_sprite;
};
