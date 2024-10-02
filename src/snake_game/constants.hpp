#pragma once
#include <cstdint>
#include <chrono>

namespace game {
    const std::uint32_t board_width = 100, board_height = 100;
    //snake movement interval
    const std::chrono::milliseconds interval{100};
    const std::uint32_t apple_score{1};
    const std::uint32_t level_up_score{20};
}