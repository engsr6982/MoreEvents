#pragma once
#include "Macros.h"
#include "ll/api/event/Cancellable.h"
#include "ll/api/event/Event.h"
#include "mc/enums/FertilizerType.h"
#include "mc/world/level/BlockSource.h"


namespace more_events {


class MossSpreadEvent final : public ll::event::Cancellable<ll::event::Event> {
protected:
    BlockSource&     mRegion;
    BlockPos const&  mPos;
    Actor*           mActor;
    ::FertilizerType mFertilizer;

public:
    constexpr explicit MossSpreadEvent(
        BlockSource&     region,
        BlockPos const&  pos,
        Actor*           actor,
        ::FertilizerType fertilizer
    )
    : Cancellable(),
      mRegion(region),
      mPos(pos),
      mActor(actor),
      mFertilizer(fertilizer) {}

    MORE_EVENTS_API BlockSource&     getRegion() const;
    MORE_EVENTS_API BlockPos const&  getPos() const;
    MORE_EVENTS_API Actor*           getActor() const;
    MORE_EVENTS_API ::FertilizerType getFertilizer() const;
};


} // namespace more_events
