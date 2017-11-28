#ifndef FB_SEMAPHORE_H
#define FB_SEMAPHORE_H

#include <mutex>
#include <condition_variable>
#include <cstdint>

namespace fb {
    class Semaphore {
        public:
            Semaphore(uint64_t count = 0) : count(count) {};

            void wait() {
                std::unique_lock<std::mutex> lock(mtx);

                while (count == 0) cv.wait(lock);

                count--;
            }
            
            void notify() {
                std::unique_lock<std::mutex> lock(mtx);
                
                count++;

                cv.notify_one();
            }

        private:
            std::mutex mtx;
            std::condition_variable cv;
            uint64_t count;
    };
}

#endif
