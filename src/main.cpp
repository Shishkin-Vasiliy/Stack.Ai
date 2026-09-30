#include "Stack.h"

int main(void)
{
    Stack_t stk1 = {};
    size_t capacity = 2;

    StackErr_t err = STACK_INIT(stk1, capacity);
    ERROR_MSG(&stk1, err);

    err = StackPush(&stk1, 30);
    printf("Push 30\n");
    ERROR_MSG(&stk1, err);

    err = StackPush(&stk1, 40);
    printf("Push 40\n");
    ERROR_MSG(&stk1, err);

    err = StackPush(&stk1, 50);
    printf("Push 50\n");
    ERROR_MSG(&stk1, err);

    StackElem_t x = 0;
    err = StackPop(&stk1, &x);
    printf("Pop %lg\n", x);
    ERROR_MSG(&stk1, err);

    StackElem_t y = 0;
    err = StackPop(&stk1, &y);
    printf("Pop %lg\n", y);
    ERROR_MSG(&stk1, err);

    StackElem_t z = 0;
    err = StackPop(&stk1, &z);
    printf("Pop %lg\n", z);
    ERROR_MSG(&stk1, err);

    StackElem_t X = 0;
    err = StackPop(&stk1, &X);
    printf("Pop %lg\n", X);
    ERROR_MSG(&stk1, err);

    err = StackDestroy(&stk1);

    return 0;
}