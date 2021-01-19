#include "lib.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

auto sqr(int a) { return a * a; }

auto bad_increment(int a) { return ++a; } // Не увеличивает переменную
auto increment(int &a) { return ++a; }

auto make_array(size_t my_size) {
    auto array = std::vector(my_size, 0);
    // ^ Создаёт массив длины my_size из нулей
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

    Person(std::string arg_name, int arg_age) { // как __init__ в python
        name = arg_name;
        age = arg_age;
    }
};

auto make_person(std::string name, int age) { return Person{name, age}; }

void print(Person const &person) {
    std::cout << "Person(\"" << person.name << "\", " << person.age << ")\n";
}

auto main() -> int { // or int main()
    std::cout << not_random() << "\n";
    std::cout << sqr(not_random()) << "\n";
    auto value = 0;
    std::cout << value << " ";
    std::cout << increment(value) << " "; // increment(3) - error
    std::cout << value << "\n";

    auto const my_size = 1024;
    // нельзя my_size = 1;
    auto array = make_array(my_size);
    std::cout << "Sum of variable array " << sum(array) << "\n";
    std::cout << "Sum of temporary array " << sum(make_array(my_size)) << "\n";

    auto john = Person{"John", 23};
    std::cout << "Person(\"" << john.name << "\", " << john.age << ")\n";
    john.age = 32;

    auto ptr = std::make_shared<Person>("Joe", 33);
    // std::shared_ptr<Person>(new Person{"Joe", 33})
    // new использовать не надо
    auto ptr2 = ptr;
    ptr2->student = false; // (*ptr2).student = false;
    std::cout << "Joe student=" << ptr->student << "\n";
    print(*ptr);
    auto &person_ref = *ptr;
    ptr = std::make_shared<Person>("Jack", 55);
    // На Joe остался 1 указатель
    print(person_ref);
    ptr2 = nullptr; // примерно то же, что None в python
    // Joe немедленно удаляется
    // ссылка person_ref содержит некорректное значение
    // читать и писать её нельзя
    // Мы говорим, что shared_ptr "владеет" объектом, на который ссылается
    // А ссылка не "владеет" им
    // Пока жив "владелец", живы все его "владения"

    struct List {
        int value;
        // auto std::make_shared<Type>(...) -> std::shared_ptr<Type>
        std::shared_ptr<List> next; // лучше не так
        List(int v) { value = v; }
        auto print() -> void {
            if (next) {
                std::cout << value << ", ";
                next->print();
            } else
                std::cout << value << "\n";
        }
    };

    auto list_ptr = std::make_shared<List>(1);
    list_ptr->next = list_ptr;
    // ^ Утечка памяти: list_ptr никогда не будет удалён
    list_ptr->next = std::make_shared<List>(2);
    list_ptr->print();
    // дописали в конец, теперь список длины 2
    {
        auto new_list_elem = std::make_shared<List>(3);
        new_list_elem->print();
        new_list_elem->next = list_ptr;
        new_list_elem->print();
        list_ptr = new_list_elem;
        list_ptr->print();
    } // здесь удаляется указатель new_list_elem
    // дописали в начало, теперь список длины 3

    struct List2 {
        int value;
        std::shared_ptr<List2> next;
        // std::shared_ptr<List2> prev; // Неминуемая утечка памяти
        // list2_ref будет владеть собой через list2_ref->next->prev
        std::weak_ptr<List2> prev;
        List2(int v) { value = v; }
    };
    auto list2_ref = std::make_shared<List2>(1);
    list2_ref->next = std::make_shared<List2>(2);
    list2_ref->next->prev = list2_ref;
    auto second = list2_ref->next;
    {
        auto second_prev = second->prev.lock();
        std::cout << "prev to second is " << second_prev->value << "\n";
    }

    struct Tree {
        std::shared_ptr<Tree> left, right; // лучше std::unique_ptr
    };
    return 0;
}