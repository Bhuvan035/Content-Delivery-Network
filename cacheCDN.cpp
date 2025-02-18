#include "cacheCDN.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

namespace ICS45C {
namespace CDN {
// vector<string> valuesvec;
Cache::Cache(unsigned int freshnessCount)
    : freshnesscount(freshnessCount), totaltimeread(0) {}

Cache::~Cache() {
  for (pair<string, char*> p : mainb1map) {
    delete (p.second);
  }
  mainb1map.clear();
}
string Cache::readf(string fname) {
  totaltimeread++;
  ifstream inFile;
  string text;
  string finaltext;
  inFile.open(fname);
  while (getline(inFile, text)) {
    finaltext += text + "\n";
  }
  inFile.close();
  return finaltext;
}

char* Cache::readbf(string bfname) {
  totaltimeread++;
  streampos size;
  char* memblock;
  ifstream inBinFile(bfname, ios::in | ios::binary | ios::ate);
  size = inBinFile.tellg();
  memblock = new char[size];
  inBinFile.seekg(0, ios::beg);
  inBinFile.read(memblock, size);
  inBinFile.close();
  return memblock;
}

string Cache::getText(string filepath) {
  string text;
  string rettext;
  int fc;
  string vectext;
  if (main1map.empty() == true) {
    text = readf(filepath);
    main1map[filepath] = text;
    main2map[filepath] = freshnesscount - 1;
    if (countmap.find(filepath) != countmap.end()) {
      countmap[filepath] += 1;
    } else {
      countmap[filepath] = 1;
    }
    rettext = text;
  } else {
    if (main1map.find(filepath) != main1map.end()) {
      fc = main2map[filepath];
      if (freshnesscount == 0 || freshnesscount == 1) {
        text = readf(filepath);
        fc = 0;
        main1map[filepath] = text;
        main2map[filepath] = fc;
        rettext = text;
        countmap[filepath] += 1;
      } else {
        if (fc > 0) {
          rettext = main1map[filepath];
          main2map[filepath] -= 1;
          countmap[filepath] += 1;
        } else {
          text = readf(filepath);
          fc = freshnesscount - 1;
          main1map[filepath] = text;
          main2map[filepath] = fc;
          rettext = text;
          countmap[filepath] += 1;
        }
      }
    } else {
      text = readf(filepath);
      fc = freshnesscount - 1;
      main1map[filepath] = text;
      main2map[filepath] = fc;
      rettext = text;
      countmap[filepath] += 1;
    }
  }
  return rettext;
  /*if (mainmap.empty() == true) {
  valuesvec.clear();
  text = readf(filepath);
  valuesvec.push_back(text);
  valuesvec.push_back(to_string(freshnesscount - 1));
  mainmap[filepath] = valuesvec;
  if (countmap.find(filepath) != countmap.end()) {
    countmap[filepath] += 1;
  } else {
    countmap[filepath] = 1;
  }
  auto val = mainmap.find(filepath);
  vectext = (val->second)[0];
  // fc = stoi((val->second)[1]);
  rettext = vectext;
} else {
  if (mainmap.find(filepath) != mainmap.end()) {
    valuesvec.clear();
    auto val = mainmap.find(filepath);
    fc = stoi((val->second)[1]);
    if (freshnesscount == 0 || freshnesscount == 1) {
      valuesvec.clear();
      text = readf(filepath);
      valuesvec.push_back(text);
      valuesvec.push_back(to_string(0));
      // valuesvec.push_back(to_string(freshnesscount - 1));
      mainmap[filepath] = valuesvec;
      countmap[filepath] += 1;
      auto val = mainmap.find(filepath);
      vectext = (val->second)[0];
      // fc = stoi((val->second)[1]);
      rettext = vectext;
    } else {
      if (fc > 0) {
        vectext = (val->second)[0];
        rettext = vectext;
        fc -= 1;
        valuesvec.clear();
        valuesvec.push_back(vectext);
        valuesvec.push_back(to_string(fc));
        mainmap[filepath] = valuesvec;
        countmap[filepath] += 1;
      } else {
        valuesvec.clear();
        text = readf(filepath);
        valuesvec.push_back(text);
        valuesvec.push_back(to_string(freshnesscount - 1));
        mainmap[filepath] = valuesvec;
        countmap[filepath] += 1;
        auto val = mainmap.find(filepath);
        vectext = (val->second)[0];
        // fc = stoi((val->second)[1]);
        rettext = vectext;
      }
    }
  } else {
    valuesvec.clear();
    text = readf(filepath);
    valuesvec.push_back(text);
    valuesvec.push_back(to_string(freshnesscount - 1));
    mainmap[filepath] = valuesvec;
    countmap[filepath] += 1;
    auto val = mainmap.find(filepath);
    vectext = (val->second)[0];
    // fc = stoi((val->second)[1]);
    rettext = vectext;
  }
}*//*if (mainmap.empty() == true) {
  valuesvec.clear();
  text = readf(filepath);
  valuesvec.push_back(text);
  valuesvec.push_back(to_string(freshnesscount - 1));
  mainmap[filepath] = valuesvec;
  if (countmap.find(filepath) != countmap.end()) {
    countmap[filepath] += 1;
  } else {
    countmap[filepath] = 1;
  }
  auto val = mainmap.find(filepath);
  vectext = (val->second)[0];
  // fc = stoi((val->second)[1]);
  rettext = vectext;
} else {
  if (mainmap.find(filepath) != mainmap.end()) {
    valuesvec.clear();
    auto val = mainmap.find(filepath);
    fc = stoi((val->second)[1]);
    if (freshnesscount == 0 || freshnesscount == 1) {
      valuesvec.clear();
      text = readf(filepath);
      valuesvec.push_back(text);
      valuesvec.push_back(to_string(0));
      // valuesvec.push_back(to_string(freshnesscount - 1));
      mainmap[filepath] = valuesvec;
      countmap[filepath] += 1;
      auto val = mainmap.find(filepath);
      vectext = (val->second)[0];
      // fc = stoi((val->second)[1]);
      rettext = vectext;
    } else {
      if (fc > 0) {
        vectext = (val->second)[0];
        rettext = vectext;
        fc -= 1;
        valuesvec.clear();
        valuesvec.push_back(vectext);
        valuesvec.push_back(to_string(fc));
        mainmap[filepath] = valuesvec;
        countmap[filepath] += 1;
      } else {
        valuesvec.clear();
        text = readf(filepath);
        valuesvec.push_back(text);
        valuesvec.push_back(to_string(freshnesscount - 1));
        mainmap[filepath] = valuesvec;
        countmap[filepath] += 1;
        auto val = mainmap.find(filepath);
        vectext = (val->second)[0];
        // fc = stoi((val->second)[1]);
        rettext = vectext;
      }
    }
  } else {
    valuesvec.clear();
    text = readf(filepath);
    valuesvec.push_back(text);
    valuesvec.push_back(to_string(freshnesscount - 1));
    mainmap[filepath] = valuesvec;
    countmap[filepath] += 1;
    auto val = mainmap.find(filepath);
    vectext = (val->second)[0];
    // fc = stoi((val->second)[1]);
    rettext = vectext;
  }
}*/
}

char* Cache::getBinary(std::string filepath) {
  char* text;
  char* rettext;
  int fc = 0;
  if (mainb1map.empty() == true) {
    text = readbf(filepath);
    fc = freshnesscount - 1;
    mainb1map[filepath] = text;
    mainb2map[filepath] = fc;
    if (countbmap.find(filepath) != countbmap.end()) {
      countbmap[filepath] += 1;
    } else {
      countbmap[filepath] = 1;
    }
    rettext = text;
  } else {
    if (mainb1map.find(filepath) != mainb1map.end()) {
      fc = mainb2map[filepath];
      if (freshnesscount == 0 || freshnesscount == 1) {
        delete[] mainb1map[filepath];
        text = readbf(filepath);
        fc = 0;
        mainb1map[filepath] = text;
        mainb2map[filepath] = fc;
        rettext = text;
        countbmap[filepath] += 1;
      } else {
        if (fc > 0) {
          rettext = mainb1map[filepath];
          mainb2map[filepath] = (mainb2map[filepath]) - 1;
          countbmap[filepath] += 1;
        } else {
          delete[] mainb1map[filepath];
          text = readbf(filepath);
          fc = freshnesscount - 1;
          mainb1map[filepath] = text;
          mainb2map[filepath] = fc;
          rettext = text;
          countbmap[filepath] += 1;
        }
      }
    } else {
      delete[] mainb1map[filepath];
      text = readbf(filepath);
      fc = freshnesscount - 1;
      mainb1map[filepath] = text;
      mainb2map[filepath] = fc;
      rettext = text;
      countbmap[filepath] += 1;
    }
  }

  return rettext;
}

bool Cache::isCached(string filepath) {
  if (main1map.find(filepath) != main1map.end()) {
    return true;
  } else if (mainb1map.find(filepath) != mainb1map.end()) {
    return true;
  } else {
    return false;
  }
}

unsigned int Cache::getFreshness(string filepath) {
  unsigned int f1 = 0;
  if (freshnesscount == 0) {
    f1 = 0;
  } else {
    if (isCached(filepath) == false) {
      f1 = 0;
    } else {
      if (main1map.find(filepath) != main1map.end()) {
        f1 = main2map[filepath];
      } else {
        f1 = mainb2map[filepath];
      }
    }
  }
  return f1;
}

/*unsigned int Cache::getFreshness(string filepath) {
  unsigned int f1 = 0;
  string vectext1 = 0;
  if (isCached(filepath) == false) {
    return 0;
  } else {
    auto val = mainmap.find(filepath);
    f1 = (stoul)((val->second)[1]);
    if (f1 == freshnesscount) {
      return 0;
    } else {
      return f1;
    }
  }
}*/

void Cache::markFileFresh(string filepath) {
  if (isCached(filepath) == true) {
    if (main1map.find(filepath) != main1map.end()) {
      main2map[filepath] = freshnesscount;
      /*unsigned int f1 = 0;
      string vectext1;
      auto val = mainmap.find(filepath);
      valuesvec.clear();
      vectext1 = (val->second)[0];
      f1 = freshnesscount;
      valuesvec.push_back(vectext1);
      valuesvec.push_back(to_string(f1));
      mainmap[filepath] = valuesvec;*/

    } else {
      mainb2map[filepath] = freshnesscount;
    }
  }
}

void Cache::purgeCache() {
  for (pair<string, char*> p : mainb1map) {
    delete (p.second);
  }
  main1map.clear();
  main2map.clear();
  mainb1map.clear();
  mainb2map.clear();
}

string Cache::topFile() {
  int check = 0;
  string checkfinal;
  for (pair<string, int> p : countmap) {
    if ((p.second) > check) {
      check = p.second;
      checkfinal = p.first;
    }
  }
  for (pair<string, int> p1 : countbmap) {
    if ((p1.second) > check) {
      check = p1.second;
      checkfinal = p1.first;
    }
  }
  if (check == 0) {
    checkfinal = "";
  } else {
    checkfinal = checkfinal;
  }
  return checkfinal;
}

string Cache::getStats() {
  float totalreq = 0;
  float totalfreq = 0;
  float num;
  if ((countmap.empty() != true) || (countbmap.empty() != true)) {
    for (pair<string, int> p : countmap) {
      totalreq += p.second;
      totalfreq += 1;
    }
    for (pair<string, int> p1 : countbmap) {
      totalreq += p1.second;
      totalfreq += 1;
    }
  } else {
    totalreq = 0;
    totalfreq = 0;
  }

  if (totalfreq == 0) {
    num = 0;
  } else {
    num = totalreq / totalfreq;
  }
  stringstream stream;
  stream << fixed << setprecision(2) << num;
  string finalnum = stream.str();

  string final;
  final = "Cache Stats\n";
  final += "----------\n";
  final += "Total requests: ";
  final += to_string((int)totalreq) + "\n";
  final += "Total files requested: " + to_string((int)totalfreq) + "\n";
  final += "Average requests per file: " + finalnum + "\n";
  final += "Top file: " + topFile() + " (" +
           to_string(countmap[topFile()] + countbmap[topFile()]) +
           " requests)\n";
  final += "Total times read from disk: " + to_string(totaltimeread) + "\n";
  final += "----------\n";
  return final;
}

}  // namespace CDN
}  // namespace ICS45C
