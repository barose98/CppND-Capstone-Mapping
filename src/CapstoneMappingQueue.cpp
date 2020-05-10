/*
 * CapstoneMappingQueue.cpp
 *
 *  Created on: May 8, 2020
 *      Author: roseba
 */

#include "CapstoneMappingQueue.h"

template<class T>
 void CapstoneMappingQueue<T>::push(T data, int num)
{
    // perform vector modification under the lock
    std::lock_guard<std::mutex> uLock(_mutex);
    _messages.push_back(std::move(data));
    total_size += num;
    std::cout <<  total_size <<std::endl;
    _cond.notify_one();
}

template<class T>
inline T CapstoneMappingQueue<T>::pull()
{
    return _messages.at(0);
}

template<class T>
inline int CapstoneMappingQueue<T>::getTotalSize()
{
    return total_size;
}
