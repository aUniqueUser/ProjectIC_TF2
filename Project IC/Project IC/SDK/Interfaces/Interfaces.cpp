#include "Interfaces.h"

#define CHECKNULL(func, message) if (!func) printf("%s", message)

#define CLIENT_SO		"client.so"
#define ENGINE_SO		"engine.so"
#define SERVER_SO		"server.so"
#define VGUI2_SO		"vgui2.so"
#define MATSURFACE_SO	"vguimatsurface.so"
#define VSTDLIB_SO		"vstdlib.so"
#define STEAMCLIENT_SO "SteamClient.so"
#define MATSYSTEM_SO   "MaterialSystem.so"

void C_Interfaces::Init()
{
	Client = reinterpret_cast<C_BaseClientDLL*>(gInterface.Get(CLIENT_SO, CLIENT_DLL_INTERFACE_VERSION));
	CHECKNULL(Client, "Client = nullptr!");

	ClientShared = reinterpret_cast<C_ClientDLLSharedAppSystems*>(gInterface.Get(CLIENT_SO, CLIENT_DLL_SHARED_APPSYSTEMS));
	CHECKNULL(ClientShared, "ClientShared = nullptr!");

	EntityList = reinterpret_cast<C_ClientEntityList*>(gInterface.Get(CLIENT_SO, VCLIENTENTITYLIST_INTERFACE_VERSION));
	CHECKNULL(EntityList, "EntityList = nullptr!");

	Prediction = reinterpret_cast<C_Prediction*>(gInterface.Get(CLIENT_SO, VCLIENT_PREDICTION_INTERFACE_VERSION));
	CHECKNULL(Prediction, "Prediction = nullptr!");

	GameMovement = reinterpret_cast<C_GameMovement*>(gInterface.Get(CLIENT_SO, CLIENT_GAMEMOVEMENT_INTERFACE_VERSION));
	CHECKNULL(GameMovement, "GameMovement = nullptr!");

	ModelInfo = reinterpret_cast<C_ModelInfoClient*>(gInterface.Get(ENGINE_SO, VMODELINFO_CLIENT_INTERFACE_VERSION));
	CHECKNULL(ModelInfo, "ModelInfo = nullptr!");

	Engine = reinterpret_cast<C_EngineClient *>(gInterface.Get(ENGINE_SO, VENGINE_CLIENT_INTERFACE_VERSION_13));
	CHECKNULL(Engine, "Engine = nullptr!");

	EngineTrace = reinterpret_cast<C_EngineTrace*>(gInterface.Get(ENGINE_SO, VENGINE_TRACE_CLIENT_INTERFACE_VERSION));
	CHECKNULL(EngineTrace, "EngineTrace = nullptr!");

	Panel = reinterpret_cast<C_Panel*>(gInterface.Get(VGUI2_SO, VGUI_PANEL_INTERFACE_VERSION));
	CHECKNULL(Panel, "Panel = nullptr!");

	Surface = reinterpret_cast<C_Surface*>(gInterface.Get(MATSURFACE_SO, VGUI_SURFACE_INTERFACE_VERSION));
	CHECKNULL(Surface, "Surface = nullptr!");

	CVars = reinterpret_cast<ICvar*>(gInterface.Get(VSTDLIB_SO, VENGINE_CVAR_INTERFACE_VERSION));
	CHECKNULL(CVars, "CVars = nullptr!");

	GlobalVars = *reinterpret_cast<C_GlobalVarsBase**>(gPattern.Find(CLIENT_SO, "8B 45 08 8B 15 ? ? ? ? F3 0F 10 88 ? ? ? ?") + 5);
	CHECKNULL(GlobalVars, "GlobalVars = nullptr!");

	void *ClientTable = reinterpret_cast<void *>(gPattern.Find(CLIENT_SO, "8B 0D ? ? ? ? 8B 02 D9 05"));
	CHECKNULL(ClientTable, "ClientTable = nullptr!");

	ClientMode = **reinterpret_cast<C_ClientModeShared ***>(reinterpret_cast<uintptr_t>(ClientTable) + 2);
	CHECKNULL(ClientMode, "ClientMode = nullptr!");

	EngineVGui = reinterpret_cast<C_EngineVGui *>(gInterface.Get(ENGINE_SO, VENGINE_VGUI_VERSION));
	CHECKNULL(EngineVGui, "EngineVGui = nullptr!");

	RandomSeed = *reinterpret_cast<int32_t **>(gPattern.Find(CLIENT_SO, "A3 ? ? ? ? C3 8D 74 26 00 B8 FF FF FF FF 5D A3 ? ? ? ? C3") + 1);
	CHECKNULL(RandomSeed, "RandomSeed = nullptr!");

	DemoPlayer = **reinterpret_cast<void***>(gPattern.Find(ENGINE_SO, "89 15 ? ? ? ? BA ? ? ? ? 83 38 01") + 0x2);
	CHECKNULL(DemoPlayer, "DemoPlayer = nullptr!");

	EngineRenderer = **reinterpret_cast<C_Render ***>(gPattern.Find(ENGINE_SO, "8B 0D ? ? ? ? FF 75 0C FF 75 08 8B 01 FF 50 0C 83 7D FC 00") + 0x2);
	CHECKNULL(EngineRenderer, "EngineRenderer = nullptr!");

	DebugOverlay = reinterpret_cast<IDebugOverlay*>(gInterface.Get(ENGINE_SO, VENGINE_DEBUGOVERLAY_INTERFACE_VERSION));
	CHECKNULL(DebugOverlay, "DebugOverlay = nullptr!");

	GameEvent = reinterpret_cast<C_GameEventManager*>(gInterface.Get(ENGINE_SO, GAMEEVENTSMANAGER_ENGINE_INTERFACE));
	CHECKNULL(GameEvent, "GameEvent = nullptr!");

	ModelRender = reinterpret_cast<C_ModelRender*>(gInterface.Get(ENGINE_SO, VENGINE_MODELRENDER_INTERFACE));
	CHECKNULL(ModelRender, "ModelRender = nullptr!");

	MatSystem = reinterpret_cast<C_MaterialSystem*>(gInterface.Get(MATSYSTEM_SO, VMATERIALSYSTEM_INTERFACE));
	CHECKNULL(MatSystem, "MatSystem = nullptr!");

	RenderView = reinterpret_cast<IVRenderView*>(gInterface.Get(ENGINE_SO, VENGINE_RENDERVIEW_INTERFACE_VERSION));
	CHECKNULL(RenderView, "RenderView = nullptr!");

	//Njet problem, normal katastrof
	//Lets hope I remember to change this
	auto pdwClient = reinterpret_cast<uintptr_t *>(Client);
	auto pdwTable = *reinterpret_cast<uintptr_t **>(pdwClient);
	ViewRender = **reinterpret_cast<IViewRender***>(static_cast<uintptr_t>(pdwTable[27]) + 5);
	CHECKNULL(ViewRender, "ViewRender = nullptr!");
}

