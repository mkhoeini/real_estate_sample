
#include "database.h"

#include <iterator>
#include <algorithm>


static Land land_from_str(string str)
{
  // TODO
}

Database::Database(string file_name)
  : m_file(file_name)
{
  string line;
  while(getline(m_file, line))
  {
    auto land = land_from_str(line);
    m_data.push_back(land);
  }
  m_file.seekp(0, ios::end);
}

void Database::add(Land land)
{
  m_data.push_back(land);
  m_file << land.to_str();
}

vector<Land> Database::search(SearchData data)
{
  vector<Land> result;

  copy_if(m_data.cbegin(), m_data.cend(), back_inserter(result),
      [data](Land l){return all_of(data.cbegin(), data.cend(),
        [l](Matcher *m){return m->matches(&l);});});
  
  return result;
}

