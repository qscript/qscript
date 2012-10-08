/*
 * =====================================================================================
 *
 *       Filename:  fast_memcpy_example.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Friday 05 October 2012 07:36:48  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
         
          static void (*resolve_memcpy (void)) (void)
          {
            // ifunc resolvers fire before constructors, explicitly call the init
            // function.
            __builtin_cpu_init ();
            if (__builtin_cpu_supports ("ssse3"))
              return ssse3_memcpy; // super fast memcpy with ssse3 instructions.
            else
              return default_memcpy;
          }
          
          void *memcpy (void *, const void *, size_t)
               __attribute__ ((ifunc ("resolve_memcpy")));
     
