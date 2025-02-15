#pragma once
#include <Hermes/Encrypter.h>
#include <Hermes/Sqlite3.h>
#include <crow.h>
#include <fmt/format.h>
#include <memory>
#include <optional>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/spdlog.h>
#include <string>

class LoginView final {
  std::optional<std::string> token{std::nullopt};
  std::shared_ptr<spdlog::logger> logger;
  std::unique_ptr<Hermes::Sqlite3> db_ptr;

public:
  LoginView(std::shared_ptr<spdlog::logger> logger = nullptr);

  crow::response login(const crow::request &req);
};
