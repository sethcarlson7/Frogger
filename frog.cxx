#include "frog.hxx"
#include "game_config.hxx"

Frog::Frog(Game_config const& config)
    : frog_posn(config.starting_posn)
{
    lives = 3;
}

void
Frog::dead_frog(Game_config const& config)
{
    frog_posn = config.starting_posn;
    lives--;
}
