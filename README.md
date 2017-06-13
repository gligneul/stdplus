# stdplus [![Build Status](https://travis-ci.org/gligneul/stdplus.svg?branch=master)](https://travis-ci.org/gligneul/stdplus)
Lightweight extension for ANSI C89

## Modules
- stdplus/inttypes: Size of integer types
- stdplus/mem: Memory allocation utilities
- stdplus/vector: Dynamic array (like stl vector)

## How to build
```
cd path/to/stdplus
mkdir build; cd build
cmake -DCMAKE_INSTALL_PREFIX=custom/install/dir ..
make
make install
```

## Add to another project
Add stdplus as a git submodule:
```
cd path/to/myproject
mkdir ext
git submodule add https://github.com/gligneul/stdplus.git ext/stdplus
```

Now add it to your top level cmake file:
```
add_subdirectory(ext/stdplus)
target_link_libraries(mylib stdplus)
```
