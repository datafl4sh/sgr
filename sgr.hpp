/* ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <datafl4sh@toxicnet.eu> wrote this file. As long as you retain this notice
 * you can do whatever you want with this stuff. If we meet some day, and you
 * think this stuff is worth it, you can buy me a beer in return.
 * Matteo Cicuttin
 * ----------------------------------------------------------------------------
 */

#pragma once

#include <iostream>
#include <cstdlib>
#include <unistd.h>

#define MAKE_MANIPULATOR(function_name, escape)                             \
    template<typename CharT, typename Traits = std::char_traits<CharT>>     \
    inline std::basic_ostream<CharT, Traits>&                               \
    function_name(std::basic_ostream<CharT, Traits>& os)                    \
    {                                                                       \
        if ( priv::sgr_enabled(os) )                                        \
            os << escape;                                                   \
        return os;                                                          \
    }

namespace sgr {

enum class sgrmode {
    ALWAYS_ENABLED,
    ONLY_IF_TTY,
    DISABLED
};

namespace priv
{
    std::streambuf const * coutbuf = std::cout.rdbuf();
    std::streambuf const * cerrbuf = std::cerr.rdbuf();
    std::streambuf const * clogbuf = std::clog.rdbuf();
    template< typename CharT, typename Traits = std::char_traits<CharT> > 
    bool isatty(std::basic_ostream<CharT, Traits>& os)
    {
        std::streambuf const * osbuf = os.rdbuf();
        if (osbuf == coutbuf)
            return ::isatty(1);

        if (osbuf == cerrbuf or osbuf == clogbuf)
            return ::isatty(2);

        return false;
    }

    static sgrmode mode = sgrmode::ONLY_IF_TTY;
 
