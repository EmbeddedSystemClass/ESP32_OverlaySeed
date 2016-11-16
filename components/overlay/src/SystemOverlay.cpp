#include "SystemOverlay.hpp"

SystemOverlay* SystemOverlay::_me;

bool SystemOverlay::Init(){
    return true;
}

SystemOverlay* SystemOverlay::Instance(){
    if(SystemOverlay::_me == NULL){
        _me = new SystemOverlay();
    }
    return _me;
}

SystemOverlay::SystemOverlay(){

}