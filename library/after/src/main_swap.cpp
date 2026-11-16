#include "InMemoryBookRepository.h"
#include "SmsNotifier.h"
#include "Library.h"

int main() {
    InMemoryBookRepository repository;   
    SmsNotifier notifier;                
    Library library(repository, notifier);
    BookPrinter printer;

    library.addBook(Book("The Catcher in the Rye", "J.D. Salinger"));
    library.addBook(Book("To Kill a Mockingbird", "Harper Lee"));
    library.displayBooks(printer);
    return 0;
}
