#pragma once
#include "Macros.h"
#include "ll/api/event/Cancellable.h"
#include "ll/api/event/Event.h"
#include "mc/world/actor/Actor.h"
#include "mc/world/actor/boss/WitherBoss.h"
#include "mc/world/level/BlockPos.h"
#include "mc/world/level/BlockSource.h"


namespace more_events {


class WitherDestroyBlockEvent final : public ll::event::Cancellable<ll::event::Event> {
protected:
    Level&       mLevel;
    AABB const&  mAABB;
    BlockSource& mRegion;
    WitherBoss&  mWitherBoss;

public:
    MORE_EVENTS_API constexpr explicit WitherDestroyBlockEvent(
        Level&       level,
        AABB const&  aabb,
        BlockSource& region,
        WitherBoss&  witherBoss
    )
    : Cancellable(),
      mLevel(level),
      mAABB(aabb),
      mRegion(region),

      mWitherBoss(witherBoss) {}

    MORE_EVENTS_API Level&       getLevel() const;
    MORE_EVENTS_API AABB const&  getAABB() const;
    MORE_EVENTS_API BlockSource& getRegion() const;
    MORE_EVENTS_API WitherBoss&  getWitherBoss() const;
};


} // namespace more_events