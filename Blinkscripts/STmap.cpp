kernel STmap : ImageComputationKernel<ePixelWise> {
    Image<eRead, eAccessRandom, eEdgeClamped> src;  
    Image<eRead, eAccessPoint, eEdgeClamped> STmap; 
    Image<eWrite> dst;
  
    param: 
  
    local:
      int2 resolution; 
      float2 UV;
    
    void define() {  
    }
  
    void init() {
      resolution.x = src.bounds.width() - .5f;
      resolution.y = src.bounds.height() - .5f;
    }
  
    void process(int2 pos) {
      UV.x = STmap().x  * resolution.x - .5f;
      UV.y = STmap().y * resolution.y - .5f;
      dst() = bilinear(src, UV.x, UV.y);
    }
  };