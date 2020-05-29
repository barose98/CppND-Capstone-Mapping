        /*
 * CapstoneMappingQueue.h
 *
 *  Created on: May 8, 2020
 *      Author: Barrett Rose
 */

#ifndef SRC_CAPSTONEDRAWINGQUEUE_H_
#define SRC_CAPSTONEDRAWINGQUEUE_H_

#include <iostream>
#include <thread>
#include <queue>
#include <future>
#include <mutex>
#include <algorithm>
#include "OSMQueue.h"
/**
The mapping Queue classes allow for repeated messaging between threads, with the message deques protected by locks, so as to avoid data races.

The drawing queue allows for repeated messaging between the data parsing thread and the main thread. The parsing thread pushes "true" booleans on to the queue while it is still drawing, and a "false" after it is done. This way the drawing area class can continuously redraw itself on its own timer, so that changes to the Cairo surface immediately appear to the user. Otherwise the user would have to move the window, drag the surface,  or maximize the window before the drawing area would redraw itself and drawn lines would be apparent. 

On a side note, both queue header files also contain the implementations of the methods. The linker was throwing up errors as the templated nature of the class seemed to be confusing it. This was my workaround. I'm sure there is a proper way to control the linker. 
*/

template <class T>
class OSMDrawingQueue  : OSMQueue<T>{
public:
    OSMDrawingQueue();
    ~OSMDrawingQueue();
    void push(T msg);
    T pull();
private:
    std::mutex _mutex;
    std::condition_variable _cond;
    std::deque<T> still_drawing;
};

template<class T>
inline OSMDrawingQueue<T>::OSMDrawingQueue()
{
//    std::cout <<  "Drawing Queue Constructor "<<this<<std::endl;
}

template<class T>
inline OSMDrawingQueue<T>::~OSMDrawingQueue()
{
//    std::cout <<  "Drawing Queue Destructor "<<this<<std::endl;
}

template<class T>
 void OSMDrawingQueue<T>::push(T data)
{
    // perform vector modification under the lock
    std::lock_guard<std::mutex> uLock(_mutex);
    still_drawing.push_back(std::move(data));
    _cond.notify_one();
}

template<class T>
inline T OSMDrawingQueue<T>::pull()
{
    // perform queue modification under the lock
    std::unique_lock<std::mutex> uLock(_mutex);
    _cond.wait(uLock, [this] { return !still_drawing.empty(); }); // pass unique lock to condition variable

    // remove last vector element from queue
    T chunk = std::move(still_drawing.front());
    still_drawing.pop_front();

    return chunk; // will not be copied due to return value optimization (RVO) in C++
}



#endif /* SRC_CAPSTONEDRAWINGQUEUE_H_ */
