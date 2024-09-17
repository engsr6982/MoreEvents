#pragma once
#include "Macros.h"
#include "ll/api/event/Cancellable.h"
#include "ll/api/event/Event.h"
#include "mc/world/actor/player/Player.h"
#include "mc/world/item/registry/ItemStack.h"

namespace more_events {


class PlayerDropItemEvent final : public ll::event::Cancellable<ll::event::Event> {
protected:
    Player&          mPlayer;
    ItemStack const& mItemStack;

public:
    MORE_EVENTS_API constexpr explicit PlayerDropItemEvent(Player& player, ItemStack const& itemStack)
    : Cancellable(),
      mPlayer(player),
      mItemStack(itemStack) {}

    MORE_EVENTS_API Player&          getPlayer() const;
    MORE_EVENTS_API ItemStack const& getItemStack() const;
};


} // namespace more_events