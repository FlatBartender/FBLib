#ifndef FB_ABSTRACTSIGNAL_H
#define FB_ABSTRACTSIGNAL_H

#include <cstdint>

// I'm not sure how to do this.
// Basically every signal needs to implement the disconnect() and connect() methods but not the emit method
// that would need this class to have a template, which isn't what I want
// (I want to be able to disconnect a callback when I destroy a class, mainly)

namespace fb {
    class AbstractSignal {
        public:
            virtual void disconnect(uint64_t lid) = 0;
        protected:
            uint64_t nextFreeIndex;
    };
}

#endif
