#include "tests.h"

void LinkedList_test_push_and_peek() {
    __PERSON_INIT_LOCALS__

    LinkedList_push(first, &p1);
    LinkedList_push(first, &p2);
    LinkedList_push(first, &p3);

    // Assert that first   == &p3
    // Assert that p3.next == &p2
    // Assert that p2.next == &p1
    // Assert that p1.next == NULL`

    {
        int offset = 1;
        Person person = { 0 };
        LinkedList_peek(Person, first, offset, &person);
        printf("Person:\n");
        Person_print(person, "  ");
    }

    // TODO: set first to NULL
}

void LinkedList_test_peek_in_a_loop() {
    __PERSON_INIT_LOCALS__

    LinkedList_push(first, &p1);
    LinkedList_push(first, &p2);
    LinkedList_push(first, &p3);

    {
        Person person = { 0 };
        printf("People:\n");
        for (int i = 0; i < 4; i += 1) {
            LinkedList_peek(Person, first, i, &person);
            Person_print(person, "  ");
            printf("---------------------\n");
            // Assert that out of bounds access returns (Person){0}
        }
    }

    // TODO: set first to NULL
}

void LinkedList_test_foreach() {
    __PERSON_INIT_LOCALS__

    LinkedList_push(first, &p1);
    LinkedList_push(first, &p2);
    LinkedList_push(first, &p3);

    // Assert loop doesn't break on a empty list
    // Assert loop doesn't break when accessing values out of bounds

    {
        printf("\n");
        LinkedList_foreach(Person, first, person) {
            if (person.next) {
                printf("Person #%d                  --> Person\n", (person.i + 1));
                printf("  Id:      %-22dId:      %d\n", person.curr->id, person.next->id); 
                printf("  Name:    %-22sName:    %s\n", person.curr->name, person.next->name);
                printf("  Height:  %-22fHeight:  %f\n", person.curr->height, person.next->height);
                printf("  Gender:  %-22sGender:  %s\n", person.curr->gender == Gender_Male ? "Male" : "Female", person.next->gender == Gender_Male ? "Male" : "Female");
            } else {
                printf("Person #%d\n", person.i);
                Person_print(*person.curr, "  ");
            }
            printf("\n");

        }
    }
}

void LinkedList_test_loop_and_pop() {
    __PERSON_INIT_LOCALS__

    LinkedList_push(first, &p1);
    LinkedList_push(first, &p2);
    LinkedList_push(first, &p3);

    {
        Person person = { 0 };
        for (;;) {
            LinkedList_peek_top(Person, first, &person);
            if (LinkedList_is_empty(first)) break;
    
            Person_print(person, "");
            printf("---------------------\n");

            Person* p = {0};
            LinkedList_pop(first, p);
        }
    }

    {
        Person person = { 0 };
        printf("People:\n");
        LinkedList_peek(Person, first, 0, &person);
        Person_print(person, "  ");
    }
}