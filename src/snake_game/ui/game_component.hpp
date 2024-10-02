#pragma once
#include "ftxui/component/component.hpp" // for Renderer, CatchEvent, Horizontal, Menu, Tab
#include "ftxui/dom/canvas.hpp"          // for Canvas
#include "ftxui/dom/elements.hpp"
#include "model/game_model.hpp"
#include "store.hpp"

namespace game
{
    auto render = []()
    {
        const auto &model = game::get_store().get();
        auto c = ftxui::Canvas(game::board_width, game::board_height);
        // Draw apple
        c.DrawBlock(model.apple.first, model.apple.second, true, game::apple_color);
        // Draw snake
        model.snake_modl.for_each([&](const auto &point)
                                  {
            const auto &[x, y] = point;
            c.DrawBlock(x, y, true, game::snake_color); });
        return ftxui::vbox({ftxui::hbox({
                                ftxui::text(std::string("Level - ") + std::to_string(model.level)) | ftxui::border,
                                ftxui::text(std::string("Score - ") + std::to_string(model.level_score)) | ftxui::border,
                                ftxui::text(std::string("Total Score - ") + std::to_string(model.total_score)) | ftxui::border,
                            }),
                            ftxui::canvas(std::move(c)) | ftxui::border});
    };

    auto event_handler = [](ftxui::Event event)
    {
        auto &store = game::get_store();
        if (event == ftxui::Event::ArrowLeft)
            store.dispatch(game::change_direction_action{game::utils::direction::left});
        else if (event == ftxui::Event::ArrowUp)
            store.dispatch(game::change_direction_action{game::utils::direction::top});
        else if (event == ftxui::Event::ArrowRight)
            store.dispatch(game::change_direction_action{game::utils::direction::right});
        else if (event == ftxui::Event::ArrowDown)
            store.dispatch(game::change_direction_action{game::utils::direction::bottom});
        return true;
    };

    // returns a board component, which renders using given render method and handles events using given event handler method.
    auto board()
    {
        return ftxui::Renderer(render) |
               ftxui::CatchEvent(event_handler);
    }
}