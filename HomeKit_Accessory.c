#include <Arduino.h>
#include <homekit/types.h>
#include <homekit/homekit.h>
#include <homekit/characteristics.h>
#include <stdio.h>
#include <port.h>

//Called to identify the accessory
void my_accessory_identify(homekit_value_t _value) {
  printf("accessory identify\n");
}

// FOR WINDOW
// the required characteristics are: CURRENT_POSITION, TARGET_POSITION, POSITION_STATE
// the optional characteristics are: NAME, HOLD_POSITION, OBSTRUCTION_DETECTED
// See HAP section 8.41 and characteristics.h

homekit_characteristic_t cha_current_position = HOMEKIT_CHARACTERISTIC_(CURRENT_POSITION, "0");
homekit_characteristic_t cha_target_position = HOMEKIT_CHARACTERISTIC_(TARGET_POSITION, "0");
homekit_characteristic_t cha_position_state = HOMEKIT_CHARACTERISTIC_(POSITION_STATE, "0");

// (optional) format: bool; HAP section x.xx 
// homekit_characteristic_t cha_name = HOMEKIT_CHARACTERISTIC_(NAME, "window blinds");

// (optional) format: bool; HAP section x.xx 
// homekit_characteristic_t cha_hold_postion = HOMEKIT_CHARACTERISTIC_(HOLD_POSITION, "typ av parameter?"); //unsure of parameter

// (optional) format: bool; HAP section x.xx 
// homekit_characteristic_t cha_obstruction_detected = HOMEKIT_CHARACTERISTIC_(OBSTRUCTION_DETECTED, false);


homekit_accessory_t *accessories[] = {
    HOMEKIT_ACCESSORY(.id=1, .category=homekit_accessory_category_window, .services=(homekit_service_t*[]) {
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(CURRENT_POSTION, "0"),
            HOMEKIT_CHARACTERISTIC(TARGET_POSTION, "0"),
            HOMEKIT_CHARACTERISTIC(POSTION_STATE, "0"),
            NULL
        }),
        HOMEKIT_SERVICE(WINDOW, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
            &cha_current_position,
      &cha_target_position,
      &cha_position_state,
      //&cha_name,//optional
      //&cha_hold_position,//optional
      //&cha_obstruction_detected,//optional
            NULL
        }),
    // Add this HOMEKIT_SERVICE if you want to use another accessory together
    /*
        HOMEKIT_SERVICE(ACCESSORY, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "accessory-example-button"),
            &cha_accessory,
            NULL
        }),*/
        NULL
    }),
    NULL
};

homekit_server_config_t config = {
    .accessories = accessories,
    .password = "111-11-111"
    .setupId = "ABCD" // Not sure if this is needed
};
