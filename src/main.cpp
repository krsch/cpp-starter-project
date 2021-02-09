#include "lib.hpp"
#include <algorithm>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <iostream>
#include <list>
#include <memory>
#include <vector>

template <typename T> struct List {
    // class и typename - одно и то же
    // Заменить все T на содержимое угловых скобок
    T value;
    std::unique_ptr<List<T>> next = nullptr;
    List() = default;
    List(T a_value) : value(a_value) {}
};

auto step01() {
    List<int> l1;
    List<char> l2;
}

template <typename T> List<T> make_list123() {
    List<T> result{1};
    result.next = std::make_unique<List<T>>(2);
    result.next->next = std::make_unique<List<T>>(3);
    return result;
}

template <typename T> List<T> make_listx3(T a, T b, T c) {
    using Res = List<T>;
    // typedef List<T> Res; // то же самое
    Res result{a};
    result.next = std::make_unique<Res>(b);
    result.next->next = std::make_unique<Res>(c);
    return result;
}

// Продвинутая тема!
template <typename T> List<T> make_list(T val) { return List<T>(val); }

template <typename T, typename... Args>
List<T> make_list(T first, Args... rest) {
    // py: make_list(first, *args)
    // auto rest2 = rest; // error
    List<T> result{first};
    result.next = std::make_unique<List<T>>(make_list(rest...));
    // py: make_list(*rest)
    return result;
}
// Конец продвинутой темы

auto smaller_than_4(int value) { return value < 4; }

auto step02() {
    auto vec = std::vector{1, 2, 3, 4};
    auto sm4 = std::all_of(vec.begin(), vec.end(), smaller_than_4);
    fmt::print("All is <4: {}\n", sm4);
    fmt::print("All positive: {}\n",
               std::all_of(vec.begin(), vec.end(),
                           [](int value) { return value > 0; }));
    auto N = 3;
    fmt::print("All not equal to {}: {}\n", N,
               std::all_of(vec.begin(), vec.end(),
                           [N](int value) { return value != N; }));
    // [N] - скопировать
    // [&N] - сохранить ссылку
    // [&] - сохранить сслыки на всё
    // [b = N] - скопировать N под именем b
    // [b = N*N] - создать переменную b со значением N*N
    // [=] - скопировать всё (нужно ли?)
    // [this] - скопировать указатель this (взять ссылку на текущий экземпляр
    //          класса)
    // auto l = [b=[](){return 1;}]() {return b();}; // так тоже работает
}

auto step03() {
    auto vec = std::vector{1, 2, 3, 4};
    // std::vector<int>::iterator
    auto it = std::find_if(vec.begin(), vec.end(),
                           [](int x) { return x * x > x + x; });
    // it указывает на 3
    --it; // Двигаемся назад, it указывает на 2
    it = vec.erase(it); // 2 удалено, it указывает на 3
    fmt::print("After erase: {}, it points to {} at pos {}\n", vec, *it,
               it - vec.begin());
    auto l = std::list{1, 2, 3, 4};
    for (auto lit = l.begin(); lit != l.end();)
        if (*lit % 2 == 0)
            lit = l.erase(lit);
        else
            ++lit;
    fmt::print("After loop with erase {}\n", l);
}

int main() {
  std::cout << not_random() << "\n";
  auto l = make_list123<int>();
  l = make_listx3(1, 2, 3);
  l = make_list(1, 2, 3);
  step02();
  step03();
  return 0;
}
