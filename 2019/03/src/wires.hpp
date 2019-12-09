#pragma once
#include <optional>
#include <string>
#include <vector>

//jednak je treba mit datovou strukturu, ktera reprezentuje jeden drat
//dvak je potreba umet vzit dva draty a najit vsechny jejich pruseciky
//trik je treba umet pruseciky porovnavat na vzdalenost od pocatku, to je asi trivka
//
//class wire:
//inicializovat pomoci segmentu: initSegment je kombinace [smerNESW, vzdalenost]
//ukladat taky pomoci segmentu, storageSegment je kombinace [smerHorVert, constCoord, lowerNonConstCoord, higherNonConstCoord]
//
//kdybych mel ty segmenty opravdu jako hor/vert, c1 x c2..c3, tak kolize hledam vzdy mezi
//jednim hor a jednim vert segmentem a je to very easy, cili rozhodnuto
//

struct InitSegment {
  InitSegment( const std::string& initStr );

  bool horizontal_;
  int deltaLength_;
};

std::vector<InitSegment> parseInitString( const std::string& str );

using Point = std::pair<int, int>;

struct Segment {
  Segment( Point start, Point end );
  Point start_, end_, bottomLeft_, topRight_;
};

struct Intersection {
  Intersection( int x, int y ) : p_{ x, y }, distance_{ std::abs( x ) + std::abs( y ) } {}
  Point p_;
  int distance_;
};

struct Wire {
  Wire( const std::vector<InitSegment>& init );
  std::vector<Segment> segments;
};

std::optional<std::pair<int, int>> countCoordsOverlap( int min1, int max1, int min2, int max2 );

std::optional<Intersection> countSegmentsIntersection( const Segment& s1, const Segment& s2 );

Intersection countMinimalWiresIntersection( const Wire& w1, const Wire& w2 );
