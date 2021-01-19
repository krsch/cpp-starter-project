// import lib
#include "lib.hpp"
// import std
#include <iostream>
#include <map>
#include <string>
#include <vector>

// def main():
//     ...
// if __name__=="__main__": # есть всегда
//    main()                # есть всегда

// if __name__=="__main__":
auto main() -> int {                   // def main() -> int:
    std::cout << not_random() << "\n"; // print(not_random(),"\n")
    // std::cout <-> std.cout
    auto a = 3; // a = 3
    // int a_no_value; // без указания значения - не стоит так делать
    std::cout << "a = " << a << "\n"; // print("a = ", a, "\n")
    if (a == 3) {                     // if a == 3:
        auto b = a * a;
        std::cout << "b = " << b << "\n";
    } else { // b исчезает здесь
    }
    auto f = 0.1;
    std::cout << "f = " << f << "\n";
    auto s1 = std::string("abc"); // s1 = "abc"
    std::string s2 = "abc";       // s2 = "abc"
    using namespace std::literals; // позвояет использовать суффикс s
    auto s3 = "ab"s + "c"s;        // s3 = "ab" + "c"
    // суффикс s - преобразовать глупую строку в умную строку
    // "abc"s == std::string("abc")
    // Про умную строку читать
    // https://ru.cppreference.com/w/cpp/string/basic_string
    for (auto c : s1) { // for c in s1:
        std::cout << c << ", "s;
    }
    std::cout << "\n";
    // for (long i = 0; i < std::ssize(s3); ++i) { // C++20
    for (size_t i = 0; i < s3.size(); ++i) { // for i in range(0, len(s1))
        // ++i <=> i += 1
        std::cout << s3[i] << ", ";
    }
    std::cout << "\n";

    auto not_array = {1, 2, 3}; // глупый массив
    for (auto elem : not_array)
        std::cout << elem << ", ";
    std::cout << "\n";
    auto arr = std::vector{1, 2, 3}; // arr = [1,2,3]
    std::cout << "Array capacity was " << arr.capacity();
    arr.emplace_back(4); // arr.append(4) в python
    std::cout << " and changed to " << arr.capacity() << " but size is "
              << arr.size() << "\n";
    for (auto elem : arr) // Если не указать {}, в цикл входит всё до ;
        std::cout << elem << ", ";
    std::cout << "\n";

    auto arr2 = arr; // arr2 = arr.copy() или arr2 = arr[:], а не arr = arr2
    arr2[2] += 4;    // выглядит как в python
    arr2.at(1) += 4; // работает как в python
    // Меняя arr2 мы не меняем arr, что хорошо
    for (auto elem : arr)
        std::cout << elem << ", ";
    std::cout << " - arr\n";
    for (auto elem : arr2)
        std::cout << elem << ", ";
    std::cout << " - arr2\n";
    // std::cout << "This element does not exist: " << arr.at(4) << "\n";

    // auto bad = std::vector{1, 2, "1"s}; // - ошибка
    auto arr3 = std::vector<int>{}; // arr3 = [] или arr3 : List[int] = []
    // std::vector<int> arr3;
    arr3.emplace_back(1);
    std::vector arr4{1, 2, 3};
    auto array_of_strings = std::vector<std::string>{};

    auto dict = std::map<int, std::string>{{1, "one"}, {2, "two"}};
    // dict = {1: "one", 2: "two"}
    for (auto [key, value] : dict) // for key, value in dict.items()
        std::cout << "dict[" << key << "] = " << value << "\n";

    std::cout << "After change to dict2\n";

    auto &dict2 = dict;
    dict2[3] = "three";
    for (auto [key, value] : dict) // for key, value in dict.items()
        std::cout << "dict[" << key << "] = " << value << "\n";

    std::cout << "After assignment to dict2\n";
    dict2 = std::map<int, std::string>{{1, "one"}, {2, "two"}};
    for (auto [key, value] : dict) // for key, value in dict.items()
        std::cout << "dict[" << key << "] = " << value << "\n";

    std::cout << "After change of elements\n";
    for (auto &[key, value] : dict) // for key, value in dict.items()
        value += value;
    for (auto &[key, value] : dict) // for key, value in dict.items()
        std::cout << "dict[" << key << "] = " << value << "\n";

    return 0; // ОБЯЗАТЕЛЬНО!
} // a исчезает здесь