
#include <iostream>
#include <string>
#include <fstream>

#include "database.h"
#include "estates.h"
#include "matchers.h"

using namespace std;


const string db_name = "data.db";

enum class Choise {
  input_land_data = 1,
  input_house_data,
  search_land_data,
  search_house_data,
  quit
};

Choise show_menu(void);
void process_choise(Choise, Database &);
Land get_new_land(void);
House get_new_house(void);
SearchData get_search_land(void);
SearchData get_search_house(void);
void print_results(vector<Land>);

int main()
{
  Database db(db_name);

  auto choise = show_menu();
  while (choise != Choise::quit)
  {
    process_choise(choise, db);
    choise = show_menu();
  }

  return 0;
}

Choise show_menu()
{
  const string menu_items[] = {
    "1- Enter new land data",
    "2- Enter new house data",
    "3- Search a land",
    "4- Search a house",
    "5- quit"
  };

  for(auto entry: menu_items)
  {
    cout << entry << endl;
  }

  int choise = 0;
  while (choise < 1 || choise > 5)
  {
    cout << endl << "Enter your choise: ";
    cin >> choise;
  }

  return static_cast<Choise>(choise);
}

void process_choise(Choise choise, Database &db)
{
  switch(choise)
  {
    case Choise::input_land_data:
      {
        auto land = get_new_land();
        db.add(land);
        break;
      }

    case Choise::input_house_data:
      {
        auto house = get_new_house();
        db.add(house);
        break;
      }

    case Choise::search_land_data:
      {
        auto search_land = get_search_land();
        auto lands = db.search(search_land);
        print_results(lands);
        break;
      }

    case Choise::search_house_data:
      {
        auto search_house = get_search_house();
        auto houses = db.search(search_house);
        print_results(houses);
        break;
      }

    default:
      break;
  }
}

Land get_new_land()
{
  string first, last;
  int nat_num;
  float area;
  string addr;
  int unit_price;

  cout << "\nEnter the owner's first name: ";
  cin.ignore(1000, '\n');
  getline(cin, first);

  cout << "\nEnter the owner's last name: ";
  getline(cin, last);

  cout << "\nEnter the owner's national Id: ";
  cin >> nat_num;

  cout << "\nEnter the land's total area: ";
  cin >> area;

  cout << "\nEnter the land's address: ";
  cin.ignore(1000, '\n');
  getline(cin, addr);

  cout << "\nEnter the land's per square metter price: ";
  cin >> unit_price;

  return Land(first, last, nat_num, area, addr, unit_price);
}

House get_new_house()
{
  string first, last;
  int nat_num;
  float area;
  string addr;
  int unit_price;
  int b_type;
  int year;
  int total_units, unit_num, level;

  cout << "\nEnter the owner's first name: ";
  cin.ignore(1000, '\n');
  getline(cin, first);

  cout << "\nEnter the owner's last name: ";
  getline(cin, last);

  cout << "\nEnter the owner's national Id: ";
  cin >> nat_num;

  cout << "\nEnter the building's total area: ";
  cin >> area;

  cout << "\nEnter the building's address: ";
  cin.ignore(1000, '\n');
  getline(cin, addr);

  cout << "\nEnter the building's per square metter price: ";
  cin >> unit_price;

  cout << "\nEnter the building's type."
    << "\n  1- Villa"
    << "\n  2- Appartment"
    << "\n? ";
  cin >> b_type;
  
  cout << "\nEnter the year of construction of building: ";
  cin >> year;

  if(b_type == 2)
  {
    cout << "\nHow many units the appartment has in total: ";
    cin >> total_units;

    cout << "\nEnter the appartment's unit number: ";
    cin >> unit_num;

    cout << "\nEnter the appartment's level number: ";
    cin >> level;

    return House(first, last, nat_num, area, addr, unit_price, year, total_units, unit_num, level);
  }

  return House(first, last, nat_num, area, addr, unit_price, year);
}

SearchData get_search_land()
{
  SearchData result;
  int lower_area, upper_area,
      lower_price, upper_price;

  cout << "\nEnter the lower bound of the requested area(negative number to ignore area): ";
  cin >> lower_area;

  if (lower_area >= 0)
  {
    cout << "\nEnter the upper bound of the area: ";
    cin >> upper_area;

    result.push_back(new AreaMatcher(lower_area, upper_area));
  }

  cout << "\nEnter the lower bound of the requested price(negative number to ignore the price): ";
  cin >> lower_price;

  if (lower_price >= 0)
  {
    cout << "\nEnter the upper bound of the price: ";
    cin >> upper_price;

    result.push_back(new TotalPriceMatcher(lower_price, upper_price));
  }

  return result;
}

SearchData get_search_house()
{
  SearchData result;
  int lower_area, upper_area,
      lower_price, upper_price,
      lower_level, upper_level,
      b_type, year;

  cout << "\nEnter the lower bound of the requested area(negative number to ignore area): ";
  cin >> lower_area;

  if (lower_area >= 0)
  {
    cout << "\nEnter the upper bound of the area: ";
    cin >> upper_area;
    
    result.push_back(new AreaMatcher(lower_area, upper_area));
  }

  cout << "\nEnter the lower bound of the requested price(negative number to ignore the price): ";
  cin >> lower_price;

  if (lower_price >= 0)
  {
    cout << "\nEnter the upper bound of the price: ";
    cin >> upper_price;

    result.push_back(new TotalPriceMatcher(lower_price, upper_price));
  }

  cout << "\nWhat kind of building you request."
    << "\n  0- ignore"
    << "\n  1- Villa"
    << "\n  2- Appartment";
  cin >> b_type;

  if (b_type == 1)
  {
    result.push_back(new BuildingTypeMatcher(House::Villa));
  }
  else if (b_type == 2)
  {
    result.push_back(new BuildingTypeMatcher(House::Appartment));
  }

  cout << "\nFrom what year do you want it to be newer(0 to ignore): ";
  cin >> year;

  if (year > 0)
  {
    result.push_back(new NewerYearMatcher(year));
  }

  if (b_type == 2)
  {
    cout << "\nWhat is the lowest level you request(negative number to ignore level): ";
    cin >> lower_level;
    
    if (lower_level >= 0)
    {
      cout << "\nWhat is the highest level you request: ";
      cin >> upper_level;

      result.push_back(new LevelMatcher(lower_level, upper_level));
    }
  }

  return result;
}

void print_results(vector<Land> results)
{
  cout << "\nHere is the list of all matching results:\n";

  for(auto land: results)
  {
    cout << land.formatted_str() << endl;
  }
}

