
// library_management_system.cpp
// A C++ project demonstrating:
// - C++ Inheritance
// - C++ Polymorphism
// - C++ Templates (implicitly via std::vector, and conceptually for Library)
// - C++ Friend Functions
// - C++ Files (for data persistence)
// - C++ Date (custom class for dates)
// - C++ OOP, Classes/Objects, Class Methods, Constructors, Access Specifiers, Encapsulation

#include <iostream>   // For input/output operations (std::cout, std::cin)
#include <string>     // For string manipulation (std::string, std::getline)
#include <vector>     // For dynamic arrays (std::vector)
#include <fstream>    // For file input/output (std::ifstream, std::ofstream)
#include <limits>     // For std::numeric_limits (used in input validation)
#include <sstream>    // For std::stringstream (used in file parsing)
#include <algorithm>  // For std::find_if

// --- Helper Functions for Robust Input ---
// These functions ensure the user enters valid data types.

// Function to get a valid integer input from the user.
int getIntegerInput(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail()) { // Check if input operation failed (e.g., non-numeric input)
            std::cout << "Invalid input. Please enter a whole number." << std::endl;
            std::cin.clear(); // Clear the error flag on std::cin
            // Ignore the rest of the invalid line to prevent an infinite loop
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            // Clear the remaining buffer after successful input (e.g., newline character)
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

// Function to get a string input from the user, handling spaces.
std::string getStringInput(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value); // Use getline to read entire line, including spaces
    return value;
}

// --- C++ Date Class ---
// Represents a simple date (day, month, year).
class Date {
private:
    int day;
    int month;
    int year;

public:
    // Constructor
    Date(int d = 1, int m = 1, int y = 2000) : day(d), month(m), year(y) {
        // Basic validation in constructor
        if (!isValid()) {
            std::cout << "Warning: Invalid date provided. Setting to 1/1/2000." << std::endl;
            day = 1; month = 1; year = 2000;
        }
    }

    // Class Method: Check if the date is valid.
    bool isValid() const {
        if (month < 1 || month > 12 || day < 1 || day > 31) return false;
        // More robust date validation would be needed for a real system (e.g., days in month, leap year)
        return true;
    }

    // Class Method: Display the date.
    void display() const {
        std::cout << day << "/" << month << "/" << year;
    }

    // Getters for private members (useful for saving/loading)
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
};

// --- C++ LibraryItem Base Class ---
// Represents a generic item in the library.
class LibraryItem {
protected:
    // Protected members: Accessible by derived classes, but still private from outside.
    std::string title;
    std::string itemID;
    Date publicationDate; // Composition: LibraryItem has a Date object
    std::string type; // To help with file serialization/deserialization for polymorphism

private:
    // Private member: Not accessible by derived classes or outside.
    // This could be a unique internal tracking number, for example.
    int internalTrackingID;
    static int nextInternalID; // Static member to generate unique IDs

public:
    // Constructor
    LibraryItem(std::string title, std::string itemID, Date pubDate, std::string type)
        : title(title), itemID(itemID), publicationDate(pubDate), type(type) {
        internalTrackingID = ++nextInternalID; // Assign unique ID
    }

    // Virtual Destructor: Essential for polymorphic classes to ensure proper cleanup
    // when deleting derived objects via base class pointers.
    virtual ~LibraryItem() {
        // std::cout << "LibraryItem destructor called for " << itemID << std::endl;
    }

    // Pure Virtual Method: Makes LibraryItem an abstract class.
    // Derived classes MUST implement this method.
    virtual void displayInfo() const = 0;

    // Getters (public interface for encapsulated data)
    std::string getItemID() const { return itemID; }
    std::string getTitle() const { return title; }
    std::string getType() const { return type; }
    Date getPublicationDate() const { return publicationDate; }

    // --- C++ Friend Function Declaration ---
    // Declares 'generateQuickReport' as a friend, allowing it to access private/protected members.
    friend void generateQuickReport(const LibraryItem& item);

