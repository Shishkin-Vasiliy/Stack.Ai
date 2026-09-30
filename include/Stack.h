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

#define CHICKEN_LOWER 1e13
#define CHICKEN_UPPER 1e10
#define CHICKEN_LEFT 0xDEADDEAD
#define CHICKEN_RIGHT 0xFACEFEED
#define STACK_MIN_CAPACITY 16
#define STACK_MAX_CAPACITY 1000
#define QUARTER_CAPACITY(stk) ((stk) -> capacity / 4)
#define RESIZE_COEFF 2
#define POIZON_STK_PTR ((StackElem_t *)1638)
#define POIZON_DBL NAN 

struct Stack_t
{
    unsigned long long chicken_left;
    StackElem_t *buf;
    StackElem_t *data;
    size_t size;
    size_t capacity;
    ON_DBG (const char *stack_name;
        const char *file_name;
        const char *func_name;
        int line;)
    unsigned long long chicken_right;
};
        
enum StackErr_t {   
    STACK_OK,                           // ошибок нет
    STACK_BAD_PTR,                      // стек не создан (calloc вернул NULL)
    EMPTY_STACK_BAD_SIZE,               // размеры size и capacity не 0 у пустого стека
    STACK_BAD_SIZE,                     // size > capacity
    STACK_STRUCT_LEFT_CHICKEN_ATTACKED, // атакована курица слева от структуры стека
    STACK_STRUCT_RIGHT_CHICKEN_ATTACKED,// атакована курица справа от структуры стека
    STACK_DATA_LOWER_CHICKEN_ATTACKED,  // атакована курица внизу стека
    STACK_DATA_UPPER_CHICKEN_ATTACKED,  // атакована курица наверху стека
    STACK_UNDERFLOW,                    // стек пуст, невозможно выполнить pop()
    STACK_OVERFLOW                      // стек переполнен, невозможно выполнить push()
};

// TODO возвращать все ошибки одним числом, коды ошибок это степени двойки
// сделать функцию которая обращает i-й бит числа в единицу
// чтобы вернуть накопленный код ошибки можно просто переводить полученное двоичное число в десятичное

StackErr_t StackInit(Stack_t *stk, size_t capacity
                ON_DBG(, const char *stack_name, const char *file_name, const char *func_name, int line));
StackErr_t StackChickenCheck(Stack_t *stk);
StackErr_t StackIsEmpty(Stack_t *stk);                
StackErr_t StackVerify(Stack_t *stk);
void StackDump(Stack_t *stk);
void PrintShrtErrMsg(StackErr_t err);
StackErr_t StackPush(Stack_t *stk, StackElem_t value);
StackErr_t StackPop(Stack_t *stk, StackElem_t *ptr);
StackErr_t StackDestroy(Stack_t *stk);
StackErr_t ResizeUp(Stack_t *stk);
StackErr_t ResizeDown(Stack_t *stk);
StackErr_t StackStructChickenCheck(Stack_t *stk);
StackErr_t StackDataChickenCheck(Stack_t *stk);
int DblCmp(StackElem_t a, StackElem_t b);
//void PrintStack(Stack_t *stk);


#define STACK_INIT(stk, capacity) (StackInit(&(stk), (capacity) \
                                    ON_DBG(, #stk,              \
                                            __FILE__,           \
                                            __func__,           \
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

#endif