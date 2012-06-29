#ifndef __MONAD_H__
#define __MONAD_H__
#include <stdint.h>

struct monad;
typedef struct monad monad_t;

typedef monad_t* (*bound_func)(monad_t*, void*);
typedef monad_t* (*bind_func)(monad_t*, bound_func);
typedef monad_t* (*return_func)(void*);
typedef void* (*curriable_func)(void*, void*);
typedef void* (*curried_func)(void*);

struct monad
{
    void*       mvalue;
    return_func mreturn;
    bind_func   mbind;
};

#endif
