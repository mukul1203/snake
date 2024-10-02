#pragma once
#include "model/game_model.hpp"
#include "actions.hpp"
#include "reducer.hpp"
#include <lager/event_loop/manual.hpp>
#include <lager/store.hpp>

namespace game {
    auto& get_store() {
        static auto store = lager::make_store<game::action>(
        game_model{}, lager::with_manual_event_loop{});
        return store;
    }
}