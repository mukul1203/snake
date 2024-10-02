#pragma once
#include "model/game_model.hpp"
#include "actions.hpp"
#include <variant>
#include <lager/effect.hpp>
#include <lager/util.hpp>

namespace game
{
    using update_result = std::pair<game_model, lager::effect<action>>;
    inline update_result update(game_model c, action action)
    {
        return std::visit(lager::visitor{
                              [&](tick_action) -> update_result
                              {
                                  c.snake_modl.take_step();
                                  // check for danger
                                  if (c.snake_modl.breaks_boundary(board_width, board_height) || c.snake_modl.has_cycle())
                                  {
                                      c.over = true;
                                  }
                                  if (c.snake_modl.head() == c.apple)
                                      return {c, [](auto &&ctx)
                                              {
                                                  ctx.dispatch(apple_eaten_action{});
                                              }};
                                  return {c, lager::noop};
                              },
                              [&](apple_eaten_action) -> update_result
                              {
                                  c.level_score += apple_score;
                                  c.total_score += apple_score;
                                  c.snake_modl.eat_apple(c.apple);
                                  // Update apple position
                                  c.apple = {rand() % board_width, rand() % board_height};
                                  if (c.level_score == level_up_score)
                                  {
                                      c.level++;
                                      c.level_score = 0;
                                      c.snake_modl = {};
                                  }
                                  return {c, lager::noop};
                              },
                              [&](change_direction_action a) -> update_result
                              {
                                  c.snake_modl.set_direction(a.new_direction);
                                  // We want to move faster if user presses the key in the existing direction of snake.
                                  //  if(a.new_direction == c.snake_modl.get_direction())
                                  //      c.snake_modl.take_step();
                                  return {c, lager::noop};
                              },
                          },
                          action);
    }
}