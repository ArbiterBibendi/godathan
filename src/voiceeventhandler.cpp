#include "voiceeventhandler.h"
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
}
