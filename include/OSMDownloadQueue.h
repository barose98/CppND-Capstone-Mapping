/*
 * CapstoneMappingQueue.h
 *
 *  Created on: May 8, 2020
 *      Author: Barrett Rose
 */

#ifndef SRC_CAPSTONEMAPPINGQUEUE_H_
#define SRC_CAPSTONEMAPPINGQUEUE_H_

#include <iostream>
#include <thread>
#include <queue>
#include <future>
#include <mutex>
#include <algorithm>
//#include "CapstoneMappingQueue_Impl.h"

template <class T>
class OSMDownloadQueue {
public:
    OSMDownloadQueue();
    ~OSMDownloadQueue();
    void push(T msg);
    T pull();
    bool hasMoreData();
private:
    std::mutex _mutex;
    std::condition_variable _cond;
    std::deque<T> xml_chunks;
    int total_size;
};

template<class T>
inline OSMDownloadQueue<T>::OSMDownloadQueue(): total_size(0)
{
    std::cout <<  "Queue Constructor "<<this<<std::endl;
}

template<class T>
inline OSMDownloadQueue<T>::~OSMDownloadQueue()
{
    std::cout <<  "Queue Destructor "<<this<<std::endl;
}

template<class T>
 void OSMDownloadQueue<T>::push(T data)
{
    // perform vector modification under the lock
    std::lock_guard<std::mutex> uLock(_mutex);
    xml_chunks.push_back(std::move(data));
    _cond.notify_one();
}

template<class T>
inline T OSMDownloadQueue<T>::pull()
{
    // perform queue modification under the lock
    std::unique_lock<std::mutex> uLock(_mutex);
    _cond.wait(uLock, [this] { return !xml_chunks.empty(); }); // pass unique lock to condition variable

    // remove last vector element from queue
    T chunk = std::move(xml_chunks.front());
    xml_chunks.pop_front();

    return chunk; // will not be copied due to return value optimization (RVO) in C++
}

template<class T>
inline bool OSMDownloadQueue<T>::hasMoreData()
{
    return xml_chunks.empty() ;
}

#endif /* SRC_CAPSTONEMAPPINGQUEUE_H_ */
