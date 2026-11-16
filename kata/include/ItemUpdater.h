#pragma once
#include "IItemUpdater.h"

class ItemUpdater : public IItemUpdater {
public:
    void update(Item& item) const final;

protected:
    static constexpr int MaxQuality = 50;

    static void increaseQuality(Item& item, int steps = 1);
    static void decreaseQuality(Item& item, int steps = 1);

    virtual void updateQuality(Item& item) const = 0;
    virtual void updateSellIn(Item& item) const;
    virtual void updateExpiredQuality(Item& item) const = 0;
};
