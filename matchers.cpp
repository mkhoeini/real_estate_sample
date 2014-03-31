
#include "matchers.h"

#include "estates.h"


AreaMatcher::AreaMatcher(int low, int high)
  : m_low(low), m_high(high)
{}

bool AreaMatcher::matches(Land const *land)
{
  return (land->area() >= m_low) && (land->area() <= m_high);
}

TotalPriceMatcher::TotalPriceMatcher(int low, int high)
  : m_low(low), m_high(high)
{}

bool TotalPriceMatcher::matches(Land const *land)
{
  return (land->totalPrice() >= m_low) && (land->totalPrice() <= m_high);
}

BuildingTypeMatcher::BuildingTypeMatcher(int _type)
  : m_type(_type)
{}

bool BuildingTypeMatcher::matches(Land const *land)
{
  return dynamic_cast<House const *>(land)->buildingType() == m_type;
}

NewerYearMatcher::NewerYearMatcher(int year)
  : m_year(year)
{}

bool NewerYearMatcher::matches(Land const *land)
{
  return dynamic_cast<House const *>(land)->yearOfConstruction() >= m_year;
}

LevelMatcher::LevelMatcher(int low, int high)
  : m_low(low), m_high(high)
{}

bool LevelMatcher::matches(Land const *land)
{
  auto h = dynamic_cast<House const *>(land);
  return (h->level() >= m_low) && (h->level() <= m_high);
}

