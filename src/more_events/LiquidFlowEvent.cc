#include "LiquidFlowEvent.h"
#include "ll/api/event/Emitter.h"
#include "ll/api/event/EmitterBase.h"
#include "ll/api/event/EventBus.h"
#include "ll/api/memory/Hook.h"
#include "mc/world/level/BlockPos.h"
#include "mc/world/level/BlockSource.h"
#include "mc/world/level/block/LiquidBlockDynamic.h"


namespace more_events {

BlockSource&    LiquidFlowEvent::getBlockSource() const { return mBlockSource; }
BlockPos const& LiquidFlowEvent::getFlowFromPos() const { return mFlowFromPos; }
BlockPos const& LiquidFlowEvent::getLiquidPos() const { return mLiquidPos; }


LL_TYPE_INSTANCE_HOOK(
    LiquidFlowHook,
    HookPriority::Normal,
    LiquidBlockDynamic,
    &LiquidBlockDynamic::_canSpreadTo,
    bool,
    BlockSource&    region,
    BlockPos const& pos,
    BlockPos const& flowFromPos,
    uchar           flowFromDirection
) {
    LiquidFlowEvent ev(region, flowFromPos, pos);
    ll::event::EventBus::getInstance().publish(ev);
    if (ev.isCancelled()) {
        return false;
    }
    return origin(region, pos, flowFromPos, flowFromDirection);
}


static std::unique_ptr<ll::event::EmitterBase> emitterFactory(ll::event::ListenerBase&);
class EventEmitter : public ll::event::Emitter<emitterFactory, LiquidFlowEvent> {
    ll::memory::HookRegistrar<LiquidFlowHook> hook;
};
static std::unique_ptr<ll::event::EmitterBase> emitterFactory(ll::event::ListenerBase&) {
    return std::make_unique<EventEmitter>();
}


} // namespace more_events