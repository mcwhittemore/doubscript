#include <map>
#include <vector>

namespace mlg {
class Function {
  std::map<std::string, double> dbls;
  public:
    Function(){}
    Function(std::vector<std::string> args, std::vector<std::string> logic) {
      std::cout << "args: ";
      for(int i=0; i<args.size(); i++) {
        std::cout << args[i] + " ";
        dbls[args[i]] = 0;
      }
      std::cout << "\n";

      std::cout << "logic: \n";
      for(int i=0; i<logic.size(); i++) {
        std::cout << "\t" << logic[i] << "\n";
      }
      std::cout << "\n";
    }
    void run(std::vector<double> args) {}
    void run(double arg){}
};
}
