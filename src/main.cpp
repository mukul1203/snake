#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/component/loop.hpp" 

#include "snake_game/game.hpp"
#include "snake_game/snake.hpp"
#include "snake_game/ui/game.hpp"

#include <lager/event_loop/manual.hpp>
#include <lager/store.hpp>

void run_snake_game() {
    watch(game::get_store(), [](auto model){
      game::g_instance = model;
    });
    auto screen = ftxui::ScreenInteractive::FitComponent();
    ftxui::Loop loop(&screen, game::get());
 
    while (!loop.HasQuitted()) {
      if(game::g_instance.over)
        break;
      screen.PostEvent(ftxui::Event::Custom);
      game::get_store().dispatch(game::tick_action{});
      loop.RunOnce();
      std::this_thread::sleep_for(std::chrono::milliseconds(game::interval));
    }
    // screen.Loop(game::get());
}

int main(void) {
  run_snake_game();
  return EXIT_SUCCESS;
}