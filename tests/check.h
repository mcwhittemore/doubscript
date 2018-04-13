#include <iostream>
#include <sstream>
#include <fstream>
#include <streambuf>

#include "../doubscript.h"
#include "./diff.h"

namespace test {

std::string loadFile(std::string file) {
  std::ifstream f(file);
  std::string log((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
  return log;
}

int check(std::string script, std::string result, std::vector<double> args) {
  std::cout << script << ": ";
  try {
    doub::Doubscript maths = doub::Doubscript::fromFile(script);
    std::ostream stream(nullptr);
    std::stringbuf str;
    stream.rdbuf(&str);
    maths.debug("main", args, stream);

    std::string expected = loadFile(result);
    std::string d = test::diff(str.str(), expected);

    bool update = false;
    if(const char* updateChar = std::getenv("UPDATE")) {
      update = true;
    }
    if (d.size() && update) {
      std::ofstream updateLog;
      updateLog.open (result);
      updateLog << str.str();
      updateLog.close();
      std::cout << "PASS (forced and updated)" << std::endl;
      return 0;
    }

    if (d.size() > 0) {
      std::cout << "FAIL (unexpected changes)" << std::endl;
      std::cout << d;
      return 1;
    }

    std::cout << "PASS" << std::endl;
    return 0;
  } catch(const char* c) {
    std::cout << "FAIL (" << c << ")" << std::endl;
    return 1;
  }
  catch (std::out_of_range e) {
    std::cout << "FAIL (out_of_range " << e.what() << ")" << std::endl;
    return 1;
  }
};
  
}