    // Virtual method for saving to file (to handle polymorphic saving)
    virtual void saveToFile(std::ofstream& outFile) const {
        outFile << type << "," << itemID << "," << title << ","
                << publicationDate.getDay() << "," << publicationDate.getMonth() << ","
                << publicationDate.getYear();
    }
};

// Initialize static member
int LibraryItem::nextInternalID = 0;

// --- C++ Book Derived Class ---
// Inherits from LibraryItem.
class Book : public LibraryItem {
private:
    std::string author;
    std::string isbn;

public:
    // Constructor: Calls base class constructor using initializer list.
    Book(std::string title, std::string author, std::string itemID, Date pubDate, std::string isbn)
        : LibraryItem(title, itemID, pubDate, "BOOK"), author(author), isbn(isbn) {}

    // Overrides the virtual displayInfo method from the base class.
    void displayInfo() const override {
        std::cout << "\n--- Book Details ---" << std::endl;
        std::cout << "Type:           Book" << std::endl;
        std::cout << "Title:          " << title << std::endl;
        std::cout << "Author:         " << author << std::endl;
        std::cout << "Item ID:        " << itemID << std::endl;
        std::cout << "ISBN:           " << isbn << std::endl;
        std::cout << "Publication Date: "; publicationDate.display(); std::cout << std::endl;
        std::cout << "--------------------" << std::endl;
    }

    // Override saveToFile for Book specific data
    void saveToFile(std::ofstream& outFile) const override {
        LibraryItem::saveToFile(outFile); // Call base class save method
        outFile << "," << author << "," << isbn << std::endl; // Add Book-specific data
    }

    // Getters for Book-specific data (useful for file loading)
    std::string getAuthor() const { return author; }
    std::string getISBN() const { return isbn; }
};

// --- C++ Magazine Derived Class ---
// Inherits from LibraryItem.
class Magazine : public LibraryItem {
private:
    std::string publisher;
    int issueNumber;

public:
    // Constructor: Calls base class constructor using initializer list.
    Magazine(std::string title, std::string publisher, std::string itemID, Date pubDate, int issueNum)
        : LibraryItem(title, itemID, pubDate, "MAGAZINE"), publisher(publisher), issueNumber(issueNum) {}

    // Overrides the virtual displayInfo method from the base class.
    void displayInfo() const override {
        std::cout << "\n--- Magazine Details ---" << std::endl;
        std::cout << "Type:           Magazine" << std::endl;
        std::cout << "Title:          " << title << std::endl;
        std::cout << "Publisher:      " << publisher << std::endl;
        std::cout << "Item ID:        " << itemID << std::endl;
        std::cout << "Issue Number:   " << issueNumber << std::endl;
        std::cout << "Publication Date: "; publicationDate.display(); std::cout << std::endl;
        std::cout << "------------------------" << std::endl;
    }

    // Override saveToFile for Magazine specific data
    void saveToFile(std::ofstream& outFile) const override {
        LibraryItem::saveToFile(outFile); // Call base class save method
        outFile << "," << publisher << "," << issueNumber << std::endl; // Add Magazine-specific data
    }

    // Getters for Magazine-specific data (useful for file loading)
    std::string getPublisher() const { return publisher; }
    int getIssueNumber() const { return issueNumber; }
};

// --- C++ Friend Function Definition ---
// This function is a friend of LibraryItem and can access its private/protected members.
void generateQuickReport(const LibraryItem& item) {
    std::cout << "Quick Report: ID: " << item.itemID << ", Title: " << item.title
              << " (Internal Tracking ID: " << item.internalTrackingID << ")" << std::endl;
}

// --- Library Management Class ---
// Manages a collection of LibraryItem objects.
// Uses std::vector (a template class) to store items.
class Library {
private:
    std::vector<LibraryItem*> items; // Stores pointers to base class objects (Polymorphism)
    const std::string dataFilename = "library_data.txt"; // File for persistence

public:
    // Constructor: Loads data when Library object is created.
    Library() {
        loadItemsFromFile();
    }

