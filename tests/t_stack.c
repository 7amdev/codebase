#include "tests.h"

//
// Stack
// 

static void Stack_print(StackPerson *stack, const char* indent) {
    printf("Stack State:\n");
    printf("%sNr of elements: %d\n", indent, stack->top);
}

static void Stack_print_items(StackPerson* stack, const char* indent) {
    for (int i = 0; i < stack->top; i += 1) {
        printf("%sItem #%d\n", indent, (i +  1));
        Person_print(stack->items[i], "      "); 
    }
}

bool Stack_test_push(char* out_error_msg, int error_msg_length) {
    __PERSON_INIT_LOCALS__
    StackPerson people = {0};
    Person ret = {0};

    Stack_push(&people, p1, &ret);
    if (Person_is_equal(ret, p1) == false)
        Return_Error("expected person '%s', but got '%s'.", p1.name, ret.name);

    Stack_push(&people, p2, &ret);
    if (Person_is_equal(ret, p2) == false)
        Return_Error("expected person '%s', but got '%s'.", p2.name, ret.name);

    Stack_push(&people, p3, &ret);
    if (Person_is_equal(ret, p3) == false)
        Return_Error("expected person '%s', but got '%s'.", p3.name, ret.name);

    if (Stack_is_full(&people) == false) 
        Return_Error("expected Stack to be full.", "");

    // NOTE: Push item only if the stack is not full
    //
    int stack_len = people.top;
    if(!Stack_is_full(&people)) Stack_push(&people, p4, &ret);
    if (people.top > stack_len) 
        Return_Error("expected Stack items length to be %d, but got %d.", stack_len, people.top);

    bool is_equal = true;
    if      (!Person_is_equal(people.items[0], p1)) is_equal = false;
    else if (!Person_is_equal(people.items[1], p2)) is_equal = false;
    else if (!Person_is_equal(people.items[2], p3)) is_equal = false;
    if (is_equal == false) 
        Return_Error("Stack items differs with the inputs.");

    return true;
}

bool Stack_test_pop(char* out_error_msg, int error_msg_length) {
    __PERSON_INIT_LOCALS__
    StackPerson people = {0};
    Person ret          = {0};

    if (!Stack_is_empty(&people)) Stack_pop(&people, &ret);
    
    Stack_push(&people, p1, &ret);
    Stack_push(&people, p2, &ret);
    Stack_push(&people, p3, &ret);

    int top = people.top;
    Person item_popped = {0};
    Person top_item = {0};

    Stack_pop(&people, &item_popped);
    Stack_peek(&people, &top_item, 0);
    {
        if (people.top != top - 1) 
            Return_Error("expected '%d' items, but got '%d'.", (top - 1), people.top);
        if (Person_is_equal(item_popped, p3) == false)
            Return_Error("expected popped item's name to be '%s', but got '%s'.", p3.name, item_popped.name);
        if (!Person_is_equal(top_item, p2))
            Return_Error("expected top item's name to be '%s', but got '%s'.", p2.name, top_item.name);
    }

    Stack_pop(&people, &item_popped);
    Stack_peek(&people, &top_item, 0);
    {
        if (people.top != top - 2) 
            Return_Error("expected '%d' items, but got '%d'.", (top - 2), people.top);
        if (Person_is_equal(item_popped, p2) == false)
            Return_Error("expected popped item's name to be '%s', but got '%s'.", p2.name, item_popped.name);
        if (!Person_is_equal(top_item, p1))
            Return_Error("expected top item's name to be '%s', but got '%s'.", p1.name, top_item.name);
    }

    Stack_pop(&people, &item_popped);
    {
        if (people.top != top - 3) 
            Return_Error("expected '%d' items, but got '%d'.", (top - 3), people.top);
        if (Person_is_equal(item_popped, p1) == false)
            Return_Error("expected popped item's name to be '%s', but got '%s'.", p1.name, item_popped.name);
        if (!Stack_is_empty(&people))
            Return_Error("expected an empty Stack, but it has '%d' item(s).", people.top);
    }

    if (Stack_is_empty(&people)) top_item = (Person) {0};
    if (!Stack_is_empty(&people)) Stack_pop(&people, &item_popped);
    Stack_peek(&people, &top_item, 0);
    if (!Person_is_equal(top_item, (Person) {0})) 
        Return_Error("expected an empty Stack, but it has '%d' item(s).", people.top);

    return true;
}

bool Stack_test_peek(char* out_error_msg, int error_msg_length) {
    __PERSON_INIT_LOCALS__
    StackPerson people = {0};
    Person top_item    = {0};

    // TODO: Peeking on a empty state
    Stack_peek(&people, &top_item, 0);
    if (Person_is_equal(top_item, (Person) {0}) == false)
        Return_Error("expected a '(null)' item, but got '%s'.", top_item.name);

    if (!Stack_is_empty(&people))
        Stack_pop(&people, &top_item);
    
    Stack_push(&people, p1, &top_item);
    if (Person_is_equal(top_item, p1) == false)
        Return_Error("expected top item's name to be '%s', but got '%s'.", p1.name, top_item.name);

    Stack_push(&people, p2, &top_item);
    if (Person_is_equal(top_item, p2) == false)
        Return_Error("expected top item's name to be '%s', but got '%s'.", p2.name, top_item.name);

    Stack_push(&people, p3, &top_item);
    if (Person_is_equal(top_item, p3) == false)
        Return_Error("expected top item's name to be '%s', but got '%s'.", p3.name, top_item.name);

    Person person = {0};
    Stack_peek(&people, &person, 0);
    if (Person_is_equal(top_item, p3) == false)
        Return_Error("expected top item's name to be '%s', but got '%s'.", p3.name, person.name);
    
    Stack_peek(&people, &person, 1);
    if (Person_is_equal(person, p2) == false)
        Return_Error("expected top item's name to be '%s', but got '%s'.", p2.name, person.name);

    Stack_peek(&people, &person, 2);
    if (Person_is_equal(person, p1) == false)
        Return_Error("expected top item's name to be '%s', but got '%s'.", p1.name, person.name);
    
    person = (Person) {0};
    Stack_peek(&people, &person, 3);
    if (Person_is_equal(person, (Person) {0}) == false)
        Return_Error("expected '(null)' item, but got '%s'.", person.name);

#ifdef Tests_Debug_Trace
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
#endif   

    return true;
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

bool StackPointer_test_push(char* out_error_msg, int error_msg_length) {
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

bool StackPointer_test_pop(char* out_error_msg, int error_msg_length) {
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