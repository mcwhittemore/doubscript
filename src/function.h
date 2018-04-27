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
  std::vector<doub::Function> blocks;

  public:
    Function(){}
    Function(std::vector<std::string> ag, std::vector<std::string> logic) {
      args = ag;


      std::vector<std::string> activeBlock;
      for(int i=0; i<logic.size(); i++) {
        char c = logic[i][0];
        if(c == ' ') {
          activeBlock.push_back(blockTrim(logic[i]));
          logic.erase(logic.begin()+i);
          i--;
        }
        else if(c != ' ' && activeBlock.size() > 0) {
          doub::Function block(activeBlock);
          logic[i-1] = logic[i-1] + "@@" + std::to_string(blocks.size());
          blocks.push_back(block);
          activeBlock.erase(activeBlock.begin(), activeBlock.end());
        }
      }

      for(int i=0; i<logic.size(); i++) {
        doub::Command cmd(logic[i]);
        cmds.push_back(cmd);
      }
    }
    Function(std::vector<std::string> logic) : Function({}, logic) {}
    double run(doub::Scope *scope, std::map<std::string, doub::Function> funcs, std::ostream &debug) {
      for(int i=0; i<cmds.size(); i++) {
        bool exit = runCommand(cmds[i], scope, funcs, debug);
        if (exit) break;
      }
      return scope->getReturn();
    }
    double run(std::vector<double> input, std::map<std::string, doub::Function> funcs, std::ostream &debug) {
      if (input.size() < args.size()) throw "not enough args";
      if (input.size() > args.size()) throw "too many args";
      debug << "args:";
      for(int i=0; i<input.size(); i++) {
        debug << " " << args[i] << "=" << input[i];
        dbls[args[i]] = input[i];
      }
      debug << "\n";

      doub::Scope scope = doub::Scope(dbls);
      return run(&scope, funcs, debug);
    }

  private:
    std::string blockTrim(std::string c) {
      if (c[0] != ' ' || c[1] != ' ') throw "improper indentation";
      return c.substr(2);
    }
    bool runCommand(doub::Command cmd, doub::Scope *scope, std::map<std::string, doub::Function> funcs, std::ostream &debug) {
      std::string symbols = "^*/-+=";
      int numActions = cmd.numActions();
      bool exit = false;
      for (int i=0; i<numActions; i++) {
        std::vector<std::string> args = cmd.getAction(i);
        if (args[0] == "if") {
          if (scope->get(args[1]) == 1) {
            int blockId = stoi(args[2]);
            blocks[blockId].run(scope, funcs, debug);
            debug << "if(" << args[1] << ") => run block " << args[2] << std::endl;
            if (scope->hasReturn()) {
              exit = true;
              break;
            }
          }
          else if (scope->get(args[1]) != 0) {
            throw "if statements must resolve to either 1 or 0";
          }
        }
        else if (args[0] == "return") {
          exit = true;
          scope->setReturn(scope->get(args[1]));

          // LOG TO DEBUG STREAM
          debug << "return(" << args[1] << ") => " << scope->get(args[1]) << std::endl;

          break;
        }
        else if (args[0] == "<" || args[0] == ">" || args[0] == "<=" || args[0] == ">=" || args[0] == "==" || args[0] == "||" || args[0] == "&&") {
          cmd.compare(args, scope, debug);
        }
        else if (symbols.find(args[0]) < symbols.size()) {
          cmd.math(args, scope, debug);
        }
        else {
          std::vector<double> vars;
          for(int i=1; i<args.size(); i++) {
            double varVal = scope->get(args[i]);
            vars.push_back(varVal);
          }

          debug << args[0] << "(";
          if (args.size() >= 1) debug << args[1];
          for (int i=2; i<args.size(); i++) {
            debug << ", " << args[i];
          }

          double val = funcs[args[0]].run(vars, funcs, debug);
          scope->set(args[1], val);

          debug << ") => " << scope->get(args[1]) << std::endl;
        }
      }
      return exit;
    }
};
}
