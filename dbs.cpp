#include<iostream>
#include "doubscript.cpp"

int main(int argc, char **argv)
{
  dbs::Doubscript prog = dbs::Doubscript::fromFile(argv[1]);

  std::vector<double> args;
  for (int i=2; i<argc; i++) {
    args.push_back(std::stod(argv[i]));
  }

  prog.run("main", args);
}
