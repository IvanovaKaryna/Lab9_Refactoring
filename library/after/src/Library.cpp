#include "Library.h"

Library::Library(IBookRepository& repository, INotifier& notifier)
    : repository_(repository), notifier_(notifier) {}

void Library::addBook(const Book& book) {
    books_.push_back(book);
    repository_.save(book);
    notifier_.notifyBookAdded(book);
}

void Library::displayBooks(const BookPrinter& printer) const {
    for (const auto& book : books_) {
        printer.print(book);
    }
}

const std::vector<Book>& Library::books() const {
    return books_;
}
