#include "RCReceiver.h"

// Define channel pins (adjust as needed)
static const uint8_t channelPins[MAX_CHANNELS] = {0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U, 9U};

// Initialize arrays to store PWM values and last capture times
volatile uint32_t RCReceiver::pwmValues[MAX_CHANNELS] = {0U};
volatile uint32_t RCReceiver::lastCapture[MAX_CHANNELS] = {0U};

// Constructor to initialize the RC receiver with a specific number of channels
RCReceiver::RCReceiver(uint8_t numChannels) : numChannels(numChannels) {
    for (uint8_t i = 0U; i < MAX_CHANNELS; ++i) {
        channelEnabled[i] = false;
        inputMin[i] = 1000U; // Default minimum input value
        inputMax[i] = 2000U; // Default maximum input value
        outputMin[i] = 0;    // Default minimum output value
        outputMax[i] = 100;  // Default maximum output value
        lastValidValue[i] = 0; // Initialize last valid value
    }
}

// Function to initialize the RC receiver
void RCReceiver::begin(void) {
    for (uint8_t i = 0U; i < numChannels; ++i) {
        if (channelEnabled[i]) {
            // Configure pins as input
            pinMode(channelPins[i], INPUT);

            // Attach interrupts to the pins
            switch (i) {
                case 0U: attachInterrupt(digitalPinToInterrupt(channelPins[0U]), captureCH0, CHANGE); break;
                case 1U: attachInterrupt(digitalPinToInterrupt(channelPins[1U]), captureCH1, CHANGE); break;
                case 2U: attachInterrupt(digitalPinToInterrupt(channelPins[2U]), captureCH2, CHANGE); break;
                case 3U: attachInterrupt(digitalPinToInterrupt(channelPins[3U]), captureCH3, CHANGE); break;
                case 4U: attachInterrupt(digitalPinToInterrupt(channelPins[4U]), captureCH4, CHANGE); break;
                case 5U: attachInterrupt(digitalPinToInterrupt(channelPins[5U]), captureCH5, CHANGE); break;
                case 6U: attachInterrupt(digitalPinToInterrupt(channelPins[6U]), captureCH6, CHANGE); break;
                case 7U: attachInterrupt(digitalPinToInterrupt(channelPins[7U]), captureCH7, CHANGE); break;
                case 8U: attachInterrupt(digitalPinToInterrupt(channelPins[8U]), captureCH8, CHANGE); break;
                case 9U: attachInterrupt(digitalPinToInterrupt(channelPins[9U]), captureCH9, CHANGE); break;
                default: break;
            }
        }
    }
}

// Function to enable a specific channel
void RCReceiver::enableChannel(uint8_t channel) {
    if (channel < MAX_CHANNELS) {
        channelEnabled[channel] = true;
    }
}

// Function to disable a specific channel
void RCReceiver::disableChannel(uint8_t channel) {
    if (channel < MAX_CHANNELS) {
        channelEnabled[channel] = false;
    }
}

// Function to get the PWM value of a specific channel
uint32_t RCReceiver::getChannelValue(uint8_t channel) const {
    uint32_t value = 0U;
    if (channel < MAX_CHANNELS && channelEnabled[channel]) {
        // Disable interrupts to ensure data consistency
        noInterrupts();
        value = pwmValues[channel];
        // Re-enable interrupts
        interrupts();
    }
    return value;
}

// Function to set the input and output range for a specific channel
void RCReceiver::setChannelRange(uint8_t channel, uint32_t inMin, uint32_t inMax, int32_t outMin, int32_t outMax) {
    if (channel < MAX_CHANNELS) {
        inputMin[channel] = inMin;
        inputMax[channel] = inMax;
        outputMin[channel] = outMin;
        outputMax[channel] = outMax;
    }
}

