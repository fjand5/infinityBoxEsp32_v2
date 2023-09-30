#pragma once
#include <Preferences.h>
class Pref
{

protected:
  Preferences _preferences;
  String _name;

public:
  Pref(/* args */);
  void begin(String name);
  ~Pref();
};
