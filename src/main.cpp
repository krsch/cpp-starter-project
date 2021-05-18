// extern "C" { // - Если этого нет в .h файле
#include "lib.h"
//}
#include "lib.hpp"
#include <array>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <functional>
#include <ios>
#include <iostream>
#include <memory>
#include <string>
#include <system_error>
#include <vector>

// auto fcloser = [](FILE *f) { return fclose(f); };
struct fcloser {
    auto operator()(FILE *f) const noexcept { return fclose(f); }
};
using unique_file = std::unique_ptr<FILE, struct fcloser>;

auto my_open(const char *filename, const char *mode = "r") {
    unique_file f_uniq{fopen(filename, mode)};
    if (f_uniq)
        return f_uniq;
    throw std::system_error(errno, std::generic_category());
}

struct freer {
    auto operator()(void *f) const noexcept { return free(f); }
};

int call(std::function<int(int)> fun, int arg) { return fun(arg); }

template <typename Fun, typename... Args>
auto call(Fun &&f, Args &&...args) { // Самый общий
    return f(std::forward<Args>(args)...);
}

template <typename Fun, typename Arg> auto call(Fun f, Arg arg) {
    return f(arg);
}

int call(std::function<int()> fun) { return fun(); }

void memory_mgmt() {
    int *num = new int;
    *num = 3;
    delete num;
    int *num2 = new int(2);
    delete num2;
    const int sz = 1024;
    int *mem = new int[sz];
    mem[sz - 1] = 0;
    delete[] mem;
    std::unique_ptr<int> num3{new int};
    std::unique_ptr<int[]> mem3{new int[sz]};
    std::vector<int> mem4(sz);
}

int main(int argc, char *argv[]) {
    for (int i = 0; i < argc; ++i)
        std::cout << argv[i] << "\n";
    std::cout << calc() << "\n";
    // int a[2]; // Не используйте C-шные массивы в коде на C++
    // sum(a); // ОШИБКА!!!!
    {
        std::string s = "Hello!\n";
        std::ofstream f("123.bin",
                        std::ios_base::binary | std::ios_base::trunc);
        f << s;
    } // Здесь f закрывается
    {
        std::string filename = "123.bin";
        unique_file f_uniq{fopen(filename.c_str(), "r")};
        // unique_file f_uniq{my_open(filename.c_str())};
        if (f_uniq) {
            auto *f = f_uniq.get(); // Если не хотим каждый раз писать get()
            std::string result;
            while (result.empty() || result.back() != '\n') {
                std::array<char, 4> buf;
                char *res = fgets(buf.data(), buf.size(), f);
                if (res != nullptr)
                    result += res;
                else
                    break;
            }
            std::cout << result;
        } else {
            if (errno == ENOENT)
                std::cerr << "File does not exist\n";
            else
                perror("While opening file");
        }
    }
    // fclose(f); // Если нет unique_ptr

    const size_t buf_len = 4;
    auto ptr = std::unique_ptr<int[], freer>{make_buf(buf_len)};
    for (size_t i = 0; i < buf_len; ++i)
        std::cout << ptr[i] << ", ";
    std::cout << "\n";

    std::cout << call_c([](int a){return a*a;}, 2) << "\n";

    auto fun = [](void *arg) {
        int *val = static_cast<int *>(arg);
        return *val* *val;
    };
    int a = -3;
    std::cout << call_void(fun, &a) << std::endl;

    auto fun2 = [](void *arg) {
        float *val = static_cast<float *>(arg);
        return static_cast<int>(std::lround(*val));
    };
    float b = -3.2f;
    std::cout << call_void(fun2, &b) << std::endl;

    std::cout << call([b] { return int(std::lround(b)); }) << std::endl;

    auto fun3 = std::lroundf;
    auto fun3bind = std::bind(fun3, b);
    std::cout << call(fun3bind) << std::endl;

    memory_mgmt();

    return 0;
}