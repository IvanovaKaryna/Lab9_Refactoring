
#include <sstream>
#include <string>
#include <vector>

#include "mini_test.h"

#include "DatabaseBookRepository.h"
#include "EmailNotifier.h"
#include "InMemoryBookRepository.h"
#include "Library.h"
#include "SmsNotifier.h"

namespace {

class FakeRepository : public IBookRepository {
public:
    explicit FakeRepository(std::vector<std::string>& log) : log_(log) {}
    void save(const Book& book) override { log_.push_back("save:" + book.title()); }
private:
    std::vector<std::string>& log_;
};

class FakeNotifier : public INotifier {
public:
    explicit FakeNotifier(std::vector<std::string>& log) : log_(log) {}
    void notifyBookAdded(const Book& book) override { log_.push_back("notify:" + book.title()); }
private:
    std::vector<std::string>& log_;
};

} 

TEST(Book_ReturnsTitleAndAuthor) {
    Book book("Dune", "Frank Herbert");
    CHECK_EQ(std::string("Dune"), book.title());
    CHECK_EQ(std::string("Frank Herbert"), book.author());
}

TEST(Library_AddBook_StoresBook) {
    std::vector<std::string> log;
    FakeRepository repo(log);
    FakeNotifier notifier(log);
    Library library(repo, notifier);

    library.addBook(Book("Dune", "Frank Herbert"));

    CHECK_EQ(static_cast<size_t>(1), library.books().size());
    CHECK_EQ(std::string("Dune"), library.books()[0].title());
}

TEST(Library_AddBook_CallsRepositoryThenNotifier) {
    std::vector<std::string> log;
    FakeRepository repo(log);
    FakeNotifier notifier(log);
    Library library(repo, notifier);

    library.addBook(Book("Dune", "Frank Herbert"));

    CHECK_EQ(static_cast<size_t>(2), log.size());
    CHECK_EQ(std::string("save:Dune"), log[0]);
    CHECK_EQ(std::string("notify:Dune"), log[1]);
}

TEST(Library_AddTwoBooks_CallsDependenciesForEachBook) {
    std::vector<std::string> log;
    FakeRepository repo(log);
    FakeNotifier notifier(log);
    Library library(repo, notifier);

    library.addBook(Book("A", "x"));
    library.addBook(Book("B", "y"));

    std::vector<std::string> expected = {"save:A", "notify:A", "save:B", "notify:B"};
    CHECK_TRUE(expected == log);
}

TEST(BookPrinter_FormatsBookLikeOriginalCode) {
    std::ostringstream out;
    BookPrinter printer(out);
    printer.print(Book("Dune", "Frank Herbert"));
    CHECK_EQ(std::string("Title: Dune, Author: Frank Herbert\n"), out.str());
}

TEST(Library_DisplayBooks_PrintsAllBooksInOrder) {
    std::vector<std::string> log;
    FakeRepository repo(log);
    FakeNotifier notifier(log);
    Library library(repo, notifier);
    library.addBook(Book("A", "x"));
    library.addBook(Book("B", "y"));

    std::ostringstream out;
    library.displayBooks(BookPrinter(out));

    CHECK_EQ(std::string("Title: A, Author: x\nTitle: B, Author: y\n"), out.str());
}

TEST(Library_DefaultImplementations_ProduceOriginalOutput) {
    std::ostringstream out;
    DatabaseBookRepository repo(out);
    EmailNotifier notifier(out);
    Library library(repo, notifier);

    library.addBook(Book("The Catcher in the Rye", "J.D. Salinger"));

    CHECK_EQ(std::string("Saving book to database...\n"
                         "Sending email notification about the new book...\n"),
             out.str());
}

TEST(Library_SmsNotifier_CanReplaceEmailWithoutChangingLibrary) {
    std::ostringstream out;
    DatabaseBookRepository repo(out);
    SmsNotifier notifier(out);
    Library library(repo, notifier);

    library.addBook(Book("Dune", "Frank Herbert"));

    CHECK_EQ(std::string("Saving book to database...\n"
                         "Sending SMS notification about the new book...\n"),
             out.str());
}

TEST(Library_InMemoryRepository_CanReplaceDatabaseWithoutChangingLibrary) {
    std::ostringstream out;
    InMemoryBookRepository repo(out);
    EmailNotifier notifier(out);
    Library library(repo, notifier);

    library.addBook(Book("Dune", "Frank Herbert"));

    CHECK_EQ(static_cast<size_t>(1), repo.saved().size());
    CHECK_EQ(std::string("Dune"), repo.saved()[0].title());
}

int main() {
    return RUN_ALL_TESTS();
}
