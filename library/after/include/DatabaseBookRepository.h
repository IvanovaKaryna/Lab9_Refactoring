#pragma once
#include <iostream>
#include "IBookRepository.h"

class DatabaseBookRepository : public IBookRepository {
public:
    explicit DatabaseBookRepository(std::ostream& out = std::cout) : out_(out) {}

    void save(const Book&) override {
        out_ << "Saving book to database..." << std::endl;
    }

private:
    std::ostream& out_;
};
