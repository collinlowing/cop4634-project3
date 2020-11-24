/*
 * semaphore.cpp
 *
 *  Created on: Nov 18, 2020
 *      Author: Collin
 */

#include "semaphore.hpp"

Semaphore::Semaphore(int count)
{
	counter = count;
}

void Semaphore::signal()
{
	//std::unique_lock<std::mutex> lock(mtx);
	counter++;
	//std::cout << "thread " << threadID <<  " notify" << std::endl;
	//notify the waiting thread
	cv.notify_one();
}

void Semaphore::wait()
{
	std::unique_lock<std::mutex> lock(mtx);
	while(counter == 0)
	{
		//std::cout << "thread " << threadID << " wait" << std::endl;
		//wait on the mutex until notify is called
		cv.wait(lock);
		//std::cout << "thread " << threadID << " run" << std::endl;
	}
	counter--;
}

