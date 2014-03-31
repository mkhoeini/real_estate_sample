
#include "estates.h"

#include <sstream>

using namespace std;


Land::Land(string first, string last, int nat_id, float area, string addr, int price)
  : m_first(first), m_last(last), m_nat_id(nat_id), m_area(area), m_address(addr), m_unit_price(price)
{}

string Land::formatted_str()
{
  stringstream out;
  out << m_first << '\t' << m_last << '\t' << m_nat_id << '\t' << m_area << '\t' << m_address << '\t' << m_unit_price;
  return out.str();
}

string Land::to_str()
{
  // TODO
}

float Land::area() const
{
  return m_area;
}

float Land::totalPrice() const
{
  return m_area * m_unit_price;
}

House::House(string first, string last, int nat_num, float area, string addr, int price, int year)
  : Land(first, last, nat_num, area, addr, price), m_year(year), m_type(House::Villa), m_total_units(0), m_unit_number(0), m_level(0)
{}

House::House(string first, string last, int nat_num, float area, string addr, int price, int year, int tot_units, int unit_num, int level)
  : Land(first, last, nat_num, area, addr, price), m_year(year), m_type(House::Appartment), m_total_units(tot_units),
  m_unit_number(unit_num), m_level(level)
{}

string House::formatted_str()
{
  stringstream out;
  out << Land::formatted_str() << '\t' << m_year << '\t' << (m_type == House::Villa ? "Villa" : "Appartment") << '\t' << m_total_units << '\t'
    << m_unit_number << '\t' << m_level;
  return out.str();
}

string House::to_str()
{
  // TODO
}

int House::yearOfConstruction() const
{
  return m_year;
}

enum House::Type House::buildingType() const
{
  return m_type;
}

int House::level() const
{
  return m_level;
}

