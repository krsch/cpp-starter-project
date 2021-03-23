#include <fmt/core.h>
#include <locale>
#include <pybind11/pybind11.h>
#include <stdexcept>
#include <string_view>
namespace py = pybind11;
std::locale loc{""};

int add(int i, int j) {
    // throw std::runtime_error("bad python call");
    return i + j;
}

auto operator""_dec(unsigned long long d) {
    py::object Decimal = py::module_::import("decimal").attr("Decimal");
    return Decimal(d);
}

auto get_decimal() {
    py::object Decimal = py::module_::import("decimal").attr("Decimal");
    return Decimal(-3.1415).attr("copy_abs")();
}

auto get_decimal2() { return 123_dec; }

struct Pet {
    Pet(const std::string &name) : name(name) {}
    void setName(const std::string &name_) { name = name_; }
    const std::string &getName() const noexcept { return name; }
    void set(std::string_view s) { name = s; }
    void set(int a) noexcept { age = a; }

    std::string name;
    int age;
};

PYBIND11_MODULE(cpplib, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring

    m.def("add", &add, "A function which adds two numbers");
    m.def("pi", &get_decimal, "Return pi as decimal");
    py::class_<Pet>(m, "Pet")
        .def(py::init<const std::string &>())
        .def("setName", &Pet::setName)
        .def("getName", &Pet::getName)
        .def("__repr__",
             [](const Pet &a) {
                 return fmt::format("<example.Pet named '{}'>", a.name);
             })
        .def_readwrite("name", &Pet::name)
        .def_property(
            "NAME",
            [](const Pet &a) {
                std::string res;
                for (auto ch : a.name)
                    res += std::toupper(ch, loc);
                return res;
            },
            [](Pet &p, std::string_view name) {
                p.name = "";
                for (auto ch : name)
                    p.name += std::tolower(ch, loc);
            })
        .def("set", static_cast<void (Pet::*)(std::string_view)>(&Pet::set))
        .def("set", static_cast<void (Pet::*)(int)>(&Pet::set));
}
