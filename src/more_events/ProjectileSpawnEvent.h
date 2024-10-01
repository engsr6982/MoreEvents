#pragma once
#include "Macros.h"
#include "ll/api/event/Cancellable.h"
#include "ll/api/event/Event.h"
#include "mc/world/actor/Actor.h"


namespace more_events {


class ProjectileSpawnEvent final : public ll::event::Cancellable<ll::event::Event> {
protected:
    Actor*            mSpawner;
    std::string const mProjectileType;

public:
    MORE_EVENTS_API constexpr explicit ProjectileSpawnEvent(Actor* spawner, std::string const projectileType)
    : Cancellable(),
      mSpawner(spawner),
      mProjectileType(projectileType) {}

    MORE_EVENTS_API Actor* getSpawner() const;
    MORE_EVENTS_API std::string const& getProjectileType() const;
};


} // namespace more_events