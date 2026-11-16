#pragma once
#include "Item.h"

class IItemUpdater {
public:
    virtual ~IItemUpdater() = default;
    virtual void update(Item& item) const = 0;
};
