#include<iostream>
#include "mathlog.cpp"

int main(int argc, char **argv)
{
  mlg::Mathlog m = new mlg::Mathlog(argc[0]);
  std::vector<double> args = {7};
  m.run("main", args);
}
