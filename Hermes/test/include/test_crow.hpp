#pragma once
#include <crow.h>
#include <fmt/format.h>

inline void test_crow() {
  crow::SimpleApp app;

  CROW_ROUTE(app, "/json")([]() {
    crow::json::wvalue x({{"message", "Hello, World!"}});
    return x;
  });

  CROW_ROUTE(app, "/jsonarr")([]() {
    crow::json::wvalue x(
        {{{"name", "Ess"}, {"age", 12}}, {{"gender", "male"}}});
    return x;
  });

  CROW_ROUTE(app, "/response/<int>")([](int count) {
    crow::response resp;
    resp.code = 404;
    resp.body = "response body" + std::to_string(count);
    return resp;

    // 重定向
    // crow::response res;
    // res.redirect("/")

    // if (count > 100) {
    //   return crow::response(500);
    // }
    // std::ostringstream os;
    // os << count << " bottles of beer!";
    // return crow::response(os.str());
  });

  // MARK: POST
  CROW_ROUTE(app, "/add_json")
      .methods("POST"_method)([](const crow::request &req) {
        crow::json::rvalue x = crow::json::load(req.body);
        if (!x) {
          return crow::response(crow::status::BAD_REQUEST);
        }

        int sum = x["a"].i() + x["b"].i();
        std::ostringstream os;
        os << sum;
        return crow::response(os.str());
      });

  // MARK: GET
  CROW_ROUTE(app, "/getfunc")
      .methods("GET"_method)([](const crow::request &req) {
        std::string key1 =
            req.url_params.get("key1") ? req.url_params.get("key1") : "unknown";
        std::string key2 =
            req.url_params.get("key2") ? req.url_params.get("key2") : "unknown";
        std::string keys1 =
            req.url_params.get("keys") ? req.url_params.get("keys") : "unknown";

        return crow::response(crow::status::ACCEPTED);
      });

  app.port(17800).run();
}
