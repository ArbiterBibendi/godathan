#pragma once
#include "godathan.h"
#include "sleepy_discord/websocketpp_websocket.h"
#include <fstream>
#include <iomanip>
#include <math.h>
#include <cstring>


class VoiceEventHandler : public SleepyDiscord::BaseVoiceEventHandler {
public:
    VoiceEventHandler();
    ~VoiceEventHandler();
    void onReady(SleepyDiscord::VoiceConnection& connection) override;
    
};



/**
 * TODO: USE CORRECT WAV FILE
 * TODO: FIX ALIASING
 * TODO: RESAMPLE CORRECT WAV FILE TO 48000HZ
 * TODO: REFACTOR THIS MESS
 */
struct WavFile {
    WavFile(std::string filePath){
        std::ifstream wavFile;
        wavFile.open(filePath, std::ios::in);
        if(wavFile.is_open()){
            std::cout << "Could open WAV" << std::endl;
            wavFile.read((char*)this, sizeof(WavFile) - sizeof(data));
        
            for (int i = 0; i < subchunk2Size/sizeof(int16_t); i++){
                int16_t sample = 0;
                wavFile.read((char*) &sample, sizeof(sample));
                data.push_back(sample);
            }
            wavFile.close();
        } else{
            std::cout << "Couldn't open WAV" << std::endl;
        }
    }
    char            chunkID[4];
    unsigned int    chunkSize;
    char            format[4];
    char            subchunkID[4];
    unsigned int    subchunkSize;
    unsigned short  audioFormat;
    unsigned short  numChannels;
    unsigned int    sampleRate;
    unsigned int    byteRate;
    unsigned short  blockAlign;
    unsigned short  bitsPerSample;
    char            subchunk2ID[4];
    unsigned int    subchunk2Size;
    std::vector<int16_t> data;
    
};


struct Source : public SleepyDiscord::AudioPointerSource {
    Source() : SleepyDiscord::AudioPointerSource(), file("../externals/dectalk/piano2.wav"), sampleOffset(0) { //Init file with test file: 48khz 16 bits per sample not pushed to git
        numSamples = file.data.size();
        std::cout << "NUMSAMPLES " << (unsigned int)numSamples << std::endl;
    }
    
    
    
    void read(SleepyDiscord::AudioTransmissionDetails& details, int16_t*& buffer, std::size_t& length) {
        length = (signed)details.proposedLength() < (numSamples-sampleOffset) ? details.proposedLength() : 0;
        std::vector<int16_t> target(details.proposedLength());
        memset(target.data(), 0, target.capacity());
        for (int16_t& sample : target){
            //sample = (++sampleOffset / 100) % 2 ? 1 : -1;
            if(sampleOffset < numSamples){
                sample = file.data[sampleOffset++];
                if(sample != 0){
                    std::cout << sample << std::endl;
                } else {
                    sample = 1000;
                }
            }
            
            
            
            
        }
        buffer = target.data();
    }
    int numSamples = 0;
    int sampleOffset = 0;
    WavFile file;
};


