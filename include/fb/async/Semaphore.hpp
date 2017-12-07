/**
 * @file Semaphore.hpp
 * @brief Defines Semaphores
 * @author Flat Bartender <flat.bartender@gmail.com>
 * @version 1.0.0
 * @date 2017-12-07
 */
#ifndef FB_SEMAPHORE_H
#define FB_SEMAPHORE_H

#include <mutex>
#include <condition_variable>
#include <cstdint>

namespace fb {
    namespace async {
        /**
         * @brief Implements a Semaphore
         */
        class Semaphore {
            public:
                /**
                 * @brief Creates a new semaphore
                 *
                 * @param count Initial value of the semaphore (default: 0)
                 */
                Semaphore(uint64_t count = 0);

                /**
                 * @brief Suspend the current thread until the semaphore is notified
                 */
                void wait();

                /**
                 * @brief Notify the semaphore (increment it)
                 */
                void notify();
            private:
                std::mutex mtx;
                std::condition_variable cv;
                uint64_t count;
        };
    }
}

#endif
