#include <map>
#include <vector>
#include "command.cpp"

namespace mlg {
class Command;
class Function {
  std::map<std::string, double> dbls;
  std::vector<mlg::Command> cmds;
  std::vector<std::string> args;
  public:
    Function(){}
    Function(std::vector<std::string> ag, std::vector<std::string> logic) {
      args = ag;
      for(int i=0; i<logic.size(); i++) {
        mlg::Command cmd = mlg::Command(logic[i]);
        cmds.push_back(cmd);
      }
    }
    void run(std::vector<double> input, std::map<std::string, mlg::Function> funcs) {
      for(int i=0; i<input.size(); i++) {
        std::string arg = args[0] + "[" + std::to_string(i) + "]";
        dbls[arg] = input[i];
      }

      for(int i=0; i<cmds.size(); i++) {
        cmds[i].run(dbls, funcs);
      }
    }
    void run(double arg, std::map<std::string, mlg::Function> funcs){}
};
}
