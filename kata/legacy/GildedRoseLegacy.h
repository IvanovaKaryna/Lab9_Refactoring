#pragma once
#include <vector>
#include "Item.h"
class GildedRoseLegacy {
public:
    std::vector<Item>& items;
    explicit GildedRoseLegacy(std::vector<Item>& items);
    void updateQuality();
};
