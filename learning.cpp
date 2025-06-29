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

  int n,m;
  n = m = 10;
  n++;
  m++;
  
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

  if (20 > 18) {
  cout << "20 is greater than 18";
  }
  cout << "\n";

  int time = 22;
  if (time < 10) {
    cout << "Good morning.";
  } else if (time < 20) {
    cout << "Good day.";
  } else {
    cout << "Good evening.";
  }
  cout << "\n";

  int day = 4;
  switch (day) {
  case 1:
    cout << "Monday";
    break;
  case 2:
    cout << "Tuesday";
    break;
  case 3:
    cout << "Wednesday";
    break;
  case 4:
    cout << "Thursday";
    break;
  case 5:
    cout << "Friday";
    break;
  case 6:
    cout << "Saturday";
    break;
  case 7:
    cout << "Sunday";
    break;
  }

  int i = 0;
  while (i < 5) {
    cout << i << "\n";
    i++;
  }

  int j = 0;
  do {
    cout << j << "\n";
    j++;
  }
  while (j < 5);


  for (int k = 0; k < 5; k++) {
  cout << k << "\n";
  }

  for (i = 1; i <= 3; i++) {
  for (j = 1; j <= 3; j++) {
      cout << i * j << " ";
    }
    cout << "\n";
  }

  int myNumbers[5] = {10, 20, 30, 40, 50};
  for (int a : myNumbers) {
    cout << a << "\n";
  }

  i = 0;
  while (i < 10) {
    cout << i << "\n";
    i++;
    if (i == 4) {
      break;
    }
  }

  i = 0;
  while (i < 10) {
    if (i == 4) {
      i++;
      continue;
    }
    cout << i << "\n";
    i++;
  }

  string cars[4] = {"Volvo", "BMW", "Ford", "Mazda"};
  cout << cars[0];
  cout << "\n";

  struct {
  string brand;
  string model;
  int year;
  } myCar1, myCar2; // We can add variables by separating them with a comma here

  myCar1.brand = "Audi";
  myCar1.model = "A5";
  myCar1.year = 2005;

  cout << myCar1.brand << " " << myCar1.model << " " << myCar1.year << "\n";


  enum Level {
    LOW = 25,
    MEDIUM = 50,
    HIGH = 75
  };

  enum Level myVar = MEDIUM;
  cout << "Level: " << myVar << "\n";

  string food = "Pizza";
  string &meal = food;

  cout << food << "\n"; 
  cout << meal << "\n"; //Same output

  string* ptr = &food;

  cout << &food << "\n"; // Memory Address
  cout << ptr << "\n"; //Memory Adress
 
  cout << *ptr << "\n"; //
  return 0;
}