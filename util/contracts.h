#ifndef CONTRACTS_H
#define CONTRACTS_H

#include <assert.h>

// from CMU CS 15-122 
#ifdef DEBUG
  #define ASSERT(COND) assert(COND)
  #define REQUIRES(COND) assert(COND)
  #define ENSURES(COND) assert(COND)
#else
  #define ASSERT(COND) ((void)0)
  #define REQUIRES(COND) ((void)0)
  #define ENSURES(COND) ((void)0)
#endif

#endif