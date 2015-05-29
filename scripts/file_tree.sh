#!/bin/bash

cd /mnt/foo

mkdir t1 t2
mkdir t1/dirA
mkdir t2/dirB t2/dirC

echo "FOO.TXT" > t1/dirA/foo.txt
echo "A" > t1/a.txt
echo "B" > t1/b.txt
echo abc{,,,}{,,,}{,,,}{,,,}{,,,}{,} > t1/c.txt

echo "FOO" > foo.txt 

cd -
