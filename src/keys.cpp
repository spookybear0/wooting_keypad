#include <Arduino.h>
#include "HID-Project.h"
#include "keys.h"
#include "main.h"

// basic structure of project from: https://github.com/chent7/hall-2k-keypad-handmade

void press_key(int key_num) {
    if (key_num == 0) {
        digitalWrite(LED_BUILTIN_RX, LOW);
        Keyboard.press(static_cast<KeyboardKeycode>(config.key_1));
    }
    else if (key_num == 1) {
        digitalWrite(LED_BUILTIN_TX, LOW);
        Keyboard.press(static_cast<KeyboardKeycode>(config.key_2));
    }
    keys[key_num].pressed = true;
}

void release_key(int key_num) {
    if (key_num == 0) {
        digitalWrite(LED_BUILTIN_RX, HIGH);
        Keyboard.release(static_cast<KeyboardKeycode>(config.key_1));
    }
    else if (key_num == 1) {
        digitalWrite(LED_BUILTIN_TX, HIGH);
        Keyboard.release(static_cast<KeyboardKeycode>(config.key_2));
    }
    keys[key_num].pressed = false;
}

void convert_distance(int key_num) {
    keys[key_num].trigger = ((keys[key_num].max - keys[key_num].min) / config.bottom_out_distance) * config.trigger;
    keys[key_num].release = ((keys[key_num].max - keys[key_num].min) / config.bottom_out_distance) * config.release;
}

void init_key(int key_num) {
    pinMode(keyPins[key_num], INPUT);
    keys[key_num].value = analogRead(keyPins[key_num]);
    keys[key_num].reference = keys[key_num].value;

    // auto-balancing keys
    keys[key_num].min = keys[key_num].value - CUSHION;
    keys[key_num].max = keys[key_num].value + CUSHION;

    keys[key_num].trigger = config.trigger * CUSHION;
    keys[key_num].release = config.release * CUSHION;
}

void balance_key(int key_num) {
    // min (rest) and max value is updated when key is not pressed
    if (!keys[key_num].pressed && (keys[key_num].value < keys[key_num].min)) {
        keys[key_num].min = keys[key_num].value;
        convert_distance(key_num);
    }
    else if (keys[key_num].pressed && (keys[key_num].value > keys[key_num].max)) {
        keys[key_num].max = keys[key_num].value;
        convert_distance(key_num);
    }
}

void process_key(int key_num) {
    // check if key is triggered
    if (keys[key_num].pressed) {
        if (keys[key_num].value > keys[key_num].reference + keys[key_num].trigger) {
            release_key(key_num);
        }

        if (keys[key_num].value < keys[key_num].reference) {
            keys[key_num].reference = keys[key_num].value;
        }
    }
    else {
        if (keys[key_num].value <= keys[key_num].reference - keys[key_num].release) {
            press_key(key_num);
        }

        if (keys[key_num].value > keys[key_num].reference) {
            keys[key_num].reference = keys[key_num].value;
        }
    }
}

void run_key(int key_num) {
    keys[key_num].value = analogRead(keyPins[key_num]);
    balance_key(key_num);
    process_key(key_num);
}