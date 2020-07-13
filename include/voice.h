#pragma once
#include "godathan.h"
#include "sleepy_discord/websocketpp_websocket.h"
#include <fstream>
#include <iomanip>

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
    unsigned int   chunkSize;
    char            format[4];
    char            subchunkID[4];
    unsigned int   subchunkSize;
    unsigned short  audioFormat;
    unsigned short  numChannels;
    unsigned int   sampleRate;
    unsigned int   byteRate;
    unsigned short  blockAlign;
    unsigned short  bitsPerSample;
    char            subchunk2ID[4];
    unsigned int   subchunk2Size;
    std::vector<int16_t> data;
    
};


struct Source : public SleepyDiscord::AudioPointerSource {
    Source() : SleepyDiscord::AudioPointerSource(), file("../externals/dectalk/piano2.wav"), sampleOffset(0) { //Init file with test file: 48khz 16 bits per sample not pushed to git
        numSamples = file.subchunk2Size / file.numChannels;
        std::cout << "NUMSAMPLES " << (unsigned int)numSamples << std::endl;
    }
    
    
    
    void read(SleepyDiscord::AudioTransmissionDetails& details, int16_t*& buffer, std::size_t& length) {
        length = details.proposedLength() < (numSamples-sampleOffset) ? details.proposedLength() : 0;
        std::vector<int16_t> target(details.proposedLength());
        for (int16_t& sample : target){

            //sample = (++sampleOffset / 100) % 2 ? 1 : -1;
            sample = file.data[sampleOffset++];
            //std::cout << sampleOffset << std::endl;
            //std::cout << sample << std::endl;

        }
        buffer = target.data();
    }
    unsigned int numSamples = 0;
    std::size_t sampleOffset = 0;
    WavFile file;
};

