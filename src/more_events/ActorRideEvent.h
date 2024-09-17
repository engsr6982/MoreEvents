#pragma once
#include "Macros.h"
#include "ll/api/event/Cancellable.h"
#include "ll/api/event/Event.h"
#include "mc/world/actor/Actor.h"


namespace more_events {


class ActorRideEvent final : public ll::event::Cancellable<ll::event::Event> {
protected:
    Actor& mPassenger;
    Actor& mRided;

public:
    MORE_EVENTS_API constexpr explicit ActorRideEvent(Actor& passenger, Actor& rided)
    : Cancellable(),
      mPassenger(passenger),
      mRided(rided) {}

    MORE_EVENTS_API Actor& getPassenger() const;
    MORE_EVENTS_API Actor& getRided() const;
};


} // namespace more_events