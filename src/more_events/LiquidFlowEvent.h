#pragma once
#include "Macros.h"
#include "ll/api/event/Cancellable.h"
#include "ll/api/event/Event.h"
#include "mc/world/level/BlockPos.h"
#include "mc/world/level/BlockSource.h"


namespace more_events {


class LiquidFlowEvent final : public ll::event::Cancellable<ll::event::Event> {
protected:
    BlockSource&    mBlockSource;
    BlockPos const& mFlowFromPos; // liquid flow from block position
    BlockPos const& mLiquidPos;   // liquid block position == will flow to this position

public:
    MORE_EVENTS_API constexpr explicit LiquidFlowEvent(
        BlockSource&    blockSource,
        BlockPos const& flowFromPos,
        BlockPos const& liquidPos
    )
    : Cancellable(),
      mBlockSource(blockSource),
      mFlowFromPos(flowFromPos),
      mLiquidPos(liquidPos) {}

    MORE_EVENTS_API BlockSource&    getBlockSource() const;
    MORE_EVENTS_API BlockPos const& getFlowFromPos() const;
    MORE_EVENTS_API BlockPos const& getLiquidPos() const;
};


} // namespace more_events