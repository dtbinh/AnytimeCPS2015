
libpowutil.so: powutil.c parsec_barrier.c
	gcc -Wall -O3 -g -std=c99 -pthread -fpic $^ -c
	gcc -shared -o $@ $(^:.c=.o)

client: pu-client.c
	gcc -Wall -O3 -g -std=c99 -L. -pthread $^ -lpowutil -o $@

clean:
	rm -f *.o libpowutil.so client

