
#ifndef _matchers_h
#define _matchers_h

#include <vector>

using namespace std;


class Land;
class Matcher
{
  public:
    virtual bool matches(Land const *) = 0;
};

class AreaMatcher : public Matcher
{
  public:
    AreaMatcher(int, int);

    virtual bool matches(Land const *);

  private:
    int m_low, m_high;
};

class TotalPriceMatcher : public Matcher
{
  public:
    TotalPriceMatcher(int, int);

    virtual bool matches(Land const *);

  private:
    int m_low, m_high;
};

class BuildingTypeMatcher : public Matcher
{
  public:
    BuildingTypeMatcher(int);

    virtual bool matches(Land const *);

  private:
    int m_type;
};

class NewerYearMatcher : public Matcher
{
  public:
    NewerYearMatcher(int);

    virtual bool matches(Land const *);

  private:
    int m_year;
};

class LevelMatcher : public Matcher
{
  public:
    LevelMatcher(int, int);

    virtual bool matches(Land const *);

  private:
    int m_low, m_high;
};

typedef vector<Matcher *> SearchData;

#endif
