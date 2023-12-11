#include "view.hxx"

static ge211::Color const grass_color {124,252,0}; //lawn_green
static ge211::Color const road_color {105,105,105}; //dim gray
static ge211::Color const water_color {72,209,204}; //medium turquoise
static ge211::Color const car_color {255,69,0}; //orange red
static ge211::Color const bus_color {255,215,0}; //gold
static ge211::Color const log_color {139,69,19}; //saddle brown
static ge211::Color const wall_color {128,0,0}; //maroon

static ge211::Color const frog_color {255,20,147}; //deep pink


View::View(Model const& m)
        : model_(m),
            grass_sprite(m.config.cell_dims, grass_color),
            water_sprite(m.config.cell_dims, water_color),
            road_sprite(m.config.cell_dims, road_color),
            car_sprite(m.config.cell_dims, car_color),
            bus_sprite(m.config.cell_dims, bus_color),
            log_sprite(m.config.cell_dims, log_color),
            wall_sprite(m.config.cell_dims, wall_color),
            frog_sprite(m.config.cell_dims, frog_color)


{ }

void
View::draw(ge211::Sprite_set& set)
{
    float x = 0;
    float y = 0;

    for (auto lane : model_.lanes_vec) {
        for (size_t i = 0;
             i < model_.config.scene_dims.width / model_.config.cell_size;
             i++) {
            char lane_object = lane.lane_objects[(lane.view_posn + i) % 64];

            ge211::Posn<int> top_left_lane_object = {(int)
                                              (x+i) * model_.config.cell_size,
                                              (int)
                                              (y * model_.config.cell_size)};
            switch (lane_object)
            {
            case '.': set.add_sprite(road_sprite, top_left_lane_object);
                break;
            case ',': set.add_sprite(water_sprite, top_left_lane_object);
                break;
            case 'g': set.add_sprite(grass_sprite, top_left_lane_object);
                break;
            case 'c': set.add_sprite(car_sprite, top_left_lane_object);
                break;
            case 'b': set.add_sprite(bus_sprite, top_left_lane_object);
                break;
            case 'l': set.add_sprite(log_sprite, top_left_lane_object);
                break;
            case 'w': set.add_sprite(wall_sprite, top_left_lane_object);
                break;
            }

        }
        y++;
    }
    ge211::Posn<int> frog_posn_int = {(int)model_.frog.frog_posn.x,
                                      (int)model_.frog.frog_posn.y};
    set.add_sprite(frog_sprite, frog_posn_int, 1);

    // This needs to do something!



}
