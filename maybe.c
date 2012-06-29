#include <stdlib.h>
#include <stdio.h>
#include "monad.h"

enum maybe_id {
    NOTHING = 0,
    JUST
};

struct maybe {
    enum  maybe_id type;
    void* value;
};

typedef enum maybe_id maybe_id_t;
typedef struct maybe maybe_t;

maybe_t* mk_just(void* val);
maybe_t* mk_nothing();
maybe_t* mk_maybe(void* val);
monad_t* maybe_bind(monad_t*, monad_t* (*f)(void*));
monad_t* maybe_return(void* v);
monad_t* just(void* val);
monad_t* nothing();

maybe_t* mk_just(void* val)
{
    maybe_t* m = malloc(sizeof(maybe_t));
    m->type = JUST;
    m->value = val;
    return m;
}

maybe_t* mk_nothing()
{
    static maybe_t* m = NULL;
    if(__builtin_expect((NULL == m), 0)) {
        m = malloc(sizeof(maybe_t));
        m->type  = NOTHING;
        m->value = NULL;
    }
    return m;
}

maybe_t* mk_maybe(void* val)
{
    if(val) return mk_just(val);
    return mk_nothing();
}

monad_t* maybe_return(void* v)
{
    if(v)
        return just(v);
    else
        return nothing();
}

monad_t* maybe_bind(monad_t* m, monad_t* (*f)(void*))
{
    monad_t* rv = nothing();
    if(!m) {
        goto cleanup;
    }
    maybe_t* maybe = (maybe_t*)(m->mvalue);
    if(NOTHING == maybe->type) {
        goto cleanup;
    }
    rv = f(maybe->value);
cleanup:
    return rv;
}

monad_t* just(void* val)
{
    monad_t* monad = malloc(sizeof(monad_t));
    monad->mvalue = mk_maybe(val);
    monad->mreturn = maybe_return;
    monad->mbind = (bind_func)maybe_bind;
    return monad;
}

monad_t* nothing()
{
    monad_t* monad = malloc(sizeof(monad_t));
    monad->mvalue = mk_nothing();
    monad->mreturn = maybe_return;
    monad->mbind = (bind_func)maybe_bind;
    return monad;
}

monad_t* increment_evens(int* val)
{
    if(!val) {
        return nothing();
    }
    if(0 != ((*val) % 2))
    {
        return nothing();
    }
    int* v2 = malloc(sizeof(int));
    *v2 = (*val) + 1;
    return just(v2);
}

monad_t* increment_odds(int* val)
{
    if(!val || 0 == ((*val) % 2))
    {
        return nothing();
    }
    int* v = malloc(sizeof(int));
    *v = (*val) + 1;
    return just(v);
}

void print_maybe_int(maybe_t* maybe)
{
    if(!maybe) {
        printf("Error: Got a NULL maybe\n");
        return;
    }
    if(NOTHING == maybe->type) {
        printf("Nothing\n");
        return;
    }
    if(!(maybe->value)) {
        printf("Error: Got a JUST (NULL)\n");
        return;
    }
    int* x = (int*)(maybe->value);
    printf("Just %d\n",*x);
}

void print_maybe_int_monad(monad_t* m)
{
    if(!m) {
        printf("Error: Got a NULL monad\n");
        return;
    }
    if(!(m->mvalue)) {
        printf("Error: Monadic value is NULL\n");
        return;
    }
    print_maybe_int((maybe_t*)(m->mvalue));
}

void* add_numbers(void* aa, void* bb)
{
    uintptr_t a = (uintptr_t)aa;
    uintptr_t b = (uintptr_t)bb;
    printf("%lu + %lu = %lu\n", a, b, a + b);
    return NULL;
}

int main()
{
    int x = 2;
    int y = 4;
    int z = 6;
    monad_t* m = just(&x);
    print_maybe_int_monad(m);
    m = m->mbind(m, (bound_func)increment_evens);
    print_maybe_int_monad(m);
    m = m->mbind(m, (bound_func)increment_evens);
    print_maybe_int_monad(m);
    m = just(&y);
    m = m->mbind(m, (bound_func)increment_evens);
    m = m->mbind(m, (bound_func)increment_odds);
    print_maybe_int_monad(m);
    m = just(&z);
    m = m->mbind(m, (bound_func)increment_odds);
    print_maybe_int_monad(m);

    return 0;
}
