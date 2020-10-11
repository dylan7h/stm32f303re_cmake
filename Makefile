all: build

# NATIVE_BUILD_TOOL := "Ninja"
NATIVE_BUILD_TOOL := "Unix Makefiles"

config:
	cmake -Bbuild -H. -G $(NATIVE_BUILD_TOOL)

build: config
	cmake --build build --target all

clean:
	cmake --build build --target clean

remove:
	cmake -E remove_directory build