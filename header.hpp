#pragma once
// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <any>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>
#include <typeinfo>

using nlohmann::json;

struct Student {
  std::string Name;
  std::any Group;
  std::any Avg;
  std::any Debt;
};

void from_json(const json& j, Student& s) {
  if (j.at("group").is_string()) {
    std::string g;
    j.at("group").get_to(g);
    s.Group = g;
  } else if (j.at("group").is_number_integer()) {
    int g;
    j.at("group").get_to(g);
    s.Group = g;
  }
  j.at("name").get_to(s.Name);
  if (j.at("avg").is_string()) {
    std::string a;
    j.at("avg").get_to(a);
    s.Avg = a;
  } else if (j.at("avg").is_number_integer()) {
    int a;
    j.at("avg").get_to(a);
    s.Avg = a;
  } else if (j.at("avg").is_number_float()) {
    double a;
    j.at("avg").get_to(a);
    s.Avg = a;
  }
  if (j.at("debt").is_string()) {
    s.Debt = j.at("debt").get<std::string>();
  } else if (j.at("debt").is_null()) {
    s.Debt = nullptr;
  } else if (j.at("debt").is_array()) {
    s.Debt = j.at("debt").get<std::vector<std::string>>();
  }
}

void print_table(const std::vector<Student>& students) {
  int n = 4, g = 5, a = 3, d = 4;
  std::string buf_g, buf_a;
  for (auto const& s : students) {
    if (static_cast<int>(s.Name.size()) > n) n = s.Name.size();
    buf_g = std::any_cast<std::string>(s.Group);
    if (static_cast<int>(buf_g.size()) > g) g = buf_g.size();
    buf_a = std::any_cast<std::string>(s.Avg);
    if (static_cast<int>(buf_a.size()) > a) a = buf_a.size();
    std::vector<std::string> S;
    std::any M = std::any_cast<std::vector<std::string>>(S);
    if (s.Debt.type() == M.type()) {
      if (static_cast<int>(sizeof("__ items")) > d)
        d = static_cast<int>(sizeof("__ items"));
    } else {
      buf_a = std::any_cast<int>(s.Debt);
      if (static_cast<int>(buf_a.size()) > d) d = buf_a.size();
    }
  }
  std::cout << "|" << std::setw(n + 2) << " name";
  std::cout << "|" << std::setw(g + 2) << " group";
  std::cout << "|" << std::setw(a + 2) << " avg";
  std::cout << "|" << std::setw(d + 2) << " debt";
  std::cout << "|" << std::endl;
  std::cout << std::setfill('-') << std::setw(n + 2) << "|";
  std::cout << std::setfill('-') << std::setw(g + 2) << "|";
  std::cout << std::setfill('-') << std::setw(a + 2) << "|";
  std::cout << std::setfill('-') << std::setw(d + 2) << "|";
  for (auto const& st : students) {
    std::string s;
    std::cout << "|" << std::setw(n + 2) << st.Name;
    s = std::any_cast<std::string>(st.Group);
    std::cout << "|" << std::setw(g + 2) << s;
    s = std::any_cast<std::string>(st.Avg);
    std::cout << "|" << std::setw(a + 2) << std::fixed << std::setprecision(2)
              << s;
    std::any v = std::vector<std::string>();
    std::any p = nullptr;
    if (st.Debt.type() == v.type()) {
      auto m = std::any_cast<std::vector<std::string>>(st.Debt);
      s = std::to_string(m.size()) + " items";
    } else if (st.Debt.type() == p.type()) {
      s = "null";
    } else {
      s = std::any_cast<std::string>(st.Debt);
    }
    std::cout << "|" << std::setw(d + 2) << s;
    std::cout << "|" << std::endl;
  }
}

#endif  // INCLUDE_HEADER_HPP_
