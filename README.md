# 3DEngine [![Build Status](https://travis-ci.com/AdrienNeveu/3DEngine.svg?token=AGcLYmG3qkhAiyxVFXyU&branch=master)](https://travis-ci.com/AdrienNeveu/3DEngine)



## Build Instructions


### Linux
To build the source, you need:

* The source repository
* A C++ compiler
* [CMake 2.8+](http://www.cmake.org/)
* [GLFW 3](http://www.glfw.org/) (only if you want to build samples)

If you want to only build the engine library, type this:

```shell
mkdir build && cd $_ && cmake .. && make engine
```

If you want to build the demos scenes, type this:

```shell
mkdir build && cd $_ && cmake .. && make samples
```

If you want to launch the test suite, make the 'test' target

```shell
mkdir build && cd $_ && cmake .. && make check
```

### Windows & OS X
(Not yet supported)

