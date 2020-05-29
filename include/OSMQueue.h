/*
 * CapstoneMappingQueue.h
 *
 *  Created on: May 8, 2020
 *      Author: Barrett Rose
 */

#ifndef SRC_MAPPINGQUEUE_H_
#define SRC_MAPPINGQUEUE_H_

#include <iostream>
#include <thread>
#include <queue>
#include <future>
#include <mutex>
#include <algorithm>
/**
The mapping Queue classes allow for repeated messaging between threads, with the message deques protected by locks, so as to avoid data races.

This file allows for safe messaging between the downloading thread and the data parsing thread. 
Here in the downloader thread,  the data parsing class must access the XML data chunks in the exact order the are downloaded over http. The downloader class pushes the chunks onto the back of the queue, and the parser class pulls them off the front. This way the XML chunks are reassembled exactly as they were downloaded, preserving the well-formedness. 

On a side note, both queue header files also contain the implementations of the methods. The linker was throwing up errors as the templated nature of the class seemed to be confusing it. This was my workaround. I'm sure there is a proper way to control the linker. 

*/
template<class T>
class OSMQueue {
public:
    virtual void push(T msg) = 0;
    virtual T pull()=0;

};


#endif /* SRC_CAPSTONEMAPPINGQUEUE_H_ */
