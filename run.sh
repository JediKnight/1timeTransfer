#!/bin/sh

nm=0
prog='./check_first_incoming'
domain='bamboo-copter.com'
from="test03@${domain}"
to="onetime@${domain}"
log='/tmp/maillog'

echoc='echo'
[ `uname -s|grep Darwin|wc -l` -ne 0 ] && echoc='/usr/local/bin/gecho'

$echoc
$echoc 'make'
$echoc '========================================'
make clean || $(echo 'make clean error'; exit)
make || $(echo 'make error'; exit)
$echoc
$echoc "run $prog"
$echoc '========================================'
$echoc -e "Return-Path: $from\nTo: $to\nfrom: $from\nsubject: Test Mail\n\n`date +'%Y/%m/%d %H:%M:%S'`\ntest messages\n" | $prog
$echoc
$echoc "$log"
$echoc '========================================'
cat -b $log

next=`expr $nm + 1`
sed -i "s|nm=${nm}|nm=${next}|" $0
