#pragma once
#include <map>
#include <vector>
#include <math.h>
#include "function.cpp"
#include "scope.cpp"

namespace doub {
class Function;
class Command {
  std::vector<std::vector<std::string> > actions;
  int numVar = -1; // start as a negative number so the first var is 0
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
    bool run(doub::Scope *scope) {
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
        // TODO: Or print(input * 9)
        return 0;
      }

      // TODO: resolve return()
      // TODO: resolve function(v,v,v)

      // ACTION: (...)
      c = resolveParens(c);
 
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
      c = resolveAssign(c);

      return c.length();
    }

    std::string resolveParens(std::string c) {
      std::vector<std::string> paren = {"("};
      size_t pos = findSymbol(c, 0, paren);
      while(pos < c.size()) {
        std::string var = newVar();
        std::string cmd = internal(c, pos);
        std::string tempLine = var + "=" + cmd;
        int finished = toActions(tempLine);
        if (finished > 0) throw "Unexpected end of command";

        std::string content = "(" + cmd + ")";
        pos = c.find(content);
        c.replace(pos, content.length(), var);

        pos = findSymbol(c, 0, paren);
      }
      return c;
    }

    std::string internal(std::string c, size_t pos) {
      int open = 1;
      int close = 0;
      size_t end = pos;
      size_t full = c.size();
      while(close < open && end < full) {
        size_t next = c.find(")", end+1);
        if (next != full) {
          close++;
          end = c.find("(", end+1);
          while(end < next) {
            end = c.find("(", end+1);
            open++;
          }
        }
        end = next;
      }

      if (close != open) throw "Unexptected end of command";
      return c.substr(pos+1, end-pos-1);
    }

    std::string resolveAssign(std::string c) {
      // TODO: All lines should be hit here (until there are logic statements)
      size_t s = c.find("=");
      if (s < c.size()) {
        std::vector<std::string> args;
        std::string left = before(c, s);
        std::string right = after(c, s);

        args.push_back("assign");
        args.push_back(left);
        args.push_back(right);
        actions.push_back(args);

        std::string cmd = left + "=" + right;
        s = c.find(cmd);
        c.replace(s, cmd.length(), "");
      }

      return c;
    }

    std::string resolveSymbol(std::string c, std::vector<std::string> symbols) {
      size_t pos = findSymbol(c, 0, symbols);
      while(pos < c.size()) {
        c = mathAction(c, pos);
        pos = findSymbol(c, 0, symbols);
      }
      return c;
    }

    std::string newVar() {
      numVar++;
      return "@" + std::to_string(numVar);
    }

    std::string mathAction(std::string c, size_t loc) {
      std::string var = newVar();

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

    void math(std::vector<std::string> args, doub::Scope *scope) {
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

    void assign(std::vector<std::string> args, doub::Scope *scope) {
      double v = scope->get(args[2]);
      scope->set(args[1], v);
    }

    void print(std::vector<std::string> args, doub::Scope *scope) { 
      double v = scope->get(args[1]);
      std::cout << args[1] << ": " << v << "\n";
    }

    size_t findSymbol(std::string text, size_t start) {
      std::vector<std::string> symbols = {"=", "*", "/", "^", "+", "-",  "(", ")"};
      return findSymbol(text, start, symbols);
    }

    size_t findSymbol(std::string text, size_t start, std::vector<std::string> symbols) {
      int numSymbols = symbols.size();
      size_t best = text.size();
      for (int i=0; i<numSymbols; i++) {
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
      size_t end = findSymbol(text, start+1);
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
