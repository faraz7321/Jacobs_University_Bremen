#!/bin/sh

PROG=./cat

# $1: test number/name
# $2: test case input
# $3: expected return code
# $4: expected result (stdout & stderr)

runtest()
{
    out=`$PROG $2 2>&1`
    if [ "$?" -ne "$3" -o "$out" != "$4" ] ; then
	echo "test $1 failed:"
	echo "    result:   $out"
	echo "    expected: $4"
    fi
}

runtest 1 "/dev/kmem" 1 "cat: Permission denied"
runtest 2 "<&-"       1 "cat: No such file or directory"
runtest 3 "."         1 "cat: Is a directory"
runtest 4 "-x"        1 "./cat: invalid option -- x"
