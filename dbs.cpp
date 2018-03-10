#include<iostream>
#include "dubscript.cpp"

int main(int argc, char **argv)
{
  dbs::Dubscript prog = dbs::Dubscript::fromFile(argv[1]);

  std::vector<double> args;
  for (int i=2; i<argc; i++) {
    args.push_back(std::stod(argv[i]));
  }

  prog.run("main", args);
}
