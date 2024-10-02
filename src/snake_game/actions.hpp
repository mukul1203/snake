#pragma once
#include <variant>
#include "utils.hpp"

namespace game
{
    struct tick_action
    {
    };
    struct apple_eaten_action
    {
    };
    struct change_direction_action
    {
        game::utils::direction new_direction;
    };
    using action = std::variant<tick_action, apple_eaten_action, change_direction_action>;
}