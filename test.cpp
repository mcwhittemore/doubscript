#include<iostream>
#include "mathlog.cpp"

int main(int argc, char **argv)
{
  mlg::Mathlog m = mlg::Mathlog(argv[0]);
  std::vector<double> args;
  args.push_back(7);
  m.run("main", args);
}
