#pragma once
#include "core/Core.h"
#include "Events/Event.h"
#include "core/util/TimeStep.h"
//#include "imgui.h"
class Layer {
public:
    Layer(const std::string& name = "Layer");
    virtual ~Layer();

    virtual void OnAttach(GLFWwindow* window);
    virtual void OnDetach();
    virtual void OnUpdate(TimeStep ts);
    virtual void OnEvent(Event& event);
    virtual void OnImGuiRender();
    inline const std::string& GetName() const { return m_DebugName; }
protected:
    std::string m_DebugName;
};