#pragma once
#include<map>
#include<optional>
#include<sstream>
#include<string>
#include<vector>

class SpaceObject {
  public:
    void addSatellite( const std::string& satellite ) { satellites_.push_back( satellite ); }
    const std::vector<std::string>& satellites() const { return satellites_; }
    void setDistance( int distance ) { distance_ = distance; }
    int getDistance() { return *distance_; }
    bool distanceIsSet() const { return distance_.has_value(); }
  private:
    std::vector<std::string> satellites_;
    std::optional<int> distance_;
};

class OrbitMap {
  private:
    using Container = std::map<std::string, SpaceObject>;
  public:
    OrbitMap( std::istream& inputStream );
    std::size_t size() const { return map_.size(); }
    SpaceObject& get( const std::string& key ) { return map_.at( key ); }
    const SpaceObject& get( const std::string& key ) const { return map_.at( key ); }
    Container::const_iterator begin() const { return map_.begin(); }
    Container::const_iterator end() const { return map_.end(); }
    int totalOrbitsCount() const;
    void addOrbit( const std::string& primary, const std::string& orbiting );
    void countDistances() { countDistances( "COM", 0 ); }
    void countDistances( const std::string& id, int distance );
  private:
    Container map_;
};
