#pragma once
#include <map>
#include <vector>
#include "command.h"
#include "scope.h"

namespace doub {
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

      doub::Scope scope = doub::Scope(dbls);

      for(int i=0; i<cmds.size(); i++) {
        bool exit = runCommand(cmds[i], &scope, funcs);
        if (exit) break;
      }
      return scope.getReturn();
    }

  private:
    bool runCommand(doub::Command cmd, doub::Scope *scope, std::map<std::string, doub::Function> funcs) {
      std::string symbols = "^*/-+";
      int numActions = cmd.numActions();
      bool exit = false;
      for (int i=0; i<numActions; i++) {
        std::vector<std::string> args = cmd.getAction(i);
        if (args[0] == "return") {
          exit = true;
          scope->setReturn(scope->get(args[1]));
          break;
        }
        else if (args[0] == "assign") cmd.assign(args, scope);
        else if (args[0] == "print") cmd.print(args, scope);
        else if (symbols.find(args[0]) < symbols.size()) cmd.math(args, scope);
        else {
          std::vector<double> vars;
          for(int i=1; i<args.size(); i++) {
            double varVal = scope->get(args[i]);
            vars.push_back(varVal);
          }
          double val = funcs[args[0]].run(vars, funcs);
          scope->set(args[1], val);
        }
      }
      return exit;
    }
};
}
