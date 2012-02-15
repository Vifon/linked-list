.PHONY: lib
lib:
	mkdir -p build
	sh -c 'cd build && cmake ..'
	make -C build
	mkdir -p lib
	cp -v build/src/liblist.{a,so} lib

.PHONY: man
man: list.3.gz

list.3.gz:
	pod2man --utf8 --name=list.h --section=3 README.pod | gzip > list.3.gz

.PHONY: install
install: lib man
	install -D -m 644 lib/liblist.a  /usr/lib/liblist.a
	install -D -m 644 lib/liblist.so /usr/lib/liblist.so
	install -D -m 644 list.3.gz /usr/man/man3/list.3.gz
	@ echo '---installation complete---'

.PHONY: clean
clean:
	rm -rf ./lib/
	rm -f  ./list.3.gz

.PHONY: unittests
unittests:
	mkdir -p unittests
	sh -c 'cd unittests && cmake -D unittest=1 ..'
	make -C unittests
	./unittests/tests/unittests
