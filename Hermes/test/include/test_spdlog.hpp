#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

inline void test_simple_console_print() {
  auto console = spdlog::stdout_color_mt("console");
  spdlog::set_level(spdlog::level::debug);
  spdlog::info("hello, {}", "world");
  spdlog::warn("hello, {}", "world");
  spdlog::error("hello, {}", "world");
}
