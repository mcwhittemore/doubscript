#pragma once
#include <map>
#include <vector>
#include "function.cpp"

namespace dbs {
class Function;
class Scope {
  std::map<std::string, double> dbls;
  std::map<std::string, dbs::Function> funcs;
  double returnVal;

  public:
    Scope() {};
    Scope(std::map<std::string, double> d, std::map<std::string, dbs::Function> f) {
      dbls = d;
      funcs = f;
      returnVal = 0;
    }

    double get(std::string name) {
      try {
        return stod(name);
      } catch(const std::exception& e) {
        return dbls[name];
      }
    }

    void set(std::string name, double val) {
      dbls[name] = val;
    }

    void setReturn(double val) {
      returnVal = val;
    }

    double getReturn() {
      return returnVal;
    }
};
}
