#!/bin/bash

# 临时版本的启动脚本

PKTSPY_PATH=/home/pktspy/pktspy
SPIDER=$PKTSPY_PATH/bin/spider
SPIDER_PORT=7788

PARSER=$PKTSPY_PATH/bin/parser
PARSER_MODE=4
LOG_DIR=`dirname $0`/../log

# 创建Log目录
mkdir -p $LOG_DIR/merge
mkdir -p $LOG_DIR/spider
mkdir -p $LOG_DIR/parser

# 启动爬虫
echo staring spider ...

mkdir -p $HOME/pktspy/log/spider

nohup $SPIDER --port=$SPIDER_PORT --logDir=$HOME/pktspy/log/spider >> $PKTSPY_PATH/log/spider.log &

i=0
total=5
SPIDER_STARTUP=
while [[ $i < $total  ]]; do
	SPIDER_STARTUP=`lsof -i :$SPIDER_PORT | grep spider | awk '{print $1}'`
	if [[ $SPIDER_STARTUP == "spider" ]]; then
		i=$total
	else
		sleep 1
		((i=$i+1))
	fi
done

if [ -z $SPIDER_STARTUP ]; then
	echo spider start failed
	exit 1
fi

echo start spider success

# 启动解析进程
echo starting parser ...

nohup $PARSER $PARSER_MODE >> $PKTSPY_PATH/log/parser.log &

sleep 2

echo start parser success

exit 0

