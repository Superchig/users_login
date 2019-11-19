#ifndef KEYSENDER_H
#define KEYSENDER_H

// Takes an 8-byte buffer representing a USB keyboard report and an ASCII character,
// and modifies the buffer to represent the character.
// Returns -1 if the character was invalid.
int findLetter(byte buffer[8], char character);

// Sends a c-style string as keyboard input
// If no string length is specified, send at most 20 characters
// If a character is invalid, that character is returned.
// If the sending succeeded, the null character is returned.
char sendKeys(byte buf[8], const char* str, int len = 20);

// Sends a keyboard report representing no keys being pressed
// Should be called after a single key is pressed
void releaseKey(byte buf[8]);

#endif
