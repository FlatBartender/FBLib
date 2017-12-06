#ifndef FB_SLOTTABLE_H
#define FB_SLOTTABLE_H

#include <vector>
#include <utility>
#include <cstdint>

#include "AbstractSignal.hpp"

namespace fb {
    class Slottable {
        public:
            ~Slottable();

            void store(uint64_t lid, fb::AbstractSignal * as);

        private:
            std::vector<std::pair<uint64_t, fb::AbstractSignal *>> registeredSignals;           
    };
}

#endif
