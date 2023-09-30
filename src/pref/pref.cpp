#include "pref.h"
Pref::Pref(/* args */)
{
}
void Pref::begin(String name)
{
  _preferences.begin(name.c_str());
};

Pref::~Pref()
{
}