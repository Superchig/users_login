#ifndef USERS_H
#define USERS_H

#include <Arduino.h>

// Represents a username-password combination
struct User {
  byte ID[4]; // 4-byte ID that corresponds to one in an RFID card
  String username;
  String password;
};

// Compares if two 4-byte IDs are equal
bool equalID(byte ID1[4], byte ID2[4]);
// Searches for a User in a User array by ID
// Returns a pointer to the User if its ID matches
// Returns nullptr if no such User is found
User *find_user_by_id(User users[], int users_length, byte ID[]);

#endif
