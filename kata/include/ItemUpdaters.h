#pragma once
#include "ItemUpdater.h"

class NormalItemUpdater : public ItemUpdater {
protected:
    void updateQuality(Item& item) const override;
    void updateExpiredQuality(Item& item) const override;
};

class AgedBrieUpdater : public ItemUpdater {
protected:
    void updateQuality(Item& item) const override;
    void updateExpiredQuality(Item& item) const override;
};

class BackstagePassUpdater : public ItemUpdater {
protected:
    void updateQuality(Item& item) const override;
    void updateExpiredQuality(Item& item) const override;
};

class SulfurasUpdater : public ItemUpdater {
protected:
    void updateQuality(Item& item) const override;
    void updateSellIn(Item& item) const override;
    void updateExpiredQuality(Item& item) const override;
};

class ConjuredItemUpdater : public ItemUpdater {
protected:
    void updateQuality(Item& item) const override;
    void updateExpiredQuality(Item& item) const override;
};
