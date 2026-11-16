// Тести Kata Gilded Rose.
//  1) Тести вимог 1-7 виконуються і для початкової, і для рефакторованої версії.
//  2) Тести індивідуального розширення (Conjured) - лише для рефакторованої.
//  3) "Golden master": порівняння траєкторій старої та нової реалізацій.
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "mini_test.h"

#include "GildedRose.h"
#include "GildedRoseLegacy.h"
#include "ItemNames.h"
#include "ItemUpdater.h"

namespace {

const std::string kNormal   = "+5 Dexterity Vest";
const std::string kElixir   = "Elixir of the Mongoose";
const std::string kBrie     = ItemNames::AgedBrie;
const std::string kBackstage= ItemNames::Backstage;
const std::string kSulfuras = ItemNames::Sulfuras;
const std::string kConjured = ItemNames::Conjured;

// Виконує `days` днів для одного товару і повертає його стан.
template <class GR>
Item simulate(const std::string& name, int sellIn, int quality, int days = 1) {
    std::vector<Item> items{Item(name, sellIn, quality)};
    GR app(items);
    for (int d = 0; d < days; ++d) app.updateQuality();
    return items[0];
}

template <class GR>
void expectState(const std::string& name, int sellIn, int quality,
                 int expectedSellIn, int expectedQuality, int days = 1) {
    Item r = simulate<GR>(name, sellIn, quality, days);
    CHECK_EQ(expectedSellIn, r.sellIn);
    CHECK_EQ(expectedQuality, r.quality);
}

// ---- Тести функціональних вимог 1-7 ----
template <class GR>
void registerRequirementTests(const std::string& tag) {
    auto add = [&](const std::string& name, std::function<void()> fn) {
        mini::addCase(tag + " " + name, std::move(fn));
    };
    add("R1_Normal_QualityDecreasesBy1",            [] { expectState<GR>(kNormal, 10, 20, 9, 19); });
    add("R1_SellInDecreasesBy1_ForAgedBrie",        [] { expectState<GR>(kBrie, 10, 20, 9, 21); });
    add("R2_Normal_AtSellDate_DecreasesBy2",        [] { expectState<GR>(kNormal, 0, 10, -1, 8); });
    add("R2_Normal_AlreadyExpired_DecreasesBy2",    [] { expectState<GR>(kNormal, -1, 10, -2, 8); });
    add("R3_Normal_QualityNeverNegative",           [] { expectState<GR>(kNormal, 5, 0, 4, 0); });
    add("R3_Normal_Expired_QualityNeverNegative",   [] { expectState<GR>(kNormal, 0, 1, -1, 0); });
    add("R4_AgedBrie_QualityIncreases",             [] { expectState<GR>(kBrie, 2, 0, 1, 1); });
    add("R4_AgedBrie_AfterSellDate_IncreasesBy2",   [] { expectState<GR>(kBrie, 0, 10, -1, 12); });
    add("R5_AgedBrie_QualityNotAbove50",            [] { expectState<GR>(kBrie, 5, 50, 4, 50); });
    add("R5_AgedBrie_Expired_QualityNotAbove50",    [] { expectState<GR>(kBrie, 0, 49, -1, 50); });
    add("R6_Sulfuras_QualityStays80",               [] { expectState<GR>(kSulfuras, 0, 80, 0, 80); });
    add("R6_Sulfuras_NegativeSellInUnchanged",      [] { expectState<GR>(kSulfuras, -1, 80, -1, 80); });
    add("R7_Backstage_MoreThan10Days_Plus1",        [] { expectState<GR>(kBackstage, 15, 20, 14, 21); });
    add("R7_Backstage_10Days_Plus2",                [] { expectState<GR>(kBackstage, 10, 20, 9, 22); });
    add("R7_Backstage_6Days_Plus2",                 [] { expectState<GR>(kBackstage, 6, 20, 5, 22); });
    add("R7_Backstage_5Days_Plus3",                 [] { expectState<GR>(kBackstage, 5, 20, 4, 23); });
    add("R7_Backstage_1Day_Plus3",                  [] { expectState<GR>(kBackstage, 1, 20, 0, 23); });
    add("R7_Backstage_AfterConcert_QualityZero",    [] { expectState<GR>(kBackstage, 0, 20, -1, 0); });
    add("R5_Backstage_QualityNotAbove50",           [] { expectState<GR>(kBackstage, 5, 49, 4, 50); });
    add("Normal_TwelveDays",                        [] { expectState<GR>(kElixir, 10, 20, -2, 6, 12); });
    add("MultipleItems_AreUpdatedIndependently", [] {
        std::vector<Item> items{Item(kBrie, 2, 0), Item(kNormal, 10, 20)};
        GR app(items);
        app.updateQuality();
        CHECK_EQ(1, items[0].quality);
        CHECK_EQ(19, items[1].quality);
    });
}

// ---- Індивідуальне розширення: Conjured ----
class MysteryBoxUpdater : public ItemUpdater {   // тестовий НОВИЙ тип товару
protected:
    void updateQuality(Item& item) const override { item.quality = 7; }
    void updateExpiredQuality(Item&) const override {}
};

void registerExtensionTests() {
    using GR = GildedRose;
    mini::addCase("[extension] Conjured_QualityDecreasesBy2",
                  [] { expectState<GR>(kConjured, 10, 20, 9, 18); });
    mini::addCase("[extension] Conjured_AfterSellDate_DecreasesBy4",
                  [] { expectState<GR>(kConjured, 0, 20, -1, 16); });
    mini::addCase("[extension] Conjured_QualityNeverNegative",
                  [] { expectState<GR>(kConjured, 5, 1, 4, 0); });
    mini::addCase("[extension] Conjured_Expired_QualityNeverNegative",
                  [] { expectState<GR>(kConjured, 0, 3, -1, 0); });
    mini::addCase("[extension] Conjured_ZeroQualityStaysZero",
                  [] { expectState<GR>(kConjured, 5, 0, 4, 0); });
    mini::addCase("[extension] Conjured_SixDays",
                  [] { expectState<GR>(kConjured, 3, 30, -3, 12, 6); });
    mini::addCase("[extension] Legacy_TreatsConjuredAsNormal_NotSupported",
                  [] { expectState<GildedRoseLegacy>(kConjured, 10, 20, 9, 19); });
    mini::addCase("[extension] UnknownItemName_IsTreatedAsNormal",
                  [] { expectState<GR>("Unknown Thing", 5, 10, 4, 9); });
    mini::addCase("[extension] NewItemType_AddedViaRegistry_WithoutChangingGildedRose", [] {
        ItemUpdaterRegistry registry = makeDefaultRegistry();
        registry.add("Mystery Box", std::make_unique<MysteryBoxUpdater>());
        std::vector<Item> items{Item("Mystery Box", 3, 40), Item(kNormal, 3, 40)};
        GildedRose app(items, std::move(registry));
        app.updateQuality();
        CHECK_EQ(7, items[0].quality);
        CHECK_EQ(2, items[0].sellIn);
        CHECK_EQ(39, items[1].quality);   // інші типи не зачеплені
    });
}

// ---- Golden master: стара і нова реалізації мають збігатися день за днем ----
long long compareTrajectories(const std::vector<std::string>& names,
                              int sellInFrom, int sellInTo,
                              int qualityFrom, int qualityTo, int days) {
    long long scenarios = 0;
    for (const auto& name : names) {
        for (int s = sellInFrom; s <= sellInTo; ++s) {
            for (int q = qualityFrom; q <= qualityTo; ++q) {
                std::vector<Item> a{Item(name, s, q)};
                std::vector<Item> b{Item(name, s, q)};
                GildedRoseLegacy legacy(a);
                GildedRose refactored(b);
                for (int d = 1; d <= days; ++d) {
                    legacy.updateQuality();
                    refactored.updateQuality();
                    if (a[0].sellIn != b[0].sellIn || a[0].quality != b[0].quality) {
                        CHECK_TRUE(false);
                        std::cout << "      mismatch: " << name << " sellIn=" << s
                                  << " quality=" << q << " day=" << d << std::endl;
                        return scenarios;
                    }
                }
                ++scenarios;
            }
        }
    }
    return scenarios;
}

void registerGoldenMasterTests() {
    mini::addCase("[golden master] Legacy_And_Refactored_Match_ValidRange", [] {
        std::vector<std::string> names = {kNormal, kElixir, kBrie, kBackstage};
        long long n = compareTrajectories(names, -5, 20, 0, 50, 40);
        n += compareTrajectories({kSulfuras}, -5, 20, 80, 80, 40);
        std::cout << "         compared scenarios: " << n << " (each for 40 days)" << std::endl;
    });
    mini::addCase("[golden master] Legacy_And_Refactored_Match_OutOfRangeQuality", [] {
        std::vector<std::string> names = {kNormal, kElixir, kBrie, kBackstage, kSulfuras};
        long long n = compareTrajectories(names, -2, 12, -3, -1, 20);
        n += compareTrajectories(names, -2, 12, 51, 60, 20);
        std::cout << "         compared scenarios: " << n << " (each for 20 days)" << std::endl;
    });
}

} // namespace

int main() {
    registerRequirementTests<GildedRoseLegacy>("[legacy]    ");
    registerRequirementTests<GildedRose>("[refactored]");
    registerExtensionTests();
    registerGoldenMasterTests();
    return RUN_ALL_TESTS();
}
