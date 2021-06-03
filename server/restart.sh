#!/bin/bash
id=`ps aux|awk '{print $2 $11}'|grep ./server|awk 'BEGIN{FS="."}{print $1}'`
kill -9 ${id}
if [ $? -eq 0 ]; then
    echo "success!"
else
    echo "failed!"
fi
./server