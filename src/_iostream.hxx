#pragma once
#include <utility>
#include <string>
#include <vector>
#include <ostream>
#include <fstream>
#include <iostream>
#include <type_traits>

using std::pair;
using std::string;
using std::vector;
using std::ios;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::is_fundamental;
using std::cout;




// READ-FILE
// ---------

string readFile(const char *pth) {
  string a; ifstream f(pth);
  f.seekg(0, ios::end);
  a.resize(f.tellg());
  f.seekg(0);
  f.read((char*) a.data(), a.size());
  return a;
}
string readFile(const string& pth) {
  return readFile(pth.c_str());
}




// WRITE-FILE
// ----------

void writeFile(const char *pth, const char *data, size_t len) {
  ofstream f(pth);
  f.write(data, len);
  f.close();
}
void writeFile(const char* pth, const string& data) {
  return writeFile(pth, data.c_str(), data.length());
}
void writeFile(const string& pth, const string& data) {
  return writeFile(pth.c_str(), data);
}




// WRITE
// -----

template <class T>
void writePlain(ostream& a, const T& v) {
  a << v;
}

template <class K, class V>
void writePlain(ostream& a, const pair<K, V>& x) {
  a << x.first << ' ' << x.second;
}

template <class T>
void writePlain(ostream& a, const vector<T>& x) {
  for (T v : x)
  { writePlain(a, v); a << '\n'; }
}


template <class K, class V>
ostream& operator<<(ostream& a, const pair<K, V>& x) {
  a << x.first << ": " << x.second;
  return a;
}

template <class T>
ostream& operator<<(ostream& a, const vector<T>& x) {
  if (is_fundamental<T>::value) {
    a << "{";
    for (T v : x)
      a << " " << v;
    a << " }";
  }
  else {
    a << "{\n";
    for (const T& v : x)
      a << "  " << v << "\n";
    a << "}";
  }
  return a;
}




// PRINT*
// ------

template <class T>
void print(const T& x) {cout << x; }

template <class T>
void println(const T& x) { cout << x << "\n"; }
