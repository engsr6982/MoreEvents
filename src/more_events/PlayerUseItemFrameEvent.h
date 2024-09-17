#pragma once
#include "Macros.h"
#include "ll/api/event/Cancellable.h"
#include "ll/api/event/Event.h"
#include "mc/world/actor/player/Player.h"
#include "mc/world/level/BlockPos.h"
#include "mc/world/level/BlockSource.h"


namespace more_events {


class PlayerUseItemFrameEvent final : public ll::event::Cancellable<ll::event::Event> {
protected:
    BlockPos const& mPos;
    Player*         mPlayer;


public:
    MORE_EVENTS_API constexpr explicit PlayerUseItemFrameEvent(Player* player, BlockPos const& pos)
    : Cancellable(),
      mPos(pos),
      mPlayer(player) {}

    MORE_EVENTS_API BlockPos const& getPos() const;
    MORE_EVENTS_API Player*         getPlayer() const;
};


} // namespace more_events