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
      int ei = find(c, '=', 0);
      if (ei > -1) {
        std::vector<std::string> args;
        args.push_back("assign");
        args.push_back(before(c, ei));
        args.push_back(after(c, ei));
        actions.push_back(args);
      }


      std::cout << "Setup: " << c << " (" << actions.size() << ")\n";
    }
    bool run(mlg::Scope scope) {
      bool exit = false;
      for (int i=0; i<actions.size(); i++) {
        std::vector<std::string> args = actions[i];
        std::cout << "\tRunning Cmd: " << args[0] << "\n";
        if (args[0] == "assign") assign(args, scope);
        else if (args[0] == "log") log(args, scope);
      }
      return exit;
    }

  private:
    void assign(std::vector<std::string> args, mlg::Scope scope) {
      std::cout << "\t\t"<<args[1]<<" - " << args[2]<<"\n";
      double v = scope.get(args[1]);
      scope.set(args[2], v);
    }

    void log(std::vector<std::string> args, mlg::Scope scope) { 
      double v = scope.get(args[1]);
      std::cout << args[1] << ": " << v << "\n";
    }

    int find(std::string text, char c, int start) {
      for (int i=start; i<text.length(); i++) {
        if (text[i] == c) return i; 
      }
      return -1;
    }

    std::string before(std::string text, int b) {
      int start = 0;
      int next = find(text, ' ', start);
      while(next < b) {
        start = next;
        next = find(text, ' ', start+1);
      }

      return substr(text, start, b);
    }

    std::string after(std::string text, int e) {
      int we = find(text, ' ', e);
      std::cout << "after: " << e << " to " << we << "\n";
      if (we == -1) we = text.length();
      return substr(text, e, we);
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
