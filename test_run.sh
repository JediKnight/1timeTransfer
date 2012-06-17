#!/bin/sh

prog='./check_first_incoming';
domain='bamboo-copter.com';
srcaddr="test03@${domain}";
dstaddr="onetime@${domain}";
log='/tmp/maillog';

echo
echo 'make'
echo '========================================'
make clean || $(echo 'make clean error'; exit)
make || $(echo 'make error'; exit)
echo
echo "run $prog"
echo '========================================'
echo -e "From: $srcaddr\nTo: $dstaddr\n\n\n\n\n\n\n\n\nfrom: $srcaddr\nsubject: Test Mail\n`date +'%Y/%m/%d %H:%M:%S'`\ntest messages" | $prog;
echo
echo "$log"
echo '========================================'
cat -b $log
echo '========================================'
