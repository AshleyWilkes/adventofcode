#include<array>
#include<vector>

class LayerInfo {
  public:
    LayerInfo( int width, int height ) : width_{ width }, height_{ height } {}
    void addPixel( int value );
    const std::vector<int>& getPixels() const { return pixels_; }
    int getPixel( int index ) const { return pixels_.at( index ); }
    int numDigit( int digit ) const;
    void printPixel( int row, int col ) const;
    void print() const;
  private:
    int width_, height_;
    std::vector<int> pixels_;
    std::array<int, 3> counts_{ 0, 0, 0 };
};

class Image {
  public:
    using Layer = std::vector<std::vector<int>>;
    Image( int width, int height, const std::vector<int>& input );
    const std::vector<LayerInfo>& getLayerInfos() const { return layers_; }
    LayerInfo decode() const;
    int decodePixel( int index ) const;
  private:
    int width_, height_;
    std::vector<LayerInfo> layers_;
};
