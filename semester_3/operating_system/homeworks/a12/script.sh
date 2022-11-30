#!/bin/bash
rm -f foo
touch foo
./catloop foo &
echo -n "hello " > foo