// import lib
#include "lib.hpp"
// import std
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std::literals;

// if __name__=="__main__":
auto main() -> int {                   // def main() -> int:
    std::cout << not_random() << "\n"; // print(not_random(),"\n")
    // std::cout <-> std.cout
    auto a = 3;
    std::cout << "a = " << a << "\n"; // print("a = ", a, "\n")
    if (a == 3) {                     // if a == 3:
        auto b = a * a;
        std::cout << "b = " << b << "\n";
    } // b исчезает здесь
    auto f = 0.1;
    auto s1 = std::string("abc"); // s1 = "abc"
    std::string s2 = "abc";       // s2 = "abc"
    auto s3 = "ab"s + "c"s;       // s3 = "abc"
    // суффикс s - преобразовать глупую строку в умную строку
    // Про умную строку читать
    // https://ru.cppreference.com/w/cpp/string/basic_string
    for (auto c : s1) { // for c in s1:
        std::cout << c << ", "s;
    }
    std::cout << "\n";
    auto arr = std::vector{1, 2, 3}; // arr = [1,2,3]
    std::cout << "Array capacity was " << arr.capacity();
    arr.emplace_back(4);
    std::cout << " and changed to " << arr.capacity() << " but size is "
              << arr.size() << "\n";
    // std::cout << "This element does not exist: " << arr.at(4) << "\n";
    for (auto elem : arr) // Если не указать {}, в цикл входит всё до ;
        std::cout << elem << ", ";
    std::cout << "\n";

    auto arr2 = arr; // arr2 = arr.copy() или arr2 = arr[:]
    arr2[2] = 5;     // выглядит как в python
    arr2.at(1) = 6;  // работает как в python
    // Меняя arr2 мы не меняем arr, что хорошо
    for (auto elem : arr)
        std::cout << elem << ", ";
    std::cout << " - arr\n";
    for (auto elem : arr2)
        std::cout << elem << ", ";
    std::cout << " - arr2\n";

    // std::vector{1, "1"} - ошибка
    auto arr3 = std::vector<int>{}; // arr3 = [] или arr3 : List[int] = []
    arr.emplace_back(1);
    auto array_of_strings = std::vector<std::string>{};

    auto dict = std::map<int, std::string>{{1, "one"}, {2, "two"}};
    // dict = {1: "one", 2: "two"}
    for (auto [key, value] : dict) // for key, value in dict.items()
        std::cout << "dict[" << key << "] = " << value << "\n";

    return 0; // ОБЯЗАТЕЛЬНО!
} // a исчезает здесь

// def main():
//     ...
// if __name__=="__main__": # есть всегда
//    main() # есть всегда