/**
 * @file JobQueue.hpp
 * @brief Defines JobQueue
 * @author Flat Bartender <flat.bartender@gmail.com>
 * @version 1.0.0
 * @date 2017-12-07
 */

#ifndef FB_JOB_QUEUE_H
#define FB_JOB_QUEUE_H

#include <functional>
#include <thread>
#include <mutex>
#include <vector>
#include <queue>

#include "fb/async/Semaphore.hpp"

namespace fb::async {
    /**
     * @brief Implements the jobs parallelism pattern
     * Jobs are function with parameters already resolved.
     * They're queued, and when a thread is available, they're
     * run.
     */
    class JobQueue {
        public: 
            /**
             * @brief Creates the worker threads and initializes the semaphore.
             *
             * @param thread_number The number of threads the JobQueue will use (default: 8)
             */
            JobQueue(uint32_t thread_number = 8);
            
            /**
             * @brief Signals the threads to finish operating, joins them and returns.
             */
            ~JobQueue();

            /**
             * @brief Queue a job
             *
             * @param job A function returning void and taking 0 arguments (the job function).
             */
            void queue(std::function<void()> job);

        protected:
            /**
             * @brief A worker's handling function.
             */
            void worker();
            /**
             * @brief Holds the available job list.
             */
            std::queue<std::function<void()>> jobs;
            /**
             * @brief To synchronize the multiple workers so that no job is executed twice.
             */
            std::mutex jobs_mtx;
            /**
             * @brief Contains all the workers allocated by the JobQueue.
             */
            std::vector<std::thread> workers;
            /**
             * @brief To synchronize the multiple workers so that they wake up when a job is available.
             */
            fb::async::Semaphore semaphore;
            /**
             * @brief So signal the threads they need to deactivate themselves (used when the JobQueue will be destroyed).
             */
            bool destroy;
    };
}

#endif
