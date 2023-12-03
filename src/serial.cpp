#include <Arduino.h>
#include "main.h"
#include "data.h"

// string sep (https://arduino.stackexchange.com/questions/1013/how-do-i-split-an-incoming-string)
String getValue(String data, char separator, int index) {
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void recieve_heartbeat() {
    Serial.println("h");
}

void recieve_config(String inp) {
    // config = "c float, float, int, int, int"
    float trigger = getValue(inp, ' ', 1).toFloat();
    float release = getValue(inp, ' ', 2).toFloat();
    int bottom_out_distance = getValue(inp, ' ', 3).toInt();
    int key_1 = getValue(inp, ' ', 4).toInt();
    int key_2 = getValue(inp, ' ', 5).toInt();

    config.trigger = trigger;
    config.release = release;
    config.bottom_out_distance = bottom_out_distance;
    config.key_1 = static_cast<KeyboardKeycode>(key_1);
    config.key_2 = static_cast<KeyboardKeycode>(key_2);

    save_data(config);

    Serial.println("c 1"); // config saved successfully
}

void send_config() {
    Serial.print("c ");
    Serial.print(config.trigger);
    Serial.print(" ");
    Serial.print(config.release);
    Serial.print(" ");
    Serial.print(config.bottom_out_distance);
    Serial.print(" ");
    Serial.print(config.key_1);
    Serial.print(" ");
    Serial.println(config.key_2);
}

void serial_communicate() {
    if (Serial.available() > 0) {
        String inp = Serial.readString();
        
        if (inp == "h") {
            recieve_heartbeat();
        }
        else if (inp.startsWith("c ")) {
            recieve_config(inp);
        }
        else if (inp == "cg") {
            send_config();
        }
        else if (inp == "cr") {

        }
    }
}