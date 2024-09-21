#include "MossFertilizerEvent.h"
#include "ll/api/event/Emitter.h"
#include "ll/api/event/EmitterBase.h"
#include "ll/api/event/EventBus.h"
#include "ll/api/memory/Hook.h"
#include "mc/world/level/BlockPos.h"
#include "mc/world/level/BlockSource.h"
#include "mc/world/level/block/MossBlock.h"


namespace more_events {


BlockSource&     MossFertilizerEvent::getRegion() const { return mRegion; }
BlockPos const&  MossFertilizerEvent::getPos() const { return mPos; }
Actor*           MossFertilizerEvent::getActor() const { return mActor; }
::FertilizerType MossFertilizerEvent::getFertilizer() const { return mFertilizer; }


LL_TYPE_INSTANCE_HOOK(
    MossFertilizerEventHook,
    ll::memory::HookPriority::Normal,
    MossBlock,
    "?onFertilized@MossBlock@@UEBA_NAEAVBlockSource@@AEBVBlockPos@@PEAVActor@@W4FertilizerType@@@Z",
    bool,
    BlockSource&     region,
    BlockPos const&  pos,
    Actor*           actor,
    ::FertilizerType fertilizer
) {
    MossFertilizerEvent ev(region, pos, actor, fertilizer);
    ll::event::EventBus::getInstance().publish(ev);
    if (ev.isCancelled()) {
        return false;
    }
    return origin(region, pos, actor, fertilizer);
}


static std::unique_ptr<ll::event::EmitterBase> emitterFactory(ll::event::ListenerBase&);
class EventEmitter : public ll::event::Emitter<emitterFactory, MossFertilizerEvent> {
    ll::memory::HookRegistrar<MossFertilizerEventHook> hook;
};
static std::unique_ptr<ll::event::EmitterBase> emitterFactory(ll::event::ListenerBase&) {
    return std::make_unique<EventEmitter>();
}


} // namespace more_events