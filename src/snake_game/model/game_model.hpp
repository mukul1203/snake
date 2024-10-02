#pragma once
#include "utils.hpp"
#include "snake_model.hpp"
#include "constants.hpp"
class game_model {
public:
    // current apple position
    game::utils::point apple{game::board_width/2, game::board_height/2};
    // total score so far since the first level
    int total_score{0};
    // current score in the current level
    int level_score{0};
    // current level
    int level{1};
    snake_model snake_modl{};
    // game state, currently only a boolean
    bool over{false};
};