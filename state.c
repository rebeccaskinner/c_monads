#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "monad.h"

struct tuple;
struct state;
typedef struct tuple tuple_t;
typedef struct state state_t;
typedef uintptr_t seed_t;
typedef uintptr_t random_t;
typedef tuple_t* (*state_gen_func)(void*);

struct tuple {
    void* fst;
    void* snd;
};

struct state {
    state_gen_func runstate;
};

monad_t* state_return(void* v)
{
    state_t* st = malloc(sizeof(state_t));
    tuple_t* generator_func()
    {
        tuple_t* tuple = malloc(sizeof(tuple_t));
        tuple->fst = v;
        tuple->snd = (void*)(generator_func);
        return tuple;
    }
    st->runstate = (void*)generator_func;
    return NULL;
}

void* state_get(monad_t* m)
{
    if(!m) {
        printf("Error: state_get - no monad!\n");
        return NULL;
    }
    state_t* st = m->mvalue;
}

tuple_t* roll(seed_t s)
{
    tuple_t* t = malloc(sizeof(tuple_t));
    srand(s);
    t->fst = (void*)random();
    t->snd = (void*)random();
    return t;
}

int main()
{
    tuple_t  t  = {0, 0};
    tuple_t* t2 = roll((uintptr_t)t.snd);
    printf("rolled: %lu\n",(uintptr_t)t2->fst);
    tuple_t* t3 = roll((uintptr_t)t2->snd);
    printf("rolled: %lu\n",(uintptr_t)t3->fst);
    return 0;
}
