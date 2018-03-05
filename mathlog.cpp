namespace mlg {
class Mathlog {
  std::map<std::string, mlg::Function> functions;
  
  Mathlog(std::string filename) { 
    // read file into blob of text
    // parse function name, args and logic out of text
    // create mlg::Functions with this data
    // store them in a map
  }

  void run(std::string f, std::vector<double> args) {
    mlg::Function func = functions[f];
    func.run(args);
  }

  void run(std::string f, double arg) {
    mlg::Function func = functions[f];
    func.run(arg);
  }
}
}
