#ifndef RC_RECEIVER_H
#define RC_RECEIVER_H

#include <Arduino.h>

// Maximum number of channels supported
#define MAX_CHANNELS 10U

// RCReceiver class to handle reading PWM signals from an RC receiver
class RCReceiver {
public:
    // Constructor to initialize the RC receiver with a specific number of channels
    RCReceiver(uint8_t numChannels);

    // Initialize the RC receiver
    void begin(void);

    // Enable a specific channel
    void enableChannel(uint8_t channel);

    // Disable a specific channel
    void disableChannel(uint8_t channel);

    // Get the PWM value of a specific channel
    // @param channel: The channel number (0 to MAX_CHANNELS-1)
    // @return The PWM value in microseconds
    uint32_t getChannelValue(uint8_t channel) const;

    // Set the input and output range for a specific channel
    // @param channel: The channel number (0 to MAX_CHANNELS-1)
    // @param inMin: The minimum input value
    // @param inMax: The maximum input value
    // @param outMin: The minimum output value
    // @param outMax: The maximum output value
    void setChannelRange(uint8_t channel, uint32_t inMin, uint32_t inMax, int32_t outMin, int32_t outMax);

    // Map the PWM value of a specific channel to a user-defined range
    // @param channel: The channel number (0 to MAX_CHANNELS-1)
    // @return The mapped value
    int32_t getMappedChannelValue(uint8_t channel) const;

private:
    // Interrupt service routines for each channel
    static void captureCH0(void);
    static void captureCH1(void);
    static void captureCH2(void);
    static void captureCH3(void);
    static void captureCH4(void);
    static void captureCH5(void);
    static void captureCH6(void);
    static void captureCH7(void);
    static void captureCH8(void);
    static void captureCH9(void);

    // Arrays to store PWM values and last capture times for each channel
    static volatile uint32_t pwmValues[MAX_CHANNELS];
    static volatile uint32_t lastCapture[MAX_CHANNELS];

    // Array to store the enabled state of each channel
    bool channelEnabled[MAX_CHANNELS];

    // Arrays to store the input and output ranges for each channel
    uint32_t inputMin[MAX_CHANNELS];
    uint32_t inputMax[MAX_CHANNELS];
    int32_t outputMin[MAX_CHANNELS];
    int32_t outputMax[MAX_CHANNELS];

    // Array to store the last valid mapped value for each channel
    mutable int32_t lastValidValue[MAX_CHANNELS];

    // Number of channels
    uint8_t numChannels;
};

#endif // RC_RECEIVER_H