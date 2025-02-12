#pragma once
#include <Arachne/Autils.hpp>
#include <httplib.h>

class NewGetter {
public:
  NewGetter() : cli("https://news.hbut.edu.cn") {}

  std::string get_new(const std::string &url) {
    httplib::Result result = cli.Get(url);
    if (!result) {
      LOG("结果为空");
      exit(-1);
    }
    if (result->status != 200) {
      LOG("结果错误");
    }
    return result->body;
  }

private:
  httplib::Client cli;
};
