#!/bin/sh

OS=`uname -s`


NEWLIB=newlib-3.0.0.20180831

PATH=${PATH}:${HOME}/bin

cd work

rm -rf ${NEWLIB}

tar -zxf ${NEWLIB}.tar.gz

START=`date '+%s'`

cd ${NEWLIB};./configure --disable-newlib-supplied-syscalls --target=arm-none-eabi --host=amd64 CC_FOR_BUILD=cc;gmake -j8

END=`date '+%s'`

TIME=`expr ${END} - ${START}`

echo "${TIME} sec"
