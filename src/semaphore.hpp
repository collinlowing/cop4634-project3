/*
 * semaphore.hpp
 *
 *  Created on: Nov 18, 2020
 *      Author: Collin
 */

#ifndef SEMAPHORE_HPP_
#define SEMAPHORE_HPP_

#include <mutex>
#include <condition_variable>
#include <iostream>

class Semaphore {
private:
	int counter;

	std::mutex mtx;
	std::condition_variable cv;
public:
	Semaphore(int count);
	void signal();
	void wait();
};

#endif /* SEMAPHORE_HPP_ */
