#pragma once

#include <cstddef>


template <class T, std::size_t N>
class StaticCheckedArray {
public:
    StaticCheckedArray() = default;
    StaticCheckedArray(std::initializer_list<T> init_list);

    T& at(std::size_t index);
    T* begin();
    T* end();
    const T* cbegin() const;
    const T* cend() const;
    constexpr std::size_t size() const;
private:
    std::array<T, N> data_;
};