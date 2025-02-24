kernel BlankKernel : ImageComputationKernel<ePixelWise> {
  Image<eRead, eAccessPoint, eEdgeClamped> src;  
  Image<eWrite> dst;
  param: 
  float4 weight;
  float4 sourceColor;
  float4 targetColor;
  float4 multiply;
      
  local:
  float4 output;
  void define() {
  }
  void init() {
  }
  void process() {    
    dst() = src();
  }
};