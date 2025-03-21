#ifndef RCC_RECEIVER_H
#define RCC_RECEIVER_H

#include <Arduino.h>
#include <initializer_list>

#define MAX_CHANNELS 10

class RCReceiver {
public:
    RCReceiver(std::initializer_list<uint8_t> pins);
    void begin(void);
    void enableChannel(uint8_t channel);
    void disableChannel(uint8_t channel);
    uint32_t getChannelValue(uint8_t channel) const;
    void setChannelRange(uint8_t channel, uint32_t inMin, uint32_t inMax, int32_t outMin, int32_t outMax);
    int32_t getMappedChannelValue(uint8_t channel) const;

private:
    uint8_t numChannels;
    static uint8_t channelPins[MAX_CHANNELS];
    bool channelEnabled[MAX_CHANNELS];
    uint32_t inputMin[MAX_CHANNELS];
    uint32_t inputMax[MAX_CHANNELS];
    int32_t outputMin[MAX_CHANNELS];
    int32_t outputMax[MAX_CHANNELS];
    uint32_t lastValidValue[MAX_CHANNELS];

    static volatile uint32_t pwmValues[MAX_CHANNELS];
    static volatile uint32_t lastCapture[MAX_CHANNELS];

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
};

#endif // RCC_RECEIVER_H