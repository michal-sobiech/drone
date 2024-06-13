#include "UniqueValueMap.hpp"
#include <initializer_list>
#include <vector>


// TODO const????
template <class KeyType, class ValueType, std::size_t N> 
UniqueValueMap<KeyType, ValueType, N>::UniqueValueMap(
    std::initializer_list<std::pair<const KeyType, const ValueType>> init_list
) {
    static_assert(init_list.size() == N, 'SAMPLE TEXT');
    if 
    for (auto new_pair : init_list) {
        for (auto exisiting_pair : _data) {
            static_assert(
                new_pair.first != existing_pair.first
                & new_pair.second != exisitng_pair.second
            );
        }
        _data.push_back(new_pair);
    }
}


