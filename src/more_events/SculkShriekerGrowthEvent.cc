#include "SculkShriekerGrowthEvent.h"
#include "ll/api/event/Emitter.h"
#include "ll/api/event/EmitterBase.h"
#include "ll/api/event/EventBus.h"
#include "ll/api/memory/Hook.h"
#include "mc/world/level/BlockPos.h"
#include "mc/world/level/BlockSource.h"
#include "mc/world/level/IBlockWorldGenAPI.h"
#include "mc/world/level/block/utils/SculkBlockBehavior.h"


namespace more_events {


BlockSource*    SculkShriekerGrowthEvent::getBlockSource() const { return mBlockSource; }
BlockPos const& SculkShriekerGrowthEvent::getPos() const { return mPos; }

LL_STATIC_HOOK(
    SculkBlockGrowthHook,
    ll::memory::HookPriority::Normal,
    "?_placeGrowthAt@SculkBlockBehavior@@CAXAEAVIBlockWorldGenAPI@@PEAVBlockSource@@AEBVBlockPos@@AEAVRandom@@"
    "AEAVSculkSpreader@@@Z",
    void,
    IBlockWorldGenAPI& target,
    BlockSource*       region,
    BlockPos const&    pos,
    Random&            random,
    SculkSpreader&     a5
) {
    auto ev = SculkShriekerGrowthEvent(region, pos);
    ll::event::EventBus::getInstance().publish(ev);
    if (ev.isCancelled()) {
        return;
    }

    origin(target, region, pos, random, a5);
}


static std::unique_ptr<ll::event::EmitterBase> emitterFactory(ll::event::ListenerBase&);
class EventEmitter : public ll::event::Emitter<emitterFactory, SculkShriekerGrowthEvent> {
    ll::memory::HookRegistrar<SculkBlockGrowthHook> hook;
};
static std::unique_ptr<ll::event::EmitterBase> emitterFactory(ll::event::ListenerBase&) {
    return std::make_unique<EventEmitter>();
}


} // namespace more_events