
namespace test {

std::vector<std::string> byline(std::string s) {
  std::vector<std::string> out;

  size_t at = 0;
  size_t to = s.find("\n");
  while(to < s.size()) {
    out.push_back(s.substr(at, to-at-1));
    at = to+1;
    to = s.find("\n", at);
  }
  out.push_back(s.substr(at, s.size()-at));
  return out;
}

std::string dline(int t, std::string v) {
  std::string prefix = " ";
  if (t < 0) prefix = "-";
  if (t > 0) prefix = "+";
  return "\t" + prefix + " " + v + "\n";
}

int findMatch(std::string needle, std::vector<std::string> hay, int start) {
  for (int i=start; i<hay.size(); i++) {
    if (needle == hay[i]) return i;
  }
  return hay.size();
}

std::string diff(std::string left, std::string right) {
  std::vector<std::string> is = byline(left);
  std::vector<std::string> was = byline(right);

  std::string d = "";

  int isPos = 0;
  int wasPos = 0;
  int maxMatch = 2;
  int match = 0;
  while (isPos < is.size() && wasPos < was.size()) {
    if (is[isPos] == was[wasPos]) {
      match = match < maxMatch ? match + 1 : maxMatch;
      if (match <= 0) d = d + dline(0, is[isPos]);
    }
    else {
      // add context lines
      for(int i=match*-1; i<0 && isPos+i < is.size(); i++) {
        d = d + dline(0, is[isPos+i]);
      }

      match = -1;
      int isNext = findMatch(was[wasPos], is, isPos+1);
      int wasNext = findMatch(is[isPos], was, wasPos+1);
      
      int isD = isNext - isPos;
      int wasD = wasNext - wasPos;

      if (isD < wasD) {
        for(; isPos < isNext; isPos++) {
          d = d + dline(1, is[isPos]);
        }
      }

      if (wasD < isD) {
        for(; wasPos < wasNext; wasPos++) {
          d = d + dline(1, was[wasPos]);
        }
      }
    }

    isPos++;
    wasPos++;
  }

  while (wasPos < was.size()) {
    d = d + dline(-1, was[wasPos]);
    wasPos++;
  }

  while (isPos < is.size()) {
    d = d + dline(+1, is[isPos]);
    isPos++;
  }

  return d;
}
  
}
