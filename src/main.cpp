#include "lib.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

auto sqr(int a) { return a * a; }

auto increment(int &a) { return ++a; }

auto make_array(size_t my_size) {
    auto array = std::vector(my_size, 0); // Создаёт массив длины 1024 из нулей
    for (size_t i = 0; i < my_size; ++i)
        array[i] = int(i);
    return array;
}

auto sum(std::vector<int> const &array) {
    int result = 0;
    for (int elem : array)
        result += elem;
    return result;
}

struct Person { // как @dataclass
    std::string name;
    int age;
    bool student = true;

    Person(std::string _name, int _age) { // как __init__ в python
        name = _name;
        age = _age;
    }
};

void print(Person const &person) {
    std::cout << "Person(\"" << person.name << "\", " << person.age << ")\n";
}

struct List {
    std::shared_ptr<List> next; // лучше не так
};

auto main() -> int { // or int main()
    std::cout << not_random() << "\n";
    std::cout << sqr(not_random()) << "\n";
    auto value = 0;
    std::cout << value << " ";
    std::cout << increment(value) << " "; // increment(3) - error
    std::cout << value << "\n";

    auto const my_size = 1024;
    // нельзя my_size = 1;
    std::cout << "Sum of array " << sum(make_array(my_size)) << "\n";

    auto john = Person{"John", 23};
    std::cout << "Person(\"" << john.name << "\", " << john.age << ")\n";
    john.age = 32;

    auto ptr = std::make_shared<Person>("Joe", 33);
    auto ptr2 = ptr;
    ptr2->student = false;
    std::cout << "Joe student=" << ptr->student << "\n";
    print(*ptr);

    auto list_ptr = std::make_shared<List>();
    list_ptr->next = list_ptr;
    // ^ Утечка памяти: list_ptr никогда не будет удалён
    return 0;
}