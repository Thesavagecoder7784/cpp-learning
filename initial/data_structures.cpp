#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <deque>
#include <set>
#include <map>
#include <iterator>
#include <algorithm>
#include <numeric> // For std::accumulate

// Function to print elements of a container
template<typename T>
void print_container(const T& container, const std::string& name) {
    std::cout << "---- " << name << " ----" << std::endl;
    if (container.empty()) {
        std::cout << "(empty)" << std::endl;
        return;
    }
    for (const auto& element : container) {
        std::cout << element << " ";
    }
    std::cout << std::endl << std::endl;
}

// Specialization for maps
template<typename K, typename V>
void print_container(const std::map<K, V>& container, const std::string& name) {
    std::cout << "---- " << name << " ----" << std::endl;
    if (container.empty()) {
        std::cout << "(empty)" << std::endl;
        return;
    }
    for (const auto& pair : container) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    std::cout << std::endl;
}


int main() {
    std::cout << "=== C++ Data Structures & STL ===\n\n";

    // C++ Vectors
    std::vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(5);
    print_container(vec, "Vectors (initial)");
    std::cout << "Vector size: " << vec.size() << std::endl;
    std::cout << "Vector element at index 1: " << vec.at(1) << std::endl;
    vec.insert(vec.begin() + 1, 15); // Insert 15 at index 1
    print_container(vec, "Vectors (after insert)");
    vec.erase(vec.begin()); // Erase first element
    print_container(vec, "Vectors (after erase)");
    std::cout << "Is vector empty? " << (vec.empty() ? "Yes" : "No") << std::endl;
    vec.clear();
    std::cout << "Is vector empty after clear? " << (vec.empty() ? "Yes" : "No") << std::endl << std::endl;

    // C++ List
    std::list<int> myList;
    myList.push_back(100);
    myList.push_front(200);
    myList.push_back(300);
    myList.push_back(200); // Another 200 for remove demonstration
    print_container(myList, "Lists (initial)");
    std::cout << "List size: " << myList.size() << std::endl;
    myList.pop_front();
    print_container(myList, "Lists (after pop_front)");
    myList.remove(200); // Remove all occurrences of 200
    print_container(myList, "Lists (after remove 200)");
    std::cout << "Is list empty? " << (myList.empty() ? "Yes" : "No") << std::endl;
    myList.clear();
    std::cout << "Is list empty after clear? " << (myList.empty() ? "Yes" : "No") << std::endl << std::endl;

    // C++ Stacks (LIFO)
    std::stack<std::string> books;
    books.push("The Great Gatsby");
    books.push("Moby Dick");
    books.push("Pride and Prejudice");
    std::cout << "---- Stacks ----" << std::endl;
    std::cout << "Stack size: " << books.size() << std::endl;
    std::cout << "Top of stack: " << books.top() << std::endl;
    books.pop();
    std::cout << "Top of stack after pop: " << books.top() << std::endl;
    std::cout << "Is stack empty? " << (books.empty() ? "Yes" : "No") << std::endl << std::endl;

    // C++ Queues (FIFO)
    std::queue<std::string> customers;
    customers.push("Alice");
    customers.push("Bob");
    customers.push("Charlie");
    std::cout << "---- Queues ----" << std::endl;
    std::cout << "Queue size: " << customers.size() << std::endl;
    std::cout << "Front of queue: " << customers.front() << std::endl;
    std::cout << "Back of queue: " << customers.back() << std::endl;
    customers.pop();
    std::cout << "Front of queue after pop: " << customers.front() << std::endl;
    std::cout << "Is queue empty? " << (customers.empty() ? "Yes" : "No") << std::endl << std::endl;

    // C++ Deque
    std::deque<int> deq;
    deq.push_back(10);
    deq.push_front(5);
    deq.push_back(20);
    print_container(deq, "Deque (initial)");
    std::cout << "Deque size: " << deq.size() << std::endl;
    std::cout << "Front: " << deq.front() << ", Back: " << deq.back() << std::endl;
    deq.pop_back();
    print_container(deq, "Deque (after pop_back)");
    std::cout << "Is deque empty? " << (deq.empty() ? "Yes" : "No") << std::endl;
    deq.clear();
    std::cout << "Is deque empty after clear? " << (deq.empty() ? "Yes" : "No") << std::endl << std::endl;

    // C++ Sets (Unique, sorted elements)
    std::set<int> mySet;
    mySet.insert(50);
    mySet.insert(20);
    mySet.insert(50); // Duplicate, will be ignored
    mySet.insert(80);
    print_container(mySet, "Sets (initial)");
    std::cout << "Set size: " << mySet.size() << std::endl;
    std::cout << "Count of 50: " << mySet.count(50) << std::endl;
    std::cout << "Count of 100: " << mySet.count(100) << std::endl;
    mySet.erase(20);
    print_container(mySet, "Sets (after erase 20)");
    std::cout << "Is set empty? " << (mySet.empty() ? "Yes" : "No") << std::endl;
    mySet.clear();
    std::cout << "Is set empty after clear? " << (mySet.empty() ? "Yes" : "No") << std::endl << std::endl;

    // C++ Maps (Key-Value pairs)
    std::map<std::string, int> ages;
    ages["Alice"] = 30;
    ages["Bob"] = 25;
    ages.insert(std::make_pair("Charlie", 35));
    print_container(ages, "Maps (initial)");
    std::cout << "Map size: " << ages.size() << std::endl;
    std::cout << "Bob's age: " << ages["Bob"] << std::endl;
    std::cout << "Count of Alice: " << ages.count("Alice") << std::endl;
    std::cout << "Count of David: " << ages.count("David") << std::endl;
    ages.erase("Bob");
    print_container(ages, "Maps (after erase Bob)");
    std::cout << "Is map empty? " << (ages.empty() ? "Yes" : "No") << std::endl;
    ages.clear();
    std::cout << "Is map empty after clear? " << (ages.empty() ? "Yes" : "No") << std::endl << std::endl;

    // C++ Iterators
    std::cout << "---- Iterators ----" << std::endl;
    std::vector<int> iterator_vec = {1, 2, 3, 4, 5};
    std::cout << "Using iterators to print vector (forward): ";
    for (std::vector<int>::iterator it = iterator_vec.begin(); it != iterator_vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Using const iterators (cbegin/cend): ";
    for (std::vector<int>::const_iterator it = iterator_vec.cbegin(); it != iterator_vec.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Using reverse iterators (rbegin/rend): ";
    for (std::vector<int>::reverse_iterator it = iterator_vec.rbegin(); it != iterator_vec.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl << std::endl;

    // C++ Algorithms
    std::cout << "---- Algorithms ----" << std::endl;
    std::vector<int> algo_vec = {5, 2, 8, 1, 9, 3};
    print_container(algo_vec, "Algorithms (initial vector)");
    
    // Sort
    std::sort(algo_vec.begin(), algo_vec.end());
    print_container(algo_vec, "Algorithms (sorted)");

    // Find
    auto it_find = std::find(algo_vec.begin(), algo_vec.end(), 8);
    if (it_find != algo_vec.end()) {
        std::cout << "Found 8 at index: " << std::distance(algo_vec.begin(), it_find) << std::endl;
    } else {
        std::cout << "8 not found" << std::endl;
    }

    // Min/Max element
    std::cout << "Min element: " << *std::min_element(algo_vec.begin(), algo_vec.end()) << std::endl;
    std::cout << "Max element: " << *std::max_element(algo_vec.begin(), algo_vec.end()) << std::endl;

    // Reverse
    std::reverse(algo_vec.begin(), algo_vec.end());
    print_container(algo_vec, "Algorithms (reversed)");

    // Accumulate (sum)
    int sum = std::accumulate(algo_vec.begin(), algo_vec.end(), 0);
    std::cout << "Sum of elements: " << sum << std::endl;

    // for_each with a lambda
    std::cout << "Vector elements doubled: ";
    std::for_each(algo_vec.begin(), algo_vec.end(), [](int& n){ n *= 2; });
    for (int element : algo_vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;


    return 0;
}