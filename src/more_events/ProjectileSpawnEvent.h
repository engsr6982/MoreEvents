#pragma once
#include "Macros.h"
#include "ll/api/event/Cancellable.h"
#include "ll/api/event/Event.h"
#include "mc/world/actor/Actor.h"


namespace more_events {


class ProjectileSpawnEvent final : public ll::event::Cancellable<ll::event::Event> {
protected:
    Actor*             mSpawner;
    std::string const& mProjectileType;

public:
    constexpr explicit ProjectileSpawnEvent(Actor* spawner, std::string const& projectileType)
    : Cancellable(),
      mSpawner(spawner),
      mProjectileType(projectileType) {}

    Actor*             getSpawner() const;
    std::string const& getProjectileType() const;
};


} // namespace more_events