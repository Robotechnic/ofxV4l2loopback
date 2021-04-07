#include "ofxV4l2loopback.h"


ofxV4l2loopback::ofxV4l2loopback()
{

}

void ofxV4l2loopback::setup(int width, int height, int device, int fps){
    //init virtual cam with given parameters
    params = new V4L2DeviceParameters(("/dev/video"+ofToString(device)).c_str(),V4L2_PIX_FMT_UYVY,width,height,fps,IOTYPE_MMAP);
    virtualCam = V4l2Output::create(*params);

    if (virtualCam == NULL){
        ofLogError()<<"Cannot create V4L2 output interface for device : /dev/video" + ofToString(device);
        return;
    }

    ofLog()<<"Device /dev/video" + ofToString(device) + "was corectly initialised";
}

void ofxV4l2loopback::YUVfromRGB(double &Y, double &U, double &V, const double R, const double G, const double B){
    //convert RGB values to YUV values
    Y =  0.257 * R + 0.504 * G + 0.098 * B +  16;
    U = -0.148 * R - 0.291 * G + 0.439 * B + 128;
    V =  0.439 * R - 0.368 * G - 0.071 * B + 128;

//    Y = R *  .299000 + G *  .587000 + B *  .114000;
//    U = R * -.168736 + G * -.331264 + B *  .500000 + 128;
//    V = R *  .500000 + G * -.418688 + B * -.081312 + 128;
}

void ofxV4l2loopback::update(ofPixels pix){
    if (virtualCam == NULL){
        ofLogError()<<"Device was not initialised or corectly created";
        return;
    }

    //init pixel buffer
    int bufferSize = virtualCam->getBufferSize();
    char buffer[bufferSize];

    double yc,uc,vc;
    ofColor c;

    int width = virtualCam->getWidth();

    //fill buffer with colors in yuv code
    for (int y = 0; y<(int)virtualCam->getHeight(); y++)
        for (int x = 0; x<width; x++){
            c = pix.getColor(x,y);
            YUVfromRGB(yc,uc,vc,c.r,c.g,c.b);



            buffer[(y * width + x)*2] = uc;
            buffer[(y * width + x)*2 + 1] = yc;
            buffer[(y * width + x)*2 + 2] = vc;
        }

    //write image to cam
    virtualCam->write(buffer,bufferSize);

}
