#! /bin/sh
echo $1
./qscript -f $1
bcpp test_script.C test_script_bcpp.C
