#include <Arduino.h>
#include "keysender.h"

int findLetter(byte buffer[8], char character) {
    buffer[0] = 0; // Set modifier keys status to 0

    bool presshift = false;
    byte usage_id = -1;

    if (character >= 65 && character <= 90) { // Character is a capital letter
        usage_id = character - 61;
        presshift = true;
    } else if (character >= 97 && character <= 122) { // Character is a lowercase letter
        usage_id = character - 93;
    } else if (character >= 49 && character <= 57) { // Character is a digit 1-9
        usage_id = character - 19;
    } else if (character == '0') {
        usage_id = 39;
    } else if (character == ' ') {
        usage_id = 44;
    } else if (character == '!') {
        usage_id = 30;
        presshift = true;
    } else if (character == '"') {
        usage_id = 52;
        presshift = true;
    } else if (character == '#') {
        usage_id = 20;
        presshift = true;
    } else if (character == '$') {
        usage_id = 33;
        presshift = true;
    } else if (character == '%') {
        usage_id = 34;
        presshift = true;
    } else if (character == '&') {
        usage_id = 36;
        presshift = true;
    } else if (character == '\'') {
        usage_id = 52;
    } else if (character == '(' || character == ')') {
        usage_id = character - 12;
        presshift = true;
    } else if (character == '*') {
        usage_id = 37;
        presshift = true;
    } else if (character == '+') {
        usage_id = 87;
        presshift = true;
    } else if (character == ',') {
        usage_id = 54;
    } else if (character == '-') {
        usage_id = 45;
    } else if (character == '.') {
        usage_id = 55;
    } else if (character == '/') {
        usage_id = 56;
    } else if (character == ':') {
        usage_id = 51;
        presshift = true;
    } else if (character == ';') {
        usage_id = 51;
    } else if (character == '<') {
        usage_id = 54;
        presshift = true;
    } else if (character == '=') {
        usage_id = 46;
        presshift = true;
    } else if (character == '>') {
        usage_id = 55;
        presshift = true;
    } else if (character == '?') {
        usage_id = 56;
        presshift = true;
    } else if (character == '@') {
        usage_id = 31;
        presshift = true;
    } else if (character == '[') {
        usage_id = 47;
    } else if (character == '\\') {
        usage_id = 49;
    } else if (character == ']') {
        usage_id = 48;
    } else if (character == '^') {
        usage_id = 35;
        presshift = true;
    } else if (character == '_') {
        usage_id = 45;
        presshift = true;
    } else if (character == '`') {
        usage_id = 53;
    } else if (character == '{') {
        usage_id = 47;
        presshift = true;
    } else if (character == '|') {
        usage_id = 49;
        presshift = true;
    } else if (character == '}') {
        usage_id = 48;
        presshift = true;
    } else if (character == '~') {
        usage_id = 53;
        presshift = true;
    } else if (character == '\t') {
        usage_id = 43;
    } else if (character == '\n') {
        usage_id = 40;
    } else {
        return -1;
    }

    buffer[2] = usage_id;
    if (presshift) {
        // Set the 2nd bit of the first byte to 1
        // This activates left shift
        buffer[0] |= 1UL << 1;
    }

    return 0;
}

char sendKeys(byte buf[8], const char* str, int len) {
  for (int i = 0; i < len; ++i) {
    int result = findLetter(buf, str[i]);
    if (result == -1) {
      return str[i];
    }
    Serial.write(buf, 8);
    releaseKey(buf);
  }

  return '\0';
}


void releaseKey(byte buf[8]) {
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8); // Release key
}
