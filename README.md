# ofxV4l2loopback

An openframeworks addon that allow to create virtual camera

This module use this lib:
[lbv4l2cpp](https://github.com/mpromonet/libv4l2cpp/tree/c165469e94521b767b548c2b34dcbb57a027bb01$)


## Intalation

1. Install **[v4l2loopback](https://github.com/umlaeute/v4l2loopback)**

⚠️ You must install kernel headers to do that because v4l2loopback is a kernel module

2. Create a virtual device
```sh
sudo modprobe v4l2loopback card_label="myCamNameHere" exclusive_caps=1
```

3. Clone this repo
```sh
cd /yourOfPath/addons
git clone https://github.com:Robotechnic/ofxV4l2loopback.git --recurse-submodules -j8
```

4. Include module in your project

* Whith qt:

Just add ofxV4l2loopback in addons:
```qbs
of.addons: [
    'ofxV4l2loopback'
]
```

* With project generator:

Add ofxV4l2loopback in addons.make file

## Usage
Firs, you need to init the camera:
```cpp
ofxV4l2loopback virtualcam;
virtualcam.setup(width,height,device,fps);

```
| parameter  | usage                                   |
|:----------:|:---------------------------------------:|
| width      | virtual device width                    |
| height     | virtual device height                   |
| device     | device number (Exemple: /dev/video**1**)|
| fps        | fps of device                           |

Then, you just need to update cam render at each frames:

```cpp
virtualcam.update(pixels)
```
| parameter  | usage                                   |
|:----------:|:---------------------------------------:|
| pixels     | ofPixel that contain your frame         |


## Examples

[https://github.com/Robotechnic/live_ascii_video](https://github.com/Robotechnic/live_ascii_video)
