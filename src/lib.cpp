#include "lib.hpp"
#include <spdlog/spdlog.h>

int not_random() {
    // Для большей универсальности можно использовать
    // https://github.com/ngrodzitski/logr
    spdlog::get("console")->info("Called not_random");

    return 3;
}