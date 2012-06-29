#ifndef __MONAD_H__
#define __MONAD_H__

struct monad;
typedef struct monad monad_t;

typedef monad_t* (*bound_func)(void*);
typedef monad_t* (*bind_func)(monad_t*, monad_t*(*)(void*));
struct monad
{
    void* value;
    monad_t* (*monadic_return)(void*);
    monad_t* (*monadic_bind)(monad_t*,monad_t*(*)(void*));
};

#endif
