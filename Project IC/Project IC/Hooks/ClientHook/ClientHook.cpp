#include "ClientHook.h"

void ClientHook::PreEntity::Hook(char const *szMapName)
{
	Table.Original<fn>(index)(gInts.Client, szMapName);
}

void ClientHook::PostEntity::Hook()
{
	Table.Original<fn>(index)(gInts.Client);
}

void ClientHook::ShutDown::Hook()
{
	Table.Original<fn>(index)(gInts.Client);
	gEntCache.Clear();
}

void ClientHook::FrameStageNotify::Hook(ClientFrameStage_t FrameStage)
{
	Table.Original<fn>(index)(gInts.Client, FrameStage);

	switch (FrameStage)
	{
		case ClientFrameStage_t::FRAME_NET_UPDATE_START:
		{
			gEntCache.Clear();
			break;
		}

		case ClientFrameStage_t::FRAME_NET_UPDATE_END:
		{
			gEntCache.Fill();
			break;
		}

		case ClientFrameStage_t::FRAME_RENDER_START:
		{

			break;
		}

		default: break;
	}
}

VMT::Table ClientHook::Table;