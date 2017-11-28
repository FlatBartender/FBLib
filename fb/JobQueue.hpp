#ifndef FB_JOB_QUEUE_H
#define FB_JOB_QUEUE_H

#include <functional>
#include <thread>
#include <mutex>
#include <vector>
#include <queue>

#include "Semaphore.hpp"

namespace fb {
    class JobQueue {
        public: 
            JobQueue(uint32_t thread_number = 8);
            // Create a new job queue with thread_number worker threads
            
            ~JobQueue();

            void queue(std::function<void()> job);
            // Queues a job

        private:
            void worker();
            std::queue<std::function<void()>> jobs;
            std::mutex jobs_mtx;
            std::vector<std::thread> workers;
            fb::Semaphore semaphore;
            bool destroy;
    };
}

#endif
