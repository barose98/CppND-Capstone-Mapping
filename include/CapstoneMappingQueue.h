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

template <class T>
class CapstoneMappingQueue {
public:
//    CapstoneMappingQueue();
    void push(T msg, int num);
    T pull();
    int getTotalSize();
private:
    std::mutex _mutex;
    std::condition_variable _cond;
    std::deque<T> _messages;
    int total_size;
};




#endif /* SRC_CAPSTONEMAPPINGQUEUE_H_ */
