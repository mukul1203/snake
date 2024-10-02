#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/component/loop.hpp" 

#include "snake_game/ui/game_component.hpp"
#include "snake_game/store.hpp"
#include <lager/watch.hpp>

// Store should be immutable, should consist of the total game state, including everything (ui state and app state)
// A store change can only be affected by dispatching an action, not otherwise. The available actions are defined before creating the store.
// How each action should modify the store is defined by a reducer. It returns the modified store. A reducer may also need to dispatch actions (verify the need).
// Any change in store can be observed by the watch listener. The new state comes in.
// In response to the new store state, the listener can trigger UI update. This means trigger Render on the root component, which will travel down the whole component
// tree to create an element tree with finalized layout (by computation of layout). This element tree then is rendered on given screen.
// The UI consists of a tree of components composed together. Each component defines its Render method which essentially returns an Element. Each component
// is also capable of handling events and modifying local or global state as a result.
// The component can have its own local state, and it can also depend on global state for state based rendering logic or event handling. How is local state defined?
// How is global state accessed within the component?
// Selectors are functions having access to store, and they return portions of the store state. Components should use selectors to access the needed store state.
// Local state should just be members of the component class being defined.

void run_snake_game() {
    auto screen = ftxui::ScreenInteractive::FitComponent();

    watch(game::get_store(), [&](auto model){
      // Trigger rendering by posting a custom dummy event. Loop object handles events once per loop and renders only if there was an event.
      screen.PostEvent(ftxui::Event::Custom);
    });

    ftxui::Loop loop(&screen, game::board());
 
    while (!loop.HasQuitted()) {
      if(game::get_store().get().over)
        break;
      game::get_store().dispatch(game::tick_action{});
      loop.RunOnce();
      std::this_thread::sleep_for(std::chrono::milliseconds(game::interval));
    }
}

int main(void) {
  run_snake_game();
  return EXIT_SUCCESS;
}