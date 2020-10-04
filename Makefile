all: build

config:
	cmake -Bbuild -H.

build: config
	cmake --build build --target all

clean:
	cmake --build build --target clean

remove:
	cmake -E remove_directory build