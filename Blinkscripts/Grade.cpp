kernel GradeKernel : ImageComputationKernel<ePixelWise> {
  Image<eRead, eAccessPoint, eEdgeClamped> src;
  Image<eWrite> dst;

  param:     
    float4 bp;
    float4 wp;
    float4 lift;
    float4 gain;
    float4 mult;
    float4 offset;
    float4 gamma;
    bool whiteclamp;
    bool blackclamp;

  local:
    float4 output;

  void define() {
    defineParam(bp, "blackpoint", float4(0.0f));
    defineParam(wp, "whitepoint", float4(1.0f));
    defineParam(lift, "lift", float4(0.0f));
    defineParam(gain, "gain", float4(1.0f));
    defineParam(mult, "multiply", float4(1.0f));
    defineParam(offset, "offset", float4(0.0f));
    defineParam(gamma, "gamma", float4(1.0f));
    defineParam(whiteclamp, "whiteclamp", bool(0));
    defineParam(blackclamp, "blackclamp", bool(0));
  }

  void init() {
  }

  void process() {
    output = src();
    output = (output - bp)/(wp - bp);
    output = output * (gain*mult - lift) + lift;
    output = output + offset;
  
    if(output.x >= 0.0f){
      output.x = pow(output.x, (1.0f/gamma.x));
    }
    if(output.y >= 0.0f){
      output.y = pow(output.y, (1.0f/gamma.y));
    }
    if(output.z >= 0.0f){
      output.z = pow(output.z, (1.0f/gamma.z));
    }
    if(output.w >= 0.0f){
      output.w = pow(output.w, (1.0f/gamma.w));
    }
    if( whiteclamp == 1 ){
      min(float4(1.0f), output);
    }
    if (blackclamp == 1){
      max(float4(0.0f), output);
    }
    dst() = output;
  }
};