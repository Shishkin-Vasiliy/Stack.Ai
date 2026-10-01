#include "Stack.h"

StackErr_t StackCTor(Stack_t *stk, size_t capacity
                ON_DBG(, const char *stack_name, const char *file_name, const char *func_name, int line))
{
    printf("Initiating Stack\n");

    StackErr_t err = StackIsEmpty(stk);
    stk -> buf = (StackElem_t *) calloc(capacity + 2, sizeof(StackElem_t));
    stk -> data = stk -> buf + 1; 

    *(stk -> buf) = CHICKEN_LOWER;
    *(stk -> buf + capacity + 1) = CHICKEN_UPPER;

    stk -> capacity = capacity;
    
    stk -> chicken_left = CHICKEN_LEFT;
    stk -> chicken_right = CHICKEN_RIGHT;
    
    err = StackVerify(stk);

    ON_DBG (stk -> stack_name = stack_name;
            stk -> file_name = file_name;
            stk -> func_name = func_name;
            stk -> line = line;)

    for (size_t i = 0; i < (stk -> capacity); i++)
    {
        (stk -> data)[i] = POIZON_DBL;
    }
    StackDump(stk);
    return err;
}

StackErr_t StackDTor(Stack_t *stk)
{
    StackErr_t err = StackVerify(stk);

    if (err)
        return err;

    printf("Destroying Stack\n");
    StackDump(stk);

    for (size_t i = 0; i < stk -> capacity + 2; i++)
    {
        (stk -> buf)[i] = POIZON_DBL;
    }

    free(stk -> buf);
    stk -> buf = POIZON_STK_PTR;
    stk -> data = POIZON_STK_PTR;

    return STACK_OK;
}





//StackErr_t StackInitNew(Stack_t *stk, size_t capacity
//                ON_DBG(, const char *stack_name, const char *file_name, const char *func_name, int line))
//{
//    StackErr_t err = StackIsEmpty(stk);
//
//    uint8_t *temp_ptr = (uint8_t *)calloc(capacity * sizeof(StackElem_t) + 2 * sizeof(Canary_t));
//    if (temp_ptr)
//        stk -> buf = temp_ptr;
//}