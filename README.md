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
4. Run it:  `./capstone-mapping`


## Running Instructions
Enter the desired Latitude and Longitude, separated by a space. If you leave this blank and press enter, the application defaults to Asheville, NC. 

Wait for the map data to download and Cairo to draw the "ways". Urban areas with lots of streets and buildings the drawing takes much longer. Cairo drawing is very slow. If I had it to do over I would look for some faster way to do drawing.

After the drawing is complete, drag the map to pan around. This application is currently in the "proof of concept" phase. 

## Documentation
See the doc folder for automatically generated documentation. 

## Rubric
### Object Oriented Programming

All class members that are set to argument values are initialized through member initialization lists.
 [OSMDataParser.cpp](src/OSMDataParser.cpp#L11) line11

All class member functions document their effects, either through function names, comments, or formal documentation. Member functions do not change program state in undocumented ways.
[doc/html/functions.html](doc/html/functions.html)

Appropriate data and functions are grouped into classes. Member data that is subject to an invariant is hidden from the user. State is accessed via member functions. **SEVERAL CLASSES**


Inheritance hierarchies are logical. Composition is used instead of inheritance when appropriate. Abstract classes are composed of pure virtual functions. Override functions are specified.
 [OSMQueue.h](include/OSMQueue.h#L27) line27
 [CapstoneDrawingArea.h](include/CapstoneDrawingArea.h#L30-33) line30-33 


One function is overloaded with different signatures for the same function name.
 [CairoDrawer.h](include/CairoDrawer.h#L39-40) line39-40

One member function in an inherited class overrides a virtual base class member function.
 [OSMDrawingQueue.h](include/OSMDrawingQueue.h#L52) line52

One function is declared with a template that allows it to accept a generic parameter.
 [OSMDownloadQueue.h](include/OSMDownloadQueue.h#L50) line50
  [OSMDrawingQueue.h](include/OSMDrawingQueue.h#L54) line54

### Memory Management

At least two variables are defined as references, or two functions use pass-by-reference in the project code.  
 [OSMDataParser.h](include/OSMDataParser.h#L55) line55  
  [CairoDrawer.cpp](src/CairoDrawer.cpp#L39) line39

At least one class that uses unmanaged dynamically allocated memory, along with any class that otherwise needs to modify state upon the termination of an object, uses a destructor.
 [OSMDataParser.h](include/OSMDataParser.h#L132) line132
  [OSMDataParser.h](include/OSMDataParser.h#L171) line171  
  **That I remember this is the only place I explicitly allocate heap memory. **

The project follows the Resource Acquisition Is Initialization pattern where appropriate, by allocating objects at compile-time, initializing objects when they are declared, and utilizing scope to ensure their automatic destruction.
 [CapstoneMapping.cpp](src/CapstoneMapping.cpp#L14-16) line14-16

For all classes, if any one of the copy constructor, copy assignment operator, move constructor, move assignment operator, and destructor are defined, then all of these functions are defined.
 [OSMDataParser.cpp](src/OSMDataParser.cpp#L17-49) line17-49
  [OSMDownloader.cpp](src/OSMDownloader.cpp#L15-39) line15-39

For classes with move constructors, the project returns objects of that class by value, and relies on the move constructor, instead of copying the object.
 [CapstoneMapping.cpp](src/CapstoneMapping.cpp#L34) line 34

The project uses at least one smart pointer: unique_ptr, shared_ptr, or weak_ptr. The project does not use raw pointers.
 [CapstoneMapping.h](include/CapstoneMapping.h#L46-50) line46-50
 [CapstoneMapping.cpp](src/CapstoneMapping.cpp#L14) line14

### Concurrency
The project uses multiple threads in the execution.
 [CapstoneMapping.cpp](src/CapstoneMapping.cpp#L34) line34
 
A promise and future is used to pass data from a worker thread to a parent thread in the project code.
 [OSMDataParser.cpp](src/OSMDataParser.cpp#L154) line154
 
A mutex or lock (e.g. std::lock_guard or `std::unique_lock) is used to protect data that is shared across multiple threads in the project code.
 [OSMDownloadQueue.h](include/OSMDownloadQueue.h#L58) line58
  [OSMDrawingQueue.h](include/OSMDrawingQueue.h#L54) line54
  
A std::condition_variable is used in the project code to synchronize thread execution.
 [OSMDrawingQueue.h](include/OSMDrawingQueue.h#L56) line56
  [OSMDownloadQueue.h](include/OSMDownloadQueue.h#L60) line60

