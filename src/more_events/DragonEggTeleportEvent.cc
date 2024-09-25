#include "DragonEggTeleportEvent.h"
#include "ll/api/event/Emitter.h"
#include "ll/api/event/EmitterBase.h"
#include "ll/api/event/EventBus.h"
#include "ll/api/memory/Hook.h"
#include "mc/world/level/BlockPos.h"
#include "mc/world/level/BlockSource.h"
#include "mc/world/level/block/DragonEggBlock.h"


namespace more_events {

BlockSource&    DragonEggTeleportEvent::getBlockSource() const { return mBlockSource; }
Random&         DragonEggTeleportEvent::getRandom() const { return mRandom; }
BlockPos const& DragonEggTeleportEvent::getPos() const { return mPos; }


LL_TYPE_STATIC_HOOK(
    DragonEggTeleportEventHook,
    ll::memory::HookPriority::Normal,
    DragonEggBlock,
    &DragonEggBlock::_attemptTeleport,
    void,
    BlockSource&    region,
    Random&         random,
    BlockPos const& pos
) {
    DragonEggTeleportEvent ev(region, random, pos);
    ll::event::EventBus::getInstance().publish(ev);
    if (ev.isCancelled()) return;

    origin(region, random, pos);
}


static std::unique_ptr<ll::event::EmitterBase> emitterFactory(ll::event::ListenerBase&);
class EventEmitter : public ll::event::Emitter<emitterFactory, DragonEggTeleportEvent> {
    ll::memory::HookRegistrar<DragonEggTeleportEventHook> hook;
};
static std::unique_ptr<ll::event::EmitterBase> emitterFactory(ll::event::ListenerBase&) {
    return std::make_unique<EventEmitter>();
}


} // namespace more_events