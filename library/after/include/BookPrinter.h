#pragma once
#include <iostream>
#include "Book.h"

class BookPrinter {
public:
    explicit BookPrinter(std::ostream& out = std::cout) : out_(out) {}

    void print(const Book& book) const {
        out_ << "Title: " << book.title()
             << ", Author: " << book.author() << std::endl;
    }

private:
    std::ostream& out_;
};
