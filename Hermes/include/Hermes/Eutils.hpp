#pragma once
#include <fmt/format.h>

#define CATCH_LOG(...)                                                         \
  fmt::println("[{}:{}]: {}", __FUNCTION__, __LINE__, fmt::format(__VA_ARGS__))
