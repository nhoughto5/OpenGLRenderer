#include "pch.h"
#include "Layer.h"

Layer::Layer(const std::string& name)
    : m_DebugName(name)
{
}

Layer::~Layer()
{

}

void Layer::OnAttach()
{
}

void Layer::OnDetach()
{
}

void Layer::OnUpdate(TimeStep ts)
{
}

void Layer::OnEvent(Event& event)
{
}

void Layer::OnImGuiRender()
{
}