    // Destructor: Cleans up dynamically allocated memory and saves data.
    ~Library() {
        saveItemsToFile(); // Save data before exiting
        for (LibraryItem* item : items) {
            delete item; // Free memory for each allocated item
        }
        items.clear();
        std::cout << "Library data saved and memory cleaned up." << std::endl;
    }

    // Class Method: Add a new item to the library.
    void addItem(LibraryItem* item) {
        // Check for duplicate itemID
        for (const auto& existingItem : items) {
            if (existingItem->getItemID() == item->getItemID()) {
                std::cout << "Error: Item with ID " << item->getItemID() << " already exists." << std::endl;
                delete item; // Don't add, delete the newly created duplicate object
                return;
            }
        }
        items.push_back(item);
        std::cout << "Item added successfully: " << item->getTitle() << " (ID: " << item->getItemID() << ")" << std::endl;
    }

    // Class Method: Find an item by its ID.
    LibraryItem* findItem(const std::string& itemID) {
        for (LibraryItem* item : items) {
            if (item->getItemID() == itemID) {
                return item;
            }
        }
        return nullptr; // Item not found
    }

    // Class Method: List all items in the library (demonstrates Polymorphism).
    void listAllItems() const {
        if (items.empty()) {
            std::cout << "The library is empty." << std::endl;
            return;
        }
        std::cout << "\n--- All Library Items ---" << std::endl;
        for (const LibraryItem* item : items) {
            item->displayInfo(); // Polymorphic call: calls Book::displayInfo or Magazine::displayInfo
        }
        std::cout << "-------------------------" << std::endl;
    }

    // Class Method: Save all library items to a file. (C++ Files)
    void saveItemsToFile() const {
        std::ofstream outFile(dataFilename);
        if (!outFile.is_open()) {
            std::cerr << "Error: Could not open file " << dataFilename << " for writing." << std::endl;
            return;
        }

        for (const LibraryItem* item : items) {
            item->saveToFile(outFile); // Polymorphic saving
        }
        outFile.close();
        std::cout << "Library data saved to " << dataFilename << std::endl;
    }

    // Class Method: Load library items from a file. (C++ Files)
    void loadItemsFromFile() {
        std::ifstream inFile(dataFilename);
        if (!inFile.is_open()) {
            std::cout << "No existing library data file found. Starting with an empty library." << std::endl;
            return;
        }

        // Clear existing items before loading to prevent duplicates
        for (LibraryItem* item : items) {
            delete item;
        }
        items.clear();
        std::string line;
        while (std::getline(inFile, line)) {
            std::stringstream ss(line);
            std::string segment;
            std::vector<std::string> parts;

            // Split line by comma
            while (std::getline(ss, segment, ',')) {
                parts.push_back(segment);
            }

            if (parts.size() < 6) { // Minimum parts for a LibraryItem (type, ID, title, day, month, year)
                std::cerr << "Warning: Skipping malformed line in file: " << line << std::endl;
                continue;
            }

            std::string type = parts[0];
            std::string itemID = parts[1];
            std::string title = parts[2];
            int day = std::stoi(parts[3]);
            int month = std::stoi(parts[4]);
            int year = std::stoi(parts[5]);
            Date pubDate(day, month, year);

            LibraryItem* newItem = nullptr;

            if (type == "BOOK" && parts.size() == 8) {
                std::string author = parts[6];
                std::string isbn = parts[7];
                newItem = new Book(title, author, itemID, pubDate, isbn);
            } else if (type == "MAGAZINE" && parts.size() == 8) {
                std::string publisher = parts[6];
                int issueNum = std::stoi(parts[7]);
                newItem = new Magazine(title, publisher, itemID, pubDate, issueNum);
            } else {
                std::cerr << "Warning: Unknown item type or malformed data: " << line << std::endl;
            }

            if (newItem) {
                items.push_back(newItem);
            }
        }
        inFile.close();
        std::cout << "Library data loaded from " << dataFilename << ". " << items.size() << " items loaded." << std::endl;
    }
};


