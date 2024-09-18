#pragma once
#include "Macros.h"
#include "ll/api/event/Cancellable.h"
#include "ll/api/event/Event.h"
#include "mc/world/actor/common/ClipDefaults.h"
#include "mc/world/level/BlockPos.h"
#include "mc/world/level/BlockSource.h"

namespace more_events {


class RedstoneUpdateEvent final : public ll::event::Cancellable<ll::event::Event> {
protected:
    BlockSource&    mBlockSource;
    BlockPos const& mPos;
    int const&      mStrength;
    bool            mISActive;

public:
    MORE_EVENTS_API constexpr explicit RedstoneUpdateEvent(
        BlockSource&    blockSource,
        BlockPos const& pos,
        int const&      strength,
        bool            isActive
    )
    : Cancellable(),
      mBlockSource(blockSource),
      mPos(pos),
      mStrength(strength),
      mISActive(isActive) {}

    MORE_EVENTS_API bool            isActive() const;
    MORE_EVENTS_API BlockSource&    getBlockSource() const;
    MORE_EVENTS_API BlockPos const& getPos() const;
    MORE_EVENTS_API int const&      getStrength() const;
};


} // namespace more_events