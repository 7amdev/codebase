#include "tests.h"

//
// Stack
// 

static void Stack_print(StackPerson *stack) {
    printf("Stack State:\n");
    printf("  Nr of elements: %d\n", stack->top);
}

static void Stack_print_items(StackPerson* stack, const char* indent) {
    for (int i = 0; i < stack->top; i += 1) {
        printf("%sItem #%d\n", indent, (i +  1));
        Person_print(stack->items[i], "      "); 
    }
}

bool Stack_test_push() {
    __PERSON_INIT_LOCALS__
    StackPerson people = {0};
    Person ret = {0};

    printf("----- Before push\n");
    Stack_print(&people);

    Stack_push(&people, p1, &ret);
    Stack_push(&people, p2, &ret);
    Stack_push(&people, p3, &ret);
    if(!Stack_is_full(&people)) 
        Stack_push(&people, p4, &ret);

    printf("\n----- After push\n");
    Stack_print(&people);
    printf("  Items:\n");
    Stack_print_items(&people, "    ");

    if (people.top == 3) return true;

    return false;
}

bool Stack_test_pop() {
    __PERSON_INIT_LOCALS__
    StackPerson people = {0};
    Person ret          = {0};

    if (!Stack_is_empty(&people))
        Stack_pop(&people, &ret);
    
    Stack_push(&people, p1, &ret);
    Stack_push(&people, p2, &ret);
    Stack_push(&people, p3, &ret);

    printf("---- Before Pop\n");
    Stack_print(&people);
    printf("  Items: \n");
    Stack_print_items(&people, "    ");

    printf("\n---- After Pop\n");

    Stack_pop(&people, &ret);
    Stack_pop(&people, &ret);
    Stack_pop(&people, &ret);

    if (!Stack_is_empty(&people))
        Stack_pop(&people, &ret);

    Stack_print(&people);

    if (people.top == 0) return true;

    return false;
}

bool Stack_test_peek() {
    __PERSON_INIT_LOCALS__
    StackPerson people = {0};
    Person ret          = {0};

    if (!Stack_is_empty(&people))
        Stack_pop(&people, &ret);
    
    Stack_push(&people, p1, &ret);
    Stack_push(&people, p2, &ret);
    Stack_push(&people, p3, &ret);
    
    printf("Items:\n");
    for (int i = 0; i < 10; i += 1) {
        if (Stack_is_out_of_bounds(&people, i)) {
            printf("ERROR: Offset '%d' is Out of Bounds.\n", i);
            return false;
        }
        
        Person item = {0};
        Stack_peek(&people, &item, i);
        Person_print(item, "  ");
        printf("\n");
    }
    
    return false;
}

bool Stack_test_out_of_bounds() {
    return false;
}


//
// StackPointer
// 

static void StackPointer_print(StackPointerPerson *stack) {
    printf("Stack State:\n");
    printf("  Nr of elements: %zu\n", StackPointer_count(stack));
    printf("  (top - bottom): %zu\n", (size_t)(stack->top - stack->items));
    printf("  Start Pointer:  %p\n", stack->items);
    printf("  Top Pointer:    %p\n", stack->top);
}

static void StackPointer_print_items(StackPointerPerson *stack) {
    Person item           = {0};
    int error             = 0;
    const char *error_msg = "";

    for (int i = 0; i < StackPointer_count(stack); i += 1) {
        StackPointer_peek(
            stack, &item, .offset = i, 
            .error = &error, .error_msg = &error_msg
        );

        if (error) { 
            printf("ERROR: %s\n", error_msg);
            continue;
        }

        printf("Item #%d:\n", (i + 1));
        Person_print(item, "  ");
        printf("---------------------\n");
    }
}

void StackPointer_test_init() {
    StackPointerPerson infos = {0};
    StackPointer_init(&infos);

    assert(infos.items == infos.top && "ERROR: Stack is not initialized properly.");
}

