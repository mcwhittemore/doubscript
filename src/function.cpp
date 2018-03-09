#pragma once
#include <map>
#include <vector>
#include "command.cpp"
#include "scope.cpp"

namespace mlg {
class Command;
class Function {
  std::map<std::string, double> dbls;
  std::vector<mlg::Command> cmds;
  std::vector<std::string> args;
  public:
    Function(){}
    Function(std::vector<std::string> ag, std::vector<std::string> logic) {
      std::cout << "setting up a function\n";
      args = ag;
      for(int i=0; i<logic.size(); i++) {
        mlg::Command cmd = mlg::Command(logic[i]);
        cmds.push_back(cmd);
      }
    }
    double run(std::vector<double> input, std::map<std::string, mlg::Function> funcs) {
      for(int i=0; i<input.size(); i++) {
        std::string arg = args[0] + "[" + std::to_string(i) + "]";
        dbls[arg] = input[i];
      }

      mlg::Scope scope = mlg::Scope(dbls, funcs);

      for(int i=0; i<cmds.size(); i++) {
        std::cout << "\nLoading Command: " << i << "\n";
        bool exit = cmds[i].run(scope);
        if (exit) break;
      }
      return scope.getReturn();
    }
};
}
