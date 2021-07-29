#!/bin/sh

BEARSSL=bearssl-0.6

cd work

rm -rf ${BEARSSL}

tar -zxf ${BEARSSL}.tar.gz

START=`date '+%s'`

cp -r ../BearSSL/ARMv4.mk ${BEARSSL}/conf/

cd ${BEARSSL};patch -p1 < ../../BearSSL/bear.patch;make CONF=ARMv4

END=`date '+%s'`

TIME=`expr ${END} - ${START}`

echo "${TIME} sec"
