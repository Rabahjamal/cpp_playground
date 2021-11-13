#ifndef TEMPLATES_H
#define TEMPLATES_H

#include <iostream>
#include <type_traits>
#include <vector>
#include <array>

// function template
template <typename T>
T absfun(T x)
{
    return (x >= 0) ? x : -x;
}

// class template
template <class T>
struct STM
{
    int sdm = 10;
};


// variable template
template<typename T>
const bool is_void_var = std::is_void<T>::value;

// C++11 alias template
template<typename T> using myvec = std::vector<T>;

// type deduction
template<typename T, typename U>
void f(T x, U y)
{
    puts(__PRETTY_FUNCTION__);
}

template<typename T>
void g(T x, T y)
{
    puts(__PRETTY_FUNCTION__);
}

template<typename T, typename U>
void foo(std::array<T, sizeof(U)> x,
         std::array<U, sizeof(T)> y,
         int z)
{
    puts(__PRETTY_FUNCTION__);
}

template<typename R, typename A>
void foo2(R (*fptr)(A))
{
    puts(__PRETTY_FUNCTION__);
}

template<typename T>
T add()
{
    puts(__PRETTY_FUNCTION__);
}

template<typename T>
void f(T& t)
{
    puts(__PRETTY_FUNCTION__);
}

template<typename T>
void f2(T&& t)
{
    puts(__PRETTY_FUNCTION__);
}

template<typename T>
void f3(void (*t)(T))
{
    puts(__PRETTY_FUNCTION__);
}

// variadic templates
template<typename T>
T adder(T v) {
  puts(__PRETTY_FUNCTION__);
  return v;
}

template<typename T, typename... Args>
T adder(T first, Args... args) {
  puts(__PRETTY_FUNCTION__);
  return first + adder(args...);
}

template<int D, typename T>
struct Vec : public std::vector<Vec<D - 1, T>> {
    static_assert(D >= 1, "Vector dimension must be greater than zero!");
    template<typename... Args>
    Vec(int n = 0, Args... args) : std::vector<Vec<D - 1, T>>(n, Vec<D - 1, T>(args...)) {
    }
};
template<typename T>
struct Vec<1, T> : public std::vector<T> {
    Vec(int n = 0, const T& val = T()) : std::vector<T>(n, val) {
    }
};

#include <sstream>

template <typename T>
void
write(std::stringstream& stream, const T& t) {
    stream.write((const char*)&t, sizeof(T));
    std::cout << sizeof(T) << std::endl;
}


#endif // TEMPLATES_H
