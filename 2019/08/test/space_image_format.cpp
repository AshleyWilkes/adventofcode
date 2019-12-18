#include "gtest/gtest.h"
#include "space_image_format.hpp"

namespace {

TEST(SpaceImageFormat, example1) {
  std::vector<int> input { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2 };
  Image image{ 3, 2, input };
  auto infos = image.getLayerInfos();
  EXPECT_EQ( infos.at( 0 ).numDigit( 0 ), 0 );
  EXPECT_EQ( infos.at( 0 ).numDigit( 1 ), 1 );
  EXPECT_EQ( infos.at( 1 ).numDigit( 1 ), 1 );
}

TEST(SpaceImageFormat, example2) {
  std::vector<int> input { 0, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 2, 0, 0, 0, 0 };
  Image image{ 2, 2, input };
  LayerInfo decoded = image.decode();
  std::vector<int> expected{ 0, 1, 1, 0 };
  EXPECT_EQ( decoded.getPixels(), expected );
}

}
