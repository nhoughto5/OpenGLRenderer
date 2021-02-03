#pragma once
#include "Layer.h"
class ImGuiLayer : public Layer {
public:
    ImGuiLayer();
    ~ImGuiLayer();

    void Begin();
    void End(float windowWidth, float windowHeight);

    virtual void OnAttach(GLFWwindow* window) override;
    virtual void OnDetach() override;
    virtual void OnImGuiRender() override;
private:
    GLFWwindow* m_Window;
    float m_Time = 0.0f;
};
