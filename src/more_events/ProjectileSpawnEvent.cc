#include "ProjectileSpawnEvent.h"
#include "ll/api/event/Emitter.h"
#include "ll/api/event/EmitterBase.h"
#include "ll/api/event/EventBus.h"
#include "ll/api/memory/Hook.h"
#include "mc/world/actor/Actor.h"
#include "mc/world/actor/ActorDefinitionIdentifier.h"
#include "mc/world/actor/player/Player.h"
#include "mc/world/item/CrossbowItem.h"
#include "mc/world/item/ItemInstance.h"
#include "mc/world/item/TridentItem.h"
#include "mc/world/level/Spawner.h"
#include <mc/world/level/Level.h>
#include <mc/world/level/block/actor/PistonBlockActor.h>


namespace more_events {

Actor*             ProjectileSpawnEvent::getSpawner() const { return mSpawner; }
std::string const& ProjectileSpawnEvent::getProjectileType() const { return mProjectileType; }


LL_TYPE_INSTANCE_HOOK(
    ProjectileSpawnHook1,
    HookPriority::Normal,
    Spawner,
    &Spawner::spawnProjectile,
    Actor*,
    BlockSource&                     region,
    ActorDefinitionIdentifier const& id,
    Actor*                           spawner,
    Vec3 const&                      position,
    Vec3 const&                      direction
) {
    if (id._getLegacyActorType() != ActorType::Trident) {
        ProjectileSpawnEvent ev(spawner, id.getCanonicalName());
        ll::event::EventBus::getInstance().publish(ev);
        if (ev.isCancelled()) {
            return nullptr;
        }
    }
    return origin(region, id, spawner, position, direction);
}

LL_TYPE_INSTANCE_HOOK(
    ProjectileSpawnHook2,
    HookPriority::Normal,
    CrossbowItem,
    &CrossbowItem::_shootFirework,
    void,
    ItemInstance const& projectileInstance,
    Player&             player
) {
    ProjectileSpawnEvent ev(&player, projectileInstance.getTypeName());
    ll::event::EventBus::getInstance().publish(ev);
    if (ev.isCancelled()) {
        return;
    }
    origin(projectileInstance, player);
}

LL_TYPE_INSTANCE_HOOK(
    ProjectileSpawnHook3,
    HookPriority::Normal,
    TridentItem,
    "?releaseUsing@TridentItem@@UEBAXAEAVItemStack@@PEAVPlayer@@H@Z",
    void,
    ItemStack& item,
    Player*    player,
    int        durationLeft
) {
    ProjectileSpawnEvent ev(player, item.getTypeName());
    ll::event::EventBus::getInstance().publish(ev);
    if (ev.isCancelled()) {
        return;
    }
    origin(item, player, durationLeft);
}


static std::unique_ptr<ll::event::EmitterBase> emitterFactory(ll::event::ListenerBase&);
class EventEmitter : public ll::event::Emitter<emitterFactory, ProjectileSpawnEvent> {
    ll::memory::HookRegistrar<ProjectileSpawnHook1, ProjectileSpawnHook2, ProjectileSpawnHook3> hook;
};
static std::unique_ptr<ll::event::EmitterBase> emitterFactory(ll::event::ListenerBase&) {
    return std::make_unique<EventEmitter>();
}


} // namespace more_events