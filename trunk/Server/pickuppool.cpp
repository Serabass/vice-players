//-----------------------------------------------------
//
// VC:Players Multiplayer Modification For GTA:VC
// Copyright 2010 GTA:Online team
//
// File Author(s): bpeterson
// License: See LICENSE in root directory
//
//-----------------------------------------------------

#include "netgame.h"

extern CNetGame *pNetGame;

CPickupPool::CPickupPool()
{
	for(EntityId i = 0; i < MAX_PICKUPS; i++) 
	{
		m_bPickupSlotState[i] = false;
		m_pPickups[i] = NULL;
	}
}

CPickupPool::~CPickupPool()
{
	// Loop through all pickup slots
	for(EntityId i = 0; i < MAX_PICKUPS; i++)
	{
		// Is this pickup slot used?
		if(m_bPickupSlotState[i])
		{
			// Delete this pickup
			Delete(i);
		}
	}
}


EntityId CPickupPool::New(int iModel, int iType, Vector3 * vecPos)
{
	// Loop through all pickup slots
	for(EntityId i = 0; i < MAX_PICKUPS; i++)
	{
		// Is this slot free?
		if(!m_bPickupSlotState[i])
		{
			// Create the pickup instance
			m_pPickups[i] = new CPickup(iModel, iType, vecPos);

			// Did the pickup instance create successfully?
			if(m_pPickups[i])
			{
				// Set the pickup id
				m_pPickups[i]->SetID(i);

				// Spawn the pickup for world
				m_pPickups[i]->SpawnForWorld();

				// Set the slot state to used
				m_bPickupSlotState[i] = true;

				// Return the pickup id
				return i;
			}
		}
	}

	// No free slots found or pickup instance creation failed
	return -1;
}

bool CPickupPool::Delete(EntityId PickupID)
{
	// Is this slot used?
	if(!GetSlotState(PickupID))
	{
		// It's not used
		return false;
	}

	// Destroy this pickup for all players
	m_pPickups[PickupID]->DestroyForWorld();

	// Delete this pickup
	delete m_pPickups[PickupID];
	m_pPickups[PickupID] = NULL;

	return true;
}

void CPickupPool::InitForPlayer(EntityId playerId)
{
	// Loop through all pickup slots
	for(EntityId i = 0; i < MAX_PICKUPS; i++)
	{
		// Is this slot used?
		if(m_bPickupSlotState[i])
		{
			// Spawn this pickup for the player
			m_pPickups[i]->SpawnForPlayer(playerId);
		}
	}
}