#include<iostream>
#include "doubscript.h"

int main(int argc, char **argv)
{
  try {
    std::cout << "First Test: assign and print\n";
    doub::Doubscript m = doub::Doubscript("main: arg // comment \n  input = arg");
    std::cout << "\n***********************\n" << m.getProgram() << "\n*****************\n";
    std::vector<double> args;
    args.push_back(7);
    m.debug("main", args);

    std::cout << "\nSecond Test: double input and print\n";
    doub::Doubscript twoX = doub::Doubscript::fromFile("./scripts/double.doub");
    std::cout << "\n***********************\n" << twoX.getProgram() << "\n*****************\n";
    twoX.debug("main", args);

    std::cout << "\nThird Test: All the maths\n";
    doub::Doubscript maths = doub::Doubscript::fromFile("./scripts/maths.doub");
    std::cout << "\n***********************\n" << maths.getProgram() << "\n*****************\n";
    maths.debug("main", args);

    std::cout << "\nForth Test: return\n";
    doub::Doubscript add = doub::Doubscript::fromFile("./scripts/add.doub");
    std::cout << "\n***********************\n" << add.getProgram() << "\n*****************\n";
    args.push_back(3);
    double out = add.debug("main", args);
    std::cout << "result: " << out << "\n";

    std::cout << "\nFifth Test: running a bunch of functions\n";
    std::vector<double> funcArgs;
    funcArgs.push_back(5);
    funcArgs.push_back(8);
    doub::Doubscript funcs = doub::Doubscript::fromFile("./scripts/funcs.doub");
    std::cout << "\n***********************\n" << funcs.getProgram() << "\n*****************\n";
    funcs.debug("main", funcArgs);
  } catch(const char* c) { std::cout << c << "\n"; }
}
