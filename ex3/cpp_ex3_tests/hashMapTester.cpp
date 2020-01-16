#include "catch.hpp"
#include "HashMap.hpp"
#include <map>


static const std::vector<int> _keys = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
static const std::vector<int> _values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
void helper(std::vector<int>& keys, std::vector<char>& values)
{
    HashMap<int, char> m(keys, values);
}

int getRandomNumber(int max)
{
    return std::rand() % max;
}
TEST_CASE("HashMap works", "[HashMap]")
{
  SECTION("HashMap default constructor works")
  {
      const HashMap<int, int> map;
      CHECK(map.size() == 0);
      CHECK(map.capacity() == 16);
      CHECK(map.empty());
      CHECK(map.getLoadFactor() == 0);
      CHECK_THROWS(map.at(5));
  }

  SECTION("HashMap vector constructor works")
  {
      std::vector<int> wrongKeys{1, 2, 3};
      std::vector<char> wrongValues1{'a', 'b', 'c', 'd'};
      //check if the values > keys, then error expected
      CHECK_THROWS(helper(wrongKeys, wrongValues1));

      std::vector<char> wrongValues2{'a', 'b'};
      //check if the values < keys, then error expected
      CHECK_THROWS(helper(wrongKeys, wrongValues2));
      std::vector<int> keys1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
      std::vector<char> values1 = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};
      try
      {
          const HashMap<int, char> map(keys1, values1);
          CHECK(map.size() == 9);
          CHECK(map.capacity() == 16);
          CHECK(!map.empty());
          CHECK(map.getLoadFactor() == 9 / 16.0);
          for(int i = 1; i < 9; i++)
          {
              CHECK(map.containsKey(i));
              CHECK(map.at(i) == i - 1 + 'a');
          }
          CHECK(!map.containsKey(13));
      }
      catch(...)
      {
          //should not arrive here
          CHECK(false);
      }
      try
      {
          const HashMap<int, int> map(_keys, _values);
          CHECK(map.size() == 13);
          //should be bigger because of load factor
          CHECK(map.capacity() == 32);
          CHECK(!map.empty());
          CHECK(map.getLoadFactor() == 13 / 32.0);
          for(int i = 1; i < 14; i++)
          {
              CHECK(map.containsKey(i));
              CHECK(map.at(i) == i);
          }
          CHECK(!map.containsKey(14));
      }
      catch(...)
      {
          //should not arrive here
          CHECK(false);
      }
  }
  SECTION("HashMap copy constructor works")
  {
      try
      {
          HashMap<int, int> map(_keys, _values);
          HashMap<int, int> map1(map);
          CHECK(map1.size() == 13);
          //should be bigger because of load factor
          CHECK(map1.capacity() == 32);
          CHECK(!map1.empty());
          CHECK(map1.getLoadFactor() == 13 / 32.0);

          CHECK(map1.insert(14, 14));
          //check that the map before didnt change
          CHECK(map.size() == 13);
          CHECK(map.capacity() == 32);
          CHECK(!map.empty());
          CHECK(map.getLoadFactor() == 13 / 32.0);
          //check map1 changed
          CHECK(map1.size() == 14);
          //should be bigger because of load factor
          CHECK(map1.capacity() == 32);
          CHECK(!map1.empty());
          CHECK(map1.getLoadFactor() == 14 / 32.0);
          CHECK(map.erase(1));
          //check that the map1 before didnt change
          CHECK(map.size() == 12);
          CHECK(map1.size() == 14);
      }
      catch(...)
      {
          //should not arrive here
          CHECK(false);
      }
  }
  SECTION("HashMap bucket size works")
  {
      try
      {
          HashMap<int, int> map(_keys, _values);
          for(int i = 1; i < 14; i++)
          {
              CHECK(map.bucketSize(i) == 1);
          }
          CHECK_THROWS(map.bucketSize(-1));
          std::vector<int> keys = _keys, values = _values;
          keys.push_back(33);
          values.push_back(19);
          HashMap<int, int> map1(keys, values);
          CHECK(map.bucketSize(1) == 1);
          for(int i = 2; i < 14; i++)
          {
              CHECK(map.bucketSize(i) == 1);
          }
          CHECK_THROWS(map.bucketSize(-1));
      }
      catch(...)
      {
          //should not arrive here
          CHECK(false);
      }
  }

  SECTION("HashMap bucket index works")
  {
      try
      {
          const HashMap<int, int> map(_keys, _values);
          for(int i = 1; i < 14; i++)
          {
              CHECK(map.bucketIndex(i) == i);
          }
          CHECK_THROWS(map.bucketIndex(-1));
          std::vector<int> keys = _keys, values = _values;
          keys.push_back(33);
          values.push_back(19);
          HashMap<int, int> map1(keys, values);
          for(int i = 1; i < 14; i++)
          {
              CHECK(map1.bucketIndex(i) == i);
          }
          CHECK(map1.bucketIndex(33) == 1);
          CHECK_THROWS(map.bucketSize(-1));
      }
      catch(...)
      {
          //should not arrive here
          CHECK(false);
      }
  }

  SECTION("HashMap contains works")
  {
      try
      {
          const HashMap<int, int> map(_keys, _values);
          for(int i = 0; i < 13; i++)
          {
              CHECK(map.containsKey(_keys[i]));
          }
          CHECK_THROWS(map.at(-1));
      }
      catch(...)
      {
          //should not arrive here
          CHECK(false);
      }
  }

  SECTION("HashMap at works")
  {
      try
      {
          HashMap<int, int> map(_keys, _values);
          for(int i = 0; i < 13; i++)
          {
              CHECK_NOTHROW(map.at(_keys[i]));
              CHECK(map.at(_keys[i]) == _values[i]);
          }
          map.at(1) = 4;
          CHECK(map.at(1) == 4);
          CHECK_THROWS(map.at(-1));

          const HashMap<int, int> map1(_keys, _values);
          for(int i = 0; i < 13; i++)
          {
              CHECK_NOTHROW(map1.at(_keys[i]));
              CHECK(map1.at(_keys[i]) == _values[i]);
          }
          CHECK_THROWS(map1.at(-1));
      }
      catch(...)
      {
          //should not arrive here
          CHECK(false);
      }
  }

  SECTION("HashMap clear works")
  {
      try
      {
          HashMap<int, int> map(_keys, _values);
          map.clear();
          CHECK(map.size() == 0);
          CHECK(map.empty());
          CHECK(map.capacity() == 32);
          CHECK(map.getLoadFactor() == 0);
          for(int i = 1; i < 14; i++)
          {
              CHECK(!map.containsKey(i));
          }
          HashMap<int, int> map1;
          //both maps don't have keys so they are equal
          CHECK(map == map1);
      }
      catch(...)
      {
          //should not arrive here
          CHECK(false);
      }
  }

  SECTION("HashMap insert works")
  {
      std::vector<int> keys = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
      std::vector<int> values = {13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
      int size = 0;
      try
      {
          HashMap<int, int> map;
          for(int i = 0; i < 12; i++)
          {
              size++;
              CHECK(map.insert(keys[i], values[i]));
              CHECK(map.size() == size);
              CHECK(map.at(keys[i]) == values[i]);
          }
          CHECK(map.insert(keys[12], values[12]));
          CHECK(!map.insert(keys[12], 1));
          CHECK(map.size() == 13);
          CHECK(map.capacity() == 32);
          CHECK(map.at(keys[12]) == values[12]);

          map.clear();
          int val;
          size = 0;
          for(int i = 0; i < 200; i++)
          {
              size++;
              val = getRandomNumber(500);
              CHECK(map.insert(i, val));
              CHECK(map.size() == size);
              CHECK(map.getLoadFactor() == (double) map.size() / map.capacity());
              CHECK(map.at(i) == val);
          }
          CHECK(map.capacity() == 512);
          CHECK(!map.empty());
      }catch(...)
      {
          //should not arrive here
          CHECK(false);
      }
  }


  SECTION("HashMap erase works")
  {
      std::vector<int> keys = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
      std::vector<int> values = {13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
      try
      {
          int size = 13;
          HashMap<int, int> map(keys, values);
          for(int i = 1; i < 6; i++)
          {
              CHECK(map.erase(i));
              CHECK(map.capacity() == 32);
              size--;
              CHECK(map.size() == size);
              CHECK(map.getLoadFactor() == size / 32.0);
          }
          CHECK(map.erase(6));
          CHECK(!map.erase(-1));
          CHECK(map.capacity() == 16);
          CHECK(map.size() == 7);
          CHECK(map.getLoadFactor() == 7 / 16.0);
          for(int i = 1; i < 7; i++)
          {
              CHECK(!map.containsKey(i));
              CHECK_THROWS(map.at(i));
          }
          for(int i = 7; i < 13; i++)
          {
              CHECK(map.containsKey(i));
              CHECK_NOTHROW(map.at(i));
          }
      }catch(...)
      {
          //should not arrive here
          CHECK(false);
      }
  }

  SECTION("HashMap operator==, operator!= works")
  {
      try
      {
          HashMap<int, int> map(_keys, _values);
          HashMap<int, int> map1(_keys, _values);
          HashMap<int, int> map2;
          CHECK(map == map1);
          CHECK(map == map);
          CHECK(!(map != map1));
          CHECK(!(map != map));
          CHECK(map != map2);
          CHECK(map2 == map2);
          CHECK(map.insert(-2, -2));
          CHECK(map != map1);
          CHECK(!(map == map1));
      }
      catch(...)
      {
          //should not arrive here
          CHECK(false);
      }
  }

  SECTION("HashMap operator= works")
  {
      try
      {
          const HashMap<int, int> map(_keys, _values);
          HashMap<int, int> map1;
          map1 = map;
          CHECK(map == map1);
          CHECK(map.size() == map1.size());
          CHECK(map.capacity() == map1.capacity());
          CHECK(map1.insert(14, 14));
          CHECK(map1.containsKey(14));
          CHECK(!map.containsKey(14));
      }
      catch(...)
      {
          //should not arrive here
          CHECK(false);
      }
  }

  SECTION("HashMap operator= check self works")
  {
      try
      {
          HashMap<int, int> map(_keys, _values);
          map = map;
          CHECK(map.insert(15, 15));
          CHECK(map == map);
          CHECK(map.size() == _keys.size() + 1);
          CHECK(map.capacity() == 32);
      }
      catch(...)
      {
          //should not arrive here
          CHECK(false);
      }
  }

  SECTION("HashMap operator[] works")
  {
      try
      {
          HashMap<int, int> map;
          for(int i = 0; i < 15; i++)
          {
              map[i] = 2 * i;
              CHECK(map.containsKey(i));
              CHECK(map.at(i) == 2 * i);
              CHECK(map.size() == i + 1);
          }
          CHECK(map.capacity() == 32);
          map[1] = 0;
          CHECK(map.containsKey(1));
          CHECK(map.at(1) == 0);
          CHECK(map.size() == 15);
      }
      catch(...)
      {
          //should not arrive here
          CHECK(false);
      }
  }

  SECTION("HashMap iterator works")
  {
      try
      {
          HashMap<int, int> map;
          for(unsigned int i = 0; i < 15; i++)
          {
              map[i] = 5 * i;
          }
          int counter = 0;
          auto it = map.cbegin();
          //check values in iterator
          for(; it != map.cend(); it++)
          {
              counter++;
              CHECK((*it).first * 5 == (*it).second);
          }
          //check the amount of values
          CHECK(counter == 15);
          //check that can run twice
          for(; it != map.cend(); ++it)
          {
              counter++;
              CHECK((*it).first * 5 == (*it).second);
          }
      }
      catch(...)
      {
          //should not arrive here
          CHECK(false);
      }
  }


  SECTION("HashMap random insert and deletes checks works")
  {
      try
      {
          HashMap<int, int> map;
          std::map<int, int> realMap;
          int num1, num2;
          for(unsigned int i = 0; i < 200; i++)
          {
              num1 = getRandomNumber(1000);
              num2 = getRandomNumber(500);
              map[num1] = num2;
              realMap[num1] = num2;
          }
          CHECK(map.size() == realMap.size());
          //check at & [], iterator
          for(auto it = map.cbegin(); it != map.cend(); ++it)
          {
              CHECK(realMap.count((*it).first) == 1);
              CHECK(realMap.at((*it).first) == (*it).second);
          }

          for(auto it : realMap)
          {
              CHECK(map.containsKey(it.first));
              CHECK(map.at(it.first) == it.second);
          }

          //check erase
          for(unsigned int i = 0; i < 200; i++)
          {
              num1 = getRandomNumber(1000);
              if(realMap.erase(num1))
              {
                  CHECK(map.erase(num1));
              }
          }
          CHECK(map.size() == realMap.size());
          map.clear();
          realMap.clear();
          CHECK(map.size() == realMap.size());
          //check insert this time
          for(unsigned int i = 0; i < 200; i++)
          {
              num1 = getRandomNumber(1000);
              num2 = getRandomNumber(500);
              if(!map.containsKey(num1))
              {
                  CHECK(map.insert(num1, num2));
                  realMap[num1] = num2;
              }
          }
          CHECK(map.size() == realMap.size());
          //check at & [], iterator
          for(auto it = map.cbegin(); it != map.cend(); ++it)
          {
              CHECK(realMap.count((*it).first) == 1);
              CHECK(realMap.at((*it).first) == (*it).second);
          }

          for(auto it : realMap)
          {
              CHECK(map.containsKey(it.first));
              CHECK(map.at(it.first) == it.second);
          }
      }
      catch(...)
      {
          //should not arrive here
          CHECK(false);
      }
  }
}
