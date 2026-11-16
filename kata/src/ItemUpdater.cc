#include "ItemUpdater.h"

void ItemUpdater::update(Item& item) const {
    updateQuality(item);
    updateSellIn(item);
    if (item.sellIn < 0) {
        updateExpiredQuality(item);
    }
}

void ItemUpdater::updateSellIn(Item& item) const {
    --item.sellIn;
}

void ItemUpdater::increaseQuality(Item& item, int steps) {
    for (int i = 0; i < steps; ++i) {
        if (item.quality < MaxQuality) {
            ++item.quality;
        }
    }
}

void ItemUpdater::decreaseQuality(Item& item, int steps) {
    for (int i = 0; i < steps; ++i) {
        if (item.quality > 0) {
            --item.quality;
        }
    }
}
