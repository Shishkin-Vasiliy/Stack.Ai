#include "Stack.h"

ERROR_CODE StackIsEmpty(Stack_t *stk)
{
    assert(stk);
    
    size_t size = stk -> size;
    size_t capacity = stk -> capacity;
    
    if (size != 0 && capacity != 0)
        return CODE_TWO;
    else
        return CODE_ZERO;
}

ERROR_CODE StackVerify(Stack_t *stk)
{
    if ((!stk) || !(stk -> data))
        return CODE_ONE;

    size_t size = stk -> size;
    size_t capacity = stk -> capacity;

    if (size > capacity)
        return CODE_THREE;

    return CODE_ZERO;
}

void StackDump(Stack_t *stk)
{
    #ifdef STACK_DEBUG
    
    const char *name = stk -> stack_name;
    StackElem_t *data = stk -> data;
    const char *func = stk -> func_name;
    const char *file = stk -> file_name;
    int line = stk -> line;
    size_t capacity = stk -> capacity;
    size_t size = stk -> size;

    printf("STACK_DUMP\n");
    printf("****************************************\n");
    printf("Stack_t <%s> [%p], %s at %s: %d\n", name, stk, func, file, line);
    printf("{\n");
    printf("capacity = %lu\n", capacity);
    printf("size     = %lu\n", size);
    printf("data[%p]\n", data);
    if (data)
    {
        printf("    {\n");
        for (size_t i = 0; i < size; i++)
            printf("    *[%lu] = %lg\n", i, data[i]);
        for (size_t j = size; j < capacity; j++)
            printf("     [%lu] = %lg (POIZON)\n", j, data[j]);
        printf("    }\n");
    }
    printf("}\n");
    printf("****************************************\n\n");

    #endif
}

void PrintShrtErrMsg(ERROR_CODE err)
{
    switch(err)
    {
        case CODE_ZERO:
            break;

        case CODE_ONE:
            printf("Error: failed to allocate memory for stack\n");
            break;
        
        case CODE_TWO:
            printf("Error: (invalid Stack) empty Stack has capacity and size unequal to 0\n");
            break;

        case CODE_THREE:
            printf("Error: size > capacity\n");
            break;

        case CODE_FOUR:
            printf("Stack UnderFlow: cannot do pop() from an empty Stack\n");
            break;

        case CODE_FIVE:
            printf("Stack OverFlow: cannot push() to an overflowing Stack\n");
            break;

        default:
            ;
    }
}
