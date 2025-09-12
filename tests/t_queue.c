#include "tests.h"

typedef struct {
    int         id;
    const char *name;
    float       amount;
} Account;

typedef struct {
    QueueHeader;
    Account items[256];
} QueueAccount;

bool Queue_test_insert() {
    return false;
}

bool Queue_test_remove() {
    return false;
}