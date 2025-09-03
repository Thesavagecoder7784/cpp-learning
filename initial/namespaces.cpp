#include <iostream>
#include <string>

// A namespace to represent functions for a "First Project"
namespace ProjectA {
    // A function within ProjectA
    void sayHello() {
        std::cout << "Hello from Project A!" << std::endl;
    }
    
    // Another function in ProjectA
    std::string getMessage() {
        return "This is a message from Project A.";
    }
}

// A namespace to represent functions for a "Second Project"
namespace ProjectB {
    // A function with the same name as in ProjectA
    void sayHello() {
        std::cout << "Hello from Project B!" << std::endl;
    }
    
    // Another function in ProjectB
    std::string getMessage() {
        return "This is a message from Project B.";
    }
}

// The main function where we will use the namespaces
int main() {
    // 1. Explicitly calling functions using the scope resolution operator (::)
    std::cout << "--- Calling with full namespace qualification ---" << std::endl;
    ProjectA::sayHello();
    ProjectB::sayHello();

    // 2. Using a 'using declaration' to bring a single function into scope
    std::cout << "\n--- Using a 'using declaration' ---" << std::endl;
    using ProjectA::getMessage;
    std::cout << getMessage() << std::endl; // Calls ProjectA::getMessage()
    
    // Note: You must still use the full name for the other namespace
    std::cout << ProjectB::getMessage() << std::endl;

    // 3. Using a 'using directive' to bring an entire namespace into scope
    std::cout << "\n--- Using a 'using directive' (caution!) ---" << std::endl;
    // This can lead to naming conflicts if both namespaces have the same function name.
    using namespace ProjectB;
    sayHello(); // This will now call ProjectB::sayHello()
    std::cout << getMessage() << std::endl; // This will now call ProjectB::getMessage()

    return 0;
}
