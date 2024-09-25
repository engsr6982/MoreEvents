#pragma once
#include "Macros.h"
#include "ll/api/event/Cancellable.h"
#include "ll/api/event/Event.h"
#include "mc/world/level/BlockSource.h"


class Random;

namespace more_events {


class DragonEggTeleportEvent final : public ll::event::Cancellable<ll::event::Event> {
protected:
    BlockSource&    mBlockSource;
    Random&         mRandom;
    BlockPos const& mPos; // DragonEggBlock

public:
    MORE_EVENTS_API constexpr explicit DragonEggTeleportEvent(
        BlockSource&    blockSource,
        Random&         random,
        BlockPos const& pos
    )
    : Cancellable(),
      mBlockSource(blockSource),
      mRandom(random),
      mPos(pos) {}

    MORE_EVENTS_API BlockSource&    getBlockSource() const;
    MORE_EVENTS_API Random&         getRandom() const;
    MORE_EVENTS_API BlockPos const& getPos() const;
};


} // namespace more_events