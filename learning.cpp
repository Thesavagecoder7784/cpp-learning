#include <iostream>
using namespace std;

int main() {
  cout << 2 + 2; // Comment
  cout << "\n"; // Add a new line
  cout << 5 * 2;
  cout << "\n";
  int age = 19;                // Integer (whole number without decimals)
  double floatnum = 5.99;      // Floating point number (with decimals)
  char letter = 'T';           // Character
  string txt = "Adieu";        // String (text)
  bool boolean = false;        // Boolean (true or false)

  cout << "I am " << age << " years old\n";
  int a = 10, b = 20, c = 30;
  cout << a + b + c << "\n";
  a = b = c;

  const int year_of_birth = 1984;

  int length = 8;
  int width = 3;
  cout << "The area is " << length * width << "\n";

  int input;
  cout << "Enter a number\n";
  cin >> input;

  bool winner = true;
  cout << "\n" << winner << "\n"; // output will be 1

  auto x = 10; // automatically treated as int

  cout << 15%7; // output = 1

  int i,j;
  i = j = 10;
  i++;
  j++;
  
	x %= 3;  // x = x % 3
  x &= 3;  // x = x & 3 - AND operation
  x |= 3;  // x = x | 3 - OR operation
  x ^= 3;  // Exponent operator
  x >>= 3; // Shifts 3 places to the right - same as x = x//8 for +ve numbers
  x <<= 3; // Shifts 3 places to the left - same as x = x * 8 for +ve numbers

  int y = 10; 
  bool win = true;
  cout << x && y; // Logical AND
  cout << x || y; // Logical OR
  cout << "\n";
  return 0;
}