#ifndef COMMON_HPP
#define COMMON_HPP

#include <cstdio>
#include <cmath>
#include <vector>

#include <SFML/Graphics.hpp>

namespace sgui{
    namespace _dev{
        #define _BITSET1(var, bit) ((var) |= (bit))
        #define _BITSET0(var, bit) ((var) &= ~ (bit))
        #define _BITGET(var, bit) ((var) & (bit))
        #define _DEFAULT_TEXT_FONT_PATH std::string("./res/fonts/OpenSans-Regular.ttf")
    } // namespace _dev
} // namespace sgui

#endif 