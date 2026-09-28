#include "Stack.h"

ERROR_CODE StackInit(Stack_t *stk, size_t capacity
                ON_DBG(, const char *stack_name, const char *file_name, const char *func_name, int line))
{
    printf("Initiating Stack\n");
    ERROR_CODE err = StackIsEmpty(stk);
    stk -> data = (StackElem_t *) calloc(capacity, sizeof(StackElem_t));
    err = StackVerify(stk);
    stk -> capacity = capacity;

    #ifdef STACK_DEBUG
    stk -> stack_name = stack_name;
    stk -> file_name = file_name;
    stk -> func_name = func_name;
    stk -> line = line; 
    #endif

    for (size_t i = 0; i < capacity; i++)
    {
        (stk -> data)[i] = POIZON_DBL;
    }
    StackDump(stk);
    return err;
}

ERROR_CODE StackDestroy(Stack_t *stk, size_t capacity)
{
    ASSERT_OK(stk);

    printf("Destroying Stack\n");
    StackDump(stk);
    for (size_t i = 0; i < capacity; i++)
    {
        (stk -> data)[i] = POIZON_DBL;
    }
    free(stk -> data);
    stk -> data = POIZON_STK_PTR;

    return CODE_ZERO;
}


