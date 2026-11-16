#include "DatabaseBookRepository.h"
#include "EmailNotifier.h"
#include "Library.h"

int main() {
    DatabaseBookRepository repository;
    EmailNotifier notifier;
    Library library(repository, notifier);
    BookPrinter printer;

    Book book1("The Catcher in the Rye", "J.D. Salinger");
    Book book2("To Kill a Mockingbird", "Harper Lee");

    library.addBook(book1);
    library.addBook(book2);
    library.displayBooks(printer);
    return 0;
}
