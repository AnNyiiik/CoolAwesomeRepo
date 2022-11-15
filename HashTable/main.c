#include <stdio.h>
#include "hashTable.h"
#include "../List/list.h"
#include "test.h"

int main() {
    if (!testCreateTable()) {
        return 1;
    }
    if (!testDelete()) {
        return 1;
    }
    if (!testHash()) {
        return 1;
    }
    if (!testAdd()) {
        return 1;
    }
    if (!testDelete()) {
        return 1;
    }
    if (!testMaxSegment()) {
        return 1;
    }
    if (!testAverageSegment()) {
        return 1;
    }
    if (!testOccupancy()) {
        return 1;
    }
    return 0;
}
