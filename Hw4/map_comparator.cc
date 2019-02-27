#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <cmath>


struct Key_t
{
  double qsq;
  std::vector<int> d;
  std::string label;
  bool operator<(const Key_t &rhs) const;
  //std::ostream &operator<<(std::ostream &os, const Key_t &k );
};

std::ostream& operator<<(std::ostream &os, const Key_t &k )
{
  os << "{" << k.qsq << ", (";
  for (std::vector<int>::const_iterator i = k.d.begin(); i != k.d.end(); ++i)
  {
    os << *i << ' ';

  }
  os << "), ";
  os << k.label;
  os << "} ";
  return os;
}

bool Key_t::operator<(const Key_t &rhs) const
{
  if (this->qsq != rhs.qsq) { return this->qsq < rhs.qsq; }
  if (this->d.size() == rhs.d.size())
  {
    for (int i=0; i< this->d.size(); i++)
    {
      if (this->d[i] != rhs.d[i])
      {
        return this->d[i] < rhs.d[i];
      }
    }
  }
  else if (this->d.size() < rhs.d.size())
  {
    for (int i=0; i< this->d.size(); i++)
    {
      if (this->d[i] != rhs.d[i])
      {
        return this->d[i] < rhs.d[i];
      }
    }
    return true;
  }
  else
  {
    for (int i=0; i< rhs.d.size(); i++)
    {
      if (this->d[i] != rhs.d[i])
      {
        return this->d[i] < rhs.d[i];
      }
    }
    return false;
  }
  if (this->label != rhs.label) { return this->label < rhs.label; }
  return false;
}

int main()
{


  std::map<Key_t, double> Store;

  //test cases
  {
    Key_t k;
    k.qsq = 1.0;
    k.d = {0, 0, 0};
    k.label = "A1";
    double v = 1.0;
    Store.insert(std::make_pair(k, v));
  }

  {
    Key_t k;
    k.qsq = 1.01;
    k.d = {0, 0, 0};
    k.label = "A1";
    double v = 1.01;
    Store.insert(std::make_pair(k, v));
  }

  {
    Key_t k;
    k.qsq = 1.01;
    k.d = {0, 0, 0};
    k.label = "A2";
    double v = 2.0;
    Store.insert(std::make_pair(k, v));
  }

  {
    Key_t k;
    k.qsq = 1.01;
    k.d = {0, 0, 1};
    k.label = "A1";
    double v = 3.0;
    Store.insert(std::make_pair(k, v));
  }

  for (std::map<Key_t, double>::const_iterator it = Store.begin(); it != Store.end(); ++it)
  {
    std::cout << "key = " << (*it).first << ", value = " << (*it).second << std::endl;
  }

  return 0;
}
