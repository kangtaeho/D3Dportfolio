#include "stdafx.h"
#include "cInventory.h"
#include "citem.h"

cInventory::cInventory()
{
}


cInventory::~cInventory()
{
}

void cInventory::render()
{
	item->GetItemInfo()->Itemtexture->Render();
}