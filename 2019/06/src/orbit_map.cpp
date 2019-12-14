#include "orbit_map.hpp"
#include<numeric>

void SpaceObject::addSatellite( const std::string& satellite ) {
  satellites_.push_back( satellite );
}

//velmi nehezke; uz to, ze jako primaryBody ukladam string a ne primo objekt,
//je asi spatne; i satellity by nejspis mely byt primo objekty
//no a to, ze se tady v kazdem kroku kopiruje cely vector, no ehm
std::vector<std::string> SpaceObject::getPathToCenter( const OrbitMap *map ) const {
  if ( hasPrimaryBody() ) {
    std::vector<std::string> result{ getName() };
    auto subPath = map->get( getPrimaryBody() ).getPathToCenter( map );
    result.insert( result.end(), subPath.begin(), subPath.end() );
    return result;
  } else {
    return { getName() };
  }
}

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
  map_.try_emplace( primary, primary );
  map_.try_emplace( orbiting, orbiting );
  get( primary ).addSatellite( orbiting );
  get( orbiting ).setPrimaryBody( primary );
}

void OrbitMap::countDistances( const std::string& id, int distance ) {
  auto& body = get( id );
  body.setDistance( distance );
  for ( auto sat : body.satellites() ) {
    countDistances( sat, distance + 1 );
  }
}

int OrbitMap::getMinimalOrbitTransfers( const std::string& body1, const std::string& body2 ) const {
  auto path1 = get( body1 ).getPathToCenter( this );
  auto path2 = get( body2 ).getPathToCenter( this );
  while ( path1.back() == path2.back() ) {
    path1.pop_back();
    path2.pop_back();
  }
  return path1.size() + path2.size();
}
