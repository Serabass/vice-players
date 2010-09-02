//----------------------------------------------------
//
// GPL code license:
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
//-----------------------------------------------------
//
// VC:Players Multiplayer Modification For GTA:VC
// Copyright 2010 GTA:Online team
//
// File Author(s): adamix
//
//-----------------------------------------------------
#pragma once

#define MAX_OBJECTS 100

class CObjectPool
{
public:
	CObjectPool();
	~CObjectPool();

	EntityId New(int iModel, Vector3 * vecPos, Vector3 * vecRot);
	BOOL Delete(EntityId ObjectID);

	CObject* GetAt(EntityId ObjectID)
	{
		if(ObjectID > MAX_OBJECTS) { return NULL; }
		return m_pObjects[ObjectID];
	};

	BOOL GetSlotState(EntityId ObjectID)
	{
		if(ObjectID > MAX_OBJECTS) { return FALSE; }
		return m_bObjectSlotState[ObjectID];
	};

	void InitForPlayer(EntityId playerID);

	EntityId GetFreeSlot();

private:
	BOOL m_bObjectSlotState[MAX_OBJECTS];
	CObject * m_pObjects[MAX_OBJECTS];
};