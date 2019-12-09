#include <array>
#include <iostream>

constexpr int numDigits = 6;

using Digits = std::array<int, numDigits>;

Digits parseDigits( int number ) {
  Digits result;
  for ( int i = 0; i < numDigits; ++i ) {
    result[numDigits - i -1] = number % 10;
    number = number / 10;
  }
  return result;
}

bool neverDecreases( Digits digits ) {
  for ( int i = 0; i < numDigits; ++i ) {
    if ( digits[i + 1] < digits[i] ) {
      return false;
    }
  }
  return true;
}

bool has2AdjacentSameDigits( Digits digits ) {
  for ( int i = 0; i < numDigits - 1; ++i ) {
    if ( digits[i+1] == digits[i] ) {
      return true;
    }
  }
  return false;
}

bool passesRules( int i ) {
  Digits digits = parseDigits( i );
  return neverDecreases( digits ) && has2AdjacentSameDigits( digits );
}

int main() {
  int count;
  for ( int i = 171309; i <= 643603; ++i ) {
    count += passesRules( i ) ? 1 : 0;
  }
  std::cout << count << '\n';
}
