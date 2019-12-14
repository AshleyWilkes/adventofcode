#pragma once
#include<map>
#include<optional>
#include<sstream>
#include<string>
#include<vector>

class OrbitMap;

class SpaceObject {
  public:
    SpaceObject( const std::string& name ) : name_{ name } {}
    std::string getName() const { return name_; }
    void addSatellite( const std::string& satellite ); 
    const std::vector<std::string>& satellites() const { return satellites_; }
    void setPrimaryBody( const std::string& id ) { primary_ = id; }
    bool hasPrimaryBody() const { return primary_.has_value(); }
    std::string getPrimaryBody() const { return *primary_; }
    void setDistance( int distance ) { distance_ = distance; }
    int getDistance() { return *distance_; }
    bool distanceIsSet() const { return distance_.has_value(); }
    std::vector<std::string> getPathToCenter( const OrbitMap *map ) const;
  private:
    std::string name_;
    std::vector<std::string> satellites_;
    std::optional<std::string> primary_;//the body this object orbits around
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
    int getMinimalOrbitTransfers( const std::string& body1, const std::string& body2 ) const;
  private:
    Container map_;
};
