#include<iostream>
#include "doubscript.cpp"

int main(int argc, char **argv)
{
  try {
    std::cout << "First Test: assign and print\n";
    doub::Doubscript m = doub::Doubscript("main: args // comment \n  input = args[0]\n  print(input)");
    std::cout << "\n***********************\n" << m.getProgram() << "\n*****************\n";
    std::vector<double> args;
    args.push_back(7);
    m.run("main", args);

    std::cout << "\nSecond Test: double input and print\n";
    doub::Doubscript twoX = doub::Doubscript::fromFile("./scripts/double.doub");
    std::cout << "\n***********************\n" << twoX.getProgram() << "\n*****************\n";
    twoX.run("main", args);

    std::cout << "\nThird Test: All the maths\n";
    doub::Doubscript maths = doub::Doubscript::fromFile("./scripts/maths.doub");
    std::cout << "\n***********************\n" << maths.getProgram() << "\n*****************\n";
    maths.run("main", args);
  } catch(const char* c) { std::cout << c << "\n"; }
}
