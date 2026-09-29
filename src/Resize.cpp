#include "Stack.h"

StackErr_t ResizeUp(Stack_t *stk)
{
    StackErr_t err = StackVerify(stk);

    StackElem_t *temp = (StackElem_t *)realloc(stk -> data, (stk -> capacity + 2) * sizeof(StackElem_t) * RESIZE_COEFF);
    if (temp)
    {
        stk -> data = temp;
        stk -> info = temp + 1;
    }

    err = StackVerify(stk);
    if (err)
        return err;

    if (stk -> capacity * RESIZE_COEFF > STACK_MAX_CAPACITY)
        return STACK_OVERFLOW;
    
    stk -> capacity *= RESIZE_COEFF;
    
    for (size_t i = stk -> size; i < stk -> capacity; i++)
    {
        (stk -> info)[i] = POIZON_DBL;
    }
    *(stk -> info + stk -> capacity + 1) = CHICKEN02;

    err = StackVerify(stk);
    return err;
}

StackErr_t ResizeDown(Stack_t *stk)
{
    StackErr_t err = StackVerify(stk);

    StackElem_t *temp = (StackElem_t *)realloc(stk -> data, (stk -> capacity + 2) * sizeof(StackElem_t) / RESIZE_COEFF);
    if (temp)
    {
        stk -> data = temp;
        stk -> info = temp + 1;
    }

    err = StackVerify(stk);
    if (err)
        return err;
 
    stk -> capacity /= RESIZE_COEFF;
    *(stk -> info + stk -> capacity + 1) = CHICKEN02;

    err = StackVerify(stk);
    return err;
}