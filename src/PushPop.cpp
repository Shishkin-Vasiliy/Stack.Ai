#include "Stack.h"

ERROR_CODE StackPush(Stack_t *stk, StackElem_t value)
{
    ASSERT_OK(stk);
    ERROR_CODE err = CODE_ZERO;

    if ((stk -> size) == (stk -> capacity))
        err = ResizeUp(stk);

    if (err)
        return err;

    stk -> data[stk -> size++] = value;

    ASSERT_OK(stk);
    return CODE_ZERO;
}

ERROR_CODE StackPop(Stack_t *stk, StackElem_t *ptr)
{
    ASSERT_OK(stk);
    ERROR_CODE err = CODE_ZERO;

    if ((stk -> size) == 0)
        return CODE_FOUR;

    if ((stk -> size) < (stk -> capacity / RESIZE_COEFF))
        err = ResizeDown(stk);

    if (err)
        return err;
    
    *ptr = (stk -> data[--(stk -> size)]);
    stk -> data[(stk -> size)] = NAN;

    ASSERT_OK(stk);
    return CODE_ZERO;
}