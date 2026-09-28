#include "Stack.h"

int main(void)
{
    Stack_t stk1 = {};
    int capacity = 2;

    ERROR_CODE err = STACK_INIT(stk1, capacity);
    ERROR_MSG(&stk1, err);

    err = StackPush(&stk1, 30);
    ERROR_MSG(&stk1, err);

    err = StackPush(&stk1, 40);
    ERROR_MSG(&stk1, err);

    err = StackPush(&stk1, 50);
    ERROR_MSG(&stk1, err);

    StackElem_t x = 0;
    err = StackPop(&stk1, &x);
    ERROR_MSG(&stk1, err);

    StackElem_t y = 0;
    err = StackPop(&stk1, &y);
    ERROR_MSG(&stk1, err);

    StackElem_t z = 0;
    err = StackPop(&stk1, &z);
    ERROR_MSG(&stk1, err);

    StackElem_t X = 0;
    err = StackPop(&stk1, &X);
    ERROR_MSG(&stk1, err);

    err = StackDestroy(&stk1, capacity);

    return 0;
}