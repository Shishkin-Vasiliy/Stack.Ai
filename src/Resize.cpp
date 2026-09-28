#include "Stack.h"

ERROR_CODE ResizeUp(Stack_t *stk)
{
    ASSERT_OK(stk);

    stk -> data = (StackElem_t *)realloc(stk -> data, (stk -> capacity) * sizeof(StackElem_t) * RESIZE_COEFF);

    ERROR_CODE err = StackVerify(stk);
    if (err)
        return err;

    if (stk -> capacity * RESIZE_COEFF > STACK_MAX_SIZE)
        return CODE_FIVE;
    
    stk -> capacity *= RESIZE_COEFF;
    
    for (int i = stk -> size; i < stk -> capacity; i++)
    {
        (stk -> data)[i] = POIZON_DBL;
    }

    ASSERT_OK(stk);
    return CODE_ZERO;
}

ERROR_CODE ResizeDown(Stack_t *stk)
{
    ASSERT_OK(stk);

    stk -> data = (StackElem_t *)realloc(stk -> data, (stk -> capacity) * sizeof(StackElem_t) / RESIZE_COEFF);

    ERROR_CODE err = StackVerify(stk);
    if (err)
        return err;

    stk -> capacity /= RESIZE_COEFF;

    ASSERT_OK(stk);
    return CODE_ZERO;
}