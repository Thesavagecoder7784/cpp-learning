# cpp-learning

Repository of learning and applying C++ through some tutorials, projects, and ultimately in the field of quantitative finance

## 1. Arrays
Fixed-size collection of elements of the same type.
```cpp
int arr[5] = {1, 2, 3, 4, 5};
```

## 2. Vectors (std::vector)
Dynamic array (resizes automatically).
Part of the Standard Template Library (STL).

#include <vector>
std::vector<int> v = {1, 2, 3};
v.push_back(4);       // Add element
v.pop_back();         // Remove last element
int x = v[1];         // Access second element

## 3. Strings (std::string)
Sequence of characters; easier than C-style strings (char[]).
#include <string>

std::string s = "Hello";
s += " World";         // Concatenate
char c = s[0];         // Access first character

## 4. Stack (std::stack)
LIFO (Last In First Out) structure.
#include <stack>

std::stack<int> st;
st.push(1);
st.push(2);
st.pop();             // Removes 2
int top = st.top();   // 1

## 5. Queue (std::queue)
FIFO (First In First Out) structure
#include <queue>

std::queue<int> q;
q.push(1);
q.push(2);
q.pop();             // Removes 1
int front = q.front(); // 2

## 6. Deque (std::deque)
Double-ended queue, supports insertion/removal from both ends.
#include <deque>

std::deque<int> dq;
dq.push_front(1);
dq.push_back(2);
dq.pop_front();      // Removes 1
dq.pop_back();       // Removes 2

## 7. Set (std::set)
Sorted, unique elements.
#include <set>

std::set<int> s;
s.insert(5);
s.insert(3);
s.insert(5);        // Won’t add duplicate
s.erase(3);
bool found = s.count(5); // 1 (true)

## 8. Unordered Set (std::unordered_set)
Like set, but uses hashing → faster average-case.
#include <unordered_set>

std::unordered_set<int> us;
us.insert(10);
us.erase(10);

## 9. Map (std::map)
Key-value pair container, sorted by keys.
#include <map>

std::map<std::string, int> m;
m["apple"] = 2;
int x = m["apple"];    // 2

## 10. Unordered Map (std::unordered_map)
Like map, but faster with hash-based lookup.
#include <unordered_map>

std::unordered_map<std::string, int> um;
um["banana"] = 5;

## 11. Pair (std::pair)
A container for two values.
#include <utility>

std::pair<int, std::string> p = {1, "One"};
int a = p.first;         // 1
std::string b = p.second; // "One"

## 12. Priority Queue (std::priority_queue)
A heap-based queue (by default, max heap).
#include <queue>

std::priority_queue<int> pq;
pq.push(3);
pq.push(10);
int top = pq.top();   // 10

For a min-heap:
std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

## 13. Linked List (std::list)
Doubly linked list with fast insertions/removals from anywhere.
#include <list>

std::list<int> l = {1, 2, 3};
l.push_front(0);
l.push_back(4);
l.pop_front();

## 14. Bitset (std::bitset)
Fixed-size sequence of bits (like an array of booleans).
#include <bitset>

std::bitset<8> b("10101010");
bool bit = b[1];   // 1 (true)
b.set(0);          // set bit at position 0 to 1

## 15. Tuple (std::tuple)
Generalized version of pair, can hold more than 2 values.
#include <tuple>

std::tuple<int, std::string, float> t = {1, "Hello", 3.14f};
int i = std::get<0>(t);
