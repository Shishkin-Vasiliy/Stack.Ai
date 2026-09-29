#include "Stack.h"

StackErr_t StackIsEmpty(Stack_t *stk)
{
    if (!stk)   
        return STACK_BAD_PTR;
    
    size_t size = stk -> size;
    size_t capacity = stk -> capacity;
    
    if (size != 0 && capacity != 0)
        return EMPTY_STACK_BAD_SIZE;
    else
        return STACK_OK;
}

StackErr_t StackVerify(Stack_t *stk)
{
    if ((!stk) || !(stk -> data))
        return STACK_BAD_PTR;

    size_t size = stk -> size;
    size_t capacity = stk -> capacity;

    if (size > capacity)
        return STACK_BAD_SIZE;

    return STACK_OK;
}

void StackDump(Stack_t *stk)
{
    #ifdef STACK_DEBUG

    const char *name = stk -> stack_name;
    //StackElem_t *data = stk -> data;
    StackElem_t *info = stk -> info;
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
    printf("info[%p]\n", info);
    if (info)
    {
        printf("    {\n");
        for (size_t i = 0; i < size; i++)
            printf("    *[%lu] = %lg\n", i, info[i]);
        for (size_t j = size; j < capacity; j++)
            printf("     [%lu] = %lg (POIZON)\n", j, info[j]);
        printf("    }\n");
    }
    printf("}\n");
    printf("****************************************\n\n");

    #endif
}

void PrintShrtErrMsg(StackErr_t err)
{
    switch(err)
    {
        case STACK_OK:
            break;

        case STACK_BAD_PTR:
            printf("Error: failed to allocate memory for stack\n");
            break;
        
        case EMPTY_STACK_BAD_SIZE:
            printf("Error: (invalid Stack) empty Stack has capacity and size unequal to 0\n");
            break;

        case STACK_BAD_SIZE:
            printf("Error: size > capacity\n");
            break;

        case STACK_UNDERFLOW:
            printf("Stack UnderFlow: cannot do pop() from an empty Stack\n");
            break;

        case STACK_OVERFLOW:
            printf("Stack OverFlow: cannot push() to an overflowing Stack\n");
            break;

        default:
            ;
    }
}
