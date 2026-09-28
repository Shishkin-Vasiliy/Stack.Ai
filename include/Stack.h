#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

typedef double StackElem_t;

#ifdef STACK_DEBUG
#define ON_DBG(...) __VA_ARGS__
#else
#define ON_DBG(...) 
#endif

#define STACK_MIN_CAPACITY 16
#define STACK_MAX_CAPACITY 1000
#define QUARTER_CAPACITY(stk) ((stk) -> capacity / 4)
#define RESIZE_COEFF 2
#define POIZON_STK_PTR ((StackElem_t *)1638)
#define POIZON_DBL NAN 

typedef struct 
{
    StackElem_t *data;
    size_t size;
    size_t capacity;
    ON_DBG (const char *stack_name;
            const char *file_name;
            const char *func_name;
            int line;)
} Stack_t;

enum ERROR_CODE {
    CODE_ZERO,           // ошибок нет
    CODE_ONE,            // стек не создан (calloc вернул NULL)
    CODE_TWO,            // размеры size и capacity не 0 у пустого стека
    CODE_THREE,          // size > capacity
    CODE_FOUR,           // стек пуст, невозможно выполнить pop()
    CODE_FIVE            // стек переполнен, невозможно выполнить push()
};

ERROR_CODE StackInit(Stack_t *stk, size_t capacity
                ON_DBG(, const char *stack_name, const char *file_name, const char *func_name, int line));
ERROR_CODE StackIsEmpty(Stack_t *stk);                
ERROR_CODE StackVerify(Stack_t *stk);
void StackDump(Stack_t *stk);
void PrintShrtErrMsg(ERROR_CODE err);
ERROR_CODE StackPush(Stack_t *stk, StackElem_t value);
ERROR_CODE StackPop(Stack_t *stk, StackElem_t *ptr);
ERROR_CODE StackDestroy(Stack_t *stk, size_t capacity);
ERROR_CODE ResizeUp(Stack_t *stk);
ERROR_CODE ResizeDown(Stack_t *stk);


#define STACK_INIT(stk, capacity) (StackInit(&(stk), (capacity) \
                                    ON_DBG(, #stk,              \
                                            __FILE__,           \
                                            __func__,       \
                                            __LINE__))) 


#ifdef STACK_DEBUG
#define ERROR_MSG(stk, err)     \
do                              \
{                               \
    if (err)                    \
    {                           \
        PrintShrtErrMsg(err);   \
        StackDump(stk);         \
    }                           \
} while (0) 

#else
#define ERROR_MSG(stk, err)     \
do                              \
{                               \
    if (err)                    \
        PrintShrtErrMsg(err);   \
} while (0)
#endif


#define ASSERT_OK(stk) (assert(!StackVerify((stk))))

#endif