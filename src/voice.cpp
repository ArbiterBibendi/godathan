#include "voice.h"
#include <iostream>
#include "godathan.h"


VoiceEventHandler::VoiceEventHandler(){
    std::cout << "VEH Created" << std::endl;
}
VoiceEventHandler::~VoiceEventHandler(){
    std::cout << "VEH Destroyed" << std::endl;
}
void VoiceEventHandler::onReady(SleepyDiscord::VoiceConnection& connection){
    std::cout << "VEH Ready" << std::endl;
    connection.readyToSpeak = true; //TODO: Figure out why this is executing after loop godathan.cpp:102 Possible threading issue gn :)
}