    template<typename CharT, typename Traits = std::char_traits<CharT>>
    bool sgr_enabled(std::basic_ostream<CharT, Traits>& os)
    {
        if (mode == sgrmode::ALWAYS_ENABLED)
            return true;

        if (mode == sgrmode::ONLY_IF_TTY)
            return isatty(os);

        return false;
    }
}


/* Remove all attributes */
MAKE_MANIPULATOR(reset, "\x1b[0m");

/* Bold on */
MAKE_MANIPULATOR(Bon, "\x1b[1m");

/* Bold off */
MAKE_MANIPULATOR(Boff, "\x1b[22m");

/* Faint on */
MAKE_MANIPULATOR(Fon, "\x1b[2m");

/* Faint off */
MAKE_MANIPULATOR(Foff, "\x1b[22m");

/* Italic on */
MAKE_MANIPULATOR(Ion, "\x1b[3m");

/* Italic off */
MAKE_MANIPULATOR(Ioff, "\x1b[23m");

/* Underline on */
MAKE_MANIPULATOR(Uon, "\x1b[4m");

/* Underline off */
MAKE_MANIPULATOR(Uoff, "\x1b[24m");

/* Reverse video on */
MAKE_MANIPULATOR(RVon, "\x1b[7m");

/* Reverse video off */
MAKE_MANIPULATOR(RVoff, "\x1b[27m");

/* Crossed-out (strikethrough) on */
MAKE_MANIPULATOR(STon, "\x1b[9m");

/* Crossed-out (strikethrough) off */
MAKE_MANIPULATOR(SToff, "\x1b[29m");

/* Black foreground and variations */
MAKE_MANIPULATOR(blackfg, "\x1b[30m");          // Plain
MAKE_MANIPULATOR(Bblackfg, "\x1b[1;30m");       // Bold
MAKE_MANIPULATOR(Fblackfg, "\x1b[2;30m");       // Faint
MAKE_MANIPULATOR(Iblackfg, "\x1b[3;30m");       // Italic
MAKE_MANIPULATOR(Ublackfg, "\x1b[4;30m");       // Underlined

/* Bright Black foreground and variations */
MAKE_MANIPULATOR(Blackfg, "\x1b[90m");          // Plain
MAKE_MANIPULATOR(BBlackfg, "\x1b[1;90m");       // Bold
MAKE_MANIPULATOR(FBlackfg, "\x1b[2;90m");       // Faint
MAKE_MANIPULATOR(IBlackfg, "\x1b[3;90m");       // Italic
MAKE_MANIPULATOR(UBlackfg, "\x1b[4;90m");       // Underlined

/* Red foreground and variations */
MAKE_MANIPULATOR(redfg, "\x1b[31m");            // Plain
MAKE_MANIPULATOR(Bredfg, "\x1b[1;31m");         // Bold
MAKE_MANIPULATOR(Fredfg, "\x1b[2;31m");         // Faint
MAKE_MANIPULATOR(Iredfg, "\x1b[3;31m");         // Italic
MAKE_MANIPULATOR(Uredfg, "\x1b[4;31m");         // Underlined

/* Bright Red foreground and variations */
MAKE_MANIPULATOR(Redfg, "\x1b[91m");            // Plain
MAKE_MANIPULATOR(BRedfg, "\x1b[1;91m");         // Bold
MAKE_MANIPULATOR(FRedfg, "\x1b[2;91m");         // Faint
MAKE_MANIPULATOR(IRedfg, "\x1b[3;91m");         // Italic
MAKE_MANIPULATOR(URedfg, "\x1b[4;91m");         // Underlined

/* Green foreground and variations */
MAKE_MANIPULATOR(greenfg, "\x1b[32m");          // Plain
MAKE_MANIPULATOR(Bgreenfg, "\x1b[1;32m");       // Bold
MAKE_MANIPULATOR(Fgreenfg, "\x1b[2;32m");       // Faint
MAKE_MANIPULATOR(Igreenfg, "\x1b[3;32m");       // Italic
MAKE_MANIPULATOR(Ugreenfg, "\x1b[4;32m");       // Underline

/* Bright Green foreground and variations */
MAKE_MANIPULATOR(Greenfg, "\x1b[92m");          // Plain
MAKE_MANIPULATOR(BGreenfg, "\x1b[1;92m");       // Bold
MAKE_MANIPULATOR(FGreenfg, "\x1b[2;92m");       // Faint
MAKE_MANIPULATOR(IGreenfg, "\x1b[3;92m");       // Italic
MAKE_MANIPULATOR(UGreenfg, "\x1b[4;92m");       // Underline

/* Yellow foreground and variations */
MAKE_MANIPULATOR(yellowfg, "\x1b[33m");         // Plain
MAKE_MANIPULATOR(Byellowfg, "\x1b[1;33m");      // Bold
MAKE_MANIPULATOR(Fyellowfg, "\x1b[2;33m");      // Faint
MAKE_MANIPULATOR(Iyellowfg, "\x1b[3;33m");      // Italic
MAKE_MANIPULATOR(Uyellowfg, "\x1b[4;33m");      // Underline

/* Bright Yellow foreground and variations */
MAKE_MANIPULATOR(Yellowfg, "\x1b[93m");         // Plain
MAKE_MANIPULATOR(BYellowfg, "\x1b[1;93m");      // Bold
MAKE_MANIPULATOR(FYellowfg, "\x1b[2;93m");      // Faint
MAKE_MANIPULATOR(IYellowfg, "\x1b[3;93m");      // Italic
MAKE_MANIPULATOR(UYellowfg, "\x1b[4;93m");      // Underline

/* Blue foreground and variations */
MAKE_MANIPULATOR(bluefg, "\x1b[34m");           // Plain
MAKE_MANIPULATOR(Bbluefg, "\x1b[1;34m");        // Bold
MAKE_MANIPULATOR(Fbluefg, "\x1b[2;34m");        // Faint
MAKE_MANIPULATOR(Ibluefg, "\x1b[3;34m");        // Italic
MAKE_MANIPULATOR(Ubluefg, "\x1b[4;34m");        // Underline

/* Bright Blue foreground and variations */
MAKE_MANIPULATOR(Bluefg, "\x1b[94m");           // Plain
MAKE_MANIPULATOR(BBluefg, "\x1b[1;94m");        // Bold
MAKE_MANIPULATOR(FBluefg, "\x1b[2;94m");        // Faint
MAKE_MANIPULATOR(IBluefg, "\x1b[3;94m");        // Italic
MAKE_MANIPULATOR(UBluefg, "\x1b[4;94m");        // Underline

/* Magenta foreground and variations */
MAKE_MANIPULATOR(magentafg, "\x1b[35m");        // Plain
MAKE_MANIPULATOR(Bmagentafg, "\x1b[1;35m");     // Bold
MAKE_MANIPULATOR(Fmagentafg, "\x1b[2;35m");     // Faint
MAKE_MANIPULATOR(Imagentafg, "\x1b[3;35m");     // Italic
MAKE_MANIPULATOR(Umagentafg, "\x1b[4;35m");     // Underline

/* Bright Magenta foreground and variations */
MAKE_MANIPULATOR(Magentafg, "\x1b[95m");        // Plain
MAKE_MANIPULATOR(BMagentafg, "\x1b[1;95m");     // Bold
MAKE_MANIPULATOR(FMagentafg, "\x1b[2;95m");     // Faint
MAKE_MANIPULATOR(IMagentafg, "\x1b[3;95m");     // Italic
MAKE_MANIPULATOR(UMagentafg, "\x1b[4;95m");     // Underline

/* Cyan foreground and variations */
MAKE_MANIPULATOR(cyanfg, "\x1b[36m");           // Plain
MAKE_MANIPULATOR(Bcyanfg, "\x1b[1;36m");        // Bold
MAKE_MANIPULATOR(Fcyanfg, "\x1b[2;36m");        // Faint
MAKE_MANIPULATOR(Icyanfg, "\x1b[3;36m");        // Italic
MAKE_MANIPULATOR(Ucyanfg, "\x1b[4;36m");        // Underline

/* Bright Cyan foreground and variations */
MAKE_MANIPULATOR(Cyanfg, "\x1b[96m");           // Plain
MAKE_MANIPULATOR(BCyanfg, "\x1b[1;96m");        // Bold
MAKE_MANIPULATOR(FCyanfg, "\x1b[2;96m");        // Faint
MAKE_MANIPULATOR(ICyanfg, "\x1b[3;96m");        // Italic
MAKE_MANIPULATOR(UCyanfg, "\x1b[4;96m");        // Underline

/* White foreground and variations */
MAKE_MANIPULATOR(whitefg, "\x1b[37m");          // Plain
MAKE_MANIPULATOR(Bwhitefg, "\x1b[1;37m");       // Bold
MAKE_MANIPULATOR(Fwhitefg, "\x1b[2;37m");       // Faint
MAKE_MANIPULATOR(Iwhitefg, "\x1b[3;37m");       // Italic
MAKE_MANIPULATOR(Uwhitefg, "\x1b[4;37m");       // Underline

/* Bright White foreground and variations */
MAKE_MANIPULATOR(Whitefg, "\x1b[97m");          // Plain
MAKE_MANIPULATOR(BWhitefg, "\x1b[1;97m");       // Bold
MAKE_MANIPULATOR(FWhitefg, "\x1b[2;97m");       // Faint
MAKE_MANIPULATOR(IWhitefg, "\x1b[3;97m");       // Italic
MAKE_MANIPULATOR(UWhitefg, "\x1b[4;97m");       // Underline

/* No foreground color */
MAKE_MANIPULATOR(nofg, "\x1b[39m");

/* Black background */
MAKE_MANIPULATOR(blackbg, "\x1b[40m");

/* Bright Black background */
MAKE_MANIPULATOR(Blackbg, "\x1b[100m");

/* Red background */
MAKE_MANIPULATOR(redbg, "\x1b[41m");

/* Bright Red background */
MAKE_MANIPULATOR(Redbg, "\x1b[101m");

/* Green background */
MAKE_MANIPULATOR(greenbg, "\x1b[42m");

/* Bright Green background */
MAKE_MANIPULATOR(Greenbg, "\x1b[102m");

/* Yellow background */
MAKE_MANIPULATOR(yellowbg, "\x1b[43m");

/* Bright Yellow background */
MAKE_MANIPULATOR(Yellowbg, "\x1b[103m");

/* Blue background */
MAKE_MANIPULATOR(bluebg, "\x1b[44m");

/* Bright Blue background */
MAKE_MANIPULATOR(Bluebg, "\x1b[104m");

/* Magenta background */
MAKE_MANIPULATOR(magentabg, "\x1b[45m");

/* Bright Magenta background */
MAKE_MANIPULATOR(Magentabg, "\x1b[105m");

/* Cyan background */
MAKE_MANIPULATOR(cyanbg, "\x1b[46m");

/* Bright Cyan background */
MAKE_MANIPULATOR(Cyanbg, "\x1b[106m");

/* White background */
MAKE_MANIPULATOR(whitebg, "\x1b[47m");

/* Bright White background */
MAKE_MANIPULATOR(Whitebg, "\x1b[107m");

/* No background color */
MAKE_MANIPULATOR(nobg, "\x1b[49m");

namespace priv
{
    /* 6x6x6 RGB foreground/background */
    template<bool background>
    struct rgb_manip {
        int r, g, b;
        
