#include "space_image_format.hpp"
#include<iostream>

void LayerInfo::addPixel( int value ) {
  pixels_.push_back( value );
  if ( value >= 0 && value < 3 ) {
    counts_.at( value ) += 1;
  }
}

int LayerInfo::numDigit( int digit ) const {
  return counts_.at( digit );
}

void LayerInfo::printPixel( int row, int col ) const {
  char c{ '-' };
  switch ( pixels_.at( row * width_ + col ) ) {
    case 0 : c = ' '; break;
    case 1 : c = 'X'; break;
    default: break;
  }
  std::cout << c;
}

void LayerInfo::print() const {
  for ( int row = 0; row < height_; ++row ) {
    for ( int col = 0; col < width_; ++col ) {
      printPixel( row, col );
    }
    std::cout << '\n';
  }
}

Image::Image( int width, int height, const std::vector<int>& input ) : width_{ width }, height_{ height } {
  auto it = input.begin();
  while ( it != input.end() ) {
    LayerInfo layerInfo{ width_, height_ };
    for ( int col = 0; col < width_; ++col ) {
      for ( int row = 0; row < height_; ++row ) {
        layerInfo.addPixel ( *it );
        ++it;
      }
    }
    layers_.push_back( layerInfo );
  }
}

int Image::decodePixel( int index ) const {
  for ( auto layer : layers_ ) {
    int pixelInLayer = layer.getPixel( index );
    if ( pixelInLayer != 2 ) {
      return pixelInLayer;
    }
  }
  return 2;
}

LayerInfo Image::decode() const {
  LayerInfo result{ width_, height_ };
  for ( int i = 0; i < width_ * height_; ++i ) {
    result.addPixel( decodePixel( i ) );
  }
  return result;
}
