#!/bin/bash
CURRENTDIRECTORY=$(pwd)
BASEDIR=$(dirname $0)
ERRORS="$BASEDIR/errors"
cd $ERRORS/inputs
for i in {1..4}; do
    if file ./input_${i}.txt | grep -q CRLF; then
        echo "input_${i}.txt is a DOS file: converting to UNIX file"
        perl -pi -e 's/\r\n/\n/g' ./input_${i}.txt
        echo "Done"
    fi
done

cd ../../../src 

echo "Compiling Cedilha compiler"
echo "Please wait"

make clean > /dev/null 2> /dev/null
make all > /dev/null 2> /dev/null
cd ..
if [ ! -f ./cedomp ]; then
    echo "Error compiling cedomp"
    exit 1
fi
cor=0

for i in {1..4}; do
    ./cedomp tests/errors/inputs/input_${i}.txt > /dev/null 2> tests/errors/output 

diff -bBw tests/errors/expected/expected_${i}.txt tests/errors/output  > tests/errors/differ

echo "Testing version ${i}"

if [ -s tests/errors/differ ];
	then
		echo ""
        echo "======================================"
		echo "Test ${i} failed"
        echo "======================================"
		echo ""
	else
		echo ""
        echo "======================================"
		echo "Test ${i} passed"
        echo "======================================"
		let cor++
		echo ""
	fi
done

echo "---------------"
echo "---------------"
echo "---------------"
cd src
make clean > /dev/null 2> /dev/null
echo ${cor} passed.
echo $(( i - cor )) failed.
cd ../tests/errors
rm output
rm differ


