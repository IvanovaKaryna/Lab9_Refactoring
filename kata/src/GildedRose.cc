#include "GildedRose.h"

GildedRose::GildedRose(std::vector<Item>& items)
    : items(items), registry_(makeDefaultRegistry()) {}

GildedRose::GildedRose(std::vector<Item>& items, ItemUpdaterRegistry registry)
    : items(items), registry_(std::move(registry)) {}

void GildedRose::updateQuality() {
    for (auto& item : items) {
        registry_.find(item.name).update(item);
    }
}
