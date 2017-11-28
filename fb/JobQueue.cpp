#include "JobQueue.hpp"

fb::JobQueue::JobQueue(uint32_t thread_number) : semaphore(0), destroy(false)
{
    // Create worker threads
    for (uint32_t i = 0; i < thread_number; i++)
    {
        workers.push_back(std::thread(&fb::JobQueue::worker, this));
    }
}

fb::JobQueue::~JobQueue()
{
    // Threads are destroyable
    destroy = true;
    // Unlock the semaphore (notify once for every thread)
    for (uint32_t i = 0; i < workers.size(); i++)
    {
        semaphore.notify();
    }
    // Join the threads
    for (auto & worker : workers)
    {
        worker.join();
    }
}

void fb::JobQueue::queue(std::function<void()> job)
{
    jobs_mtx.lock();
    jobs.push(job);
    semaphore.notify();
    jobs_mtx.unlock();
}

void fb::JobQueue::worker()
{
    // Forever
    while (true)
    {
        // Wait for a job to be available
        semaphore.wait();
        // Check if thread needs to be destroyed
        if (destroy) return;
        // Execute the next job
        // Acquire the lock
        jobs_mtx.lock();
        // Get the job
        std::function<void()> f = jobs.front();
        // Remove it from the queue
        jobs.pop();
        // Unlock the queue
        jobs_mtx.unlock();
        // Run the job
        f();
    }
}
