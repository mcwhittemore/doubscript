#pragma once
#include <map>
#include <vector>
#include <math.h>
#include "function.h"
#include "scope.h"

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
        throw "Unexpected content";
      }
    }
    int numActions() {
      return actions.size();
    }

    std::vector<std::string> getAction(int i) {
      return actions[i];
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

  private:
    int toActions(std::string c) {

      // ACTION: print()
      c = resolvePrint(c);

      // ACTION: (...), return(...) and function(...)
      c = resolveParendsAndFunctions(c);
 
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

    std::string resolvePrint(std::string c) {
      size_t s = c.find("print(");
      if (s < c.size()) {
        std::vector<std::string> printArgs;
        printArgs.push_back("print");
        size_t e = c.find(")", s) - (s+6);
        printArgs.push_back(c.substr(s+6, e));
        actions.push_back(printArgs);
        // TODO: Check for bad syntax such as print(input) * 9;
        // TODO: Or print(input * 9)
        return "";
      }
      return c;
    }

    std::string resolveParendsAndFunctions(std::string c) {
      std::vector<std::string> paren = {"("};
      size_t pos = findSymbol(c, 0, paren);
      while(pos < c.size()) {
        std::string name = before(c, pos);
        std::string cmd = internal(c, pos);

        std::vector<std::string> cmds = toParts(cmd);
        std::vector<std::string> args;
        args.push_back(name);

        for (int i=0; i<cmds.size(); i++) {
          std::string var = newVar();
          args.push_back(var);
          std::string tempLine = var + "=" + cmds[i];
          int finished = toActions(tempLine);
          if (finished > 0) throw "Unexpected end of command";
        }

        std::string var = "";

        // the value should replace the function unless its return
        if (name == "") {
          var = args[1];
        }

        if (name != "") {
          actions.push_back(args);
        }

        std::string content = name+"(" + cmd + ")";
        pos = c.find(content);
        if (pos == c.size()) throw "Unexpected end of command";
        c.replace(pos, content.length(), var);

        pos = findSymbol(c, 0, paren);
      }
      return c;
    }

    std::vector<std::string> toParts(std::string c) {
      std::vector<std::string> parts;
      std::string v = "";
      for(int i=0; i<c.length(); i++) {
        if (c[i] == ',') {
          parts.push_back(v);
          v = "";
        }
        else {
          v.push_back(c[i]);
        }
      }
      parts.push_back(v);
      return parts;
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
        std::string left = before(c, s);
        std::string right = after(c, s);

        std::vector<std::string> args;
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
