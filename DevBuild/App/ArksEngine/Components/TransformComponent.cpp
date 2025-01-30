#include "TransformComponent.h"

void ArksEngineComponents::TransformComponent::Init()
{
	mPosition = { 0,0 }; // Default
	mRotation = { 0,0 }; // Default
	mScale = { 0,0 };  // Default
}


void ArksEngineComponents::TransformComponent::SetPosition(float x, float y)
{
	mPosition.m_x = x;
	mPosition.m_y = y;
}

void ArksEngineComponents::TransformComponent::SetRotation(float x, float y)
{
	mRotation.m_x = x;
	mRotation.m_y = y;
}

void ArksEngineComponents::TransformComponent::SetScale(float x, float y)
{
	mScale.m_x = x;
	mScale.m_y = y;
}


