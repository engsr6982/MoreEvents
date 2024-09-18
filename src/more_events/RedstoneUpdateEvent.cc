#include "RedstoneUpdateEvent.h"
#include "ll/api/event/Emitter.h"
#include "ll/api/event/EmitterBase.h"
#include "ll/api/event/EventBus.h"
#include "ll/api/memory/Hook.h"
#include <mc/world/level/Level.h>
#include <mc/world/level/block/ComparatorBlock.h>
#include <mc/world/level/block/DiodeBlock.h>
#include <mc/world/level/block/RedStoneWireBlock.h>
#include <mc/world/level/block/RedstoneTorchBlock.h>
#include <mc/world/level/block/actor/PistonBlockActor.h>


namespace more_events {


bool            RedstoneUpdateEvent::isActive() const { return mISActive; }
BlockSource&    RedstoneUpdateEvent::getBlockSource() const { return mBlockSource; }
BlockPos const& RedstoneUpdateEvent::getPos() const { return mPos; }
int const&      RedstoneUpdateEvent::getStrength() const { return mStrength; }


#define RedstoneUpdateHookMacro(NAME, TYPE, SYMBOL)                                                                    \
    LL_TYPE_INSTANCE_HOOK(                                                                                             \
        NAME,                                                                                                          \
        HookPriority::Normal,                                                                                          \
        TYPE,                                                                                                          \
        SYMBOL,                                                                                                        \
        void,                                                                                                          \
        BlockSource&    region,                                                                                        \
        BlockPos const& pos,                                                                                           \
        int             strength,                                                                                      \
        bool            isFirstTime                                                                                    \
    ) {                                                                                                                \
        RedstoneUpdateEvent ev(region, pos, strength, isFirstTime);                                                    \
        ll::event::EventBus::getInstance().publish(ev);                                                                \
        if (ev.isCancelled()) {                                                                                        \
            return;                                                                                                    \
        }                                                                                                              \
        origin(region, pos, strength, isFirstTime);                                                                    \
    }

RedstoneUpdateHookMacro(
    RedstoneUpdateHook1,
    RedStoneWireBlock,
    "?onRedstoneUpdate@RedStoneWireBlock@@UEBAXAEAVBlockSource@@AEBVBlockPos@@H_N@Z"
);

RedstoneUpdateHookMacro(
    RedstoneUpdateHook2,
    DiodeBlock,
    "?onRedstoneUpdate@DiodeBlock@@UEBAXAEAVBlockSource@@AEBVBlockPos@@H_N@Z"
);

RedstoneUpdateHookMacro(
    RedstoneUpdateHook3,
    RedstoneTorchBlock,
    "?onRedstoneUpdate@RedstoneTorchBlock@@UEBAXAEAVBlockSource@@AEBVBlockPos@@H_N@Z"
);

RedstoneUpdateHookMacro(
    RedstoneUpdateHook4,
    ComparatorBlock,
    "?onRedstoneUpdate@ComparatorBlock@@UEBAXAEAVBlockSource@@AEBVBlockPos@@H_N@Z"
);


static std::unique_ptr<ll::event::EmitterBase> emitterFactory(ll::event::ListenerBase&);
class EventEmitter : public ll::event::Emitter<emitterFactory, RedstoneUpdateEvent> {
    ll::memory::HookRegistrar<RedstoneUpdateHook1, RedstoneUpdateHook2, RedstoneUpdateHook3, RedstoneUpdateHook4> hook;
};
static std::unique_ptr<ll::event::EmitterBase> emitterFactory(ll::event::ListenerBase&) {
    return std::make_unique<EventEmitter>();
}


} // namespace more_events