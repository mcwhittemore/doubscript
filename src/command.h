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
      bool finished = toActions(c);
      if (!finished) {
        throw "Unexpected content";
      }
    }
    int numActions() {
      return actions.size();
    }

    std::vector<std::string> getAction(int i) {
      return actions[i];
    }

    void compare(std::vector<std::string> args, doub::Scope *scope, std::ostream &debug) {
      std::string act = args.at(0);
      double left = scope->get(args[1]);
      double right = scope->get(args[2]);
      std::string var = args[3];

      double val = 0;
      if (act == "<") val = left < right ? 1 : 0;
      if (act == ">") val = left > right ? 1 : 0;
      if (act == "<=") val = left <= right ? 1 : 0;
      if (act == ">=") val = left >= right ? 1 : 0;
      if (act == "==") val = left == right ? 1 : 0;

      scope->set(var, val);

      debug << var << " = " << left << act << right << " => " << scope->get(var) << std::endl;
    }

    void math(std::vector<std::string> args, doub::Scope *scope, std::ostream &debug) {
      std::string act = args[0];
      double left = scope->get(args[1]);
      double right = scope->get(args[2]);
      std::string var = args[3];

      if (act == "*") scope->set(var, left * right);
      if (act == "=") scope->set(var, scope->get(args[2]));
      else if (act == "/") scope->set(var, left / right);
      else if (act == "+") scope->set(var, left + right);
      else if (act == "-") scope->set(var, left - right);
      else if (act == "^") scope->set(var, pow(left, right));

      debug << var << " = " << args[1] << act << args[2] << " => " << scope->get(var) << std::endl;
    }

  private:
    bool toActions(std::string c) {

      // ACTION: if(...)


      // ACTION: (...), return(...) and function(...)
      c = resolveParensAndFunctions(c);
 
      // ACTION: ^
      std::vector<std::string> exp = {"^"};
      c = resolveSymbol(c, exp);

      // ACTION: * and /
      std::vector<std::string> divAndMult = {"/", "*"};
      c = resolveSymbol(c, divAndMult);

      // ACTION: + and -
      std::vector<std::string> addAndSub = {"+", "-"};
      c = resolveSymbol(c, addAndSub);

      // ACTION: <, <=, ==, >=, >
      c = resolveComparisons(c);

      // ACTION: =
      c = resolveAssign(c);

      if (c[0] == '@') {
        c.replace(0,1,"");
        int varIndex = stoi(c);
        if (varIndex <= numVar) return true;
      }
      return c.length() == 0;
    }

    std::string resolveComparisons(std::string c) {
      std::vector<std::string> comparisons = {"<=", ">=", "==", "<", ">"};
      for (int i=0; i<comparisons.size(); i++) {
        std::string comparison = comparisons[i];
        size_t pos = c.find(comparison);
        while (pos < c.size()) {
          std::string var = newVar();
          std::string left = before(c, pos);
          std::string right = after(c, pos+comparison.size()-1);
          std::vector<std::string> args = {comparison, left, right, var};
          actions.push_back(args);

          // Clean up phrase
          std::string phrase = left + comparison + right;
          c.replace(c.find(phrase), phrase.length(), var);

          pos = c.find(comparison);
        }
      }

      return c;
    }

    std::string resolveParensAndFunctions(std::string c) {
      size_t pos = c.rfind("(", -1);
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
          bool finished = toActions(tempLine);
          if (!finished) throw "Unexpected end of command";
        }

        if(name == "if") {
          size_t bpos = c.find(")@@");
          if (bpos == c.size()) throw "if statements must have sub-blocks";
          args.push_back(after(c, bpos+2));
        }

        // This is because the `toActions` call
        // in the four loop above will have already
        // taken care of adding this
        if (name != "") {
          actions.push_back(args);
        }

        std::string content = name+"(" + cmd + ")";
        pos = c.find(content);
        if (pos == c.size()) throw "Unexpected end of command";
        c.replace(pos, content.length(), args[1]);

        pos = c.rfind("(", -1);
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
      size_t s = c.find("=");
      if (s < c.size()) {
        std::string left = before(c, s);
        std::string right = after(c, s);

        std::vector<std::string> args;
        args.push_back("=");
        args.push_back(left);
        args.push_back(right);
        args.push_back(left);
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
      std::vector<std::string> args = {act, left, right, var};
      actions.push_back(args);

      // remove the added phrase and replace with a tmp var
      std::string phrase = left + act + right;
      size_t pos = c.find(phrase);
      c.replace(pos, phrase.length(), var);
      return c;
    }


    size_t findSymbol(std::string text, size_t start) {
      std::vector<std::string> symbols = {"=", "*", "/", "^", "+", "-",  "(", ")", "<", ">"};
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
