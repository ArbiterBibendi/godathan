#include "voiceeventhandler.h"
#include <iostream>

VoiceEventHandler::VoiceEventHandler(){
    std::cout << "VEH Created" << std::endl;
}
void VoiceEventHandler::onReady(SleepyDiscord::VoiceConnection& connection){
    std::cout << "VEH Ready" << std::endl;
}
