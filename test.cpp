#include<iostream>
#include "dubscript.cpp"

int main(int argc, char **argv)
{
  std::cout << "First Test: assign and print\n";
  dbs::Dubscript m = dbs::Dubscript("main: args // comment \n  input = args[0]\n  print(input)");
  std::cout << "\n***********************\n" << m.getProgram() << "\n*****************\n";
  std::vector<double> args;
  args.push_back(7);
  m.run("main", args);

  std::cout << "\nSecond Test: double input and print\n";
  dbs::Dubscript twoX = dbs::Dubscript::fromFile("./scripts/double.dbs");
  std::cout << "\n***********************\n" << twoX.getProgram() << "\n*****************\n";
  twoX.run("main", args);

  std::cout << "\nThird Test: All the maths\n";
  dbs::Dubscript maths = dbs::Dubscript::fromFile("./scripts/maths.dbs");
  std::cout << "\n***********************\n" << maths.getProgram() << "\n*****************\n";
  maths.run("main", args);
}
