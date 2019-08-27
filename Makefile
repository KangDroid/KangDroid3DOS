sub:
	$(MAKE) -C src
	mv src/app.out ./

clean:
	rm -rf src/*.o
	rm -rf src/*.out