#pragma once
#ifndef CURSESDEF_H
#define CURSESDEF_H

#include <memory>

#if (defined TILES || defined _WIN32 || defined WINDOWS)
#include "cursesport.h"
#elif (defined __CYGWIN__)
#include "ncurses/curses.h"
#else
#include <curses.h>
#endif

/// @throws std::exception upon any errors. The caller should display / log it
/// and abort the program. Only continue the program when this returned normally.
void init_interface();

struct delwin_functor {
    void operator()( WINDOW *w ) const;
};
/**
 * A Wrapper around the WINDOW pointer, it automatically deletes the
 * window (see delwin_functor) when the variable gets out of scope.
 * This includes calling werase, wrefresh and delwin.
 * Usage:
 * 1. Acquire a WINDOW pointer via @ref newwin like normal, store it in a pointer variable.
 * 2. Create a variable of type WINDOW_PTR *on the stack*, initialize it with the pointer from 1.
 * 3. Do the usual stuff with window, print, update, etc. but do *not* call delwin on it.
 * 4. When the function is left, the WINDOW_PTR variable is destroyed, and its destructor is called,
 *    it calls werase, wrefresh and most importantly delwin to free the memory associated wit the pointer.
 * To trigger the delwin call earlier call some_window_ptr.reset().
 * To prevent the delwin call when the function is left (because the window is already deleted or, it should
 * not be deleted), call some_window_ptr.release().
 */
using WINDOW_PTR = std::unique_ptr<WINDOW, delwin_functor>;

enum base_color : short {
    black = 0x00,    // RGB{0, 0, 0}
    red = 0x01,      // RGB{196, 0, 0}
    green = 0x02,    // RGB{0, 196, 0}
    yellow = 0x03,   // RGB{196, 180, 30}
    blue = 0x04,     // RGB{0, 0, 196}
    magenta = 0x05,  // RGB{196, 0, 180}
    cyan = 0x06,     // RGB{0, 170, 200}
    white = 0x07,    // RGB{196, 196, 196}
};

void init_pair( short pair, base_color f, base_color b );

#endif
