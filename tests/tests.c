#include "tests.h"

///TODO:
// [] Make a test CLI
// [] String
// [] String Builder
// [] String View
// [] Queue
// [] Arena
// [] Hash Table

int main(int argc, char* argv[]) {
    char error_msg[Error_Msg_Length] = {0};

    // Stack
    //
    if (Stack_test_push(error_msg, Error_Msg_Length)) 
        Log_Success("Stack_test_push()\n");
    else 
        Log_Error("Stack_test_push() - %s\n", error_msg);  

    if (Stack_test_pop(error_msg, Error_Msg_Length)) 
        Log_Success("Stack_test_pop()\n");
    else 
        Log_Error("Stack_test_pop() - %s\n", error_msg);  

    if (Stack_test_peek(error_msg, Error_Msg_Length))
        Log_Success("Stack_test_peek()\n");
    else 
        Log_Error("Stack_test_peek() - %s\n", error_msg);  

    // Dynamic Array
    //
    if (DynamicArray_test_ensure_capacity(error_msg, Error_Msg_Length))
        Log_Success("DynamicArray_test_capacity()\n");
    else 
        Log_Error("DynamicArray_test_capacity() - %s\n", error_msg);  

    if(DynamicArray_test_append(error_msg, Error_Msg_Length))
        Log_Success("DynamicArray_test_append()\n");
    else 
        Log_Error("DynamicArray_test_append() - %s\n", error_msg);  

    if (DynamicArray_test_append_many(error_msg, Error_Msg_Length))
        Log_Success("DynamicArray_test_append_many()\n");
    else 
        Log_Error("DynamicArray_test_append_many() - %s\n", error_msg);  

    if (DynamicArray_test_append_strings(error_msg, Error_Msg_Length))
        Log_Success("DynamicArray_test_append_strings()\n");
    else 
        Log_Error("DynamicArray_test_append_strings() - %s\n", error_msg);  
    
    if (DynamicArray_test_append_string_ptr(error_msg, Error_Msg_Length))
        Log_Success("DynamicArray_test_append_string_ptr()\n");
    else 
        Log_Error("DynamicArray_test_append_string_ptr() - %s\n", error_msg);  

    // Linked List 
    //
    if (LinkedList_test_push(error_msg, Error_Msg_Length))
        Log_Success("LinkedList_test_push()\n");
    else 
        Log_Error("LinkedList_test_push() - %s\n", error_msg);  

    if (LinkedList_test_pop(error_msg, Error_Msg_Length))
        Log_Success("LinkedList_test_pop()\n");
    else 
        Log_Error("LinkedList_test_pop() - %s\n", error_msg);  

    if (LinkedList_test_peek(error_msg, Error_Msg_Length))
        Log_Success("LinkedList_test_peek()\n");
    else 
        Log_Error("LinkedList_test_peek() - %s\n", error_msg);  

    if (LinkedList_test_foreach(error_msg, Error_Msg_Length))
        Log_Success("LinkedList_test_foreach()\n");
    else 
        Log_Error("LinkedList_test_foreach() - %s\n", error_msg);  

    if (LinkedList_test_loop_peek_and_pop_combo(error_msg, Error_Msg_Length))
        Log_Success("LinkedList_test_loop_peek_and_pop_combo()\n");
    else 
        Log_Error("LinkedList_test_loop_peek_and_pop_combo() - %s\n", error_msg);  

    // Queue
    // 
    if (Queue_test_push_back(error_msg, Error_Msg_Length))
        Log_Success("Queue_test_push_back()\n");
    else 
        Log_Error("Queue_test_push_back() - %s\n", error_msg);  

    if (Queue_test_pop_front(error_msg, Error_Msg_Length))
        Log_Success("Queue_test_pop_front()\n");
    else 
        Log_Error("Queue_test_pop_front() - %s\n", error_msg);  

    return 0;
}