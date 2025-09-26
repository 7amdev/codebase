#ifndef Tests_H
#define Tests_H

#include "c_dynamic_array.h"
#include "c_linked_list.h"
#include "c_stack.h"
#include "c_queue.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// DEBUG 
// 
// #define Tests_Debug_Trace

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define Return_Error_Custom(out_error_msg, error_msg_length, format, ...) do {      \
    snprintf(                                                                           \
        (out_error_msg), (error_msg_length),                                            \
        "%s:%2d: error: " format,                                                       \
        __FILENAME__, __LINE__, ##__VA_ARGS__                                             \
    );                                                                                  \
    return false;                                                                       \
} while (0)

#define Return_Error(format, ...)   \
    Return_Error_Custom(out_error_msg, error_msg_length, format, ##__VA_ARGS__)

#define Log_Info(format, ...)    printf("\x1b[0m[INFO] " format, __VA_ARGS__) 
#define Log_Success(format, ...) printf("\x1b[32m[PASS] " format "\x1b[0m", ##__VA_ARGS__) 
#define Log_Error(format, ...)   Log_Error_Buffer(error_msg, format, __VA_ARGS__)
#define Log_Error_Buffer(error_buffer, format, ...) do {         \
    printf("\x1b[31m[FAIL] " format "\x1b[0m", __VA_ARGS__);    \
    if (error_buffer) *error_buffer = '\0';                     \
} while (0)  

#define Not(expr)  ((expr) == false)

#define Error_Msg_Length 1024

#define Stack_Items_Max 3

typedef enum {
    Gender_Nil,

    Gender_Male,
    Gender_Female,
} Gender;

static const char* Gender_Text[] = {
    [Gender_Nil]    = "(null)", 
    [Gender_Male]   = "Male", 
    [Gender_Female] = "Female"
};

typedef struct Task Task;
struct Task {
    const char *name;
    int         priority;
    char        created_at[50];
    Link(Task)  next;
};

typedef struct Person Person;
struct Person {
    int          id;
    const char  *name;
    Gender       gender;
    float        height;
    Link(Person) next;
    Queue(Task)  tasks;
};

#define __PERSON_INIT_LOCALS__                                                                          \
    Person p1 = { .id = 1, .name = "John Doe",  .gender = Gender_Male,    .height = 1.8f };       \
    Person p2 = { .id = 2, .name = "Jane Doe",  .gender = Gender_Female,  .height = 1.65f };    \
    Person p3 = { .id = 3, .name = "Joana Doe", .gender = Gender_Female,  .height = 1.59f };    \
    Person p4 = { .id = 4, .name = "Bill Doe",  .gender = Gender_Male,    .height = 2.1f };   
    
#define Person_print(person, indent) do {                               \
    printf("%sId:      %d\n", (indent), (person).id);                   \
    printf("%sName:    %s\n", (indent), (person).name);                 \
    printf("%sHeight:  %f\n", (indent), (person).height);               \
    printf("%sGender:  %s\n", (indent), Gender_Text[(person).gender]);  \
} while (0)

#define Person_is_equal(p1, p2) (                   \
    (p1).id == (p2).id                          &&  \
    (                                               \
        ((p1).name != NULL && (p2).name != NULL)    \
        ? strcmp((p1).name, (p2).name) == 0         \
        : (p1).name == (p2).name                    \
    )                                           &&  \
    (p1).height == (p2).height                  &&  \
    (p1).gender == (p2).gender                      \
)

typedef struct {
    size_t count; 
    size_t capacity; 
    Person* items;
} DynamicArrayPerson;

typedef struct {
    DynamicArrayHeader;
    char* items;
} DynamicArrayString;

typedef struct {
    DynamicArrayHeader;
    char** items;
} DynamicArrayStringPointer;

typedef struct {
    int top;
    Person items[Stack_Items_Max];
} StackPerson;

typedef struct {
    Person *top;
    Person  items[Stack_Items_Max];
} StackPointerPerson;

bool DynamicArray_test_ensure_capacity(char* out_error_msg, int error_msg_length);
bool DynamicArray_test_append(char* out_error_msg, int error_msg_length);
bool DynamicArray_test_append_many(char* out_error_msg, int error_msg_length);
bool DynamicArray_test_append_strings(char* out_error_msg, int error_msg_length);
bool DynamicArray_test_append_string_ptr(char* out_error_msg, int error_msg_length);

bool LinkedList_test_push(char* out_error_msg, int error_msg_length);
bool LinkedList_test_pop(char* out_error_msg, int error_msg_length);
bool LinkedList_test_peek(char* out_error_msg, int error_msg_length);
bool LinkedList_test_foreach(char* out_error_msg, int error_msg_length);

bool Stack_test_push(char* out_error_msg, int error_msg_length);
bool Stack_test_pop(char* out_error_msg, int error_msg_length);
bool Stack_test_peek(char* out_error_msg, int error_msg_length);

bool StackPointer_test_init(char* out_error_msg, int error_msg_length);
bool StackPointer_test_push(char* out_error_msg, int error_msg_length);
bool StackPointer_test_pop(char* out_error_msg, int error_msg_length);
bool StackPointer_test_is_full(char* out_error_msg, int error_msg_length);
bool StackPointer_test_out_of_bounds(char* out_error_msg, int error_msg_length);

bool Queue_test_push_back(char* out_error_msg, int error_msg_length); 
bool Queue_test_pop_front(char* out_error_msg, int error_msg_length);

#endif // Tests_H