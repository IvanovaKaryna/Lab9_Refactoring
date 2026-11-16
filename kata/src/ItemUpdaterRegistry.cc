#include "ItemUpdaterRegistry.h"
#include "ItemNames.h"
#include "ItemUpdaters.h"

ItemUpdaterRegistry::ItemUpdaterRegistry()
    : defaultUpdater_(std::make_unique<NormalItemUpdater>()) {}

void ItemUpdaterRegistry::add(const std::string& itemName,
                              std::unique_ptr<IItemUpdater> updater) {
    updaters_[itemName] = std::move(updater);
}

const IItemUpdater& ItemUpdaterRegistry::find(const std::string& itemName) const {
    auto it = updaters_.find(itemName);
    return it != updaters_.end() ? *it->second : *defaultUpdater_;
}

ItemUpdaterRegistry makeDefaultRegistry() {
    ItemUpdaterRegistry registry;
    registry.add(ItemNames::AgedBrie,  std::make_unique<AgedBrieUpdater>());
    registry.add(ItemNames::Backstage, std::make_unique<BackstagePassUpdater>());
    registry.add(ItemNames::Sulfuras,  std::make_unique<SulfurasUpdater>());
    registry.add(ItemNames::Conjured,  std::make_unique<ConjuredItemUpdater>()); // розширення
    return registry;
}
