#!/bin/bash
BASEDIR=$(dirname $0)
cd $BASEDIR

echo ""
echo "####################################"
echo "TESTING CORRECT INPUTS"
echo "####################################"
echo ""
./testSucesses.sh
echo ""
echo "####################################"
echo "TESTING ERROR INPUTS"
echo "####################################"
echo ""
./testError.sh

