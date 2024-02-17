/*
  gob_adapter example : M5GFX
  Add my function to LovyanGFX
*/
#include <M5Unified.h>
#include "gob_adapter.hpp"

namespace
{
auto& lcd = M5.Display;

// Extened class
template<class LGFX> class Extended : public goblib::plugin::Adapter<LGFX>
{
    // Check base class type (*1)
    static_assert(std::is_base_of<lgfx::v1::LovyanGFX, typename std::remove_reference<LGFX>::type>::value,
                  "Valid only for classes derived from LovyanGFX");
    using goblib::plugin::Adapter<LGFX>::_cls;
  public:
    using goblib::plugin::Adapter<LGFX>::Adapter; // for constructor

    template<typename T> void fillGradientRectH(const int16_t left, const int16_t top, const int16_t wid, const int16_t hgt, const T& colorstart, const T& colorend)
    {
        for(int16_t y = top; y < top + hgt; ++y)
        {
            _cls->drawGradientLine(left, y, left + wid, y, colorstart, colorend);
        }
    }

    template<typename T> void fillGradientRectV(const int16_t left, const int16_t top, const int16_t wid, const int16_t hgt, const T& colorstart, const T& colorend)
    {
        for(int16_t x = left; x < left + wid; ++x)
        {
            _cls->drawGradientLine(x, top, x, top + hgt, colorstart, colorend);
        }
    }

};
Extended<decltype(lcd)> exLcd(lcd);

#if 0
struct Foo {};
Foo foo;
Extended<decltype(foo)> exLcd2(foo); // Compile error (*1)
#endif
//
}

void setup()
{
    M5.begin();
    lcd.setFont(&fonts::Font4);
    lcd.clear(0);
    lcd.setCursor(0,0);

    exLcd->fillRect(0, 0, exLcd->width()/2, exLcd->height(), TFT_DARKGREEN);
    exLcd.fillGradientRectH(exLcd->width()/2, 0, exLcd->width()/2, exLcd->height()/2, TFT_RED, TFT_BLUE);
    exLcd.fillGradientRectV(exLcd->width()/2, exLcd->height()/2, exLcd->width()/2, exLcd->height()/2, TFT_YELLOW, TFT_CYAN);
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
