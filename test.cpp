#include<iostream>
#include "mathlog.cpp"

int main(int argc, char **argv)
{
  std::cout << "First Test: assign and log\n";
  mlg::Mathlog m = mlg::Mathlog("main: args // comment \n  input = args[0]\n  print(input)");
  std::vector<double> args;
  args.push_back(7);
  m.run("main", args);

  std::cout << "\nSecond Test: double input and log\n";
  mlg::Mathlog twoX = mlg::Mathlog::fromFile("./scripts/double.mlg");
  twoX.run("main", args);
}
