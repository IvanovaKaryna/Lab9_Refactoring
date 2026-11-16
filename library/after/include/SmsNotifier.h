#pragma once
#include <iostream>
#include "INotifier.h"

class SmsNotifier : public INotifier {
public:
    explicit SmsNotifier(std::ostream& out = std::cout) : out_(out) {}

    void notifyBookAdded(const Book&) override {
        out_ << "Sending SMS notification about the new book..." << std::endl;
    }

private:
    std::ostream& out_;
};
