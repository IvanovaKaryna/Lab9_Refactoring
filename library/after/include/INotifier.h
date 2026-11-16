#pragma once
#include "Book.h"

class INotifier {
public:
    virtual ~INotifier() = default;
    virtual void notifyBookAdded(const Book& book) = 0;
};
