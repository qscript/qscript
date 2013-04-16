#ifndef DEBUG_H
#define DEBUG_H

#ifndef CWDEBUG

#define AllocTag1(p)
#define AllocTag2(p, desc)
#define AllocTag_dynamic_description(p, x)
#define AllocTag(p, x)
#define Debug(x)
#define Dout(a, b)
#define DoutFatal(a, b) LibcwDoutFatal(::std, , a, b)
#define ForAllDebugChannels(STATEMENT)
#define ForAllDebugObjects(STATEMENT)
#define LibcwDebug(dc_namespace, x)
#define LibcwDout(a, b, c, d)
#define LibcwDoutFatal(a, b, c, d) do { ::std::cerr << d << ::std::endl; ::std::exit(254); } while(1)
#define NEW(x) new x

#else // CWDEBUG

#ifndef DEBUGCHANNELS
// This must be defined before <libcwd/debug.h> is included and must be the
// name of the namespace containing your `dc' namespace (see below).
// You can use any namespace(s) you like, except existing namespaces
// (like ::, ::std and ::libcwd).
#define DEBUGCHANNELS ::myproject::debug::channels
#endif
#include <libcwd/debug.h>

namespace myproject {
  namespace debug {
    namespace channels {
      namespace dc {
	using namespace ::libcwd::channels::dc;

	// Add the declaration of new debug channels here
	// and their definition in a custom debug.cc file.
	extern ::libcwd::channel_ct custom;

      } // namespace dc
    } // namespace DEBUGCHANNELS
  }
}

#endif // CWDEBUG
#endif // DEBUG_H
