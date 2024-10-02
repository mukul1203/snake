#pragma once
#include <utility>
#include <cassert>
namespace game::utils {
    using point = std::pair<int, int>;
    enum class direction {
        top=0,
        left,
        bottom,
        right
    };
    direction opposite(direction d) {
        switch (d)
        {
        case direction::top: return direction::bottom;
        case direction::left: return direction::right;
        case direction::bottom: return direction::top;
        case direction::right: return direction::left;
        default:
            assert(false);
        }
    }
}