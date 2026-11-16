#pragma once
#include <iostream>
#include <vector>
#include "IBookRepository.h"

class InMemoryBookRepository : public IBookRepository {
public:
    explicit InMemoryBookRepository(std::ostream& out = std::cout) : out_(out) {}

    void save(const Book& book) override {
        saved_.push_back(book);
        out_ << "Saving book to memory (total: " << saved_.size() << ")..."
             << std::endl;
    }

    const std::vector<Book>& saved() const { return saved_; }

private:
    std::vector<Book> saved_;
    std::ostream& out_;
};
