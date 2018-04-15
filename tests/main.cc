#include "./assert.h"

int main(int argc, char **argv)
{
  int failures = 0;

  try {
    doub::Doubscript maths = doub::Doubscript::fromFile("./tests/scripts/maths.doub");

    failures += assert::equal(maths.run("add", {2,3}), 5, "2 + 3 = 5");
    failures += assert::equal(maths.run("add", {-2,-3}), -5, "-2 + -3 = -5");
    failures += assert::equal(maths.run("sub", {2,3}), -1, "2 - 3 = -1");
    failures += assert::equal(maths.run("mult", {2,3}), 6, "2 * 3 = 6");
    failures += assert::equal(maths.run("div", {6,3}), 2, "6 / 3 = 2");
    failures += assert::equal(maths.run("pow", {2,3}), 8, "2 ^ 3 = 8");
    failures += assert::equal(maths.run("all", {2,3,5,8,13,21}), -1, "2 - 3 + 5 * 8 / 13 ^ 21 = -1");
    failures += assert::equal(maths.run("ooo", {2,3,6}), -6, "(2 - 3) * 6 = -6");
    failures += assert::equal(maths.run("4min", {4}), 0, "4 - 1 - 1 - 1 - 1 = 0");

    doub::Doubscript logics = doub::Doubscript::fromFile("./tests/scripts/logics.doub");
    failures += assert::equal(logics.run("add", {2,3}), 5, "2 + 3 = 5");
    failures += assert::equal(logics.run("double", {2}), 4, "add(2,2) = 2 + 2 = 4");
    // TODO check that nothing is run after a return

    failures += assert::equal(logics.run("less", {2,4}), 1, "2 < 4 = 1");
    failures += assert::equal(logics.run("less", {4,2}), 0, "4 < 2 = 0");

    failures += assert::equal(logics.run("great", {2,4}), 0, "2 > 4 = 0");
    failures += assert::equal(logics.run("great", {4,2}), 1, "4 > 2 = 1");

    failures += assert::equal(logics.run("lequal", {2,4}), 1, "2 <= 4 = 1");
    failures += assert::equal(logics.run("lequal", {2,2}), 1, "2 <= 2 = 1");
    failures += assert::equal(logics.run("lequal", {4,2}), 0, "4 <= 2 = 0");

    failures += assert::equal(logics.run("gequal", {2,4}), 0, "2 >= 4 = 0");
    failures += assert::equal(logics.run("gequal", {2,2}), 1, "2 >= 2 = 1");
    failures += assert::equal(logics.run("gequal", {4,2}), 1, "4 >= 2 = 1");

    failures += assert::equal(logics.run("equal", {2,4}), 0, "2 == 4 = 0");
    failures += assert::equal(logics.run("equal", {2,2}), 1, "2 == 2 = 1");
    failures += assert::equal(logics.run("equal", {4,2}), 0, "4 == 2 = 0");

  } catch(const char* c) {
    std::cout << "FAIL (" << c << ")" << std::endl;
    return failures + 1;
  }

  return failures;
}
