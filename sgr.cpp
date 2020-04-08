/* ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <datafl4sh@toxicnet.eu> wrote this file. As long as you retain this notice
 * you can do whatever you want with this stuff. If we meet some day, and you
 * think this stuff is worth it, you can buy me a beer in return.
 * Matteo Cicuttin
 * ----------------------------------------------------------------------------
 */

#include "sgr.hpp"

int main(void)
{
    using namespace sgr;
    
    std::cout << "Testing " << Bon << "bold" << Boff << " mode" << std::endl;
    std::cout << "Testing " << Fon << "faint" << Foff << " mode" << std::endl;
    std::cout << "Testing " << Ion << "italic" << Ioff << " mode" << std::endl;
    std::cout << "Testing " << Uon << "underline" << Uoff << " mode" << std::endl;
    std::cout << "Testing " << RVon << "reverse" << RVoff << " mode" << std::endl;
    std::cout << "Testing " << STon << "strikethrough" << SToff << " mode" << std::endl;
    
    std::cout << "Testing " << blackfg << "black" << nofg << " color" << std::endl;
    std::cout << "Testing " << Redfg << "red" << nofg << " color" << std::endl;
    std::cout << "Testing " << Greenfg << "green" << nofg << " color" << std::endl;
    std::cout << "Testing " << yellowfg << "yellow" << nofg << " color" << std::endl;
    std::cout << "Testing " << bluefg << "blue" << nofg << " color" << std::endl;
    std::cout << "Testing " << magentafg << "magenta" << nofg << " color" << std::endl;
    std::cout << "Testing " << cyanfg << "cyan" << nofg << " color" << std::endl;
    std::cout << "Testing " << whitefg << "white" << nofg << " color" << std::endl;
    
    std::cout << "Testing " << blackbg << "black" << nobg << " color" << std::endl;
    std::cout << "Testing " << redbg << "red" << nobg << " color" << std::endl;
    std::cout << "Testing " << greenbg << "green" << nobg << " color" << std::endl;
    std::cout << "Testing " << yellowbg << "yellow" << nobg << " color" << std::endl;
    std::cout << "Testing " << bluebg << "blue" << nobg << " color" << std::endl;
    std::cout << "Testing " << magentabg << "magenta" << nobg << " color" << std::endl;
    std::cout << "Testing " << cyanbg << "cyan" << nobg << " color" << std::endl;
    std::cout << "Testing " << whitebg << "white" << nobg << " color" << std::endl;
    
    for (int r = 0; r < 6; r++)
    {
        for (int g = 0; g < 6; g++)
            for (int b = 0; b < 6; b++)
                std::cout << rgbfg(r,g,b) << '*' << nofg;
        std::cout << std::endl;
    }
    
    for (int r = 0; r < 6; r++)
    {
        for (int g = 0; g < 6; g++)
            for (int b = 0; b < 6; b++)
                std::cout << rgbbg(r,g,b) << '*' << nobg;
        std::cout << std::endl;
    }
    
    return 0;
}
