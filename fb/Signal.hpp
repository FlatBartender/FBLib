#ifndef FB_SIGNAL_H
#define FB_SIGNAL_H

#include <functional>
#include <unordered_map>

#include "AbstractSignal.hpp"
#include "Slottable.hpp"

namespace fb {
    // After a lot of reflection on how best to implement this, I think a list is the most sensible.
    // Usually, most overhead would come from iteration (at least in the applications I'm thinking of).
    // Iteration is O(n) on all containers, and on a list it only has 1 pointer dereferencing for each item
    // (compared to an array or vector where it's just literally jumping to the next cell)
    // Some would come from insertion (which is O(1) on lists), and then there's deletion
    // Calling an invalid callback should (hopefully) throw an exception, so we can catch it and delete the invalid callback.
    // This operation is O(1) on lists (deleting when we have the iterator)
    // Deleting when we don't is O(n).
    //
    // Potential bugs: if no exception is thrown when an invalid callback is called, uh...
    // I'll have to make a "delegation" object, for example a slot or something like that
    // that would be in the "called" class, and have a list of all the signals it's connected to
    // so it could remove itself from all the signals when it's destroyed.
    template<class ... Args> class Signal : AbstractSignal {
        typedef std::function<void(Args...)> callback_t;
        public:
        // Call every element of callbacks with provided arguments
        void emit(Args... args)
        {
            for (auto & callback : callbacks)
            {
                callback.second(args...);
            }
        }

        // Calls emit(args)
        void operator()(Args... args)
        {
            emit(args...);
        }

        // Add callback to the callbacks container
        void connect(callback_t callback)
        {
            callbacks[nextFreeIndex++] = callback;
        }

        // Add callback to the callbacks container, but callback is element of class
        template<class X, class Y> void connect(Y * on, void (X::*apply)(Args...))
        {
            static_assert(std::is_base_of<fb::Slottable, Y>::value);
            auto lambda = make_lambda(on, apply);
            callbacks[nextFreeIndex] = lambda;
            on->store(nextFreeIndex++, this);
        }

        void disconnect(uint64_t lid)
        {
            callbacks.erase(lid);
        }

        // Remove all callbacks from the container
        void clear()
        {
            callbacks.clear();
        }

        // Check if the callbacks container is empty
        bool empty()
        {
            return callbacks.empty();
        }

        protected:
        template<class X, class Y> callback_t make_lambda(Y * on, void (X::*apply)(Args...))
        {
            static_assert(std::is_base_of<fb::Slottable, Y>::value);
            return [on, apply](Args... args){(on->*apply)(args...);};
        }

        std::unordered_map<uint64_t, callback_t> callbacks;
    };
}

#endif
