#!/bin/bash
make -j8
sudo killall gameoneserver_keep_alive
sudo killall gameoneserver
sudo cp src/gameoneserver /usr/local/bin/
./gameoneserver_keep_alive &

