#pragma once
#include <cassert>
#include <immer/flex_vector.hpp>
#include "utils.hpp"

class snake_model {
public:
    game::utils::point head() {
        return points.front();
    }

    void eat_apple(game::utils::point apple) {
        //Snake head should be right at the apple to eat.
        assert(head() == apple);
        //Just push the apple on head. Eventually, this will come to the tail and extend snake.
        points = points.push_front(apple);
    }

    void take_step() {
        static const std::array<std::pair<int,int>, 4> deltas = {{{0, -1}, {-1, 0}, {0, 1}, {1, 0}}};
        auto [del_x, del_y] = deltas[int(dir)];
        auto [x, y] = head();
        game::utils::point next_head{x+del_x, y+del_y};
        //if direction happens to be just opposite of what it used to be, that is not possible
        if(points.size() > 1 && next_head == *(points.begin()+1)) {
            dir = game::utils::opposite(dir);
            return;
        }
        //Add a point to head based on direction of movement
        points = points.push_front(next_head);
        //Remove the last point
        points = points.erase(points.size()-1);
    }

    bool breaks_boundary(int width, int height) {
        auto [x, y] = head();
        return x < 0 || x >= width || y < 0 || y >= height;
    }

    bool has_cycle() {
        auto pts = points;
        return (std::find(pts.begin()+1, pts.end(), head()) != pts.end());
    }

    void for_each(std::function<void(const game::utils::point&)> f) {
        std::for_each(points.begin(), points.end(), [_f = std::move(f)](const auto& p) {
            _f(p);
        });
    }

    void set_direction(game::utils::direction d) {
        dir = d;
    }

private:
    // snake represented as a vector of points
    immer::flex_vector<game::utils::point> points{{0,0}};
    // current direction of motion of snake
    game::utils::direction dir{game::utils::direction::right};
};