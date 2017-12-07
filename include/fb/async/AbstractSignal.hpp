/**
 * @file AbstractSignal.hpp
 * @brief Contains only the AbstractSignal class.
 * @author Flat Bartender <flat.bartender@gmail.com>
 * @version 1.0.0
 * @date 2017-12-07
 */

#ifndef FB_ABSTRACTSIGNAL_H
#define FB_ABSTRACTSIGNAL_H

#include <cstdint>

// I'm not sure how to do this.
// Basically every signal needs to implement the disconnect() and connect() methods but not the emit method
// that would need this class to have a template, which isn't what I want
// (I want to be able to disconnect a callback when I destroy a class, mainly)

namespace fb::async {
    /**
     * @brief Enables Signal disconnecting on object destroy
     * This class isn't the common pattern each signal must follow.
     * It is here for the sole purpose of defining the common *disconnecting*
     * interface, so that objects that have a connection to a signal can
     * remove that connection when they're destroyed.
     */
    class AbstractSignal {
        public:
            /**
             * @brief Removes the specified callback from the callbacks container
             *
             * @param lid The callback ID
             */
            virtual void disconnect(uint64_t lid) = 0;
        protected:
            /**
             * @brief Stores the next free callback ID.
             */
            uint64_t nextFreeIndex;
    };
}

#endif
