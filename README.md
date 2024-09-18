# MoreEvents

This repository is designed to provide more events for the LeviLamina plug-in, and you can also understand it as a wrapper library.

The portion of this repository code is taken from the following items:

- LegacyScriptEngine

## Install

```bash
lip install github.com/engsr6982/MoreEvents
```

## Usage

- xmake.lua

```lua
add_repositories("engsr6982-repo https://github.com/engsr6982/xmake-repo.git")

add_requires("more_events 0.1.0")

package("xxx")
    -- ...
    add_packages("more_events")

```

- code.cpp

```cpp
#include "ArmorStandSwapItemEvent.h"

ll::event::ListenerPtr mArmorStandSwapItemEvent;

void setup() {
    mArmorStandSwapItemEvent =
        ll::event::EventBus::getInstance().emplaceListener<more_events::ArmorStandSwapItemEvent>([](more_events::ArmorStandSwapItemEvent& ev) {
            // do something
            return true;
        });
}
```
