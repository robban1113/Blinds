#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <arduino_homekit_server.h>
#include <AccelStepper.h>

//Defines the pins for the stepper motor(ULN2003)
#define IN1 D1
#define IN2 D2
#define IN3 D3
#define IN4 D4

const char *ssid = "SSID";
const char *password = "PASSWORD";

bool stepperRunning = false;
AccelStepper stepper(AccelStepper::HALF4WIRE, IN1, IN2, IN3, IN4);

HomekitAccessory *_homekit_accessory; //This line is giving me error

void setup() {
    Serial.begin(115200);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    _homekit_accessory = new HomekitAccessory();
    Switch *stepperSwitch = new Switch(1);
    _homekit_accessory->addService(stepperSwitch);
    _homekit_accessory->onIdentify(identifyAccessory);
    _homekit_accessory->setup();

    stepper.setMaxSpeed(1000);
    stepper.setAcceleration(500);
}

void loop() {
    _homekit_accessory->loop();
    stepper.run();

    if (stepper.distanceToGo() == 0) {
        stepperRunning = false;
        builtinledSetStatus(false);
    }
}

void onSwitchChange(bool newState) {
    stepperRunning = newState;

    if (stepperRunning) {
        // Set the appropriate direction
        stepper.setSpeed(100); // Set the speed (steps per second)
        stepper.move(1000);    // Replace with your desired step count
    } else {
        stepper.stop();
    }
}

void identifyAccessory() {
    Serial.println("Identify");
}
//No idea what's happening here
void homekit_setup() {
    accessory_init();
    uint8_t mac[WL_MAC_ADDR_LENGTH];
    WiFi.macAddress(mac);
    int name_len = snprintf(NULL, 0, "Stepper Motor_%02X%02X%02X", mac[3], mac[4], mac[5]);
    char *name_value = (char*)malloc(name_len + 1);
    snprintf(name_value, name_len + 1, "Stepper Motor_%02X%02X%02X", mac[3], mac[4], mac[5]);
    _homekit_accessory->name.value = HOMEKIT_STRING_CPP(name_value);
    arduino_homekit_setup(&config);
}
