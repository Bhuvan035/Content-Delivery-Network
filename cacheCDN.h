#ifndef __CACHECDN_H__
#define __CACHECDN_H__

using namespace std;
#include <map>
#include <string>
#include <vector>
/* Add any includes here! */
namespace ICS45C {
namespace CDN {

using namespace std;
class Cache {
 public:
  unsigned int freshnesscount;
  int totaltimeread;
  map<string, string> main1map;
  map<string, unsigned int> main2map;
  map<string, char*> mainb1map;
  map<string, int> mainb2map;
  map<string, int> countbmap;
  map<string, int> countmap;
  Cache(unsigned int freshnessCount);
  ~Cache();
  string readf(string fname);
  char* readbf(string bfname);
  string getText(std::string filepath);
  char* getBinary(std::string filepath);
  bool isCached(std::string filepath);
  unsigned int getFreshness(std::string filepath);
  void markFileFresh(std::string filepath);
  void purgeCache();
  string topFile();
  string getStats();
};

/* Define your class here! */

}  // namespace CDN
}  // namespace ICS45C

#endif  // __CACHECDN_H__
