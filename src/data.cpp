#include <EEPROM.h>
#include "main.h"

void save_data(SwitchConfig conf) {
    EEPROM.put(0, conf);
}

SwitchConfig load_data() {
    SwitchConfig conf;
    EEPROM.get(0, conf);
    return conf;
}