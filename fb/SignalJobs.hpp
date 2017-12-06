#ifndef FB_SIGNALJOBS_H
#define FB_SIGNALJOBS_H

#include "Signal.hpp"
#include "JobQueue.hpp"

extern fb::JobQueue jq;

namespace fb {
    template<class ... Args> class SignalJobs : public fb::Signal<Args...> {
        public: 
        void emit(Args... args)
        {
            for (auto & callback : fb::Signal<Args...>::callbacks)
            {
                jq.queue([callback, args...](){callback.second(args...);});
            }
        }
    };
}

#endif
