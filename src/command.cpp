#pragma once
#include <map>
#include <vector>
#include "function.cpp"
#include "scope.cpp"

namespace mlg {
class Function;
class Command {
  std::vector<std::vector<std::string> > actions;
  public:
    Command() {}
    Command(std::string c) {
      size_t s = c.find("=");
      if (s < c.size()) {
        std::vector<std::string> args;
        args.push_back("assign");
        args.push_back(before(c, s));
        args.push_back(after(c, s));
        actions.push_back(args);
      }

      s = c.find("log(");
      if (s < c.size()) {
        std::vector<std::string> logArgs;
        logArgs.push_back("log");
        size_t e = c.find(")", s) - (s+4);
        logArgs.push_back(c.substr(s+4, e));
        actions.push_back(logArgs);
      }


    }
    bool run(mlg::Scope *scope) {
      bool exit = false;
      for (int i=0; i<actions.size(); i++) {
        std::vector<std::string> args = actions[i];
        if (args[0] == "assign") assign(args, scope);
        else if (args[0] == "log") log(args, scope);
      }
      return exit;
    }

  private:
    void assign(std::vector<std::string> args, mlg::Scope *scope) {
      double v = scope->get(args[2]);
      scope->set(args[1], v);
    }

    void log(std::vector<std::string> args, mlg::Scope *scope) { 
      double v = scope->get(args[1]);
      std::cout << args[1] << ": " << v << "\n";
    }

    std::string before(std::string text, size_t end) {
      size_t start = 0;
      size_t next = text.find(" ", 0);
      while (true) {
        next = text.find(" ", start+1);
        if (next >= end) break;
        start = next;
      }

      return text.substr(start, end);
    }

    std::string after(std::string text, int start) {
      size_t end = text.find(" ", start) - start;
      return text.substr(start+1, end);
    }

    std::string substr(std::string text, int start, int end) {
      std::string out = "";
      for (int i=start; i<end; i++) {
        out.push_back(text[i]);
      }
      return out;
    }
};
}
