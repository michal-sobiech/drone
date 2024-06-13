#pragma once
#include <initializer_list>
#include <array>


template <class KeyType, class ValueType, std::size_t N>
class UniqueValueMap {
/*
A map with unique keys and values.
*/
public:
    UniqueValueMap(std::initializer_list<std::pair<const KeyType, const ValueType>> init_list);
private:
    std::array<std::pair<const KeyType, const ValueType>, N> _data;
};