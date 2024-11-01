set -e
cc -g -std=c99 -c main.c -o ./obj/main.o
cc -g -std=c99 -c component.c -o ./obj/component.o
cc -g -std=c99 -c list.c -o ./obj/list.o
cc -o ./build/main obj/main.o obj/component.o obj/list.o -s -Wall -std=c99 -lraylib -lm -lpthread -ldl -lrt -lX11
./build/main
