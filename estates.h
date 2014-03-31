
#ifndef _classes_h
#define _classes_h

#include <string>

#include "matchers.h"

using namespace std;


class Land
{
  public:
    Land(string, string, int, float, string, int);

    virtual string formatted_str(void);
    virtual string to_str(void);

    float area(void) const;
    float totalPrice(void) const;

  private:
    string m_first, m_last, m_address;
    int m_nat_id, m_unit_price;
    float m_area;
};

class House : public Land
{
  public:
    House(string, string, int, float, string, int, int);
    House(string, string, int, float, string, int, int, int, int, int);

    enum Type {Villa, Appartment};

    int yearOfConstruction(void) const;
    int level(void) const;
    enum Type buildingType(void) const;

    virtual string formatted_str(void);
    virtual string to_str(void);

  private:
    int m_year, m_total_units, m_unit_number, m_level;
    enum Type m_type;
};

#endif

