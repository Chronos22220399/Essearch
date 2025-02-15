#pragma once
#include <optional>
#include <string>

class Encrypter {
public:
  // 初始化
  static void init();

  // 哈希
  static std::optional<std::string> crypto_hash(const std::string &input);

  // 哈希加密信息
  static std::optional<std::string> hash_password(const std::string &password);

  // 校验哈希加密后的信息
  static bool verify_password(const std::string &hashed_password,
                              const std::string &password);
};
