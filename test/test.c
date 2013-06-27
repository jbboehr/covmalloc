
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

#include "covmalloc.h"

#define COVMALLOC_TEST_HEAD(m) fprintf(stderr, "%s", m)
#define COVMALLOC_TEST_CHECK(a) \
    if( a ) { \
        fprintf(stderr, "%s\n", "Passed"); \
    } else { \
        fprintf(stderr, "%s\n", "Failed"); \
        return 1; \
    }

extern void * covmalloc_dl_libc(char * symbol);
extern void * covmalloc_dlhandle;

int main() {
  // Test failure of covmalloc_dl_libc
  {
    COVMALLOC_TEST_HEAD("Checking covmalloc_dl_libc ... ");
    covmalloc_dlhandle = dlopen("libc.so", RTLD_LAZY);
    void * ret = covmalloc_dl_libc("fake_function");
    int assert = (ret == NULL);
    //dlclose(covmalloc_dlhandle);
    covmalloc_dlhandle = RTLD_NEXT;
    COVMALLOC_TEST_CHECK(assert);
  }
  
  // Test calloc
  {
    COVMALLOC_TEST_HEAD("Checking calloc ... ");
    void * ret = calloc(1, 1);
    int assert = (ret != NULL);
    free(ret);
    COVMALLOC_TEST_CHECK(assert);
  }
  
  // Test calloc failure
  {
    COVMALLOC_TEST_HEAD("Checking calloc failure ... ");
    covmalloc_failure(1);
    void * ret = calloc(1, 1);
    int assert = (ret == NULL);
    covmalloc_failure(0);
    COVMALLOC_TEST_CHECK(assert);
  }
  
  // Test malloc
  {
    COVMALLOC_TEST_HEAD("Checking malloc ... ");
    void * ret = malloc(1);
    int assert = (ret != NULL);
    free(ret);
    COVMALLOC_TEST_CHECK(assert);
  }
  
  // Test malloc failure
  {
    COVMALLOC_TEST_HEAD("Checking malloc failure ... ");
    covmalloc_failure(1);
    void * ret = malloc(1);
    int assert = (ret == NULL);
    covmalloc_failure(0);
    COVMALLOC_TEST_CHECK(assert);
  }
  
  // Test realloc
  {
    COVMALLOC_TEST_HEAD("Checking realloc ... ");
    void * ret = realloc(NULL, 1);
    int assert = (ret != NULL);
    free(ret);
    COVMALLOC_TEST_CHECK(assert);
  }
  
  // Test realloc failure
  {
    COVMALLOC_TEST_HEAD("Checking realloc failure ... ");
    covmalloc_failure(1);
    void * ret = realloc(NULL, 1);
    int assert = (ret == NULL);
    covmalloc_failure(0);
    COVMALLOC_TEST_CHECK(assert);
  }
  
  return 0;
}