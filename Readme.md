# covmalloc

[![Build Status](https://travis-ci.org/jbboehr/covmalloc.png?branch=master)](https://travis-ci.org/jbboehr/covmalloc)

Allows you to cause malloc to fail.


## Installation

### Ubuntu

```bash
git clone git://github.com/jbboehr/covmalloc.git
cd covmalloc
./configure && make install
```

## Usage

You'll need to link the module to use covmalloc_failure, and you'll also need 
to run your tests using LD_PRELOAD. For example, with automake:

```
TESTS_ENVIRONMENT += LD_PRELOAD=@LIBCOVMALLOC_DIR@/libcovmalloc.so
AM_LDFLAGS = @COVMALLOC_LIBS@
```

Example:

```c
int * a, int * b, int * c;
a = malloc(sizeof(int)); // ok
covmalloc_failure(1);
b = malloc(sizeof(int)); // NULL
covmalloc_failure(0);
c = malloc(sizeof(int)); // ok
```


## License

This project is licensed under the [MIT license](http://opensource.org/licenses/MIT).
