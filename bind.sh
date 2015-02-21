#!/bin/bash
FILES="exercise/* programs/* references/* scripts/* bind.sh LICENSE"
OUTFILE="all.tar"

if [ -x all.tar ]; then
	rm all.tar
fi

tar -c -f $OUTFILE $FILES
