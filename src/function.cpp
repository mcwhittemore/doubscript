#pragma once
#include <map>
#include <vector>
#include "command.cpp"
#include "scope.cpp"

namespace doub {
class Command;
class Function {
  std::map<std::string, double> dbls;
  std::vector<doub::Command> cmds;
  std::vector<std::string> args;
  public:
    Function(){}
    Function(std::vector<std::string> ag, std::vector<std::string> logic) {
      args = ag;
      for(int i=0; i<logic.size(); i++) {
        doub::Command cmd = doub::Command(logic[i]);
        cmds.push_back(cmd);
      }
    }
    double run(std::vector<double> input, std::map<std::string, doub::Function> funcs) {
      if (input.size() < args.size()) throw "not enough args";
      if (input.size() > args.size()) throw "too many args";
      for(int i=0; i<input.size(); i++) {
        dbls[args[i]] = input[i];
      }

      doub::Scope scope = doub::Scope(dbls, funcs);

      for(int i=0; i<cmds.size(); i++) {
        bool exit = cmds[i].run(&scope);
        if (exit) break;
      }
      return scope.getReturn();
    }
};
}
