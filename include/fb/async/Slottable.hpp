#ifndef FB_SLOTTABLE_H
#define FB_SLOTTABLE_H

#include <vector>
#include <utility>
#include <cstdint>

#include "fb/async/AbstractSignal.hpp"

namespace fb {
    namespace async {
        /**
         * @brief Base class for all "observer" classes (see fb/async/Signal.hpp)
         */
        class Slottable {
            public:
                /**
                 * @brief Makes sure this object's callbacks are removed from their respective Signal's containers.
                 */
                ~Slottable();

                /**
                 * @brief Stores the callback ID as well as the Signal it is atteched to.
                 *
                 * @param lid Callback ID
                 * @param as Signal it is attached to
                 */
                void store(uint64_t lid, fb::async::AbstractSignal * as);

            private:
                std::vector<std::pair<uint64_t, fb::async::AbstractSignal *>> registeredSignals;           
        };
    }
}

#endif
