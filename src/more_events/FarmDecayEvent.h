#pragma once
#include "Macros.h"
#include "ll/api/event/Cancellable.h"
#include "ll/api/event/Event.h"
#include "mc/world/actor/Actor.h"
#include "mc/world/level/BlockPos.h"
#include "mc/world/level/BlockSource.h"


namespace more_events {


class FarmDecayEvent final : public ll::event::Cancellable<ll::event::Event> {
protected:
    Actor*          mActor;
    BlockSource&    mBlockSource;
    BlockPos const& mPos;


public:
    MORE_EVENTS_API constexpr explicit FarmDecayEvent(Actor* actor, BlockSource& blockSource, BlockPos const& pos)
    : Cancellable(),
      mActor(actor),
      mBlockSource(blockSource),
      mPos(pos) {}

    MORE_EVENTS_API Actor*          getActor() const;
    MORE_EVENTS_API BlockSource&    getBlockSource() const;
    MORE_EVENTS_API BlockPos const& getPos() const;
};


} // namespace more_events