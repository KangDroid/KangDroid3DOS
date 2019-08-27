sub:
	$(MAKE) -C src

all: sub
	mv src/app.out ./