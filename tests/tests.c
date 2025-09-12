#include "tests.h"

///TODO:
// [] Make a test CLI
// [] String
// [] String Builder
// [] String View
// [] Queue
// [] Arena
// [] Hash Table

#define Error_Msg_Length 1024

int main(int argc, char* argv[]) {
    char error_msg[Error_Msg_Length] = {0};

    if (DynamicArray_test_ensure_capacity(error_msg, Error_Msg_Length))
         printf("[PASS] DynamicArray_test_capacity()\n"); 
    else printf("[FAIL] DynamicArray_test_capacity(): %s\n", error_msg);

    if(DynamicArray_test_append(error_msg, Error_Msg_Length))
         printf("[PASS] DynamicArray_test_append()\n"); 
    else printf("[FAIL] DynamicArray_test_append(): %s\n", error_msg);

    if (DynamicArray_test_append_many(error_msg, Error_Msg_Length))
         printf("[PASS] DynamicArray_test_append_many()\n"); 
    else printf("[FAIL] DynamicArray_test_append_many(): %s\n", error_msg);

    if (DynamicArray_test_append_strings(error_msg, Error_Msg_Length))
         printf("[PASS] DynamicArray_test_append_strings()\n"); 
    else printf("[FAIL] DynamicArray_test_append_strings(): %s\n", error_msg);
    
    if (DynamicArray_test_append_string_ptr(error_msg, Error_Msg_Length))
         printf("[PASS] DynamicArray_test_append_string_ptr()\n"); 
    else printf("[FAIL] DynamicArray_test_append_string_ptr(): %s\n", error_msg);

    return 0;
}