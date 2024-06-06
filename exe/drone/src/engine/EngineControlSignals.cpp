#include "EngineControlSignals.hpp"

#include "types.hpp"


EngineControlSignals::EngineControlSignals(std::initializer_list<T> init_list)
{
    StaticCheckedArray<EngineControlSignalType, ENGINE_COUNT>(init_list);
}


EngineControlSignals
EngineControlSignals::operator+(const EngineControlSignals& other) const
{
    auto add = [](EngineControlSignalType a, EngineControlSignalType b) {
        return a + b;
    };

    StaticCheckedArray<EngineControlSignalType, ENGINE_COUNT> new_signals;

    std::transform(
        data_.cbegin(),
        data_.cend(),
        other.cbegin(),
        new_signals.begin(),
        add
    );

    return EngineControlSignals();
}

EngineControlSignals
EngineControlSignals::operator-(const EngineControlSignals& other) const
{
    auto subtract = [](decltype(signals_) a, decltype(signals_) b) {
        return a - b;
    };

    StaticCheckedArray<decltype(signals_), 4> new_signals;

    std::transform(
        signals_.cbegin(),
        signals_.cend(),
        other.cbegin(),
        new_signals.begin(),
        subtract
    );

    return EngineControlSignals();
}