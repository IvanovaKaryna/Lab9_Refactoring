
#include <iostream>
#include <vector>

#include "GildedRose.h"

int main() {
    std::vector<Item> items;
    items.push_back(Item("+5 Dexterity Vest", 10, 20));
    items.push_back(Item("Aged Brie", 2, 0));
    items.push_back(Item("Elixir of the Mongoose", 5, 7));
    items.push_back(Item("Sulfuras, Hand of Ragnaros", 0, 80));
    items.push_back(Item("Backstage passes to a TAFKAL80ETC concert", 15, 20));
    items.push_back(Item("Backstage passes to a TAFKAL80ETC concert", 5, 49));
    items.push_back(Item("Conjured Mana Cake", 3, 6));  

    GildedRose app(items);

    for (int day = 0; day <= 5; ++day) {
        std::cout << "-------- day " << day << " --------" << std::endl;
        std::cout << "name, sellIn, quality" << std::endl;
        for (const auto& item : items) {
            std::cout << item.name << ", " << item.sellIn << ", "
                      << item.quality << std::endl;
        }
        std::cout << std::endl;
        app.updateQuality();
    }
    return 0;
}
