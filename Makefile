all: t1 t2

t1:
	gcc t1_find_d.c -lcrypto -o t1

t2:
	gcc t2_enc.c -lcrypto -o t2_enc

dev:
	docker run -p 4433:4433 -it --rm -v ${PWD}:/root/extern ubuntu:devel
