#include "lib.hpp"
#include <iostream>
#include <spdlog/cfg/env.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <spdlog/stopwatch.h>

void stdout_example() {
    // create color multi threaded logger
    spdlog::get("basic_logger")
        ->info("loggers can be retrieved from a global "
               "registry using the spdlog::get(logger_name)");
}

int main() {
    // Для настройки можно использовать и
    // https://github.com/guangie88/spdlog_setup
    try {
        spdlog::basic_logger_mt("basic_logger", "logs/basic-log.txt");
    } catch (const spdlog::spdlog_ex &ex) {
        std::cerr << "Log init failed: " << ex.what() << std::endl;
    }

    auto console = spdlog::stdout_color_mt("console");
    auto err_logger = spdlog::stderr_color_mt("stderr");
    spdlog::cfg::load_env_levels();

    stdout_example();

    spdlog::info("Welcome to spdlog!");
    spdlog::error("Some error message with arg: {}", 1); // Как fmt::print(...)

    spdlog::warn("Easy padding in numbers like {:08d}", 12);
    spdlog::critical(
        "Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    spdlog::info("Support for floats {:03.2f}", 1.23456);
    spdlog::info("Positional args are {1} {0}..", "too", "supported");
    spdlog::info("{:<30}", "left aligned");

    // change log pattern
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");

    spdlog::stopwatch sw;
    fmt::print("not random number: {}\n", not_random());
    spdlog::debug("not_random took {}\n", sw);

    spdlog::debug("This message should not be displayed..");
    spdlog::set_level(spdlog::level::debug); // Set global log level to debug
    spdlog::debug("This message should be displayed..");

    return 0;
}