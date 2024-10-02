#pragma once
#include "ftxui/component/component.hpp"  // for Renderer, CatchEvent, Horizontal, Menu, Tab
#include "ftxui/dom/canvas.hpp"           // for Canvas
#include "model/game_model.hpp"
#include "store.hpp"

namespace game {
struct instance {
    //Render
    auto operator()() {
        const auto& model = game::get_store().get();
        int canvas_w = game::board_width, canvas_h = game::board_height;
        auto c = ftxui::Canvas(canvas_w, canvas_h);
        // Draw apple
        c.DrawBlock(model.apple.first, model.apple.second, true, ftxui::Color::Palette16::Red);
        // Draw snake
        model.snake_modl.for_each([&](const auto& point) {
            const auto& [x, y] = point;
            c.DrawBlock(x, y, true, ftxui::Color::Palette16::Blue);
        });
        return canvas(std::move(c)) | ftxui::border;
    }
};

//Return component and its state pointer
auto get() {
return ftxui::Renderer(instance{}) | ftxui::CatchEvent([](ftxui::Event event) {
    auto& store = game::get_store();
    if(event == ftxui::Event::ArrowLeft)
        store.dispatch(game::change_direction_action{game::utils::direction::left});
    else if(event == ftxui::Event::ArrowUp)
        store.dispatch(game::change_direction_action{game::utils::direction::top});
    else if(event == ftxui::Event::ArrowRight)
        store.dispatch(game::change_direction_action{game::utils::direction::right});
    else if(event == ftxui::Event::ArrowDown)
        store.dispatch(game::change_direction_action{game::utils::direction::bottom});
    return true;
});
}

}