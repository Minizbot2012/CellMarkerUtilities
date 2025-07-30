#pragma once
#include <Config.h>
namespace MPL::Hooks {
    namespace detail {
        void Reconfigure(RE::TESObjectREFR*, MPL::Config::RoomMarker, bool);
    }
    void Install();
}