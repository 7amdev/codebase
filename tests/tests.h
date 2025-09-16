#ifndef Tests_H
#define Tests_H

#include "c_dynamic_array.h"
#include "c_linked_list.h"
#include "c_stack.h"
#include "c_queue.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// DEBUG Trace
// #define Tests_Debug_Trace

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

#define Person_is_equal(p1, p2) (             \
    (p1).id == (p2).id                    &&  \
    strcmp((p1).name, (p2).name) == 0     &&  \
    (p1).height == (p2).height            &&  \
    (p1).gender == (p2).gender                \
)

typedef struct {
    DynamicArrayHeader;
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

LinkedList(Person) first;

bool DynamicArray_test_ensure_capacity(char* out_error_msg, int error_msg_length);
bool DynamicArray_test_append(char* out_error_msg, int error_msg_length);
bool DynamicArray_test_append_many(char* out_error_msg, int error_msg_length);
bool DynamicArray_test_append_strings(char* out_error_msg, int error_msg_length);
bool DynamicArray_test_append_string_ptr(char* out_error_msg, int error_msg_length);

void LinkedList_test_push_and_peek();
void LinkedList_test_peek_in_a_loop();
void LinkedList_test_foreach();
void LinkedList_test_loop_and_pop();

bool Stack_test_push();
bool Stack_test_pop();
bool Stack_test_peek();

void StackPointer_test_init();
bool StackPointer_test_push();
bool StackPointer_test_is_full();
bool StackPointer_test_pop();
bool StackPointer_test_out_of_bounds();

bool Queue_test_push_back(); 
bool Queue_test_pop_front();
bool Queue_test_peek_front();
bool Queue_test_peek_back();

#endif // Tests_H