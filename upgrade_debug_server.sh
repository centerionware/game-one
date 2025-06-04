#!/bin/bash
make
sudo killall gameoneserver_keep_alive
sudo killall gameoneserver
gdb src/gameoneserver
#sudo cp src/gameoneserver /usr/local/bin/
#./gameoneserver_keep_alive &

