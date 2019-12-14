#include "orbit_map.hpp"
#include<numeric>

OrbitMap::OrbitMap( std::istream& inputStream ) {
  while ( inputStream.good() ) {
    std::string line;
    getline( inputStream, line );
    int separatorPos = line.find( ')' );
    addOrbit( line.substr( 0, separatorPos ), line.substr( separatorPos + 1, 6 ) );
  }
}

int OrbitMap::totalOrbitsCount() const {
  return std::accumulate( begin(), end(), 0, []( int curSum, auto mapEntry ) {
      return curSum + mapEntry.second.getDistance();
      } );
}

void OrbitMap::addOrbit( const std::string& primary, const std::string& orbiting ) {
  map_.try_emplace( primary );
  map_.try_emplace( orbiting );
  get( primary ).addSatellite( orbiting );
}

void OrbitMap::countDistances( const std::string& id, int distance ) {
  auto& body = get( id );
  body.setDistance( distance );
  for ( auto sat : body.satellites() ) {
    countDistances( sat, distance + 1 );
  }
}
