
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>

extern void exit(int);

static int _initialized = 0;
static int _failure = 0;
static int _print = 0;

static void * (*real_calloc)(size_t, size_t) = NULL;
static void * (*real_malloc)(size_t) = NULL;
static void * (*real_realloc)(void *, size_t) = NULL;
static void * (*real_free)(void *) = NULL;

#if !defined(__CYGWIN32__)
static void * covmalloc_dl_libc(char * symbol) {
  char * error = NULL;
  void * fn = dlsym(RTLD_NEXT, symbol);
  if( (error = dlerror()) != NULL ) {
    fprintf(stderr, "Error in `dlsym`: %s\n", error);
    return NULL;
  } else {
    return fn;
  }
}
#else
static void * covmalloc_dl_libc(char * symbol) {
  void * fn;
  void * handle = dlopen("libc.so");
  char * error;
  if( handle == NULL ) {
    fprintf(stderr, "Error in `dlopen`: %s\n", dlerror());
    return NULL;
  }
  dlerror();
  fn = dlsym(handle, symbol);
  if( (error = dlerror()) != NULL ) {
    fprintf(stderr, "Error in `dlsym`: %s\n", error);
    return NULL;
  } else {
    return fn;
  }
}
#endif

static void __covmalloc_init(void)
{
  _initialized = 1;
  
  real_calloc = covmalloc_dl_libc("calloc");
  real_malloc = covmalloc_dl_libc("malloc");
  real_realloc = covmalloc_dl_libc("realloc");
  real_free = covmalloc_dl_libc("free");
  
  if( real_calloc == NULL || 
      real_malloc == NULL || 
      real_realloc == NULL || 
      real_free == NULL ) {
    // Error message should already be printed
    exit(1);
  }
}

void * calloc(size_t __nmemb, size_t __size)
{
  if( !_initialized ) {
    __covmalloc_init();
  }
  
  // Simulate failure
  if( _failure ) {
    return NULL;
  }
  
  // Call actual function
  void * ret = real_calloc(__nmemb, __size);
  
  // Print memory location
  if( _print ) {
    fprintf(stdout, "Calloc: %p\n", ret);
  }
  
  return ret;
}

void * malloc(size_t __size)
{
  if( !_initialized ) {
    __covmalloc_init();
  }
  
  // Simulate failure
  if( _failure ) {
    return NULL;
  }
  
  // Call actual function
  void * ret = real_malloc(__size);
  
  // Print memory location
  if( _print ) {
    fprintf(stdout, "Malloc: %p\n", ret);
  }
  
  return ret;
}

void * realloc(void * __ptr, size_t __size)
{
  if( !_initialized ) {
    __covmalloc_init();
  }
  
  // Simulate failure
  if( _failure ) {
    return NULL;
  }
  
  // Call actual function
  void * ret = real_realloc(__ptr, __size);
  
  // Print memory location
  if( _print ) {
    fprintf(stdout, "Realloc: %p\n", ret);
  }
  
  return ret;
}

void free(void * __ptr)
{
  if( !_initialized ) {
    __covmalloc_init();
  }
  
  // Simulate failure?
  //if( _failure ) {
  //  return;
  //}
  
  real_free(__ptr);
}


void covmalloc_failure(int failure)
{
  _failure = failure;
}

void covmalloc_print(int print)
{
  _print = print;
}