bool StackPointer_test_push() {
    __PERSON_INIT_LOCALS__

    Person ret = {0};
    Person item = {0};
    StackPointerPerson infos = {0};
    StackPointer_init(&infos);

    StackPointer_push(&infos, p1, &ret);
    StackPointer_push(&infos, p2, &ret);
    StackPointer_push(&infos, p3, &ret);

    StackPointer_print_items(&infos);

    if (StackPointer_count(&infos) != 3)   
        return false;
    
    StackPointer_peek(&infos, &item, 0);
    if (item.id != p3.id) 
        return false;
    
    StackPointer_peek(&infos, &item, 1);
    if (item.id != p2.id) 
        return false;
    
    StackPointer_peek(&infos, &item, 2);
    if (item.id != p1.id) 
        return false;
    
    return true;
}

bool StackPointer_test_is_full() {
    __PERSON_INIT_LOCALS__

    Person ret = {0};
    StackPointerPerson infos = {0};
    StackPointer_init(&infos);

    if (!StackPointer_is_full(&infos)) StackPointer_push(&infos, p1, &ret);
    else printf("ERROR: Cannot Push Item because Stack is full.");

    if (!StackPointer_is_full(&infos)) StackPointer_push(&infos, p2, &ret);
    else printf("ERROR: Cannot Push Item because Stack is full.");

    if (!StackPointer_is_full(&infos)) StackPointer_push(&infos, p3, &ret);
    else printf("ERROR: Cannot Push Item because Stack is full.");

    if (!StackPointer_is_full(&infos)) StackPointer_push(&infos, p4, &ret);
    else printf("ERROR: Cannot Push Item because Stack is full.");

    return true;
}

bool StackPointer_test_pop() {
    __PERSON_INIT_LOCALS__
    Person ret = {0};
    StackPointerPerson infos = {0};

    StackPointer_init(&infos);

    // TEST: Expected a error thrown 
    //
    // StackPointer_pop(&infos, &ret);

    StackPointer_push(&infos, p1, &ret);
    StackPointer_push(&infos, p2, &ret);
    StackPointer_push(&infos, p3, &ret);

    printf("----- Before Pop\n");
    StackPointer_print(&infos);
    printf("\n");
    StackPointer_print_items(&infos);

    if (!StackPointer_is_empty(&infos)) StackPointer_pop(&infos, &ret);
    if (!StackPointer_is_empty(&infos)) StackPointer_pop(&infos, &ret);
    if (!StackPointer_is_empty(&infos)) StackPointer_pop(&infos, &ret);
    if (!StackPointer_is_empty(&infos)) StackPointer_pop(&infos, &ret);

    printf("\n----- After Pop\n");
    StackPointer_print(&infos);
    printf("\n");
    StackPointer_print_items(&infos);

    if (infos.items == infos.top) return true;;

    return false;
}

void StackPointer_test_peek() {
    assert(false && "TODO: Missing Implementation.");
}

void StackPointer_test_peek_on_a_empty_state() {
    assert(false && "TODO: Missing Implementation.");
}

void StackPointer_test_peek_on_a_full_state() {
    assert(false && "TODO: Missing Implementation.");
}

void StackPointer_test_if_its_empty() {
    assert(false && "TODO: Missing Implementation.");
}

void StackPointer_test_if_its_full() {
    assert(false && "TODO: Missing Implementation.");
}

bool StackPointer_test_out_of_bounds() {
    __PERSON_INIT_LOCALS__

    Person ret = {0};
    Person item = {0};
    StackPointerPerson infos = {0};
    StackPointer_init(&infos);

    StackPointer_push(&infos, p1, &ret);
    StackPointer_push(&infos, p2, &ret);

    int error = 0;
    int error_count = 0;
    const char *error_msg;

    StackPointer_peek(&infos, &item, .offset = -1, .error = &error);
    if (error) error_count += 1;
    StackPointer_peek(&infos, &item, .offset =  0, .error =  &error);
    if (error) error_count += 1;
    StackPointer_peek(&infos, &item, .offset =  1, .error = &error);
    if (error) error_count += 1;
    StackPointer_peek(&infos, &item, .offset =  2, .error = &error);
    if (error) error_count += 1;
    StackPointer_peek(&infos, &item, .offset =  3, .error = &error);
    if (error) error_count += 1;

    if (error_count == 3) return true;

    return false;
}