
#ifndef _database_h
#define _database_h


#include <string>
#include <vector>
#include <fstream>

#include "estates.h"

using namespace std;


class Database
{
  public:
    Database(string file_name);

    void add(Land);
    vector<Land> search(SearchData);

  private:
    fstream m_file;
    vector<Land> m_data;
};


#endif
