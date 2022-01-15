// Copyright 2018 Your Name <your_email>

#include <header.hpp>

int main() {
  std::string jsonPath = "students.json";
  std::ifstream file{jsonPath};
  try {
    if (!file) {
      throw std::runtime_error{"unable to open json: " + jsonPath};
    }
  } catch (const std::runtime_error& e) {
    std::cout << e.what() << '\n';
  }

  json data;
  file >> data;

  std::vector<Student> students;
  // for (auto const& student : data.at("items")) {
  // students.push_back(Student{student});
  //}

  for (json student : data.at("items")) {
    Student S;
    from_json(student, S);
    students.push_back(S);
  }

  try {
    if (students.size() != data["_meta"]["count"].get<int>()) {
      throw std::runtime_error{"_meta.count != len(items)"};
    }
  } catch (const std::runtime_error& e) {
    std::cout << e.what() << '\n';
  }
  print_table(students);
  return 0;
}