C_Interfaces gInts;

void C_SteamInterfaces::Init()
{
	gSteam.Client = reinterpret_cast<ISteamClient017*>(gInterface.Get(STEAMCLIENT_SO, STEAMCLIENT_INTERFACE_VERSION_017));

	HSteamPipe hsNewPipe = gSteam.Client->CreateSteamPipe();
	HSteamPipe hsNewUser = gSteam.Client->ConnectToGlobalUser(hsNewPipe);

	gSteam.Friends002 = reinterpret_cast<ISteamFriends002*>(gSteam.Client->GetISteamFriends(hsNewUser, hsNewPipe, STEAMFRIENDS_INTERFACE_VERSION_002));
	gSteam.Friends015 = reinterpret_cast<ISteamFriends015*>(gSteam.Client->GetISteamFriends(hsNewUser, hsNewPipe, STEAMFRIENDS_INTERFACE_VERSION_015));
	gSteam.Utils007 = reinterpret_cast<ISteamUtils007*>(gSteam.Client->GetISteamUtils(hsNewUser, STEAMUTILS_INTERFACE_VERSION_007));
	gSteam.SteamApps = reinterpret_cast<ISteamApps006*>(gSteam.Client->GetISteamApps(hsNewUser, hsNewPipe, STEAMAPPS_INTERFACE_VERSION_006));
	gSteam.UserStats = reinterpret_cast<ISteamUserStats011*>(gSteam.Client->GetISteamUserStats(hsNewUser, hsNewPipe, STEAMUSERSTATS_INTERFACE_VERSION_011));
	gSteam.User = reinterpret_cast<ISteamUser017*>(gSteam.Client->GetISteamUser(hsNewUser, hsNewPipe, STEAMUSER_INTERFACE_VERSION_017));
}

C_SteamInterfaces gSteam;