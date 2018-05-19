LSC = ./node_modules/livescript/bin/lsc
LS_SRC_FILES = src/test.ls src/mmap-io.ls

all: update_modules build

update_modules:
	npm update

build: build_addon

build_addon:
	./node_modules/.bin/node-gyp configure && ./node_modules/.bin/node-gyp rebuild

human_errors:
	clang++ --std=c++11 -S -I node_modules/nan/ -I /usr/local/include/node src/memfd-create.cc

clean:
	rm -rf build *.js

watch:
	while true; do (make build; inotifywait -qre close_write,moved_to --exclude '\.git' ./src/; ) done;
