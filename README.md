# 3DEngine

## Build Instructions


### Linux
To build the source, you need:

* The source repository
* A C++ compiler
* [CMake 2.8+](http://www.cmake.org/)
* [GLFW 3](http://www.glfw.org/) (only if you want to build samples)

If you want to only build the engine library, type this:

```shell
mkdir build && cmake .. && make
```

If you also want to build the sdemo scenes, type this:

```shell
mkdir build && cmake -DBUILD_SAMPLES=ON .. && make
```

### Windows & OS X
(Not yet supported)

