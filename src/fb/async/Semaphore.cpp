/**
 * @file Semaphore.cpp
 * @brief Implementation for fb::async::Semaphore
 * @author Flat Bartender <flat.bartender@gmail.com>
 * @version 1.0.0
 * @date 2017-12-07
 */

#include "fb/async/Semaphore.hpp"

using namespace fb::async;

Semaphore::Semaphore(uint64_t count) : count(count)
{

}

void Semaphore::wait()
{
    std::unique_lock<std::mutex> lock(mtx);

    while (count == 0) cv.wait(lock);

    count--;
}

void fb::async::Semaphore::notify()
{
    std::unique_lock<std::mutex> lock(mtx);

    count++;

    cv.notify_one();
}

