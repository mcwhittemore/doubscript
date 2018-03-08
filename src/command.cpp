#pragma once
#include <map>
#include <vector>
#include "function.cpp"

namespace mlg {
class Function;
class Command {
  std::string cmd;
  public:
    Command() {}
    Command(std::string c) {
      cmd = c; 
    }
    void run( std::map<std::string, mlg::Function> funcs) {
      std::cout << cmd << "\n";
    }
};
}
