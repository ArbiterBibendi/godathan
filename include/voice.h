#pragma once
#include "godathan.h"
#include "sleepy_discord/websocketpp_websocket.h"


class VoiceEventHandler : public SleepyDiscord::BaseVoiceEventHandler {
public:
    VoiceEventHandler();
    ~VoiceEventHandler();
    void onReady(SleepyDiscord::VoiceConnection& connection) override;
    
};

struct Source : public SleepyDiscord::AudioPointerSource {
    Source() : SleepyDiscord::AudioPointerSource(), sampleOffset(0) {}
    void read(SleepyDiscord::AudioTransmissionDetails& details, int16_t*& buffer, std::size_t& length) {
        length = details.proposedLength();
        std::vector<int16_t> target(details.proposedLength());
        for (int16_t& sample : target){
            sample = (++sampleOffset / 100) % 2 ? 2000 : -2000;
        }
        buffer = target.data();
    }
    std::size_t sampleOffset = 0;
};

