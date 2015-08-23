# recursive_hashmap

## Build instructions

In order to build this project edit **GMOCK_ROOT** variable in `CMakeLists.txt` to point to your googlemock root directory. After this is done you can simply create a build directory (out-of-source builds are preferred), create makefile using cmake and build it:

    git clone https://github.com/pmalek/recursive_hashmap.git && \ 
    mkdir build_dir && cd build_dir && \
    cmake ../recursive_hashmap && make

this will build both the main executable `recursive` and unit tests `recursive_test`
