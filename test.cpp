#include<iostream>
#include "dubscript.cpp"

int main(int argc, char **argv)
{
  std::cout << "First Test: assign and print\n";
  dbs::Dubscript m = dbs::Dubscript("main: args // comment \n  input = args[0]\n  print(input)");
  std::vector<double> args;
  args.push_back(7);
  m.run("main", args);

  std::cout << "\nSecond Test: double input and print\n";
  dbs::Dubscript twoX = dbs::Dubscript::fromFile("./scripts/double.dbs");
  twoX.run("main", args);
}
