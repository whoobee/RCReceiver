#include <Arduino.h>
#include <RCReceiver.h>

// Create an RCReceiver object with 10 channels
RCReceiver receiver(10U);

void setup(void) {
    Serial.begin(115200U);
    // Enable the channels you want to use
    receiver.enableChannel(0U);
    receiver.enableChannel(1U);
    receiver.enableChannel(2U);
    receiver.enableChannel(3U);
    receiver.enableChannel(4U);
    receiver.enableChannel(5U);
    receiver.enableChannel(6U);
    receiver.enableChannel(7U);
    receiver.enableChannel(8U);
    receiver.enableChannel(9U);
    receiver.begin();

    // Set custom input and output ranges for each channel
    receiver.setChannelRange(0U, 1000U, 2000U, 0, 100);
    receiver.setChannelRange(1U, 1000U, 2000U, -50, 50);
    receiver.setChannelRange(2U, 1000U, 2000U, 0, 255);
    receiver.setChannelRange(3U, 1000U, 2000U, -100, 100);
    receiver.setChannelRange(4U, 1000U, 2000U, 0, 180);
    receiver.setChannelRange(5U, 1000U, 2000U, -90, 90);
    receiver.setChannelRange(6U, 1000U, 2000U, 0, 1023);
    receiver.setChannelRange(7U, 1000U, 2000U, -255, 255);
    receiver.setChannelRange(8U, 1000U, 2000U, 0, 360);
    receiver.setChannelRange(9U, 1000U, 2000U, -180, 180);
}

void loop(void) {
    for (uint8_t i = 0U; i < 10U; ++i) {
        Serial.print("Channel ");
        Serial.print(i + 1U);
        Serial.print(": ");
        Serial.print(receiver.getChannelValue(i));
        Serial.print(" us, Mapped: ");
        Serial.print(receiver.mappedChannelValue(i));
        Serial.print(", Filtered: ");
        Serial.print(receiver.filteredChannelValue(i));
        Serial.print(" ");
        if (i < 9U) {
            Serial.print(", ");
        } else {
            Serial.println();
        }
    }
    delay(300U);
}