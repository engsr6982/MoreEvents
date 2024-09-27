#include "SculkCatalystAbsorbExperienceEvent.h"
#include "ll/api/event/Emitter.h"
#include "ll/api/event/EmitterBase.h"
#include "ll/api/event/EventBus.h"
#include "ll/api/memory/Hook.h"
#include "mc/world/level/BlockPos.h"
#include "mc/world/level/BlockSource.h"
#include "mc/world/level/block/actor/SculkCatalystBlockActor.h"


namespace more_events {


SculkCatalystBlockActor& SculkCatalystAbsorbExperienceEvent::getSculkCatalystBlockActor() const {
    return mSculkCatalystBlockActor;
}
Level& SculkCatalystAbsorbExperienceEvent::getLevel() const { return mLevel; }
Actor& SculkCatalystAbsorbExperienceEvent::getDiedActor() const { return mDiedActor; }


/* 
clang-format off

stacktrace:
    Actor::getOnDeathExperience();
    ...
    SculkCatalystBlockActor::_tryConsumeOnDeathExperience(class Level& level, class Actor& actor); // hooked
    ...
    SculkCatalystBlockActor::handleGameEvent(GameEvent const& gameEvent, GameEventContext const& gameEventContext, BlockSource& region);

Land
    getBlockStandingOn().getPosition() -> BlockPos
    getter: use this pos or +- 8 with AABB


clang-format on
 */


LL_TYPE_INSTANCE_HOOK(
    HandleEventHook,
    ll::memory::HookPriority::Normal,
    SculkCatalystBlockActor,
    "?_tryConsumeOnDeathExperience@SculkCatalystBlockActor@@AEAAXAEAVLevel@@AEAVActor@@@Z",
    void,
    Level& level,
    Actor& actor
) {
    SculkCatalystAbsorbExperienceEvent ev(*this, level, actor);
    ll::event::EventBus::getInstance().publish(ev);
    if (ev.isCancelled()) {
        return;
    }
    origin(level, actor);
}


static std::unique_ptr<ll::event::EmitterBase> emitterFactory(ll::event::ListenerBase&);
class EventEmitter : public ll::event::Emitter<emitterFactory, SculkCatalystAbsorbExperienceEvent> {
    ll::memory::HookRegistrar<HandleEventHook> hook;
};
static std::unique_ptr<ll::event::EmitterBase> emitterFactory(ll::event::ListenerBase&) {
    return std::make_unique<EventEmitter>();
}

} // namespace more_events