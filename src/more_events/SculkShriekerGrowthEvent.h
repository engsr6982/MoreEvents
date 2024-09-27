#pragma once
#include "Macros.h"
#include "ll/api/event/Cancellable.h"
#include "ll/api/event/Event.h"
#include "mc/world/level/BlockPos.h"
#include "mc/world/level/BlockSource.h"


namespace more_events {


class SculkShriekerGrowthEvent final : public ll::event::Cancellable<ll::event::Event> {
protected:
    BlockSource*    mBlockSource;
    BlockPos const& mPos;

public:
    constexpr explicit SculkShriekerGrowthEvent(BlockSource* source, BlockPos const& pos)
    : Cancellable(),
      mBlockSource(source),
      mPos(pos) {}

    MORE_EVENTS_API BlockPos const& getPos() const;
    MORE_EVENTS_API BlockSource*    getBlockSource() const;
};


} // namespace more_events