        rgb_manip(int pr, int pg, int pb)
        : r(pr), g(pg), b(pb)
        {}
    };

    using fg_rgb_manip = rgb_manip<false>;
    using bg_rgb_manip = rgb_manip<true>;
}

inline std::ostream&
operator<<(std::ostream& os, const priv::fg_rgb_manip& rm)
{
    if ( priv::isatty(os) )
    {
        if (rm.r < 0 || rm.r > 5) return os;
        if (rm.g < 0 || rm.g > 5) return os;
        if (rm.b < 0 || rm.b > 5) return os;
        int color = 16 + 36*rm.r + 6*rm.g + rm.b;
    
        os << "\x1b[38;5;" << color << "m";
    }

    return os;
}

inline priv::fg_rgb_manip
rgbfg(int r, int g, int b) {
    return priv::fg_rgb_manip(r,g,b);
}

inline std::ostream&
operator<<(std::ostream& os, const priv::bg_rgb_manip& rm)
{
    if ( priv::isatty(os) )
    {
        if (rm.r < 0 || rm.r > 5) return os;
        if (rm.g < 0 || rm.g > 5) return os;
        if (rm.b < 0 || rm.b > 5) return os;
        int color = 16 + 36*rm.r + 6*rm.g + rm.b;
        
        os << "\x1b[48;5;" << color << "m";
    }

    return os;
}

inline priv::bg_rgb_manip
rgbbg(int r, int g, int b) {
    return priv::bg_rgb_manip(r,g,b);
}

}

