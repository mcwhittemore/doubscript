#include "./check.h"

int main(int argc, char **argv)
{
  int failures = 0;
  failures += test::check("./tests/maths.doub", "./tests/fixtures/maths.log", {8});
  failures += test::check("./tests/funcs.doub", "./tests/fixtures/funcs.log", {5,8});
  return failures;
}
