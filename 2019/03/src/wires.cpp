#include <sstream>
#include "wires.hpp"

InitSegment::InitSegment( const std::string& initStr ) {
  char dirCh = initStr.front();
  int length = std::stoi( initStr.substr( 1 ) );
  switch( dirCh ) {
    case 'R': horizontal_ = true; deltaLength_ = length; break;
    case 'L': horizontal_ = true; deltaLength_ = -length; break;
    case 'U': horizontal_ = false; deltaLength_ = length; break;
    case 'D': horizontal_ = false; deltaLength_ = -length; break;
    default: throw "parse error in InitSegment()";
  }
}

std::vector<InitSegment> parseInitString( const std::string& str ) {
  std::vector<InitSegment> result;
  std::stringstream ss{ str };
  while ( ss.good() ) {
    std::string segmentStr;
    getline( ss, segmentStr, ',' );
    result.push_back( InitSegment{ segmentStr } );
  }
  return result;
}

Segment::Segment( Point start, Point end ) : start_{ start }, end_{ end } {
  bottomLeft_.first = std::min( start.first, end.first );
  bottomLeft_.second = std::min( start.second, end.second );
  topRight_.first = std::max( start.first, end.first );
  topRight_.second = std::max( start.second, end.second );
}

Wire::Wire( const std::vector<InitSegment>& init ) {
  int curX = 0, curY = 0;
  for ( InitSegment initSeg : init ) {
    int newX = curX + ( initSeg.horizontal_ ? initSeg.deltaLength_ : 0 );
    int newY = curY + ( initSeg.horizontal_ ? 0 : initSeg.deltaLength_ );
    segments.push_back( Segment{ { curX, curY }, { newX, newY } } );
    curX = newX;
    curY = newY;
  }
}

Intersection countMinimalWiresIntersection( const Wire& w1, const Wire& w2 ) {
  std::optional<Intersection> result;
  for ( Segment seg1 : w1.segments ) {
    for ( Segment seg2 : w2.segments ) {
      auto segmentsIntersection = countSegmentsIntersection( seg1, seg2 );
      if ( segmentsIntersection ) {
        if ( ! result || ( segmentsIntersection->distance_ < result->distance_ ) ) {
          result = segmentsIntersection;
        }
      }
    }
  }
  if ( result ) {
    return *result;
  } else {
    throw std::logic_error{ "no intersection found" };
  }
}

//imagine overlapping rectangles: how to count the overlap? in each of both directions:
//take maximum of minimal coordinates, that's the minimum of the overlap
//take minimum of maximal coordinates, that's the maximum of the overlap
//HERE, we expect the overlap to be a single point, otherwise throw an exception
std::optional<Intersection> countSegmentsIntersection( const Segment& s1, const Segment& s2 ) {
  auto x = countCoordsOverlap( s1.bottomLeft_.first, s1.topRight_.first,
      s2.bottomLeft_.first, s2.topRight_.first );
  auto y = countCoordsOverlap( s1.bottomLeft_.second, s1.topRight_.second,
      s2.bottomLeft_.second, s2.topRight_.second );
  if ( x && y ) {
    if ( x->first < x->second && y->first < y->second )
      throw "overlap too large";
    if ( x->first == 0 && y->first == 0 ) {
      return {};
    } else {
      return Intersection{ x->first, y->first };
    }
  } else {
    return {};
  }
}

std::optional<std::pair<int, int>> countCoordsOverlap( int min1, int max1, int min2, int max2 ) {
  int min = std::max( min1, min2 );
  int max = std::min( max1, max2 );
  if ( min <= max ) {
    return std::make_pair( min, max );
  } else {
    return {};
  }
}
