#pragma once
#include "Macros.h"
#include "ll/api/event/Cancellable.h"
#include "ll/api/event/Event.h"
#include "mc/world/level/BlockSource.h"


namespace more_events {


class PressurePlateTriggerEvent final : public ll::event::Cancellable<ll::event::Event> {
protected:
    BlockSource&    mRegion;
    BlockPos const& mPos;
    Actor&          mEntity;

public:
    MORE_EVENTS_API constexpr explicit PressurePlateTriggerEvent(
        BlockSource&    region,
        BlockPos const& pos,
        Actor&          entity
    )
    : Cancellable(),
      mRegion(region),
      mPos(pos),
      mEntity(entity) {}

    MORE_EVENTS_API BlockSource&    getRegion() const;
    MORE_EVENTS_API BlockPos const& getPos() const;
    MORE_EVENTS_API Actor&          getEntity() const;
};


} // namespace more_events