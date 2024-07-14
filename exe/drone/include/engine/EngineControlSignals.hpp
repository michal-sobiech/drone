#pragma once

#include <cstddef>

#include "StaticCheckedArray.hpp"

#include "types.hpp"

#define FRONT_RIGHT 0
#define FRONT_LEFT 1
#define BACK_LEFT 2
#define BACK_RIGHT 3

using EngineControlSignalType = float;
using ParentArrayType = StaticCheckedArray<EngineControlSignalType, ENGINE_COUNT>;

class EngineControlSignals: public StaticCheckedArray<EngineControlSignalType, ENGINE_COUNT> {
public:
    EngineControlSignals() = default;
    EngineControlSignals(std::initializer_list<T> init_list);

    EngineControlSignals operator+(const EngineControlSignals& other) const;
    EngineControlSignals operator-(const EngineControlSignals& other) const;
};