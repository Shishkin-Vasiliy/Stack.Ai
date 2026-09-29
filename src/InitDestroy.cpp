#include "Stack.h"

StackErr_t StackInit(Stack_t *stk, size_t capacity
                ON_DBG(, const char *stack_name, const char *file_name, const char *func_name, int line))
{
    printf("Initiating Stack\n");

    StackErr_t err = StackIsEmpty(stk);
    stk -> data = (StackElem_t *) calloc(capacity + 2, sizeof(StackElem_t));
    stk -> info = stk -> data + 1;

    *(stk -> data) = CHICKEN01;
    *((stk -> data) + capacity) = CHICKEN02;

    stk -> capacity = capacity;
    
    stk -> chicken11 = CHICKEN11;
    stk -> chicken22 = CHICKEN22;
    
    err = StackVerify(stk);

    ON_DBG (stk -> stack_name = stack_name;
            stk -> file_name = file_name;
            stk -> func_name = func_name;
            stk -> line = line;)

    for (size_t i = 0; i < (stk -> capacity); i++)
    {
        (stk -> info)[i] = POIZON_DBL;
    }
    StackDump(stk);
    return err;
}

StackErr_t StackDestroy(Stack_t *stk)
{
    StackErr_t err = StackVerify(stk);

    if (err)
        return err;

    printf("Destroying Stack\n");
    StackDump(stk);

    for (size_t i = 0; i < stk -> capacity + 2; i++)
    {
        (stk -> data)[i] = POIZON_DBL;
    }

    free(stk -> data);
    stk -> data = POIZON_STK_PTR;
    stk -> info = POIZON_STK_PTR;

    return STACK_OK;
}


