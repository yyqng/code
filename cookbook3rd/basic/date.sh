#!/bin/bash
date --date "Mon Dec 31 10:06:30 DST 2018" +%s
date --date "JAN 20 2001 " +%A
date "+%d %B %Y"
date "+%A %B %Y"
#设置日期
#date -s "21 June 2009 11:01:22"
#联网设置日期
#/usr/sbin/ntpdate -s time-b.nist.gov
start=$(date +%s)
ping www.baidu.com -c 2
end=$(date +%s)
t=$((end -start))
echo ping takes $t seconds
sec1=`date --date "Jan 2 1970" +%s`
sec2=`date --date "Jan 3 1970" +%s`
echo "`expr $sec2 - $sec1` seconds a day"
