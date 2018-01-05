# pangolin

The project implements a python binding for 3D visualization library **[Pangolin](http://github.com/stevenlovegrove/Pangolin)**.

> Pangolin is a lightweight portable rapid development library for managing OpenGL
display / interaction and abstracting video input. At its heart is a simple
OpenGL viewport manager which can help to modularise 3D visualisation without
adding to its complexity, and offers an advanced but intuitive 3D navigation
handler. Pangolin also provides a mechanism for manipulating program variables
through config files and ui integration, and has a flexible real-time plotter
for visualising graphical data.  
The ethos of Pangolin is to reduce the boilerplate code that normally
gets written to visualise and interact with (typically image and 3D
based) systems, without compromising performance. It also enables write-once
code for a number of platforms, currently including Windows, Linux, OSX, Android
and IOS.

This binding is primarily written for SLAM related visualization in python, for convenience, I write some handy functions 
(DrawPoints, DrawLines, DrawCameras, DrawBoxes) for drawing point clouds, trajectory, poses and 3d bounding boxes. These functions can access numpy array directly, so are very efficient. Actually, this library has little python overload.  
Some of Pangolin's C++ functions are not wrapped, for implemented part, see [examples](python/examples)
or [Gallery](#Gallery) below.  


## Requirements
* C++: [dependencies](#Dependencies).   
This project also relies on [pybind11](https://github.com/pybind/pybind11), 
but it's built in this repository, you don't need to install.  
* Python: To run those python examples, 
you should have [numpy](http://www.numpy.org/) and [PyOpenGL](http://pyopengl.sourceforge.net/) installed. 


## Installation
```
git clone https://github.com/uoip/pangolin.git
cd pangolin
mkdir build
cd build
cmake ..
make -j8
cd ..
python setup.py install
```
Tested under Ubuntu 16.04, Python 3.6+.

## Getting started
The code below create a window, and render a cube and a cloud of points.
```python
import numpy as np
import OpenGL.GL as gl
import pangolin

pangolin.CreateWindowAndBind('Main', 640, 480)
gl.glEnable(gl.GL_DEPTH_TEST)

# Define Projection and initial ModelView matrix
scam = pangolin.OpenGlRenderState(
    pangolin.ProjectionMatrix(640, 480, 420, 420, 320, 240, 0.2, 100),
    pangolin.ModelViewLookAt(-2, 2, -2, 0, 0, 0, pangolin.AxisDirection.AxisY))
handler = pangolin.Handler3D(scam)

# Create Interactive View in window
dcam = pangolin.CreateDisplay()
dcam.SetBounds(0.0, 1.0, 0.0, 1.0, -640.0/480.0)
dcam.SetHandler(handler)

while not pangolin.ShouldQuit():
    gl.glClear(gl.GL_COLOR_BUFFER_BIT | gl.GL_DEPTH_BUFFER_BIT)
    gl.glClearColor(1.0, 1.0, 1.0, 1.0)
    dcam.Activate(scam)
    
    # Render OpenGL Cube
    pangolin.glDrawColouredCube()

    # Draw Point Cloud
    points = np.random.random((100000, 3)) * 10
    gl.glPointSize(2)
    gl.glColor3f(1.0, 0.0, 0.0)
    pangolin.DrawPoints(points)

    pangolin.FinishFrame()

```
As shown above, this library works seamlessly with PyOpenGL and numpy, it can access 
numpy array directly without copying data (thanks to [pybind11](https://github.com/pybind/pybind11)).  

## <a name="Gallery">Gallery</a>
**[HelloPangolin.py](python/examples/HelloPangolin.py)** (point cloud and 3d object):  
![](python/examples/imgs/HelloPangolinColorful.png)

**[SimpleDisplayImage.py](python/examples/SimpleDisplayImage.py)** (image and 3d object):  
![](python/examples/imgs/SimpleDisplayImage.png)
 
**[SimpleDisplayMenu.py](python/examples/SimpleDisplayMenu.py)** (basic GUI):  
![](python/examples/imgs/SimpleDisplayMenu.png)

**[SimpleMultiDisplay.py](python/examples/SimpleMultiDisplay.py)** (multiple display windows):  
![](python/examples/imgs/SimpleMultiDisplay.png)

**[SimplePlot.py](python/examples/SimplePlot.py)** (2d plot):  
![](python/examples/imgs/SimplePlot.png)

**[SimplePlotDisplay.py](python/examples/SimplePlotDisplay.py)** (2d plot and 3d object):  
![](python/examples/imgs/SimplePlotDisplay.png)

**[simple_draw.py](python/examples/simple_draw.py)** draw point clouds, camera/pose, 3d boxes, lines(consecutive or separate):  
![](python/examples/imgs/simple_draw.png)

## License
Follow **[Pangolin](http://github.com/stevenlovegrove/Pangolin)**, the C++ binding code and 
python example code of this project is released under MIT License.

## Contact
If you have problems related to **binding code/python interface/python examples** of this project, 
you can report isseus, or email me (qihang@outlook.com).




<br><br><br><br><br>
README of **[Pangolin](http://github.com/stevenlovegrove/Pangolin)**:

------------------------------------
------------------------------------
------------------------------------

What is Pangolin {#mainpage}
====================================

Pangolin is a lightweight portable rapid development library for managing OpenGL
display / interaction and abstracting video input. At its heart is a simple
OpenGl viewport manager which can help to modularise 3D visualisation without
adding to its complexity, and offers an advanced but intuitive 3D navigation
handler. Pangolin also provides a mechanism for manipulating program variables
through config files and ui integration, and has a flexible real-time plotter
for visualising graphical data.

The ethos of Pangolin is to reduce the boilerplate code that normally
gets written to visualise and interact with (typically image and 3D
based) systems, without compromising performance. It also enables write-once
code for a number of platforms, currently including Windows, Linux, OSX, Android
and IOS.

## Code ##

Find the latest version on [Github](http://github.com/stevenlovegrove/Pangolin):

```
git clone https://github.com/stevenlovegrove/Pangolin.git
```

## <a name="Dependencies">Dependencies</a>

Optional dependencies are enabled when found, otherwise they are silently disabled.
Check the CMake configure output for details.

### Required Dependencies ###

* C++11

* OpenGL (Desktop / ES / ES2)

* Glew
 * (win) built automatically (assuming git is on your path)
 * (deb) sudo apt-get install libglew-dev
 * (mac) sudo port install glew

* CMake (for build environment)
 * (win) http://www.cmake.org/cmake/resources/software.html
 * (deb) sudo apt-get install cmake
 * (mac) sudo port install cmake

### Recommended Dependencies ###

* Python2 / Python3, for drop-down interactive console
 * (win) http://www.python.org/downloads/windows
 * (deb) sudo apt-get install libpython2.7-dev
 * (mac) preinstalled with osx

### Optional Dependencies for video input ###

* FFMPEG (For video decoding and image rescaling)
 * (deb) sudo apt-get install ffmpeg libavcodec-dev libavutil-dev libavformat-dev libswscale-dev

* DC1394 (For firewire input)
 * (deb) sudo apt-get install libdc1394-22-dev libraw1394-dev

* libuvc (For cross-platform webcam video input via libusb)
 * git://github.com/ktossell/libuvc.git

* libjpeg, libpng, libtiff, libopenexr (For reading still-image sequences)
 * (deb) sudo apt-get install libjpeg-dev libpng12-dev libtiff5-dev libopenexr-dev

* OpenNI / OpenNI2 (For Kinect / Xtrion / Primesense capture)

* DepthSense SDK

### Very Optional Dependencies ###

* Eigen / TooN (These matrix types supported in the Pangolin API.)

* CUDA Toolkit >= 3.2 (Some CUDA header-only interop utilities included)
 * http://developer.nvidia.com/cuda-downloads

* Doxygen for generating html / pdf documentation.

## Building ##

Pangolin uses the CMake portable pre-build tool. To checkout and build pangolin in the
directory 'build', execute the following at a shell (or the equivelent using a GUI):

```
git clone https://github.com/stevenlovegrove/Pangolin.git
cd Pangolin
mkdir build
cd build
cmake ..
cmake --build .
```

If you would like to build the documentation and you have Doxygen installed, you
can execute:

```
cmake --build . --target doc
```

**On Windows**, Pangolin will attempt to download and build *glew*, *libjpeg*, *libpng* and *zlib* automatically. It does so assuming that git is available on the path - this assumption may be wrong for windows users who have downloaded Pangolin via a zip file on github. You will instead need to download and compile the dependencies manually, and set the BUILD_EXTERN_(lib) options to false for these libraries. The alternate and recommended approach is to install [gitbash](https://git-scm.com/downloads) and work from within their provided console.

## Issues ##

Please visit [Github Issues](https://github.com/stevenlovegrove/Pangolin/issues) to view and report problems with Pangolin. Issues and pull requests should be raised against the master branch which contains the current development version.

Please note; most Pangolin dependencies are optional - to disable a dependency which may be causing trouble on your machine, set the BUILD_PANGOLIN_(option) variable to false with a cmake configuration tool (e.g. ccmake or cmake-gui).

## Contributions and Continuous Integration ##

For CI, Pangolin uses [travis-ci.org](https://travis-ci.org/stevenlovegrove/Pangolin) for Ubuntu, OSX and [ci.appveyor.com](https://ci.appveyor.com/project/stevenlovegrove/pangolin) for Windows.

To contribute to Pangolin, I would appreciate pull requests against the master branch. This will trigger CI builds for your changes automatically, and help me to merge with confidence.

## Binaries ##

Binaries are available for Windows x64, as output by the Windows CI server: [Appveyor Artifacts](https://ci.appveyor.com/project/stevenlovegrove/pangolin/build/artifacts).

## Acknowledgements ##

I'd like to thank the growing number of kind contributors to Pangolin for helping to make it more stable and feature rich. Many features of Pangolin have been influenced by other projects such as GFlags, GLConsole, and libcvd in particular. I'd also like to thank the FOSS projects on which Pangolin depends.

For a summary of those who have made code contributions, execute:

```
git shortlog -sne
```
