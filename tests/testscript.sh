#!/bin/bash
CURRENTDIRECTORY=$(pwd)
BASEDIR=$(dirname $0)
SUCCESSES="$BASEDIR/successes"
cd $SUCCESSES/inputs
for i in {1..6}; do
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
echo "*******************************************"
echo "Teste dos casos de sucesso: não geram erros"
echo "*******************************************"
cor=0

for i in {1..3}; do
    ./cedomp tests/successes/inputs/input_${i}.txt > tests/successes/output 

diff -bBw tests/successes/expected/expected_${i}.txt tests/successes/output  > tests/successes/differ

echo "===================="
echo "Teste da versão ${i}"

if [ -s tests/successes/differ ];
	then
		echo ""
		echo "** Falha no teste da versão ${i}"
		echo ""
		echo "****Esperado":
		echo ""
		cat tests/success/expected/expected_${i}.txt
		echo ""
		echo "****Obtido": 
		cat tests/successes/output
		echo ""
	else
		echo ""
		echo "** Sucesso no teste da versão ${i}"
		let cor++
		echo ""
	fi
done

echo "---------------"
echo "Fim dos testes."
echo "---------------"
cd src
make clean > /dev/null 2> /dev/null
echo Passou em ${cor}.
echo Falhou em $(( i - cor )).
cd ../tests/successes
rm output
rm differ


