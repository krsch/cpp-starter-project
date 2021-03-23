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

auto get_decimal() {
    py::object Decimal = py::module_::import("decimal").attr("Decimal");
    return Decimal(-3.1415).attr("copy_abs")();
}

auto operator""_dec(unsigned long long d) {
    py::object Decimal = py::module_::import("decimal").attr("Decimal");
    return Decimal(d);
}

auto get_decimal2() { return 1_dec; }

auto operator""_arg(char const *str) { return py::arg(str); }

struct Pet {
    Pet(std::string_view name, int age) : name(name), age(age) {}
    void setName(const std::string &name_) { name = name_; }
    const std::string &getName() const noexcept { return name; }
    void set(std::string_view s) { name = s; }
    void set(int a) noexcept { age = a; }

    std::string name;
    int age;
};

PYBIND11_MODULE(cpplib, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring
    using namespace pybind11::literals;

    m.def("add", &add, "A function which adds two numbers");
    m.def("pi", &get_decimal, "Return pi as decimal");
    py::class_<Pet>(m, "Pet")
        .def(py::init<std::string_view, int>(), py::arg("name"), "age"_a = 0)
        .def("setName", &Pet::setName)
        .def("getName", &Pet::getName)
        .def("__str__",
             [](const Pet &a) {
                 return fmt::format("<cpplib.Pet named '{}' aged {}>", a.name,
                                    a.age);
             })
        .def("__repr__",
             [](const Pet &a) {
                 return fmt::format("cpplib.Pet('{}', {})", a.name, a.age);
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
