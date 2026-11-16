#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include "IItemUpdater.h"

class ItemUpdaterRegistry {
public:
    ItemUpdaterRegistry();

    void add(const std::string& itemName, std::unique_ptr<IItemUpdater> updater);
    const IItemUpdater& find(const std::string& itemName) const;

private:
    std::unordered_map<std::string, std::unique_ptr<IItemUpdater>> updaters_;
    std::unique_ptr<IItemUpdater> defaultUpdater_;
};

ItemUpdaterRegistry makeDefaultRegistry();
