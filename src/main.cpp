// extern "C" { // - Если этого нет в .h файле
#include "lib.h"
//}
#include "lib.hpp"
#include <array>
#include <cstdio>
#include <functional>
#include <ios>
#include <iostream>
#include <fstream>
#include <memory>
#include <system_error>
#include <vector>

// auto fcloser = [](FILE *f) { return fclose(f); };
struct fcloser {
    auto operator()(FILE *f) const noexcept { return fclose(f); }
};
using unique_file = std::unique_ptr<FILE, struct fcloser>;

auto my_open(const char* filename, const char * mode = "r") {
    unique_file f_uniq{fopen(filename, mode)};
    if (f_uniq)
        return f_uniq;
    throw std::system_error(errno, std::generic_category());
}

struct freer {
    auto operator()(void *f) const noexcept { return free(f); }
};

int call(std::function<int(int)> fun, int arg) {
    return fun(arg);
}

template<typename Fun, typename ... Args>
auto call(Fun && f, Args&& ... args) { // Самый общий
    return f(std::forward<Args>(args)...);
}

template<typename Fun, typename Arg>
auto call(Fun f, Arg arg) {
    return f(arg);
}

int main() {
    std::cout << calc() << "\n";
    // int a[2]; // Не используйте C-шные массивы в коде на C++
    // sum(a); // ОШИБКА!!!!
    std::string s = "Hello!\n";
    {
        std::ofstream f("123.bin", std::ios_base::binary | std::ios_base::trunc);
        f << s;
    } // Здесь f закрывается

    std::string filename = "123.bin";
    unique_file f_uniq{fopen(filename.c_str(), "r")};
    // unique_file f_uniq{my_open(filename.c_str())};
    auto *f = f_uniq.get(); // Если не хотим каждый раз писать get()
    if (f_uniq) {
        std::string result;
        while (result.empty() || result.back() != '\n') {
            std::array<char, 4> buf;
            char *res = fgets(buf.data(), buf.size(), f);
            if (res != nullptr) result += res;
            else break;
        }
        std::cout << result;
    } else {
        if (errno == ENOENT)
            std::cerr << "File does not exist\n";
        else
            perror("While opening file");
    }
    // fclose(f); // Если нет unique_ptr

    std::unique_ptr<int, freer> ptr{make_buf(4)};
    auto fun = [](void* arg) {
        int *val = static_cast<int*>(arg);
        return *val;
    };
    int a = -3;
    std::cout << call_void(fun, &a) << std::endl;
    return 0;
}