/*
 * CapstoneMappingQueue.h
 *
 *  Created on: May 8, 2020
 *      Author: roseba
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
class CapstoneMappingQueue {
public:
    CapstoneMappingQueue();
    ~CapstoneMappingQueue();
    void push(T msg, int num);
    T pull();
    int getTotalSize();
private:
    std::mutex _mutex;
    std::condition_variable _cond;
    std::deque<T> _xml_chunks;
    int total_size;
};

template<class T>
inline CapstoneMappingQueue<T>::CapstoneMappingQueue(): total_size(0)
{
    std::cout <<  "Queue Constructor "<<this<<std::endl;
}

template<class T>
inline CapstoneMappingQueue<T>::~CapstoneMappingQueue()
{
    std::cout <<  "Queue Destructor "<<this<<std::endl;
}

template<class T>
 void CapstoneMappingQueue<T>::push(T data, int num)
{
    // perform vector modification under the lock
    std::lock_guard<std::mutex> uLock(_mutex);
    _xml_chunks.push_back(std::move(data));
    total_size += num;
    _cond.notify_one();
}

template<class T>
inline T CapstoneMappingQueue<T>::pull()
{
    // perform queue modification under the lock
    std::unique_lock<std::mutex> uLock(_mutex);
    _cond.wait(uLock, [this] { return !_xml_chunks.empty(); }); // pass unique lock to condition variable

    // remove last vector element from queue
    T msg = std::move(_xml_chunks.front());
    _xml_chunks.pop_front();
    total_size -= sizeof(msg);
    //std::cout <<  total_size  <<std::endl;

    return msg; // will not be copied due to return value optimization (RVO) in C++
}

template<class T>
inline int CapstoneMappingQueue<T>::getTotalSize()
{
    return total_size;
}

#endif /* SRC_CAPSTONEMAPPINGQUEUE_H_ */
