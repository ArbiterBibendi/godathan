#pragma once
#include "godathan.h"
#include "sleepy_discord/websocketpp_websocket.h"


class VoiceEventHandler : public SleepyDiscord::BaseVoiceEventHandler {
public:
    VoiceEventHandler();
    ~VoiceEventHandler();
    void onReady(SleepyDiscord::VoiceConnection& connection) override;
    
};

struct Source : public SleepyDiscord::AudioVectorSource {
    Source() : SleepyDiscord::AudioVectorSource(), sampleOffset(0) {}
    std::vector<int16_t> read(SleepyDiscord::AudioTransmissionDetails& details) {
        std::vector<int16_t> buffer(details.proposedLength());
        for (int16_t& sample : buffer){
            sample = (++sampleOffset / 100) % 2 ? 2000 : -2000;
        }
        return buffer;
    }
    std::size_t sampleOffset = 0;
};

