#include <Arduino.h>
#include "HID-Project.h"
#include <EEPROM.h>
#include "keys.h"
#include "main.h"
#include "serial.h"
#include "data.h"

SwitchConfig config = SwitchConfig();

KeyData keys[TOTAL_KEYS] = {KeyData(), KeyData()};
uint8_t keyPins[TOTAL_KEYS] = { A2, A0 };
KeyboardKeycode keyCodes[TOTAL_KEYS] = {KEY_W, KEY_E};

void setup() {
    pinMode(LED_BUILTIN_RX, OUTPUT);
    pinMode(LED_BUILTIN_TX, OUTPUT);

    for (int i = 0; i < TOTAL_KEYS; i++) {
        init_key(i);
    }

    Serial.begin(115200);

    Keyboard.begin();

    // load config from EEPROM
    if (EEPROM.read(0) == 255) {
        // no config saved, save default config
        save_data(config);
    }
    else {
        config = load_data();
    }
}

void loop() {

    // general keyboard functions
    for (int i = 0; i < TOTAL_KEYS; i++) {
        run_key(i);
    }

    serial_communicate();
}
