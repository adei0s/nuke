kernel fastDistort : ImageComputationKernel<ePixelWise> {
  Image<eRead, eAccessRandom, eEdgeClamped> src;  
  Image<eRead, eAccessPoint, eEdgeClamped> displacement; 
  Image<eWrite> dst;

  param:     
    float2 scale;
  local:

  void define() {  
  }

  void init() {
  }

  void process(int2 pos) {
    dst() = bilinear(src, pos.x+displacement().x * scale.x, pos.y+displacement().y * scale.y);
  }
};