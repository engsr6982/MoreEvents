#pragma once
#include "Macros.h"
#include "ll/api/event/Cancellable.h"
#include "ll/api/event/Event.h"
#include "mc/world/level/BlockPos.h"
#include "mc/world/level/BlockSource.h"


namespace more_events {


class ExplodeEvent final : public ll::event::Cancellable<ll::event::Event> {
protected:
    BlockSource& mRegion;
    Actor*       mSourceEntity;
    Vec3 const&  mPos;
    float&       mExplosionRadius;
    float&       mMaxResistance;
    bool&        mIsFire;
    bool&        mDestroyBlocks;
    bool&        mAllowUnderWater;

public:
    MORE_EVENTS_API constexpr explicit ExplodeEvent(
        BlockSource& region,
        Actor*       sourceEntity,
        Vec3 const&  pos,
        float&       explosionRadius,
        float&       maxResistance,
        bool&        isFire,
        bool&        destroyBlocks,
        bool&        allowUnderWater
    )
    : Cancellable(),
      mRegion(region),
      mSourceEntity(sourceEntity),
      mPos(pos),
      mExplosionRadius(explosionRadius),
      mMaxResistance(maxResistance),
      mIsFire(isFire),
      mDestroyBlocks(destroyBlocks),
      mAllowUnderWater(allowUnderWater) {}

    MORE_EVENTS_API BlockSource& getRegion() const;
    MORE_EVENTS_API Actor*       getSourceEntity() const;
    MORE_EVENTS_API Vec3 const&  getPos() const;
    MORE_EVENTS_API float&       getExplosionRadius() const;
    MORE_EVENTS_API float&       getMaxResistance() const;
    MORE_EVENTS_API bool&        getIsFire() const;
    MORE_EVENTS_API bool&        getDestroyBlocks() const;
    MORE_EVENTS_API bool&        getAllowUnderWater() const;
};


} // namespace more_events