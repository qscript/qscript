#include "cwd-sys.h"
#include "cwd-debug.h"

// Actual definition of `ghost'
namespace myproject {	// Actually, you will need a series of
  namespace debug {	// Actually, you will need a series of
    namespace channels {	// Actually, you will need a series of
				// "namespace xyz {" here, to match whatever
				// DEBUGCHANNELS is.
       namespace dc {
    libcwd::channel_ct ghost("GHOST");
      }
    }
  }
}

int main(void)
{
  Debug( dc::ghost.on() );			// Remember: don't forget to turn
  Debug( libcw_do.on() );			//   the debug Channel and Object on!

  for (int i = 0; i < 4; ++i)
    Dout(dc::ghost, "i = " << i);		// We can write more than just
						// "Hello World" to the ostream :)
  return 0;
}
