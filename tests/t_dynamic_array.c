#include "tests.h" 

static void DynamicArray_print(DynamicArrayPerson* array) {
    printf("Dynamic Array 'Person':\n");
    printf("  count:    %zu\n", array->count);
    printf("  capacity: %zu\n", array->capacity);
}

bool DynamicArray_test_ensure_capacity(char* out_error_msg, int error_msg_length) {
    DynamicArrayPerson persons = {0};

    DynamicArray_ensure_capacity(&persons, 29);
    if (persons.capacity != DynamicArray_Initial_Capacity) 
        Return_Error("expected %d total capacity, but got %zu.", DynamicArray_Initial_Capacity, persons.capacity);

    DynamicArray_ensure_capacity(&persons, 257);
    if (persons.capacity != (2*DynamicArray_Initial_Capacity)) 
        Return_Error("expected %d total capacity, but got %zu.", (2*DynamicArray_Initial_Capacity), persons.capacity);

    return true;
}

bool DynamicArray_test_append(char* out_error_msg, int error_msg_length) {
    __PERSON_INIT_LOCALS__

    DynamicArrayPerson persons = {0};

    DynamicArray_append(&persons, p1);
    DynamicArray_append(&persons, p2);

    if (persons.count != 2) 
        Return_Error("Expected %d items, but got %zu.", 2, persons.count);

    DynamicArray_append(&persons, p3);
    DynamicArray_append(&persons, p4);

    if (persons.count != 4) 
        Return_Error("Expected %d items, but got %zu.", 4, persons.count);

#ifdef Tests_Debug_Trace
    printf("DynamicArray_test_append: ----------------------------\n");
    DynamicArray_print(&persons);
    printf("\nPersons:\n");
    DynamicArray_foreach(Person, &persons, person) {
        printf("  Person #%zu: \n", person.i);
        printf("    Id:      %d\n", person.item->id);
        printf("    Name:    %s\n", person.item->name);
        printf("    Height:  %f\n", person.item->height);
        printf("    Gender:  %s\n", person.item->gender == Gender_Male ? "Male" : "Female");
    }
    printf("-------------------------------------------------------\n");
#endif // Tests_Debug_Trace

    return true;
} 

bool DynamicArray_test_append_many(char* out_error_msg, int error_msg_length) {
    __PERSON_INIT_LOCALS__

    DynamicArrayPerson persons = {0};
    Person new_persons[] = {
        {.id = 5, .name = "Praia", .height = 1.78,  .gender = Gender_Male},
        {.id = 6, .name = "Filipe", .height = 1.87, .gender = Gender_Male}
    };

    DynamicArray_append(&persons, p1);
    DynamicArray_append(&persons, p2);

    DynamicArray_append_many(
        &persons, 
        new_persons, 
        sizeof(new_persons) / sizeof(new_persons[0])
    );
    
    DynamicArray_append(&persons, p3);
    DynamicArray_append(&persons, p4);
    
    if (persons.count != 6) 
        Return_Error("Expected %d items, but got %zu.", 6, persons.count);

    if (persons.capacity != 256) 
        Return_Error("Expected %d items, but got %zu.", 256, persons.capacity);

    if (Person_is_equal(persons.items[2], new_persons[0]) == false) 
        Return_Error("Expected Person name '%s', but got '%s' at index '2'.", new_persons[0].name, persons.items[2].name);

    if (Person_is_equal(persons.items[3], new_persons[1]) == false) 
        Return_Error("Expected Person name '%s', but got '%s' at index '2'.", new_persons[1].name, persons.items[3].name);

#ifdef Tests_Debug_Trace
    printf("DynamicArray_test_append_many: ----------------------------\n");
    printf("\n");
    DynamicArray_print(&persons);
    printf("\n");
    printf("Persons:\n");
    DynamicArray_foreach(Person, &persons, person) {
        printf("  Person #%zu: \n", person.i);
        Person_print(*person.item, "    ");
    }
    printf("-------------------------------------------------------\n");
#endif // Tests_Debug_Trace
    
    return true;
}

