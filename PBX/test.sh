#!/bin/bash
PROG=./a.exe

for IN_FILE in tests/*_in.txt ; do
	REF_FILE=`echo -n $IN_FILE | sed -e 's/in/out/'`
	$PROG < $IN_FILE > out/output
	if ! diff $REF_FILE out/output ; then
		echo "Fail $IN_FILE";
		exit
	else
		echo "OK $IN_FILE";
	fi
done
