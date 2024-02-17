# gob_adapter

[日本語](README.ja.md)

## Overview
This is a library for using your own functions consisting of public functions of existing classes as if they were class functions of existing classes.   
It can be used with C++11 or later.   
It has the following features and limitations

### Features
- Can be encapsulated by classifying an ordinary function that uses the original class.
- Does not modify the source code of the original class
- "has-a" so there are no side effects on the original class (does not cause problems due to inheritance)
- The use of arrow and dot operators is a little confusing, but it makes the difference between the original class function and a call to your own function clear.
- Little impact from changes in the original class

### Limitations
- Not inherited, so only public functions of existing classes can be used.

## How to install
Install in an appropriate way depending on your environment.
* git clone or download zip, and extract into place
* platformio.ini
```ini
lib_deps = https://github.com/GOB52/gob_adapter.git
```

## How to use
```cpp
#include <gob_adapter.hpp>

// Original class
class Original
{
  public:
    explicit Original(int v) : _v(v) {}
    int value() const { return _v; }
  private:
    int _v{};
};

// Extened class
// Add function to return squared value
class Extended : public goblib::plugin::Adapter<Original>
{
    using goblib::plugin::Adapter<Original>::_cls;
  public:
    using goblib::plugin::Adapter<Original>::Adapter; // for constructor

    int square() const { return _cls->value() * _cls->value(); }
};

Original org(52);
Extended  extended(org);

void foo()
{
    printf("Value:%d\nSquare:%d\n",
           extended->value(), // Call Original::value()
           extended.square()  // Call Extended::square()
           );

    Extended* ep = &extended;
    printf("Value:%d\nSquare:%d\n%d\n",
           (*ep)->value(), // Call Original::value()
           ep->square(),   // Call Extended::square()
           (*ep).square()  // Call Extended::square()
           );
}
```

## Examples

- [simple](examples/simple) A simple example
- [M5GFX](examples/M5GFX) Example of adding your own drawing functions to LovyanGFX

