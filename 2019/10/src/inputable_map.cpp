#include "inputable_map.hpp"

InputableMap::InputableMap( std::istream& inputStream ) {
  bool firstLine{ true };
  int elementsOnThisLine{ 0 };
  char c;
  while ( ( c = inputStream.get() ) != -1 ) {
    if ( c == '\n' ) {
      if ( firstLine ) {
        cols_ = elementsOnThisLine;
        firstLine = false;
      } else if ( elementsOnThisLine != cols_ ) {
        throw std::invalid_argument{ "Invalid map input; not a rectangle" };
      }
      elementsOnThisLine = 0;
    } else {
      elements_.push_back( c );
      elementsOnThisLine++;
    }
  }
}