// --- Main Application Logic ---
int main() {
    std::cout << "--- Simple C++ Library Management System ---" << std::endl;
    std::cout << "This system demonstrates C++ OOP concepts with file persistence." << std::endl;

    Library myLibrary; // Create a Library object, which will load data from file automatically

    int choice;
    do {
        std::cout << "\n--- Main Menu ---" << std::endl;
        std::cout << "1. Add New Book" << std::endl;
        std::cout << "2. Add New Magazine" << std::endl;
        std::cout << "3. Find Item by ID" << std::endl;
        std::cout << "4. List All Items" << std::endl;
        std::cout << "5. Generate Quick Report for an Item (Friend Function Demo)" << std::endl;
        std::cout << "0. Exit" << std::endl;
        choice = getIntegerInput("Enter your choice: ");

        switch (choice) {
            case 1: { // Add New Book
                std::cout << "\n--- Add New Book ---" << std::endl;
                std::string title = getStringInput("Enter book title: ");
                std::string author = getStringInput("Enter author: ");
                std::string itemID = getStringInput("Enter unique Item ID: ");
                std::string isbn = getStringInput("Enter ISBN: ");
                int d = getIntegerInput("Enter publication day (1-31): ");
                int m = getIntegerInput("Enter publication month (1-12): ");
                int y = getIntegerInput("Enter publication year: ");
                Date pubDate(d, m, y);

                // --- Objects and Constructors ---
                // Dynamically allocate a Book object.
                Book* newBook = new Book(title, author, itemID, pubDate, isbn);
                myLibrary.addItem(newBook); // Add to library (uses LibraryItem* pointer)
                break;
            }
            case 2: { // Add New Magazine
                std::cout << "\n--- Add New Magazine ---" << std::endl;
                std::string title = getStringInput("Enter magazine title: ");
                std::string publisher = getStringInput("Enter publisher: ");
                std::string itemID = getStringInput("Enter unique Item ID: ");
                int issueNum = getIntegerInput("Enter issue number: ");
                int d = getIntegerInput("Enter publication day (1-31): ");
                int m = getIntegerInput("Enter publication month (1-12): ");
                int y = getIntegerInput("Enter publication year: ");
                Date pubDate(d, m, y);

                // Dynamically allocate a Magazine object.
                Magazine* newMagazine = new Magazine(title, publisher, itemID, pubDate, issueNum);
                myLibrary.addItem(newMagazine); // Add to library (uses LibraryItem* pointer)
                break;
            }
            case 3: { // Find Item by ID
                std::cout << "\n--- Find Item ---" << std::endl;
                std::string itemID = getStringInput("Enter Item ID to find: ");
                LibraryItem* foundItem = myLibrary.findItem(itemID);
                if (foundItem) {
                    std::cout << "Item found!" << std::endl;
                    foundItem->displayInfo(); // Polymorphic call
                } else {
                    std::cout << "Item with ID " << itemID << " not found." << std::endl;
                }
                break;
            }
            case 4: { // List All Items
                myLibrary.listAllItems(); // Demonstrates polymorphism in action
                break;
            }
            case 5: { // Generate Quick Report (Friend Function Demo)
                std::cout << "\n--- Generate Quick Report ---" << std::endl;
                std::string itemID = getStringInput("Enter Item ID for report: ");
                LibraryItem* item = myLibrary.findItem(itemID);
                if (item) {
                    // --- C++ Friend Function Call ---
                    // This function can access private members of 'item' because it's a friend.
                    generateQuickReport(*item);
                } else {
                    std::cout << "Item with ID " << itemID << " not found." << std::endl;
                }
                break;
            }
            case 0: { // Exit
                // Destructor of Library will automatically save data and clean up memory.
                std::cout << "\nExiting Library Management System. Goodbye!" << std::endl;
                break;
            }
            default: {
                std::cout << "Invalid choice. Please enter a number from the menu." << std::endl;
                break;
            }
        }
    } while (choice != 0);

    return 0; // Indicate successful program execution
}
