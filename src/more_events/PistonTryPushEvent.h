#pragma once
#include "Macros.h"
#include "ll/api/event/Cancellable.h"
#include "ll/api/event/Event.h"
#include "mc/world/level/BlockPos.h"
#include "mc/world/level/BlockSource.h"


namespace more_events {


class PistonTryPushEvent final : public ll::event::Cancellable<ll::event::Event> {
protected:
    BlockSource&    mRegion;
    BlockPos const& mPistonPos;
    BlockPos const& mPushPos;

public:
    MORE_EVENTS_API constexpr explicit PistonTryPushEvent(
        BlockSource&    region,
        BlockPos const& pistonPos,
        BlockPos const& pushPos
    )
    : Cancellable(),
      mRegion(region),
      mPistonPos(pistonPos),
      mPushPos(pushPos) {}

    MORE_EVENTS_API BlockSource&    getRegion() const;
    MORE_EVENTS_API BlockPos const& getPistonPos() const;
    MORE_EVENTS_API BlockPos const& getPushPos() const;
};


} // namespace more_events