bool DynamicArray_test_append_strings(char* out_error_msg, int error_msg_length) {
    DynamicArrayString strings = {0};
    char text_hello[]       = "Hello, ";
    char text_world[]       = "world";
    char text_end[]         = "!";
    char text_null[]        = "\0";
    const char expected[]   = "Hello, world!";
    int expected_length     = strlen(expected);
    int expected_sizeof     = sizeof(expected);

    DynamicArray_append_many(&strings, text_hello, sizeof(text_hello) - 1);
    DynamicArray_append_many(&strings, text_world, sizeof(text_world) - 1);
    DynamicArray_append_many(&strings, text_end,   sizeof(text_end)   - 1);
    DynamicArray_append_many(&strings, text_null,  sizeof(text_null)  - 1);

    int s_length = strlen(strings.items);
    if (s_length != expected_length) 
        Return_Error("Expected length '%d', but got '%d'.", expected_length, s_length);

    if (strings.count != expected_sizeof) 
        Return_Error("expected a size '%d', but got '%zu'.", expected_sizeof, strings.count);

    if (strcmp(strings.items, expected) != 0) 
        Return_Error("Expected string '%s', but got '%s'.", expected, strings.items);

    if (strings.capacity != 256) 
        Return_Error("Expected a capacity of %d, but got %zu.", 256, strings.capacity);

#ifdef Tests_Debug_Trace
    printf("DynamicArray_test_append_strings: ----------------------------\n");
    printf("\n");
    printf("Dynamic Array of 'String': %s\n", strings.items);
    printf("  count:    %zu\n", strings.count);
    printf("  capacity: %zu\n", strings.capacity);
    printf("\n");
    printf("Strings:\n");
    DynamicArray_foreach(char, &strings, string) {
        printf("  Character #%zu: '%c'\n", string.i, *string.item);
    }
    printf("--------------------------------------------------------------\n");
#endif

    return true;
}

bool DynamicArray_test_append_string_ptr(char* out_error_msg, int error_msg_length) {
    DynamicArrayStringPointer string_pointers = {0};
    char* expected[]   = {"Hello, ", "world", "!"};
    int expected_length = sizeof(expected) / sizeof(expected[0]);

    for (int i = 0; i < expected_length; i++) {
        // NOTE: Forces error for debugging purpose
        //
        // if (i == 1) {
        //     DynamicArray_append(&string_pointers, "some");
        //     continue;
        // }

        DynamicArray_append(&string_pointers, expected[i]);
    }

    if (string_pointers.count != expected_length) 
        Return_Error("Expected %d items, but got %zu.", expected_length, string_pointers.count);

    bool is_equal = true;
    int i = 0;
    for (; i < expected_length; i++) {
        if (string_pointers.items[i] != expected[i]) {
            is_equal = false;
            break;
        }

        if (strcmp(string_pointers.items[i], expected[i]) != 0) {
            is_equal = false;
            break;
        } 
    }

    if (is_equal == false) 
        Return_Error("Expected '%s' at index '%d', but got '%s'.", expected[i], i, string_pointers.items[i]);

    if (string_pointers.capacity != 256) 
        Return_Error("Expected a capacity of %d, but got %zu.", 256, string_pointers.capacity);

#ifdef Tests_Debug_Trace
    printf("DynamicArray_test_append_string_ptr: ----------------------------\n");
    printf("\n");
    printf("Dynamic Array of 'String':\n");
    printf("    count:    %zu\n", string_pointers.count);
    printf("    capacity: %zu\n", string_pointers.capacity);
    printf("\n");
    printf("Strings:\n");
    DynamicArray_foreach(char*, &string_pointers, s_ptr) {
        printf("  String #%zu: '%s'\n", s_ptr.i, *s_ptr.item);
    }
    printf("-------------------------------------------------------\n");
#endif

    return true;
}