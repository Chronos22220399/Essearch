#pragma once
#include <Hephaestus/Egutils.h>
#include <Hephaestus/Includes.h>
#include <cppjieba/Jieba.hpp>

class Cutter {
public:
  Cutter();

  Cutter(Cutter const &) = delete;

  std::set<std::string> normalDivorce(std::string const &text) const;

  std::set<std::string> advancedDivorce(std::string const &text) const;

private:
  cppjieba::Jieba jieba;
  TextProcessor text_processor;
  CharUtils char_utils;
};
