#include<iostream>
#include "doubscript.cpp"

int main(int argc, char **argv)
{
  std::cout << "First Test: assign and print\n";
  dbs::Doubscript m = dbs::Doubscript("main: args // comment \n  input = args[0]\n  print(input)");
  std::cout << "\n***********************\n" << m.getProgram() << "\n*****************\n";
  std::vector<double> args;
  args.push_back(7);
  m.run("main", args);

  std::cout << "\nSecond Test: double input and print\n";
  dbs::Doubscript twoX = dbs::Doubscript::fromFile("./scripts/double.dbs");
  std::cout << "\n***********************\n" << twoX.getProgram() << "\n*****************\n";
  twoX.run("main", args);

  std::cout << "\nThird Test: All the maths\n";
  dbs::Doubscript maths = dbs::Doubscript::fromFile("./scripts/maths.dbs");
  std::cout << "\n***********************\n" << maths.getProgram() << "\n*****************\n";
  maths.run("main", args);
}
