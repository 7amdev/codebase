#include "tests.h"

LinkedList(Person) first_person = NULL;

bool LinkedList_test_push(char* out_error_msg, int error_msg_length) {
    __PERSON_INIT_LOCALS__

    first_person = NULL;

    LinkedList_push(first_person, &p1);
    if (Person_is_equal(*first_person, p1) == false)
        Return_Error("expected person '%s', but got '%s'.", p1.name, first_person->name);

    LinkedList_push(first_person, &p2);
    if (Person_is_equal(*first_person, p2) == false)
        Return_Error("expected person '%s', but got '%s'.", p2.name, first_person->next->name);

    LinkedList_push(first_person, &p3);
    if (Person_is_equal(*first_person, p3) == false)
        Return_Error("expected person '%s', but got '%s'.", p3.name, first_person->next->next->name);

    bool error_link = false;
    if (!Person_is_equal(*first_person, p3))               error_link = true; else 
    if (!Person_is_equal(*first_person->next, p2))         error_link = true; else 
    if (!Person_is_equal(*first_person->next->next, p1))   error_link = true;
    if (error_link) 
    {
        Return_Error(
            "\nexpected: first -> p3(%p) -> p2(%p) -> p1(%p) -> (null),\n"
            "but got:  first ->   (%p) ->   (%p) ->   (%p) -> (null)", 
            &p3, &p2, &p1, 
            first_person, first_person->next, first_person->next->next
        );
    }

    return true;
}

bool LinkedList_test_pop(char* out_error_msg, int error_msg_length) {
    __PERSON_INIT_LOCALS__
    Person item_popped = {0};
    bool error_link    = false;

    first_person = NULL;

    LinkedList_pop(first_person, &item_popped);
    if (!Person_is_equal(item_popped, (Person) {0}))
        Return_Error("expected an empty Stack, but it has '%s' item(s).", first_person != NULL ? first_person->name : "");

    LinkedList_push(first_person, &p1);
    LinkedList_push(first_person, &p2);
    LinkedList_push(first_person, &p3);

    LinkedList_pop(first_person, &item_popped);
    {
        if (Person_is_equal(item_popped, p3) == false)
            Return_Error("expected popped item's name to be '%s', but got '%s'.", p3.name, item_popped.name);
        if (!Person_is_equal(*first_person, p2))
            Return_Error("expected top item's name to be '%s', but got '%s'.", p2.name, first_person->name);
        if (!Person_is_equal(*first_person, p2))       error_link = true; else 
        if (!Person_is_equal(*first_person->next, p1)) error_link = true;
        if (error_link) 
        {
            Return_Error(
                "\nexpected: first -> p2(%p) -> p1(%p) -> (null),\n"
                "but got:  first ->   (%p) ->   (%p) -> (null)", 
                &p3, &p2, &p1, 
                first_person, first_person->next, first_person->next->next
            );
        }
    }

    LinkedList_pop(first_person, &item_popped);
    {
        if (Person_is_equal(item_popped, p2) == false)
            Return_Error("expected popped item's name to be '%s', but got '%s'.", p2.name, item_popped.name);
        if (Person_is_equal(*first_person, p1) == false)
            Return_Error("expected top item's name to be '%s', but got '%s'.", p1.name, first_person->name);
    }

    LinkedList_pop(first_person, &item_popped);
    {
        if (!Person_is_equal(item_popped, p1))
            Return_Error("expected popped item's name to be '%s', but got '%s'.", p2.name, item_popped.name);
        if (first_person != NULL)
            Return_Error("expected first to '(null)', but got '%p'.", first_person);
    }

    return true;
}

bool LinkedList_test_peek(char* out_error_msg, int error_msg_length) {
    __PERSON_INIT_LOCALS__
    
    first_person = NULL;
    LinkedList_push(first_person, &p1);
    LinkedList_push(first_person, &p2);
    LinkedList_push(first_person, &p3);
    
    Person p_peek = {0};
    for (int i = 0; i < 8; i++) {
        LinkedList_peek(Person, first_person, i, &p_peek);

        if (i == 0)
        if (p_peek.id != p3.id)
        {
            Return_Error("Expected item's name '%s', bu got '%s'.", p3.name, p_peek.name);
        }

        if (i == 1)
        if (p_peek.id != p2.id)
        {
            Return_Error("Expected item's name '%s', bu got '%s'.", p2.name, p_peek.name);
        }

        if (i == 2)
        if (p_peek.id != p1.id)
        {
            Return_Error("Expected item's name '%s', bu got '%s'.", p1.name, p_peek.name);
        }

        if (i == 3)
        if (
            p_peek.id       != 0     || 
            p_peek.name     != NULL  || 
            p_peek.height   != 0 
        ) {
            Return_Error("Expected a null value, but got '%s'.", p_peek.name);
        }
    }

    return true;
}

bool LinkedList_test_foreach(char* out_error_msg, int error_msg_length) {
    __PERSON_INIT_LOCALS__

    first_person = NULL;
    LinkedList_push(first_person, &p1);
    LinkedList_push(first_person, &p2);
    LinkedList_push(first_person, &p3);

    LinkedList_foreach(Person, first_person, person) {
        Person p = *person.curr;
        if (person.i == 0)
        if (!Person_is_equal(p, p3))
        {
            Return_Error("Expected item's name '%s', bu got '%s'.", p3.name, p.name);
        }

        if (person.i == 1)
        if (!Person_is_equal(p, p2))
        {
            Return_Error("Expected item's name '%s', bu got '%s'.", p2.name, p.name);
        }

        if (person.i == 2)
        if (!Person_is_equal(p, p1))
        {
            Return_Error("Expected item's name '%s', bu got '%s'.", p1.name, p.name);
        }
        
#ifdef Tests_Debug_Trace
        if (person.next) {
            printf("Person #%d                  --> Person #%d\n", (person.i + 1), (person.i + 2));
            printf("  Id:      %-22dId:      %d\n", person.curr->id, person.next->id); 
            printf("  Name:    %-22sName:    %s\n", person.curr->name, person.next->name);
            printf("  Height:  %-22fHeight:  %f\n", person.curr->height, person.next->height);
            printf("  Gender:  %-22sGender:  %s\n", person.curr->gender == Gender_Male ? "Male" : "Female", person.next->gender == Gender_Male ? "Male" : "Female");
        } else {
            printf("Person #%d\n", person.i + 1);
            Person_print(*person.curr, "  ");
        }
        printf("\n");
#endif // Tests_Debug_Trace

    }

    return true;
}

bool LinkedList_test_loop_peek_and_pop_combo(char* out_error_msg, int error_msg_length) {
    __PERSON_INIT_LOCALS__

    first_person = NULL;
    LinkedList_push(first_person, &p1);
    LinkedList_push(first_person, &p2);
    LinkedList_push(first_person, &p3);

    Person peeked_item = { 0 };
    for (;;) {
        LinkedList_peek_top(Person, first_person, &peeked_item);
        if (LinkedList_is_empty(first_person)) break;

#ifdef Tests_Debug_Trace
        Person_print(peeked_item, "");
        printf("---------------------\n");
#endif // Tests_Debug_Trace

        Person popped_item = {0};
        LinkedList_pop(first_person, &popped_item);

        if (!Person_is_equal(peeked_item, popped_item)) 
            Return_Error("Expected item's name to be '%s', but got '%s'.", peeked_item.name, popped_item.name);
    }

    return true;
}
