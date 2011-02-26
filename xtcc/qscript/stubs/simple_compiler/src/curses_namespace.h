//namespace qs_ncurses {
//#include <cstdio>
#if _WIN32
#include <curses.h>
#include <panel.h>
#else /* _WIN32 */
#include <ncursesw/curses.h>
#include <ncursesw/panel.h>
#endif /* ELSE */

//}
