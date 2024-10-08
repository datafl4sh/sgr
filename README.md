# sgr
SGR (from Select Graphic Rendition) provides C++ stream manipulators for
colored text output and more. It is based on the [ANSI escape codes](https://en.wikipedia.org/wiki/ANSI_escape_code), and for this reason it will likely work only on Unix.

If you use `sgr` in Windows it shouldn't produce any harmful output and you should just get plain, uncolored and unformatted text.

I am not interested in supporting Windows, if you need/want Windows support you can either open a pull request or use [Termcolor](https://github.com/ikalnytskyi/termcolor).

For the impatient, look at the examples in `sgr.cpp`. For the detailed instructions, continue reading.

## Color manipulators
The basic color manipulators allow to set the foreground or the background text color to one of the basic 8 ANSI colors, which are Black, Red, Green, Yellow, Blue, Magenta, Cyan, White. Each color has a "bright" variant.

### Foreground color
For example, to use Red foreground color, you type:

    #include "sgr.hpp"
    using namespace sgr;

    std::cout << redfg << "Hello, world!" << nofg << std::endl;

In this last example you see that also the `nofg` manipulator appears: it disables the colored output when you're finished.

If you want the bright variant of a color, you just use the color name with uppercase first letter:

    std::cout << Redfg << "Hello, world!" << nofg << std::endl;

### Background color
The logic for background colors is the same as the logic for foreground colors, the only difference is that the name of manipulators finishes with `bg`. So, to set Green background color:

    std::cout << greenbg << "Hello, world!" << nobg << std::endl;

Or, if you want the bright variant:

    std::cout << Greenbg << "Hello, world!" << nobg << std::endl;

### RGB colors
In addition to the basic 8 colors, you have the possibility to use another 216 colors that are specified using an RGB triple `(r,g,b)`. Note that the components of the RGB triple can take the values from 0 to 5.

So, to set foreground color using an rgb triple:

    std::cout << rgbfg(1,2,3) << "Hello, world!" << nofg << std::endl;

Similarly, the background color is set as:

    std::cout << rgbbg(1,2,3) << "Hello, world!" << nobg << std::endl;

### Grayscale
A 24-level grayscale is available in 256-color terminals. In `sgr` the level is specified with a number from 0 to 23.

To set the foreground gray level:

    std::cout << grayscalefg(21) << "Hello, world!" << nofg << std::endl;

Similarly, to set the background gray level:

    std::cout << grayscalebg(21) << "Hello, world!" << nobg << std::endl;

## Style manipulators
In addition to colors, `sgr` allows you to specify the text styles supported by the ANSI standard: Bold, Faint, Italic, Underlined, Crossed-out and Reverse Video. Blink is not included in `sgr`. The corresponding manipulators are:

  * `Bon`/`Boff` for Bold
  * `Ion`/`Ioff` for Italic
  * `Uon`/`Uoff` for Underlined
  * `Fon`/`Foff` for Faint
  * `STon`/`SToff` for Crossed-out (Strike through)
  * `RVon`/`RVoff` for Reverse Video

## Shortcut manipulators
When you want to apply a foreground color and set a text style at the same time, there are some shortcut manipulators available with the following syntax:

    [BIUF][Cc]olorfg

For example, if you want bold bright green text you can type

    std::cout << BGreen << "Hello, world!" << reset << std::endl;

while if you want underlined blue you can type

    std::cout << Ublue << "Hello, world!" << reset << std::endl;

Note that in this case the manipulator `reset` was used: it restores normal text (no color, no styles).

## Color palette
You can define a color palette with

```
sgr::palette pal;
pal.add_color(5,0,0);
pal.add_color(0,5,0);
pal.add_color(0,0,5);
```

The maximum number of colors you can add is `SGR_PALETTE_MAX_COLORS`, which is currently set to 8. You can override the default value by defining `SGR_PALETTE_MAX_COLORS` before the inclusion of `sgr.hpp`

Once you're done adding colors, you can use the palette as following:

```
std::cout << pal(i) << "Hello, world!" << std::endl;
```
The index is treated modulo the number of colors installed in the palette, so there is no risk of overflow.

## Terminal control sequences
SGR provides limited support to other terminal control sequences, in particular:

  * `bell`: produce an audible sound (CTRL-G)
  * `backspace`: equivalent to `\b` (CTRL-H)
  * `tab`: equivalent to `\t` (CTRL-I)
  * `lf`: line feed (CTRL-J)
  * `ff`: form feed (CTRL-L)
  * `cr`: carriage return, equivalent to `\r` (CTRL-M)
  * `clrscr`: clear screen and move cursor to home position
  * `clrline`: clear current line
  * `gotoxy(x,y)`: go to position `(x,y)` in the terminal (1-based, `(1,1)` being at the top-left corner)
  * `hidecursor`: hide cursor
  * `showcursor`: show cursor

## TTY/Non-TTY output behaviour
By default, `sgr` produces colored text only if your output is a TTY. If you are writing to a file, coloring is omitted.

You can however change this behaviour. There are three modes:

    sgrmode::ALWAYS_ENABLED /* Text always colored */
    sgrmode::ONLY_IF_TTY    /* Text colored only if output is a TTY */
    sgrmode::DISABLED       /* Text never colored */

The current mode can be retrieved with the function `current_mode()`, while a new mode can be set using the function `set_mode()`. For example:

    #include "sgr.hpp"
    using namespace sgr;

    set_mode(sgrmode::ALWAYS_ENABLED);

## Support of `NO_COLOR`
`sgr` honours the `NO_COLOR` variable in order to enable/disable text coloring. See [here](https://no-color.org/) for details.

## MPI support, filter output based on process rank
In MPI you usually want only some ranks to print to the console (usually rank 0). In `sgr` there is a manipulator to accomplish this without filling your code with `if`s:

    #define SGR_ENABLE_MPI

    std::cout << rank(0) << "Hello from rank 0" << std::endl;
    std::cout << rank(1) << "Hello from rank 1" << std::endl;

The messages above will be printed only by the ranks you specified with `rank()`. If there is no MPI, `rank()` is a no-operation.

