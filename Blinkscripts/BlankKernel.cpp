kernel BlankKernel : ImageComputationKernel<ePixelWise> {
  Image<eRead, eAccessPoint, eEdgeClamped> src;  
  Image<eWrite> dst;

  param:     

  local:

  void define() {
  }

  void init() {
  }

  void process() {
    
    dst() = src();
  }
};