// Function to map the PWM value of a specific channel to a user-defined range
int32_t RCReceiver::mappedChannelValue(uint8_t channel) const {
    if (channel < MAX_CHANNELS && channelEnabled[channel]) {
        uint32_t value = getChannelValue(channel);
        int32_t mappedValue = static_cast<int32_t>((value - inputMin[channel]) * (outputMax[channel] - outputMin[channel]) / (inputMax[channel] - inputMin[channel]) + outputMin[channel]);
        // Cap the mapped value within the defined range
        if (mappedValue < outputMin[channel]) {
            mappedValue = outputMin[channel];
        } else if (mappedValue > outputMax[channel]) {
            mappedValue = outputMax[channel];
        }
        return mappedValue;
    }
    return 0;
}

// Function to filter the PWM value of a specific channel to a user-defined range
int32_t RCReceiver::filteredChannelValue(uint8_t channel) const {
    if (channel < MAX_CHANNELS && channelEnabled[channel]) {
        uint32_t value = getChannelValue(channel);
        int32_t mappedValue = static_cast<int32_t>((value - inputMin[channel]) * (outputMax[channel] - outputMin[channel]) / (inputMax[channel] - inputMin[channel]) + outputMin[channel]);
        // Check if the mapped value is within the defined range
        if (mappedValue >= outputMin[channel] && mappedValue <= outputMax[channel]) {
            lastValidValue[channel] = mappedValue;
        }
        return lastValidValue[channel];
    }
    return 0;
}

// Interrupt service routines for each channel
void RCReceiver::captureCH0(void) {
    uint32_t currentTime = micros();
    if (digitalRead(channelPins[0U]) == HIGH) {
        lastCapture[0U] = currentTime;
    } else {
        pwmValues[0U] = currentTime - lastCapture[0U];
    }
}

void RCReceiver::captureCH1(void) {
    uint32_t currentTime = micros();
    if (digitalRead(channelPins[1U]) == HIGH) {
        lastCapture[1U] = currentTime;
    } else {
        pwmValues[1U] = currentTime - lastCapture[1U];
    }
}

void RCReceiver::captureCH2(void) {
    uint32_t currentTime = micros();
    if (digitalRead(channelPins[2U]) == HIGH) {
        lastCapture[2U] = currentTime;
    } else {
        pwmValues[2U] = currentTime - lastCapture[2U];
    }
}

void RCReceiver::captureCH3(void) {
    uint32_t currentTime = micros();
    if (digitalRead(channelPins[3U]) == HIGH) {
        lastCapture[3U] = currentTime;
    } else {
        pwmValues[3U] = currentTime - lastCapture[3U];
    }
}

void RCReceiver::captureCH4(void) {
    uint32_t currentTime = micros();
    if (digitalRead(channelPins[4U]) == HIGH) {
        lastCapture[4U] = currentTime;
    } else {
        pwmValues[4U] = currentTime - lastCapture[4U];
    }
}

void RCReceiver::captureCH5(void) {
    uint32_t currentTime = micros();
    if (digitalRead(channelPins[5U]) == HIGH) {
        lastCapture[5U] = currentTime;
    } else {
        pwmValues[5U] = currentTime - lastCapture[5U];
    }
}

void RCReceiver::captureCH6(void) {
    uint32_t currentTime = micros();
    if (digitalRead(channelPins[6U]) == HIGH) {
        lastCapture[6U] = currentTime;
    } else {
        pwmValues[6U] = currentTime - lastCapture[6U];
    }
}

void RCReceiver::captureCH7(void) {
    uint32_t currentTime = micros();
    if (digitalRead(channelPins[7U]) == HIGH) {
        lastCapture[7U] = currentTime;
    } else {
        pwmValues[7U] = currentTime - lastCapture[7U];
    }
}

void RCReceiver::captureCH8(void) {
    uint32_t currentTime = micros();
    if (digitalRead(channelPins[8U]) == HIGH) {
        lastCapture[8U] = currentTime;
    } else {
        pwmValues[8U] = currentTime - lastCapture[8U];
    }
}

void RCReceiver::captureCH9(void) {
    uint32_t currentTime = micros();
    if (digitalRead(channelPins[9U]) == HIGH) {
        lastCapture[9U] = currentTime;
    } else {
        pwmValues[9U] = currentTime - lastCapture[9U];
    }
}