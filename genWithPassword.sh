#!/bin/bash
# For private deployment usage
# Usage: ./genWithPswd.sh <pswd> <seedFile> [OtherOptions...]

[[ $2 == '' ]] && echo 'Wrong usage' && exit 1
pswd="$1"
seedfl="$2"
pswdGenBin="./pswdGen"
shift
shift

echo "$pswd$(cat $seedfl)" | $pswdGenBin --seed - -y $*
exit $?