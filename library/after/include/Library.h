#pragma once
#include <vector>
#include "Book.h"
#include "BookPrinter.h"
#include "IBookRepository.h"
#include "INotifier.h"

class Library {
public:
    Library(IBookRepository& repository, INotifier& notifier);

    void addBook(const Book& book);
    void displayBooks(const BookPrinter& printer) const;
    const std::vector<Book>& books() const;

private:
    std::vector<Book> books_;
    IBookRepository& repository_;
    INotifier& notifier_;
};
