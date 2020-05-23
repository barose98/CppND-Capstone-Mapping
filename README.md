# CPPND: Capstone Mapping

This is the repo for my Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

My favorite project in this course was the first one. I wasn't aware of the existence of the Open Street Maps project before I took this course, and was fascinated by the way it represents real world data. I wanted to undertake the downloading,  parsing, and ad hoc drawing of features defined in XML

I have lots more fatures to add. For example, I would like to implement some heuritics to differentiate ways that are lines and ways that are polygons. I will spend several more months working on more features, but I hope the code at this point is enough to demonstrate the skills I have acquired. 

I want to attribute the sites where I learned to utilize the GTK, Cairo, Expat, and Libcurl API's I did. I read lots of GTK and Cairo documentation. 
Specifically:

 - [https://developer.gnome.org/gtkmm/stable/classGtk_1_1Widget.html](https://developer.gnome.org/gtkmm/stable/classGtk_1_1Widget.html)
 - [https://www.cairographics.org/documentation/cairomm/reference/classCairo_1_1Surface.html](https://www.cairographics.org/documentation/cairomm/reference/classCairo_1_1Surface.html)
 - [https://www.cairographics.org/documentation/cairomm/reference/classCairo_1_1Context.html](https://www.cairographics.org/documentation/cairomm/reference/classCairo_1_1Context.html)

For Libcurl and Expat I relied heavily on example files. 

 - [https://curl.haxx.se/libcurl/c/htmltitle.html](https://curl.haxx.se/libcurl/c/htmltitle.html)
 - [https://curl.haxx.se/libcurl/c/xmlstream.html](https://curl.haxx.se/libcurl/c/xmlstream.html)

## Dependencies for Running Locally
  cmake >= 3.7
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
 * make >= 4.1 (Linux, Mac), 3.81 (Windows)
 * Linux: make is installed by default on most Linux distros
 * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
 * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)

 gcc/g++ >= 5.4
 * Linux: gcc / g++ is installed by default on most Linux distros
 * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
 * Windows: recommend using [MinGW](http://www.mingw.org/)



 gtkmm-3.0 >= 3.24.2

cairomm-1.0 version 1.12.2

expat version 2.2.9

libcurl version 7.68.0

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./capstone-mapping


## Running Instructions

