#ifndef OFXV4L2LOOPBACK_H
#define OFXV4L2LOOPBACK_H

#include "libv4l2cpp/V4l2Device.h"
#include "libv4l2cpp/V4l2Capture.h"
#include "libv4l2cpp/V4l2Output.h"


#include <ofUtils.h>
#include <ofPixels.h>

class ofxV4l2loopback
{
public:
    ofxV4l2loopback();

    void setup(int width, int height, int device=2, int fps = 30);

    void update(ofPixels pix);

private:
    V4L2DeviceParameters *params;
    V4l2Output *virtualCam;

    void YUVfromRGB(double& Y, double& U, double& V, const double R, const double G, const double B);


};

#endif // OFXV4L2LOOPBACK_H
