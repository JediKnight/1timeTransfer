#!/bin/sh

nm=78
prog='./check_first_incoming'
domain='bamboo-copter.com'
from="test73@${domain}"
to="onetime@${domain}"
date=`date +%Y/%m/%d %H:%M:%S`
log='/tmp/maillog'

echo
echo 'make'
echo '========================================'
make clean || $(echo 'make clean error'; exit)
make || $(echo 'make error'; exit)
echo
echo "run $prog"
echo '========================================'
echo -e "Return-Path: <$from>\nTo: $to\nFrom: $from\nSubject: Test Mail\n\n$date\nTest Message\n" | $prog
echo
echo "$log"
echo '========================================'
cat -b $log

next=`expr $nm + 1`
sed -i "s|nm=${nm}|nm=${next}|" $0

make clean
