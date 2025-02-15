#include <Hermes/Encrypter.h>
#include <Hermes/Eutils.hpp>
#include <Hermes/LoginView.h>
#include <spdlog/spdlog.h>

LoginView::LoginView(std::shared_ptr<spdlog::logger> logger)
    : logger(logger), db_ptr(std::make_unique<Hermes::Sqlite3>(
                          logger, "./datas/sqlite3/admin.sqlite3")) {
  if (logger == nullptr) {
    CATCH_LOG("日志句柄初始化失败");
    exit(-1);
  }
}

crow::response LoginView::login(const crow::request &req) {
  crow::json::wvalue res_data;
  crow::json::rvalue data = crow::json::load(req.body);
  auto username = data["username"].s();
  auto password = data["password"].s();
  SPDLOG_LOGGER_INFO(logger, "");
  std::string hashed_password{};
  std::optional<Hermes::Admin> res = db_ptr->query_admin(username);

  // SPDLOG_LOGGER_INFO(logger, "[接收到信息]: 账号: <{}>  密码: <{}>",
  // username,
  //                    passwor);

  if (!res) {
    res_data["status"] = 302;
    res_data["message"] = "Username doesn't exists";
    SPDLOG_LOGGER_INFO(logger, "账号不存在");
  } else {
    hashed_password = res.value().hashed_password;
    bool pw_matched = Encrypter::verify_password(hashed_password, password);
    if (!pw_matched) {
      res_data["status"] = 401;
      res_data["message"] = "Password Wrong";
      SPDLOG_LOGGER_INFO(logger, "密码错误");
    } else {
      res_data["status"] = 200;
      res_data["message"] = "Password Correct";
      res_data["cookie"] = "Password Correct";
      SPDLOG_LOGGER_INFO(logger, "登陆成功");
    }
  }
  return crow::response(res_data);
}
