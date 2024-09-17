#pragma once
#include "Macros.h"
#include "ll/api/event/Cancellable.h"
#include "ll/api/event/Event.h"
#include "mc/world/actor/Actor.h"
#include "mc/world/level/BlockSource.h"


namespace more_events {


class MobHurtEffectEvent final : public ll::event::Cancellable<ll::event::Event> {
protected:
    ActorDamageSource const& mSource;
    Actor&                   mSelf;
    float&                   mDamage;

public:
    MORE_EVENTS_API constexpr explicit MobHurtEffectEvent(ActorDamageSource const& source, Actor& self, float& damage)
    : Cancellable(),
      mSource(source),
      mSelf(self),
      mDamage(damage) {}

    MORE_EVENTS_API ActorDamageSource const& getSource() const;
    MORE_EVENTS_API Actor&                   getSelf() const;
    MORE_EVENTS_API float&                   getDamage() const;
};


} // namespace more_events