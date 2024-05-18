#include <iostream> 
#include <string> 
#include <vector> 
#include <fstream> 
 
using namespace std; 
 
// Book class to represent a book 
class Book { 
public: 
    string title; 
    string author; 
    int year; 
    double price; 
 
    Book(string title, string author, int year, double price) : title(title), 
author(author), year(year), price(price) {} 
}; 
 
// Bookshop class to manage books 
class Bookshop { 
private: 
    vector<Book> books; 
 
public: 
    // Add a book to the bookshop 
    void addBook(string title, string author, int year, double price) { 
        Book book(title, author, year, price); 
        books.push_back(book); 
    } 
 
    // Display all books in the bookshop 
    void displayBooks() { 
        cout << "Books in the Bookshop:" << endl; 
        for (const auto& book : books) { 
            cout << "Title: " << book.title << endl; 
            cout << "Author: " << book.author << endl; 
            cout << "Year: " << book.year << endl; 
            cout << "Price: $" << book.price << endl; 
            cout << "--------------------------" << endl; 
        } 
    } 
 
    // Search for a book by title 
    void searchBookByTitle(string title) { 
        cout << "Searching for book with title: " << title << endl; 
        bool found = false; 
        for (const auto& book : books) { 
            if (book.title == title) { 
                cout << "Book found:" << endl; 
                cout << "Title: " << book.title << endl; 
                cout << "Author: " << book.author << endl; 
                cout << "Year: " << book.year << endl; 
                cout << "Price: $" << book.price << endl; 
                cout << "--------------------------" << endl; 
                found = true; 
            } 
        } 
        if (!found) { 
            cout << "Book not found." << endl; 
        } 
    } 
 
    // Update book information 
    void updateBook(string title, string newAuthor, int newYear, double 
newPrice) { 
        for (auto& book : books) { 
            if (book.title == title) { 
                book.author = newAuthor; 
                book.year = newYear; 
                book.price = newPrice; 
                cout << "Book information updated successfully." << endl; 
                return; 
            } 
        } 
        cout << "Book not found. Update failed." << endl; 
    } 
 
    // Delete a book by title 
    void deleteBook(string title) { 
        for (auto it = books.begin(); it != books.end(); ++it) { 
            if (it->title == title) { 
                books.erase(it); 
                cout << "Book deleted successfully." << endl; 
                return; 
            } 
        } 
        cout << "Book not found. Deletion failed." << endl; 
    } 
 
    // Save the book data to a file 
    void saveToFile(string filename) { 
        ofstream outFile(filename); 
        for (const auto& book : books) { 
            outFile << book.title << "," << book.author << "," << book.year << 
"," << book.price << "\n"; 
        } 
        outFile.close(); 
        cout << "Book data saved to " << filename << endl; 
    } 
 
    // Load the book data from a file 
    void loadFromFile(string filename) { 
        ifstream inFile(filename); 
        if (!inFile) { 
            cout << "Error: Unable to open the file." << endl; 
            return; 
        } 
 
        books.clear(); 
        string line; 
        while (getline(inFile, line)) { 
            string title, author; 
            int year; 
            double price; 
 
            size_t pos1 = line.find(","); 
            size_t pos2 = line.find(",", pos1 + 1); 
            size_t pos3 = line.find(",", pos2 + 1); 
 
            title = line.substr(0, pos1); 
            author = line.substr(pos1 + 1, pos2 - pos1 - 1); 
            year = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1)); 
            price = stod(line.substr(pos3 + 1)); 
 
            Book book(title, author, year, price); 
            books.push_back(book); 
        } 
        inFile.close(); 
        cout << "Book data loaded from " << filename << endl; 
    } 
}; 
 
// Function to display menu and get user choice 
int getMenuChoice() { 
    int choice; 
    cout << "\nMenu:" << endl; 
    cout << "1. Add a book" << endl; 
    cout << "2. Display all books" << endl; 
    cout << "3. Search for a book" << endl; 
    cout << "4. Update book information" << endl; 
    cout << "5. Delete a book" << endl; 
    cout << "6. Save book data to file" << endl; 
    cout << "7. Load book data from file" << endl; 
    cout << "8. Exit" << endl; 
    cout << "Enter your choice (1-8): "; 
    cin >> choice; 
    return choice; 
} 
 
int main() { 
    Bookshop bookshop; 
 
    int choice; 
    string title, author; 
    int year; 
    double price; 
 
    do { 
        choice = getMenuChoice(); 
 
        switch (choice) { 
            case 1: 
                cout << "Enter book details:" << endl; 
                cout << "Title: "; 
                cin.ignore(); 
                getline(cin, title); 
                cout << "Author: "; 
                getline(cin, author); 
                cout << "Year: "; 
                cin >> year; 
                cout << "Price: $"; 
                cin >> price; 
                bookshop.addBook(title, author, year, price); 
                break; 
 
            case 2: 
                bookshop.displayBooks(); 
                break; 
 
            case 3: 
                cout << "Enter the title of the book to search: "; 
                cin.ignore(); 
                getline(cin, title); 
                bookshop.searchBookByTitle(title); 
                break; 
 
            case 4: 
                cout << "Enter the title of the book to update: "; 
                cin.ignore(); 
                getline(cin, title); 
                cout << "Enter new author: "; 
                getline(cin, author); 
                cout << "Enter new year: "; 
                cin >> year; 
                cout << "Enter new price: $"; 
                cin >> price; 
                bookshop.updateBook(title, author, year, price); 
                break; 
 
            case 5: 
                cout << "Enter the title of the book to delete: "; 
                cin.ignore(); 
                getline(cin, title); 
                bookshop.deleteBook(title); 
                break; 
 
            case 6: 
                bookshop.saveToFile("books.txt"); 
                break; 
 
            case 7: 
                bookshop.loadFromFile("books.txt"); 
                break; 
 
            case 8: 
                cout << "Exiting the application." << endl; 
                break; 
 
            default: 
                cout << "Invalid choice. Please try again." << endl; 
        } 
 
    } while (choice != 8); 
 
    return 0; 
}