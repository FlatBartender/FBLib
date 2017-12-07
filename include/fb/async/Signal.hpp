/**
 * @file Signal.hpp
 * @brief Defines Signal
 * @author Flat Bartender <flat.bartender@gmail.com>
 * @version 1.0.0
 * @date 2017-12-07
 */
#ifndef FB_SIGNAL_H
#define FB_SIGNAL_H

#include <functional>
#include <unordered_map>

#include "fb/async/AbstractSignal.hpp"
#include "fb/async/Slottable.hpp"

namespace fb {
    namespace async {
        /**
         * @brief The Signal class implement the Observed part of the Observer/Observed pattern.
         *
         * @tparam Args The arguments the signal will send to the slots
         */
        template<class ... Args> class Signal : fb::async::AbstractSignal {
            // Simple typedef to ease the class creation.
            typedef std::function<void(Args...)> callback_t;
            public:
            /**
             * @brief "Emits" the signal (calls every callback with the provided arguments)
             *
             * @param args Arguments to pass to the callbacks
             */
            void emit(Args... args)
            {
                for (auto & callback : callbacks)
                {
                    callback.second(args...);
                }
            }

            /**
             * @brief Synonym for emit(args)
             *
             * @param args Arguments to pass to the callbacks
             */
            void operator()(Args... args)
            {
                emit(args...);
            }

            /**
             * @brief Add a lonely callback to the callbacks container
             *
             * @param callback Callback to add
             */
            void connect(callback_t callback)
            {
                callbacks[nextFreeIndex++] = callback;
            }

            /**
             * @brief Adds an object's method call to the callbacks
             * This function makes sure that when the object is destroyed the callback is removed from the container.
             *
             * @tparam X Class of the method to call
             * @tparam Y Class of the object to call the method on
             * @param on Object to call the mehtod *on*
             * @param apply Method to call on the object
             */
            template<class X, class Y> void connect(Y * on, void (X::*apply)(Args...))
            {
                static_assert(std::is_base_of<fb::async::Slottable, Y>::value);
                auto lambda = [on, apply](Args... args){(on->*apply)(args...);};
                callbacks[nextFreeIndex] = lambda;
                on->store(nextFreeIndex++, this);
            }

            /**
             * @brief Removes the specified callback from the container.
             * Currently, this function is not design for end-user usage.
             *
             * @param lid The callback's ID.
             */
            void disconnect(uint64_t lid)
            {
                callbacks.erase(lid);
            }

            /**
             * @brief Remove all callbacks from the container.
             */
            void clear()
            {
                callbacks.clear();
            }

            /**
             * @brief Check if the container is empty
             *
             * @return true if it is empty, false if it isn't.
             */
            bool empty()
            {
                return callbacks.empty();
            }

            protected:
            /**
             * @brief Holds the callbacks of this signal.
             */
            std::unordered_map<uint64_t, callback_t> callbacks;
        };
    }
}

#endif
