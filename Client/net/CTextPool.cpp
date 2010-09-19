//----------------------------------------------------------
//
// VC:MP Multiplayer Modification For GTA:VC
// Copyright 2010 VC-Players Team
//
// File Author(s): bpeterson
// License: See LICENSE in root directory
//
//----------------------------------------------------------

#pragma once

#include "StdInc.h"

extern CNetGame *pNetGame;

CTextPool::CTextPool()
{
	for(EntityId textID = 0; textID < MAX_TEXTS; textID++) 
	{
		m_bTextSlotState[textID] = FALSE;
		m_pTexts[textID] = NULL;
	}
}

CTextPool::~CTextPool()
{
	for(EntityId i = 0; i < MAX_TEXTS; i++)
	{
		Delete(i);
	}
}

EntityId CTextPool::New(EntityId TextID, DWORD color, char * szFontName, int iSize, float posX, float posY, char * szText)
{
	if(TextID == MAX_TEXTS) return -1;		

	m_pTexts[TextID] = new CText(TextID, color, szFontName, iSize, posX, posY, szText);

	if(m_pTexts[TextID])
	{
		m_bTextSlotState[TextID] = TRUE;
		return TextID;
	}
	return -1;
}

EntityId CTextPool::GetFreeSlot()
{
	for(EntityId id = 0; id < MAX_TEXTS; id++)
	{
		if(m_pTexts[id] == NULL)
			return id;
	}
	return false;
}

void CTextPool::Process()
{
	for(EntityId id = 0; id < MAX_TEXTS; id++)
	{
		if(m_pTexts[id] == NULL)
			continue;

		m_pTexts[id]->Process();
	}
}

bool CTextPool::Delete(EntityId TextID)
{
	if(TextID > MAX_TEXTS || !m_pTexts[TextID])
	{
		return false;
	}

	m_bTextSlotState[TextID] = false;
	delete m_pTexts[TextID];
	m_pTexts[TextID] = NULL;

	return true;
}