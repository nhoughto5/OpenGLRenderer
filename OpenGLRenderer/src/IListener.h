#pragma once
#include "Events/Event.h"

class IListener
{
public:
    virtual ~IListener() {}
    virtual void OnEvent(Event& e) = 0;
};