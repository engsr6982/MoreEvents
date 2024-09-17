#pragma once
#include "Macros.h"
#include "ll/api/event/Cancellable.h"
#include "ll/api/event/Event.h"
#include "mc/world/actor/Mob.h"
#include "mc/world/actor/player/Player.h"


namespace more_events {


class ArmorStandSwapItemEvent final : public ll::event::Cancellable<ll::event::Event> {
protected:
    Puv::Legacy::EquipmentSlot mSlot;
    Player&                    mPlayer;
    Mob&                       mArmorStand;

public:
    MORE_EVENTS_API constexpr explicit ArmorStandSwapItemEvent(
        Puv::Legacy::EquipmentSlot slot,
        Player&                    player,
        Mob&                       armorStand
    )
    : Cancellable(),
      mSlot(slot),
      mPlayer(player),
      mArmorStand(armorStand) {}

    MORE_EVENTS_API Puv::Legacy::EquipmentSlot getSlot() const;
    MORE_EVENTS_API Player&                    getPlayer() const;
    MORE_EVENTS_API Mob&                       getArmorStand() const;
};


} // namespace more_events