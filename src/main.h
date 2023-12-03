#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include "HID-Project.h"

struct KeyData {
    int min;
    int max;
    int trigger;
    int release;
    int value;
    int reference;
    bool pressed;
};

#define TOTAL_KEYS 2
#define CUSHION 10

// switch config in mm (default)
struct SwitchConfig {
    float trigger = 0.9;
    float release = 0.8;
    int bottom_out_distance = 4;
    KeyboardKeycode key_1 = KEY_W;
    KeyboardKeycode key_2 = KEY_E;
};

extern SwitchConfig config;

extern KeyData keys[TOTAL_KEYS];
extern uint8_t keyPins[TOTAL_KEYS];
extern KeyboardKeycode keyCodes[TOTAL_KEYS];

#endif