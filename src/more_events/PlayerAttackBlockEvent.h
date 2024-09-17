#pragma once
#include "Macros.h"
#include "ll/api/event/Cancellable.h"
#include "ll/api/event/Event.h"
#include "mc/common/wrapper/optional_ref.h"
#include "mc/world/actor/player/Player.h"
#include "mc/world/level/BlockPos.h"


namespace more_events {


class PlayerAttackBlockEvent final : public ll::event::Cancellable<ll::event::Event> {
protected:
    BlockPos const&      mPos;
    optional_ref<Player> mPlayer;

public:
    MORE_EVENTS_API constexpr explicit PlayerAttackBlockEvent(BlockPos const& pos, optional_ref<Player> player)
    : Cancellable(),
      mPos(pos),
      mPlayer(player) {}

    MORE_EVENTS_API BlockPos const& getPos() const;
    MORE_EVENTS_API optional_ref<Player> getPlayer() const;
};


} // namespace more_events