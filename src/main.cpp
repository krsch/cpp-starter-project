// import lib
#include "lib.hpp"
// import std
#include <cctype>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

// def main():
//     ...
// if __name__=="__main__": # есть всегда
//    main()                # есть всегда

// if __name__=="__main__":
auto main() -> int {                   // def main() -> int:
                                       // или int main()
    std::cout << not_random() << "\n"; // print(not_random(),"\n")
    // std::cout <-> std.cout
    auto a = 3; // a = 3
    // int a_no_value; // без указания значения - не стоит так делать
    // auto a = int(3);
    // auto a = int{3};
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
    auto s_utf8 = u8"ab"s;
    auto s_utf16 = u"ab"s;
    auto s_utf32 = U"ab"s;
    auto s_wide = L"ab"s;
    for (auto c : s1) { // for c in s1:
        std::cout << c << ", "s;
    }
    std::cout << "\n";
    // for (long i = 0; i < std::ssize(s3); ++i) { // C++20
    // for (decltype(s3.size()) i = 0; i < s3.size(); ++i) {
    for (auto i = std::size_t{0}; i < s3.size();
         ++i) { // for i in range(0, len(s3))
        // size_t почти наверняка unsigned long
        // ++i <=> i += 1
        std::cout << s3[i] << ", ";
    }
    std::cout << "\n";

    auto my_set = std::set{1, 2, 4}; // my_set = {1,2,4}
    // count возвращает, сколько раз встречается аргумент в множестве (0 или 1)
    if (my_set.contains(3)) { // if 3 in my_set:
        my_set.erase(3);      //     my_set.remove(3)
    } else                    // else:
        my_set.insert(3);     //     my_set.add(3)

    auto empty_set = std::set<int>{}; // empty_set = {}

    std::locale locale{""};
    auto symbol = 'C';
    std::cout << "Symbol '" << symbol << "', upper is '"
              << std::toupper(symbol, locale) << "', lower is '"
              << std::tolower(symbol, locale) << "'"
              << (std::isalpha(symbol, locale) ? ", it is letter" : "")
              //^ ", it is letter" if symbol.isalpha() else ""
              << "\n";

    auto not_array = {1, 2, 3}; // глупый массив
    for (auto elem : not_array)
        std::cout << elem << ", ";
    std::cout << "\n";
    auto arr = std::vector{0, 1, 2, 3}; // arr = [0,1,2,3]
    std::cout << "Array capacity was " << arr.capacity();
    arr.push_back(4); // arr.append(4) в python
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
    arr3.push_back(1);
    std::vector arr4{1, 2, 3};
    auto array_of_strings = std::vector<std::string>{};

    auto [a1, a2] = std::tuple{1, "str"s}; // a1, a2 = (1, "str")

    auto dict = std::map<int, std::string>{{1, "one"}, {2, "two"}};
    // dict = {1: "one", 2: "two"}
    for (auto [key, value] : dict) // for key, value in dict.items()
        std::cout << "dict[" << key << "] = " << value << "\n";

    std::cout << "After change of elements\n";
    for (auto &[key, value] : dict) // for key in dict:
        value += value;             //     dict[key] += dict[key]
    for (auto &[key, value] : dict) // for key, value in dict.items()
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

    return 0; // ОБЯЗАТЕЛЬНО!
} // a исчезает здесь