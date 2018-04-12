#pragma once
#include <map>
#include <vector>

namespace doub {
class Scope {
  std::map<std::string, double> dbls;
  double returnVal;

  public:
    Scope() {};
    Scope(std::map<std::string, double> d) {
      dbls = d;
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
