#pragma once

#include "ClientHook/ClientHook.h"
#include "ClientModeHook/ClientModeHook.h"
#include "PredictionHook/PredictionHook.h"
#include "SurfaceHook/SurfaceHook.h"
#include "PanelHook/PanelHook.h"
#include "EngineVGuiHook/EngineVGuiHook.h"
#include "EngineClientHook/EngineClientHook.h"
#include "ModelRenderHook/ModelRenderHook.h"

class C_Hooks
{
public:
	void Init();
	void Release();
};

extern C_Hooks gHooks;