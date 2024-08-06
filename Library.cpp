#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// Book class to represent a book in the library
class Book {
private:
    int id;
    string title;
    string author;
    bool isBorrowed;

public:
    Book(int id, string title, string author) : id(id), title(title), author(author), isBorrowed(false) {}

    int getId() {
        return id;
    }

    string getTitle() {
        return title;
    }

    bool getIsBorrowed() {
        return isBorrowed;
    }

    void borrowBook() {
        if (!isBorrowed) {
            isBorrowed = true;
            cout << "Book borrowed successfully!" << endl;
        } else {
            cout << "Book is already borrowed!" << endl;
        }
    }

    void returnBook() {
        if (isBorrowed) {
            isBorrowed = false;
            cout << "Book returned successfully!" << endl;
        } else {
            cout << "Book was not borrowed!" << endl;
        }
    }

    void displayInfo() {
        cout << "ID: " << id << ", Title: " << title << ", Author: " << author 
             << ", Status: " << (isBorrowed ? "Borrowed" : "Available") << endl;
    }
};

// Member class to represent a library member
class Member {
private:
    int id;
    string name;
    vector<int> borrowedBooks;

public:
    Member(int id, string name) : id(id), name(name) {}

    int getId() {
        return id;
    }

    void borrowBook(int bookId) {
        borrowedBooks.push_back(bookId);
    }

    void returnBook(int bookId) {
        borrowedBooks.erase(remove(borrowedBooks.begin(), borrowedBooks.end(), bookId), borrowedBooks.end());
    }

    void displayInfo() {
        cout << "ID: " << id << ", Name: " << name << ", Borrowed Books: ";
        for (int bookId : borrowedBooks) {
            cout << bookId << " ";
        }
        cout << endl;
    }
};

// Library class to manage books and members
class Library {
private:
    vector<Book> books;
    vector<Member> members;

public:
    void addBook(Book book) {
        books.push_back(book);
    }

    void addMember(Member member) {
        members.push_back(member);
    }

    void borrowBook(int memberId, int bookId) {
        auto bookIt = find_if(books.begin(), books.end(), [bookId](Book &book) { return book.getId() == bookId; });
        auto memberIt = find_if(members.begin(), members.end(), [memberId](Member &member) { return member.getId() == memberId; });

        if (bookIt != books.end() && memberIt != members.end()) {
            bookIt->borrowBook();
            memberIt->borrowBook(bookId);
        } else {
            cout << "Book or Member not found!" << endl;
        }
    }

    void returnBook(int memberId, int bookId) {
        auto bookIt = find_if(books.begin(), books.end(), [bookId](Book &book) { return book.getId() == bookId; });
        auto memberIt = find_if(members.begin(), members.end(), [memberId](Member &member) { return member.getId() == memberId; });

        if (bookIt != books.end() && memberIt != members.end()) {
            bookIt->returnBook();
            memberIt->returnBook(bookId);
        } else {
            cout << "Book or Member not found!" << endl;
        }
    }

    void displayAllBooks() {
        for (Book &book : books) {
            book.displayInfo();
        }
    }

    void displayAllMembers() {
        for (Member &member : members) {
            member.displayInfo();
        }
    }
};

// Main function to demonstrate the functionality of the Library Management System
int main() {
    Library library;

    // Add some books
    library.addBook(Book(1, "Harry Potter and the Philosopher's Stone", "J.K. Rowling"));
    library.addBook(Book(2, "Harry Potter and the Chamber of Secrets", "J.K. Rowling"));

    // Add some members
    library.addMember(Member(1, "Souvik"));
    library.addMember(Member(2, "Rahul"));

    // Display all books and members
    cout << "All Books:" << endl;
    library.displayAllBooks();
    cout << "All Members:" << endl;
    library.displayAllMembers();

    // Borrow and return books
    cout << "\nSouvik borrows Book 1:" << endl;
    library.borrowBook(1, 1);
    cout << "All Books:" << endl;
    library.displayAllBooks();
    cout << "All Members:" << endl;
    library.displayAllMembers();

    cout << "\nSouvik returns Book 1:" << endl;
    library.returnBook(1, 1);
    cout << "All Books:" << endl;
    library.displayAllBooks();
    cout << "All Members:" << endl;
    library.displayAllMembers();

    return 0;
}
