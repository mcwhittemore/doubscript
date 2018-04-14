#include <iostream>
#include <sstream>
#include <fstream>
#include <streambuf>

#include "../doubscript.h"

namespace assert {

int equal(double a, double b, std::string msg) {
  std::cout << msg << ": ";
  if (a == b) {
    std::cout << "PASS" << std::endl;
    return 0;
  }

  std::cout << "FAIL (expected " << b << " got " << a << ")" << std::endl;
  return 1;
}
  
}

