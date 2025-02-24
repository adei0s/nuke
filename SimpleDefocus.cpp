// simple defocus with any given matte
kernel SimpleDefocus : ImageComputationKernel<ePixelWise> {

  // Input and output images
  Image<eRead, eAccessRanged2D, eEdgeClamped> src;  // randomly accessing and edge clamping
  Image<eRead, eAccessPoint, eEdgeClamped> defocusMatte; // adding second input for matte
  Image<eWrite, eAccessPoint> dst;

// Parameters are made available to the user as knobs.

param:
  int maxSize; //max size of the defocus

  
local:

  void define() {
    defineParam(maxSize, "size", 0); //define size parameter with name and default value
  }

  // The init() function is run once before any calls to process().
  void init() {
    src.setRange(-maxSize, -maxSize, maxSize, maxSize);
  }

  // The process() function runs over all pixel positions of the output image.
  void process() {

    float4 output = 0; //output var for each pixel
    int normalizer = 0;
    int defocusedSize = maxSize * defocusMatte().w;

    if (defocusedSize > 0) { // prevent defocus tobe 0
      for(int y=-defocusedSize; y<=defocusedSize; y++){ 
        for(int x=-defocusedSize; x<=defocusedSize; x++){ 
          if(( defocusedSize - sqrt(pow(x,2) + pow(y,2))) > 0 ) { 
            output += src(x,y); //add pixel value to output
            normalizer += 1; //add to pixel count
          }
        }
      }
      output = output / normalizer; //normalize values to return average pixel value
    }
    else{
    output = src(0,0);
    }
    dst() = output;
  }
};
