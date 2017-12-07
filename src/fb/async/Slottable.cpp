/**
 * @file Slottable.cpp
 * @brief Implementation of fb::async::Slottable
 * @author Flat Bartender <flat.bartender@gmail.com>
 * @version 1.0.0
 * @date 2017-12-07
 */
#include "fb/async/Slottable.hpp"

using namespace fb::async;

void Slottable::store(uint64_t lid, fb::async::AbstractSignal * as)
{
    registeredSignals.push_back(std::make_pair(lid, as));
}

Slottable::~Slottable()
{
    for (auto & connection : registeredSignals)
    {
        connection.second->disconnect(connection.first);
    }
}
