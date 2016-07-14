#!/bin/bash
CURRENTDIRECTORY=$(pwd)
BASEDIR=$(dirname $0)
SUCCESSES="$BASEDIR/successes"
cd $SUCCESSES/inputs
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
    ./cedomp tests/successes/inputs/input_${i}.txt > tests/successes/output 

diff -bBw tests/successes/expected/expected_${i}.txt tests/successes/output  > tests/successes/differ

echo "Testing version ${i}"

if [ -s tests/successes/differ ];
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
cd ../tests/successes
rm output
rm differ


