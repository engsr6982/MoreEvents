#pragma once
#include "Macros.h"
#include "ll/api/event/Cancellable.h"
#include "ll/api/event/Event.h"
#include "mc/world/actor/Actor.h"
#include "mc/world/level/BlockSource.h"
#include "mc/world/level/Level.h"
#include "mc/world/level/block/actor/SculkCatalystBlockActor.h"


namespace more_events {


class SculkCatalystAbsorbExperienceEvent final : public ll::event::Cancellable<ll::event::Event> {
protected:
    SculkCatalystBlockActor& mSculkCatalystBlockActor; // block actor(self)
    Level&                   mLevel;
    Actor&                   mDiedActor; // entity that died

public:
    MORE_EVENTS_API constexpr explicit SculkCatalystAbsorbExperienceEvent(
        SculkCatalystBlockActor& sculkCatalystBlockActor,
        Level&                   level,
        Actor&                   actor
    )
    : Cancellable(),
      mSculkCatalystBlockActor(sculkCatalystBlockActor),
      mLevel(level),
      mDiedActor(actor) {}

    MORE_EVENTS_API SculkCatalystBlockActor& getSculkCatalystBlockActor() const;
    MORE_EVENTS_API Level&                   getLevel() const;
    MORE_EVENTS_API Actor&                   getDiedActor() const;
};


} // namespace more_events
