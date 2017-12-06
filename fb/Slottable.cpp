#include "Slottable.hpp"

void fb::Slottable::store(uint64_t lid, fb::AbstractSignal * as)
{
    registeredSignals.push_back(std::make_pair(lid, as));
}

fb::Slottable::~Slottable()
{
    for (auto & connection : registeredSignals)
    {
        connection.second->disconnect(connection.first);
    }
}
