#include "model.hxx"


Model::Model(Game_config const& config)
    : config(config),
      frog(config)
{
    time_since_start = 0.0;
    lanes_vec = {
            Lane(0.0, 0,
                 "wwwggwwwggwwwggwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"),
            Lane(-3.0, 0,
                 ",,,llll,,llllll,,,,,,,llll,,,,,ll,,,lllll,,,,llllll,,,,lllll,,,,"),
            Lane(3.0, 0,
                 ",,,,llll,,,,,llll,,,,llll,,,,,,,,,llll,,,,,ll,,,,,,llllll,,,,,,,"),
            Lane(2.0, 0,
                 ",,lll,,,,,lll,,,,,ll,,,,,lll,,,lll,,,,ll,,,,llll,,,,ll,,,,,,ll,,"),
            Lane(0.0, 0,
                 "gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg"),
            Lane(-3.0, 0,
                 "....bbbb.......bbbb....bbbb..........bbbb........bbbb....bbbb..."),
            Lane(3.0, 0,
                 ".....cc..cc....cc....cc.....cc........cc..cc.cc......cc.......cc"),
            Lane(-4.0, 0,
                 "..cc.....bbbb.......cc..cc........cc...cc....bbbb......cc...cc.."),
            Lane(2.0, 0,
                 "..cc.....cc.......cc.....cc......cc..cc.cc.......cc....cc......."),
            Lane(0.0, 0,
                 "gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg")};

    for (int i = 0; i < config.scene_dims.width; i++) {
        for (int j = 0; j < config.scene_dims.height; j++) {
            danger_tiles.push_back(false);
        }
    }
}

void Model::on_frame(double dt)
{
    time_since_start += dt;
    int x = -1;
    int y = 0;

    for (auto lane : lanes_vec) {
        lane.view_posn = (int)(time_since_start * lane.x_velocity) % 64;
        if (lane.view_posn < 0) {
            lane.view_posn = 64 - (abs(lane.view_posn) % 64);
        }
        for (int i = 0; i < config.lane_width; i++) {
            char lane_object = lane.lane_objects[(lane.view_posn + i) % 64];

            //choose which tiles are dangerous
            for (int j = (x + i)*config.cell_size; j < (x + i + 1)*config
            .cell_size; j++) {
                for (int k = y * config.cell_size; k < (y + 1)*config
                .cell_size; k++) {
                    //if we are on the bounds of the displayed screen
                    if (j >= 0 && j < config.scene_dims.width && k >= 0 && k
                            < config.scene_dims.height) {
                        danger_tiles[k * config.scene_dims.width + j] =
                                !(lane_object == '.' ||
                                lane_object == 'g' || lane_object == 'l');
                    }
                }
            }
        }
    }

    //move frog's posn with lane velocity if it's in a water lane
    if (water_lane()) {
        frog.frog_posn.x -= dt * lanes_vec[(int)frog.frog_posn.y].x_velocity;
    }

}

void Model::detect_collision() {

    bool tl = danger_tiles[
            (int)(frog.frog_posn.y * config.cell_size +1) *
            config.scene_dims.width +
            (int)(frog.frog_posn.x * config.cell_size + 1)
            ];

    bool tr = danger_tiles[
            (int)(frog.frog_posn.y * config.cell_size + 1) *
            config.scene_dims.width +
            (int)((frog.frog_posn.x + 1)*config.cell_size - 1)
            ];

    bool bl = danger_tiles[
            (int)((frog.frog_posn.y+1) * config.cell_size - 1) *
            config.scene_dims.width +
            (int)(frog.frog_posn.x * config.cell_size + 1)
            ];

    bool br = danger_tiles[
            (int)((frog.frog_posn.y + 1) * config.cell_size - 1) *
            config.scene_dims.width +
            (int)((frog.frog_posn.x + 1) * config.cell_size - 1)
            ];

    if (tl || tr || bl || br)
    {
        // We've gotta dead frog
        frog.dead_frog(config);
    }
}

bool
Model::water_lane() {
    if (frog.frog_posn.y <= 3) {
        return true;
    }
    return false;
}