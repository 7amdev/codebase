#include "tests.h"

static void Task_print(Task task, const char *indentation) {
    printf("%sName:       %s\n", "  ", task.name);               
    printf("%sPriority:   %d\n", "  ", task.priority);               
    printf("%sCreated at: %s\n", "  ", task.created_at);               
}

static void Queue_print_tasks(Task *task, const char *indentation) {
    for (;;) {
        if (task == NULL) break;
        printf("%s%s\n", indentation, task->name);
        task = task->next;
    }
}

void Queue_print_person(Person p) {
    printf("Person:\n");
    printf("%sId:     %d\n", "  ", p.id);                 
    printf("%sName:   %s\n", "  ", p.name);               
    printf("%sHeight: %f\n", "  ", p.height);             
    printf("%sGender: %s\n", "  ", Gender_Text[p.gender]);
    if (p.tasks.first) {
        printf("%stasks:  %s\n", "  ", p.tasks.first->name);
        Queue_print_tasks(p.tasks.first->next, "          ");
    }
}

bool Queue_test_push_back(char* out_error_msg, int error_msg_length) {
    Task t1   = { .name = "Buy grociries",              .priority = 1,  .created_at = "2025-04-14 14:35:05" };
    Task t2   = { .name = "Meeting with Bob and Jane",  .priority = 2,  .created_at = "2025-04-14 20:00:00" };
    Task t3   = { .name = "create a presentation",      .priority = 6,  .created_at = "2025-04-14 09:16:00" };
    Task t4   = { .name = "Write budget report",        .priority = 8,  .created_at = "2025-04-14 12:45:00" };
    Person p1 = { .id = 1, .name = "John Doe",  .gender = Gender_Male, .height = 1.8f };

    Queue_push_back(p1.tasks.first, p1.tasks.last, &t1);
    Queue_push_back(p1.tasks.first, p1.tasks.last, &t2);
    Queue_push_back(p1.tasks.first, p1.tasks.last, &t3);
    Queue_push_back(p1.tasks.first, p1.tasks.last, &t4);

#ifdef Tests_Debug_Trace
    Queue_print_person(p1);
#endif

    if (p1.tasks.first != &t1) 
    if (strcmp(p1.tasks.first->name, t1.name) != 0) 
    {
        snprintf(
            out_error_msg, error_msg_length, 
            "Expected the first pointer to be '%p', but got '%p'.", 
            &t1, p1.tasks.first
        );
    }

    if (p1.tasks.last != &t4) 
    if (strcmp(p1.tasks.last->name, t4.name) != 0) 
    {
        snprintf(
            out_error_msg, error_msg_length, 
            "Expected the last pointer to be '%p', but got '%p'.", 
            &t4, p1.tasks.last
        );
    }

    bool error_link = false;
    if (p1.tasks.first != &t1)                   error_link = true;
    if (p1.tasks.first->next != &t2)             error_link = true;
    if (p1.tasks.first->next->next != &t3)       error_link = true;
    if (p1.tasks.first->next->next->next != &t4) error_link = true;
    if (error_link) {
        Task *first = p1.tasks.first;
        snprintf(
            out_error_msg, error_msg_length, 
            "Expected first -> t1(%p) -> t2(%p) -> t3(%p) -> t4(%p) -> (null), \n"
            "but got first -> (%p) -> (%p) -> (%p) -> (%p) -> (null)", 
            &t1, &t2, &t3, &t4,
            first, first->next, first->next->next, first->next->next->next
        );

        return false;
    }

    return true;
}

bool Queue_test_pop_front(char* out_error_msg, int error_msg_length) {
    Task t1   = { .name = "Buy grociries",              .priority = 1,  .created_at = "2025-04-14 14:35:05" };
    Task t2   = { .name = "Meeting with Bob and Jane",  .priority = 2,  .created_at = "2025-04-14 20:00:00" };
    Task t3   = { .name = "Create a presentation",      .priority = 6,  .created_at = "2025-04-14 09:16:00" };
    Task t4   = { .name = "Write budget report",        .priority = 8,  .created_at = "2025-04-14 12:45:00" };
    Person p1 = { .id = 1, .name = "John Doe",  .gender = Gender_Male, .height = 1.8f };

    Queue_push_back(p1.tasks.first, p1.tasks.last, &t1);
    Queue_push_back(p1.tasks.first, p1.tasks.last, &t2);
    Queue_push_back(p1.tasks.first, p1.tasks.last, &t3);
    Queue_push_back(p1.tasks.first, p1.tasks.last, &t4);

    Queue_pop_front(p1.tasks.first, p1.tasks.last);
    Queue_pop_front(p1.tasks.first, p1.tasks.last);
    Queue_pop_front(p1.tasks.first, p1.tasks.last);

    if (p1.tasks.first != p1.tasks.last) {
        snprintf(
            out_error_msg, error_msg_length, 
            "Expected last to be '%p', but got '%p'.", 
            p1.tasks.first, p1.tasks.last
        );

        return false;
    }

    Queue_pop_front(p1.tasks.first, p1.tasks.last);

    if (p1.tasks.first != NULL || p1.tasks.last != NULL) {
        snprintf(
            out_error_msg, error_msg_length, 
            "Expected pointers first and last to be 'null', but got '%p' and '%p'.", 
            p1.tasks.first, p1.tasks.last
        );

        return false;
    }

    Queue_push_back(p1.tasks.first, p1.tasks.last, &t3);
    Queue_push_back(p1.tasks.first, p1.tasks.last, &t4);

    if (strcmp(p1.tasks.first->name, t3.name) != 0) 
    if (p1.tasks.first->priority != t3.priority) 
    if (p1.tasks.first != &t3) 
    {
        snprintf(
            out_error_msg, error_msg_length, 
            "Expected task '%s', but got '%s'.", 
            t3.name, p1.tasks.first->name
        );

        return false;
    }
    

    if (strcmp(p1.tasks.last->name, t4.name) == 0) 
    if (p1.tasks.first->priority != t3.priority) 
    if (p1.tasks.first != &t3) 
    {
        snprintf(
            out_error_msg, error_msg_length, 
            "Expected task '%s', but got '%s'.", 
            t4.name, p1.tasks.last->name
        );

        return false;
    }

#ifdef Tests_Debug_Trace
    Queue_print_person(p1);
#endif

    return true;
}
