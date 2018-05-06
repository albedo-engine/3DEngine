# 3DEngine [![Build Status](https://travis-ci.com/AdrienNeveu/3DEngine.svg?token=AGcLYmG3qkhAiyxVFXyU&branch=master)](https://travis-ci.com/AdrienNeveu/3DEngine)



## Build Instructions


### Linux
To build the source, you'll need:

* The source repository
* A C++ compiler
* [CMake 3.0+](http://www.cmake.org/)
* [GLFW 3](http://www.glfw.org/) (only if you want to build samples)

You can also type this in a terminal to install all dependencies:

```shell
sudo apt-get install git cmake libglew-dev
git clone https://github.com/AdrienNeveu/3DEngine && git submodule update
```


* If you want to only build the engine library, type this:

```shell
mkdir build && cd $_ && cmake .. && make engine
```

* If you want to build the demos scenes, type this:

```shell
mkdir build && cd $_ && cmake .. && make samples
```

* If you want to launch the test suite, make the 'test' target

```shell
mkdir build && cd $_ && cmake .. && make check
```

### Windows & OS X
(Not yet supported)

## TODO

* Dependencies
  * [ ] Move from GLEW to GLAD
  * [ ] Move from SOIL to stbi

* Code structure
  * [ ] Move to C++ 17
  * [ ] Make use of nested namespace
  * [ ] Move private code that do not need object attributes to anonymous namespace
  * [ ] Remove boost dependency
  * [ ] Change the way uniforms are sent (using a lot of conditions),
  boost::any is not the answer.
  * [ ] Separate includes and sources
  * [ ] Separate templates declaration / definition 
  * [ ] Add constness and staticness where we can.
  * [ ] Add Pimpl
  * [ ] Add typedef to a global scope
  * [ ] Restrict include scope only to files that need them
  * [ ] Add unit testing with Gtest
  * [ ] Better exception handling
  
* Rendering
  * [ ] Add IBL iradiance lighting with SH
  * [ ] Add IBL radiance lighting with Cubemaps mip
  * [ ] Add basic PBR on direct light
  * [ ] Improve shader generation system
  * [ ] Send 1x1 texture with color when texture is not provided
