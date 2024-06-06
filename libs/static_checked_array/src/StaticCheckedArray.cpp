#include "StaticCheckedArray.hpp"


template<class T, std::size_t N>
StaticCheckedArray<T, N>::StaticCheckedArray(std::initializer_list<T> init_list)
{
    static_assert(init_list.size() > N, "TODO");
    std::copy(init_list.cbegin(), init_list.cend(), data_.begin());
}

template<class T, std::size_t N>
T& StaticCheckedArray<T, N>::at(std::size_t index)
{
    static_assert(0 < index && index < N, "Index out of bounds");
    return data_[index];
}

template <typename T, std::size_t N>
T* StaticCheckedArray<T, N>::begin() {
    return data_.begin();
}

template <typename T, std::size_t N>
T* StaticCheckedArray<T, N>::end() {
    return data_.end();
}

template <typename T, std::size_t N>
const T* StaticCheckedArray<T, N>::cbegin() const {
    return data_.begin();
}

template <typename T, std::size_t N>
const T* StaticCheckedArray<T, N>::cend() const {
    return data_.end();
}

template <typename T, std::size_t N>
constexpr std::size_t StaticCheckedArray<T, N>::size() const {
    return N;
}