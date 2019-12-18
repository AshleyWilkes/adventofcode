#include "space_image_format.hpp"
#include<algorithm>
#include<fstream>
#include<iostream>

int main( int argc, char* argv[] ) {
  if ( argc != 2 ) {
    std::cout << "call like this: 'main \"input.txt\"!\n";
    return 1;
  }

  std::ifstream inputstream;
  inputstream.open( argv[1] );
  if ( ! inputstream.is_open() ) {
    std::cout << "couldn't open file " << argv[1] << "!\n";
    return 2;
  }

  std::vector<int> input;
  char c;
  while ( inputstream.get( c ) ) {
    input.push_back( c - '0' );
  }
  input.pop_back();

  Image image{ 25, 6, input };
  auto info = image.getLayerInfos();
  auto theLayerInfo = std::min_element( info.begin(), info.end(), []( const LayerInfo& a, const LayerInfo& b) { return a.numDigit( 0 ) < b.numDigit( 0 ); } );
  std::cout << theLayerInfo->numDigit( 1 ) * theLayerInfo->numDigit( 2 ) << '\n';
  auto decoded = image.decode();
  decoded.print();
}
