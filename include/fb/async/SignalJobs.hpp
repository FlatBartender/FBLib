#ifndef FB_SIGNALJOBS_H
#define FB_SIGNALJOBS_H

#include "fb/async/Signal.hpp"
#include "fb/async/JobQueue.hpp"

extern fb::async::JobQueue jq;

namespace fb::async {
    /**
     * @brief The same as fb::async::Signal except it queues callbacks as job in an extern fb::async::JobQueue.
     *
     * @tparam Args The arguments to be provided to the callbacks.
     */
    template<class ... Args> class SignalJobs : public fb::async::Signal<Args...> {
        public: 
            /**
             * @brief Creates a job from the callbacks and add it to the global job queue.
             *
             * @param args Arguments to pass to the callback.
             */
        void emit(Args... args)
        {
            for (auto & callback : fb::async::Signal<Args...>::callbacks)
            {
                jq.queue([callback, args...](){callback.second(args...);});
            }
        }
    };
}

#endif
