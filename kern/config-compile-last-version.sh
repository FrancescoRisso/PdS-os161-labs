#!/bin/sh

cd /home/netlab/os161/os161-base-2.0.3/kern

name=$(head -n 1 ./conf/last-conf.name)

cd conf
./config $name

# system("pause")

cd ../compile/$name
bmake depend
bmake
bmake install
