#pragma once
#include "Events/Event.h"
#include "core/util/TimeStep.h"

class IListener
{
public:
    virtual ~IListener() {}
    virtual void OnEvent(Event& e) = 0;
    virtual void OnUpdate(TimeStep ts) = 0;
};