#pragma once
#include <cstdarg>
#include <initializer_list>
#include <array>


template<typename Key, typename Value, std::size_t N>
class UniqueValueMap {
/*
A map with unique keys and values.
*/
public:
    template<typename... Pairs>
    constexpr UniqueValueMap(std::pair<Key, Value> first_pair, Pairs... other_pairs);
    constexpr Value at(Key key);
private:
    std::array<std::pair<const Key, const Value>, N> _data;
};


template<typename Key, typename Value, typename... Pairs>
UniqueValueMap(std::pair<Key, Value> first_pair, Pairs... other_pairs) -> UniqueValueMap<
    Key,
    Value,
    1 + sizeof...(other_pairs)>;


template<typename Key, typename Value, std::size_t N>
template<typename... Pairs>
constexpr UniqueValueMap<Key, Value, N>::UniqueValueMap(
    std::pair<Key, Value> first_pair, Pairs... other_pairs
) {
    static_assert(sizeof...(Pairs) == N - 1, "SAMPLE TEXT");

    std::array<std::pair<Key, Value>, N> all_new_pairs = {first_pair, other_pairs...};

    // for (auto new_pair : all_new_pairs) {
    //     for (auto existing_pair : _data) {
    //         static_assert(
    //             new_pair.first != existing_pair.first
    //             & new_pair.second != existing_pair.second
    //         );
    //     }
    // }
    // std::copy(all_new_pairs.begin(), all_new_pairs.end(), _data);

    constexpr auto is_unique = [](const auto& arr) {
        for (std::size_t i = 0; i < N; ++i) {
            for (std::size_t j = i + 1; j < N; ++j) {
                if (arr[i].first == arr[j].first || arr[i].second == arr[j].second) {
                    return false;
                }
            }
        }
        return true;
    };

    static_assert(is_unique(all_new_pairs), "Duplicate key or value found");
}

template <class KeyType, class ValueType, std::size_t N>
constexpr ValueType UniqueValueMap<KeyType, ValueType, N>::at(KeyType key) {
    std::optional<ValueType> value;
    for (auto pair : _data) {
        if (pair.first == key) {
            value = pair.second;
        }
    }
    static_assert(value.has_value());
    return value;
}