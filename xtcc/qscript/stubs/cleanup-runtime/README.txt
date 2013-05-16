maybe this should have been another branch?

Anyways, the question.h file in the runtime brings in the AbstractStatement.h
file dependency which basically screws up the entire runtime. If I want
to port to HAXE for example, I need to remove these dependencies out
completely.

My plan is to use the compiler in helping me in this process. Right now
I create a library, libqscriptruntime.so . Instead I will manually add
all the files in the library to a separate directory (this one) and then
have the compiler warn me about variables and function which are not 
used in the runtime and extract them out.

The objective is to remove as many files that directly bring the
compiler sources into play and instead create a runtime system which can
be easily ported to another programming language.


