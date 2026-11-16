#pragma once
#include <iostream>
#include "INotifier.h"

class EmailNotifier : public INotifier {
public:
    explicit EmailNotifier(std::ostream& out = std::cout) : out_(out) {}

    void notifyBookAdded(const Book&) override {
        out_ << "Sending email notification about the new book..." << std::endl;
    }

private:
    std::ostream& out_;
};
