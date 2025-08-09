#include <iostream>
#include <memory> // Required for std::unique_ptr, std::shared_ptr, std::weak_ptr
#include <string>

// A simple class to demonstrate object creation and destruction
class MyClass {
public:
    std::string name;

    MyClass(const std::string& n) : name(n) {
        std::cout << "MyClass " << name << " created." << std::endl;
    }

    ~MyClass() {
        std::cout << "MyClass " << name << " destroyed." << std::endl;
    }

    void greet() const {
        std::cout << "Hello from " << name << "!" << std::endl;
    }
};

// Function to demonstrate raw pointers
void demonstrateRawPointers() {
    std::cout << "\n--- Demonstrating Raw Pointers ---" << std::endl;

    // 1. Basic raw pointer usage
    MyClass* obj1 = new MyClass("RawObj1"); // Allocate on heap
    obj1->greet();
    delete obj1; // Manually deallocate memory
    obj1 = nullptr; // Good practice to nullify after deletion

    // 2. Potential memory leak (forgetting to delete)
    MyClass* obj2 = new MyClass("RawObj2");
    obj2->greet();
    // If we forget 'delete obj2;' here, memory will leak!
    std::cout << "WARNING: RawObj2 memory might leak if not explicitly deleted." << std::endl;
    delete obj2; // Explicitly deleting to prevent leak in this example
    obj2 = nullptr;

    // 3. Dangling pointer (accessing after deletion)
    MyClass* obj3 = new MyClass("RawObj3");
    delete obj3;
    // obj3 is now a dangling pointer. Accessing it is Undefined Behavior!
    // obj3->greet(); // DANGER! Do not uncomment in real code.
    obj3 = nullptr; // Always nullify after delete
}

// Function to demonstrate std::unique_ptr
void demonstrateUniquePtr() {
    std::cout << "\n--- Demonstrating std::unique_ptr ---" << std::endl;

    // 1. Basic unique_ptr usage
    // Memory is automatically managed. No 'delete' needed.
    std::unique_ptr<MyClass> u_obj1 = std::make_unique<MyClass>("UniqueObj1");
    u_obj1->greet();
    // When u_obj1 goes out of scope, MyClass("UniqueObj1") will be destroyed automatically.

    // 2. Ownership transfer (unique_ptr cannot be copied, only moved)
    std::unique_ptr<MyClass> u_obj2 = std::make_unique<MyClass>("UniqueObj2");
    std::cout << "u_obj2 owns UniqueObj2." << std::endl;
    std::unique_ptr<MyClass> u_obj3 = std::move(u_obj2); // Transfer ownership
    std::cout << "u_obj3 now owns UniqueObj2. u_obj2 is now empty." << std::endl;

    if (u_obj2) { // Check if unique_ptr is not empty
        u_obj2->greet();
    } else {
        std::cout << "u_obj2 is empty after move." << std::endl;
    }
    u_obj3->greet();
    // When u_obj3 goes out of scope, MyClass("UniqueObj2") will be destroyed.
}

// Function to demonstrate std::shared_ptr
void demonstrateSharedPtr() {
    std::cout << "\n--- Demonstrating std::shared_ptr ---" << std::endl;

    // 1. Basic shared_ptr usage
    std::shared_ptr<MyClass> s_obj1 = std::make_shared<MyClass>("SharedObj1");
    s_obj1->greet();
    std::cout << "SharedObj1 reference count: " << s_obj1.use_count() << std::endl;

    // 2. Multiple shared_ptr objects sharing ownership
    std::shared_ptr<MyClass> s_obj2 = s_obj1; // Copying increases reference count
    std::cout << "SharedObj1 reference count after copy to s_obj2: " << s_obj1.use_count() << std::endl;

    std::shared_ptr<MyClass> s_obj3 = s_obj1; // Another copy
    std::cout << "SharedObj1 reference count after copy to s_obj3: " << s_obj1.use_count() << std::endl;

    s_obj2->greet();
    s_obj3->greet();

    // When all shared_ptr objects pointing to "SharedObj1" go out of scope,
    // MyClass("SharedObj1") will be destroyed.
    std::cout << "s_obj2 going out of scope (simulated)." << std::endl;
    // s_obj2 will be destroyed here if it were in a nested scope.
    // For this example, we'll let them all go out of scope at the end of the function.
}

// Class to demonstrate circular dependency with shared_ptr and how weak_ptr helps
class Node {
public:
    std::string name;
    std::shared_ptr<Node> next; // Shared ownership of the next node
    std::weak_ptr<Node> prev;   // Weak ownership of the previous node

    Node(const std::string& n) : name(n) {
        std::cout << "Node " << name << " created." << std::endl;
    }

    ~Node() {
        std::cout << "Node " << name << " destroyed." << std::endl;
    }

    void setNext(std::shared_ptr<Node> n) {
        next = n;
    }

    void setPrev(std::shared_ptr<Node> p) {
        prev = p; // Assign shared_ptr to weak_ptr
    }

    void printConnections() const {
        std::cout << "Node " << name << ": ";
        if (next) {
            std::cout << "Next: " << next->name << " (shared_ptr count: " << next.use_count() << ") ";
        } else {
            std::cout << "Next: None ";
        }

        if (auto p = prev.lock()) { // Lock weak_ptr to get shared_ptr
            std::cout << "Prev: " << p->name << " (shared_ptr count: " << p.use_count() << ")";
        } else {
            std::cout << "Prev: None (expired or not set)";
        }
        std::cout << std::endl;
    }
};

void demonstrateWeakPtr() {
    std::cout << "\n--- Demonstrating std::weak_ptr (to break circular references) ---" << std::endl;

    std::shared_ptr<Node> nodeA = std::make_shared<Node>("NodeA");
    std::shared_ptr<Node> nodeB = std::make_shared<Node>("NodeB");

    std::cout << "Initial counts: NodeA: " << nodeA.use_count() << ", NodeB: " << nodeB.use_count() << std::endl;

    // Create a circular reference using shared_ptr (BAD!)
    // nodeA->next = nodeB;
    // nodeB->next = nodeA;
    // If both 'next' were shared_ptr, neither would be destroyed because their
    // reference counts would never drop to zero. This is a memory leak.

    // Correct way using weak_ptr for the back-reference
    nodeA->setNext(nodeB);
    nodeB->setPrev(nodeA); // nodeB's 'prev' is a weak_ptr to nodeA

    std::cout << "After setting connections:" << std::endl;
    nodeA->printConnections();
    nodeB->printConnections();

    // When nodeA and nodeB shared_ptr go out of scope, their reference counts
    // will drop to zero, and they will be destroyed.
    // The weak_ptr does not contribute to the reference count.
    std::cout << "\nNodeA and NodeB shared_ptr going out of scope..." << std::endl;
} // nodeA and nodeB are destroyed here

int main() {
    demonstrateRawPointers();
    demonstrateUniquePtr();
    demonstrateSharedPtr();
    demonstrateWeakPtr();

    std::cout << "\n--- End of Program ---" << std::endl;
    return 0;
}
