#pragma once
#include <vector>
#include "Item.h"
#include "ItemUpdaterRegistry.h"

class GildedRose {
public:
    std::vector<Item>& items;

    explicit GildedRose(std::vector<Item>& items);
    GildedRose(std::vector<Item>& items, ItemUpdaterRegistry registry);

    void updateQuality();

private:
    ItemUpdaterRegistry registry_;
};
