#pragma once
#include "model/game_model.hpp"
#include "actions.hpp"
#include "reducer.hpp"
#include <lager/event_loop/manual.hpp>
#include <lager/store.hpp>

namespace game {
    //Used in UI and updated by watch(store)
    game_model g_instance{};

    auto& get_store() {
        static auto store = lager::make_store<game::action>(
        game_model{}, lager::with_manual_event_loop{});
        return store;
    }
}