#ifndef _GPIO_OVERLAY_H_
#define _GPIO_OVERLAY_H_

class GPIOOverlay{
public:

    bool Init();

    static GPIOOverlay* Instance();
private:
    GPIOOverlay();

    static GPIOOverlay* _me;
};

#endif