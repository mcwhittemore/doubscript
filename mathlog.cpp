#include <map>
#include <vector>
#include "src/function.cpp"

namespace mlg {
class Mathlog {
  std::map<std::string, mlg::Function> functions;
  
  private:
    std::string readFile(std::string filename) { 
      return "main: args // comment \n  input = args[0]\n  log(input)";
    }

    void addFunction(std::vector<std::string> lines) {
      // get func logic
      std::vector<std::string> logic;
      for(int i=1; i<lines.size(); i++) {
        std::string line = stripComments(lines[i]);
        if (line.length() > 0) logic.push_back(line);
      }

      if (logic.size() == 0) return;

      // get func name and args
      std::string header = stripComments(lines[0]);
      int len = header.length();
      std::vector<std::string> headerParts;
      std::string hold = "";
      for(int i=0; i<len; i++) {
        if (header[i] == ',' || header[i] == ':') {
          headerParts.push_back(hold);
          hold = "";
        }
        else {
          hold.push_back(header[i]);
        }
      }
      if (hold.length() > 0) headerParts.push_back(hold);

      std::string name = headerParts[0];
      std::cout << "func: " << name << "\n";

      if (name.length() == 0) throw "functions must start with a name";

      headerParts.erase(headerParts.begin());
      functions[name] = mlg::Function(headerParts, logic);
    }

    std::string stripComments(std::string line) {
      std::string out = "";
      int len = line.length();
      for (int i=0; i<len; i++) {
        if (line[i] == '/' && line[i+1] == '/') break;
        if (line[i] != ' ' || line[i] != '\t') out.push_back(line[i]);
      }
      return out;
    }

  public:
    Mathlog(std::string filename) { 
      // read file into blob of text
      std::string content = readFile(filename);
      int len = content.length();
      std::vector<std::string> lines;
      std::string line = "";
      for(int i=0; i<len; i++) {
        if (content[i] == '\n' && line.length() == 0) continue;
        else if (content[i] == '\n' && line[0] == ' ') {
          lines.push_back(line);
          line = "";
        }
        else if (content[i] == '\n') {
          addFunction(lines);
          lines.clear();
          lines.push_back(line);
          line = "";
        }
        else {
          line.push_back(content[i]);
        }
      }
      if (line.length() > 0) lines.push_back(line);
      if (lines.size() > 0) addFunction(lines);
    }

    void run(std::string f, std::vector<double> args) {
      mlg::Function func = functions[f];
      func.run(args);
    }

    void run(std::string f, double arg) {
      mlg::Function func = functions[f];
      func.run(arg);
    }
};
}
