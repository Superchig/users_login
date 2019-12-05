# FFC Grand Challenges Initiative RFID Prototype
This requires this [Arduino RFID library](https://github.com/miguelbalboa/rfid).

## Basic Code Layout
NOTE: .h and .cpp files are associated together.

- **users\_login.ino** - The program's main logic. Uses the other files to send
  usernames and passwords as 4-byte IDs via keyboard input.
- **user.h** and **user.cpp** - Associates usernames, passwords, and IDs
  together, and provides a way to search for a username and password given an ID
- **keysender.h** and **keysender.cpp** - Handles sending keyboard input from
  the Arduino to a computer.
