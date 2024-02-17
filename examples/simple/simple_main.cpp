/*
  gob_adapter example : simple
*/
#include <M5Unified.h>
#include "gob_adapter.hpp"
#include <cstdio>

namespace
{
auto& lcd = M5.Display;

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
}

void setup()
{
    M5.begin();
    lcd.setFont(&fonts::Font4);
    lcd.clear(0);
    lcd.setCursor(0,0);

    lcd.printf("Value:%d\nSquare:%d\n",
               extended->value(), // Call Original::value()
               extended.square()  // Call Extended::square()
               );

    Extended* ep = &extended;
    lcd.printf("Value:%d\nSquare:%d\n%d\n",
               (*ep)->value(), // Call Original::value()
               ep->square(),   // Call Extended::square()
               (*ep).square()  // Call Extended::square()
               );
}

void loop()
{
    lgfx::delay(1000);
}

#if defined ( SDL_h_ )
__attribute__((weak)) int user_func(bool* running)
{
  setup();
  do
  {
    loop();
  } while (*running);
  return 0;
}

int main(int, char**)
{
  // The second argument is effective for step execution with breakpoints.
  // You can specify the time in milliseconds to perform slow execution that ensures screen updates.
  return lgfx::Panel_sdl::main(user_func, 128);
}
#endif
