// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>

#include <header.hpp>

using nlohmann::json;

TEST(Parser, Reading_string) {
  json j = R"(
  {
    "name": "Ivanov Petr",
    "group": "1",
    "avg": "4.25",
    "debt": "C++"
  }
  )"_json;
  Student Petr;
  from_json(j, Petr);
  EXPECT_EQ(Petr.Name, "Ivanov Petr");
  EXPECT_EQ(std::any_cast<std::string>(Petr.Group), "1");
  EXPECT_EQ(std::any_cast<std::string>(Petr.Avg), "4.25");
  EXPECT_EQ(std::any_cast<std::string>(Petr.Debt), "C++");
}

TEST(Parser, Reading_int) {
  json j = R"(
  {
    "name": "Sidorov Ivan",
    "group": 31,
    "avg": 4,
    "debt": [
        "C++",
        "Linux",
        "Network"
    ]
  }
  )"_json;
  std::vector<std::string> debt = {"C++", "Linux", "Network"};
  Student Ivan;
  from_json(j, Ivan);
  EXPECT_EQ(std::any_cast<int>(Ivan.Group), 31);
  EXPECT_EQ(std::any_cast<int>(Ivan.Avg), 4);
  EXPECT_EQ(std::any_cast<std::vector<std::string>>(Ivan.Debt), debt);
}

TEST(Parser, Reading_float) {
  json j = R"(
  {
    "name": "Petrov Nikita",
    "group": 2,
    "avg": 4.25,
    "debt": "C++"
  }
  )"_json;
  Student Nikita;
  from_json(j, Nikita);
  EXPECT_EQ(std::any_cast<double>(Nikita.Avg), 4.25);
}

TEST(Parser, Reading_null) {
  json j = R"(
  {
    "name": "Alex",
    "group": 2,
    "avg": 4.25,
    "debt": null
  }
  )"_json;
  Student Alex;
  from_json(j, Alex);
  auto n = nullptr;
  std::any N = n;
  EXPECT_EQ(Alex.Debt.type(), N.type());
}
