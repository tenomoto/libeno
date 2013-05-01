#!/bin/sh
if [ $# -lt 1 ]; then
  echo "$0 name"
  exit 0
fi
name=$1
sed "s/foo/${name}/g" test_foo.c.in > test_${name}.c
