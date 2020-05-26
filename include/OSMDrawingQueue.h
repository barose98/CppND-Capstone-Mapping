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

template <class T>
class OSMDrawingQueue {
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
    std::cout <<  "Drawing Queue Constructor "<<this<<std::endl;
}

template<class T>
inline OSMDrawingQueue<T>::~OSMDrawingQueue()
{
    std::cout <<  "Drawing Queue Destructor "<<this<<std::endl;
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
