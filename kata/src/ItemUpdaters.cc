#include "ItemUpdaters.h"

void NormalItemUpdater::updateQuality(Item& item) const {
    decreaseQuality(item);
}
void NormalItemUpdater::updateExpiredQuality(Item& item) const {
    decreaseQuality(item);
}

void AgedBrieUpdater::updateQuality(Item& item) const {
    increaseQuality(item);
}
void AgedBrieUpdater::updateExpiredQuality(Item& item) const {
    increaseQuality(item);
}

void BackstagePassUpdater::updateQuality(Item& item) const {
    int steps = 1;
    if (item.sellIn < 11) ++steps;
    if (item.sellIn < 6) ++steps;
    increaseQuality(item, steps);
}
void BackstagePassUpdater::updateExpiredQuality(Item& item) const {
    item.quality = 0;
}

void SulfurasUpdater::updateQuality(Item&) const {}
void SulfurasUpdater::updateSellIn(Item&) const {}
void SulfurasUpdater::updateExpiredQuality(Item&) const {}

void ConjuredItemUpdater::updateQuality(Item& item) const {
    decreaseQuality(item, 2);
}
void ConjuredItemUpdater::updateExpiredQuality(Item& item) const {
    decreaseQuality(item, 2);
}
