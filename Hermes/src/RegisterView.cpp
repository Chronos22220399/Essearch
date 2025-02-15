#include <Hermes/Encrypter.h>
#include <Hermes/Eutils.hpp>
#include <Hermes/RegisterView.h>
#include <fmt/format.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/spdlog.h>

RegisterView::RegisterView(std::shared_ptr<spdlog::logger> logger)
    : logger(logger), admin_db(std::make_unique<Hermes::Sqlite3>(
                          logger, "./datas/sqlite3/admin.sqlite3")) {
  if (logger == nullptr) {
    CATCH_LOG("日志句柄初始化失败");
    exit(-1);
  }
}

// Register
crow::response RegisterView::regist(const crow::request &req) {
  crow::json::rvalue data = crow::json::load(req.body);
  crow::json::wvalue res_data;
  std::string username = data["username"].s();
  std::string password = data["password"].s();

  SPDLOG_LOGGER_INFO(logger, "接收到注册请求");

  if (!data) {
    // data is empty
    res_data["status"] = 204;
    res_data["message"] = "No Content";
    SPDLOG_LOGGER_INFO(logger, "接收到空数据");
    // data is empty
  } else if (!password_is_valid(password)) {
    // password is valid
    res_data["status"] = 400;
    res_data["message"] = "Invalid Password";
    SPDLOG_LOGGER_INFO(logger, "密码不合法");
    // password is valid
  } else {
    SPDLOG_LOGGER_INFO(logger, "登陆成功");
    return handle(username, password, res_data);
  }
  return crow::response(res_data);
}

crow::response RegisterView::handle(const std::string &username,
                                    const std::string &password,
                                    crow::json::wvalue &res_data) {
  using namespace Hermes;
  std::optional<std::string> hashed_password{};
  std::string hashed_password_v{};
  std::string cookie{};

  SPDLOG_LOGGER_INFO(logger, "[接收到信息]: 账号: <{}> -- 密码: <{}>", username,
                     password);
  // store the info
  // username need not hash
  hashed_password = Encrypter::hash_password(password);

  // check hashing is successful
  if (!hashed_password) {
    res_data["status"] = 400;
    res_data["message"] = "An Error Occurred When Hashing";
    SPDLOG_LOGGER_ERROR(logger, "对密码哈希失败");
    return crow::response(res_data);
  }

  // get the value
  hashed_password_v = hashed_password.value();
  SPDLOG_LOGGER_INFO(logger, "[加密成功]: 账号: <{}> -- 密码: <{}>", username,
                     hashed_password_v);

  // check username
  auto res = admin_db->username_in_db(username);

  // occurred an error when query
  if (!res) {
    res_data["status"] = 400;
    res_data["message"] = "An Error Occurred When Quering Username";
    SPDLOG_LOGGER_ERROR(logger, "查询账号时出现错误");
    return crow::response(res_data);
  }
  // username exists
  if (res.value() != 0) {
    res_data["status"] = 302;
    res_data["message"] = "Username Exists";
    SPDLOG_LOGGER_INFO(logger, "账号已存在");
    return crow::response(res_data);
  }

  // if not exists then save it;
  admin_db->save_admininfo(username, hashed_password_v);
  SPDLOG_LOGGER_INFO(logger, "注册成功");
  res_data["cookie"] = "12121";
  res_data["status"] = 200;
  res_data["message"] = "Register Successful!";
  return crow::response(res_data);
}

// check password whether is valid
inline bool RegisterView::password_is_valid(const std::string &password) {
  if (password.length() < 8) {
    return false;
  }
  return true;
}

// store the basic userinfo
inline void RegisterView::store_userinfo(const std::string &username,
                                         const std::string &hashed_password) {}
