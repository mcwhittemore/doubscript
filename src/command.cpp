#pragma once
#include <map>
#include <vector>
#include <math.h>
#include "function.cpp"
#include "scope.cpp"

namespace dbs {
class Function;
class Command {
  std::vector<std::vector<std::string> > actions;
  public:
    Command() {}
    Command(std::string c) {
      int unresolveLength = toActions(c);
      if (unresolveLength > 0) {
        // TODO: handle errors better
        // throw "Unexpected content";
      }
      for (int i=0; i<actions.size(); i++) {
        break;
        std::vector<std::string> args = actions[i];
        std::cout << args[0] << " ("<<args.size()-1<<"): ";
        for (int j=1; j<args.size(); j++) {
          std::cout << "[" << args[j] << "] ";
        }
        std::cout << "\n";
      }
    }
    bool run(dbs::Scope *scope) {
      std::string symbols = "^*/-+";
      bool exit = false;
      for (int i=0; i<actions.size(); i++) {
        std::vector<std::string> args = actions[i];
        if (args[0] == "assign") assign(args, scope);
        else if (args[0] == "print") print(args, scope);
        else if (symbols.find(args[0]) < symbols.size()) math(args, scope);
      }
      return exit;
    }

  private:
    int toActions(std::string c) {
      // ACTION: resolve print()
      size_t s = c.find("print(");
      if (s < c.size()) {
        std::vector<std::string> printArgs;
        printArgs.push_back("print");
        size_t e = c.find(")", s) - (s+6);
        printArgs.push_back(c.substr(s+6, e));
        actions.push_back(printArgs);
        // TODO: Check for bad syntax such as print(input) * 9;
        return 0;
      }

      // TODO: resolve return()
      // TODO: resolve functions
      // TODO: resolve ( and [
 
      // ACTION: ^
      std::vector<std::string> exp = {"^"};
      c = resolveSymbol(c, exp);

      // ACTION: * and /
      std::vector<std::string> divAndMult = {"/", "*"};
      c = resolveSymbol(c, divAndMult);

      // ACTION: + and -
      std::vector<std::string> addAndSub = {"+", "-"};
      c = resolveSymbol(c, addAndSub);

      // ACTION: =
      s = c.find("=");
      if (s < c.size()) {
        std::vector<std::string> args;
        args.push_back("assign");
        args.push_back(before(c, s));
        args.push_back(after(c, s));
        actions.push_back(args);
        // TODO: clean up c so c.length doesnt include this phrase
      }

      return c.length();
    }

    std::string resolveSymbol(std::string c, std::vector<std::string> symbols) {
      size_t pos = findSymbol(c, 0, symbols);
      while(pos < c.size()) {
        c = mathAction(c, pos);
        pos = findSymbol(c, 0, symbols);
      }
      return c;
    }

    std::string mathAction(std::string c, size_t loc) {
      std::string var = "@" + std::to_string(actions.size());

      std::string act = "";
      act.push_back(c[loc]);

      std::string left = before(c, loc);
      std::string right = after(c, loc);
      std::vector<std::string> args;
      args.push_back(act);
      args.push_back(left);
      args.push_back(right);
      args.push_back(var);
      actions.push_back(args);

      // remove the added phrase and replace with a tmp var
      std::string phrase = left + act + right;
      size_t pos = c.find(phrase);
      c.replace(pos, phrase.length(), var);
      return c;
    }

    void math(std::vector<std::string> args, dbs::Scope *scope) {
      std::string act = args[0];
      double left = scope->get(args[1]);
      double right = scope->get(args[2]);
      std::string var = args[3];

      if (act == "*") scope->set(var, left * right);
      else if (act == "/") scope->set(var, left / right);
      else if (act == "+") scope->set(var, left + right);
      else if (act == "-") scope->set(var, left - right);
      else if (act == "^") scope->set(var, pow(left, right));
    }

    void assign(std::vector<std::string> args, dbs::Scope *scope) {
      double v = scope->get(args[2]);
      scope->set(args[1], v);
    }

    void print(std::vector<std::string> args, dbs::Scope *scope) { 
      double v = scope->get(args[1]);
      std::cout << args[1] << ": " << v << "\n";
    }

    size_t findSymbol(std::string text, size_t start) {
      std::vector<std::string> symbols = {"=", "*", "/", "^", "+", "-"};
      return findSymbol(text, start, symbols);
    }

    size_t findSymbol(std::string text, size_t start, std::vector<std::string> symbols) {
      int numSymbols = symbols.size();
      size_t best = text.find(symbols[0], start);
      for (int i=1; i<numSymbols; i++) {
        size_t n = text.find(symbols[i], start);
        if (n < best) best = n;
      }
      if (best == start) return text.length();
      return best;
    }

    std::string before(std::string text, size_t end) {
      size_t start = -1;
      size_t next = findSymbol(text, -1);
      while (true) {
        next = findSymbol(text,start+1);
        if (next >= end) break;
        start = next;
      }
      start++;

      return text.substr(start, end-start);
    }

    std::string after(std::string text, int start) {
      size_t end = findSymbol(text, start);
      return text.substr(start+1, end - start-1);
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
