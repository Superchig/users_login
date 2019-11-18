#include <Arduino.h>
#include "user.h"

bool equalID(byte ID1[4], byte ID2[4]) {
    for (int i = 0; i < 4; ++i) {
        if (ID1[i] != ID2[i]) {
            return false;
        }
    }

    return true;
}

User *find_user_by_id(User users[], int users_len, byte ID[4]) {
    for (int i = 0; i < users_len; ++i) {
        if (equalID(ID, users[i].ID)) {
            return &users[i];
        }
    }

    return nullptr;
}
