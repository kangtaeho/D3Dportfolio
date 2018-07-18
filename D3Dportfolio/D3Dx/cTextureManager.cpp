#include "stdafx.h"
#include "cTextureManager.h"


cTextureManager::cTextureManager()
{
}


cTextureManager::~cTextureManager()
{
}

Bitmap* cTextureManager::setUp(std::string textureName,std::string fileName,int index,int state)
{
	Bitmap* bitmap = findTexture(textureName);

	bitmap->setIndex(index);
	bitmap->SetIMAGESTATE(state);

	if (bitmap) return bitmap;
}
Bitmap* cTextureManager::addTexture(std::string strKey, const char* textureFileName, int imageIndex, int imageState)
{
	Bitmap* bitmap = findTexture(strKey);

	//if (bitmap) return bitmap;

	bitmap = new Bitmap;

	if (FAILED(bitmap->addTexture(textureFileName)))
	{
		SAFE_DELETE(bitmap);

		return NULL;
	}

	bitmap->setIndex(imageIndex);
	bitmap->SetIMAGESTATE(imageState);

	m_textureList.insert(std::make_pair(strKey, bitmap));

	return bitmap;
}
Bitmap* cTextureManager::addTexture(std::string strKey, const char* textureFileName, int imageIndex, int frameWidth, int frameHeight)
{
	Bitmap* bitmap = findTexture(strKey);

	//if (bitmap) return bitmap;

	bitmap = new Bitmap;

	if (FAILED(bitmap->addTexture(textureFileName, frameWidth, frameHeight)))
	{
		SAFE_DELETE(bitmap);

		return NULL;
	}

	bitmap->setIndex(imageIndex);

	m_textureList.insert(std::make_pair(strKey, bitmap));

	return bitmap;
}
Bitmap* cTextureManager::findTexture(std::string strKey)
{
	mapTextureIter key = m_textureList.find(strKey);

	if (key != m_textureList.end())
	{
		return key->second;
	}
	return NULL;
}

void cTextureManager::update(std::string strKey)
{
	Bitmap* bitmap = findTexture(strKey);

	if (bitmap) bitmap->update();
}
void cTextureManager::update(std::string strKey, float dt)
{
	Bitmap* bitmap = findTexture(strKey);

	if (bitmap)bitmap->update(dt);
}
void cTextureManager::aniRender(std::string strKey)
{
	Bitmap* bitmap = findTexture(strKey);

	if (bitmap) bitmap->aniRender();
}
void cTextureManager::render()
{

}
void cTextureManager::render(std::string strKey)
{
	Bitmap* bitmap = findTexture(strKey);

	if (bitmap) bitmap->Render();
}

Bitmap cTextureManager::findAllocatedTexture(std::string strKey)
{
	m_mapiter = m_maptexture.find(strKey);

	if (m_mapiter != m_maptexture.end())
	{
		return m_mapiter->second;
	}
}
void cTextureManager::updateAllocatedTexture(std::string strKey)
{
	Bitmap bitmap = findAllocatedTexture(strKey);

	bitmap.update();
}
void cTextureManager::renderAllocatedTexture(std::string strKey)
{
	Bitmap bitmap = findAllocatedTexture(strKey);

	bitmap.Render();
}
void cTextureManager::release()
{
	deleteAll();
}

BOOL cTextureManager::deleteAll()
{
	mapTextureIter iter = m_textureList.begin();

	for (; iter != m_textureList.end();)
	{
		if (iter->second != NULL)
		{
			SAFE_DELETE(iter->second);
			iter = m_textureList.erase(iter);
		}
		else ++iter;
	}

	m_textureList.clear();

	return TRUE;
}
void cTextureManager::setScale(std::string strKey, D3DXVECTOR3 scale)
{
	Bitmap* bitmap = findTexture(strKey);

	bitmap->setScale(scale);
}

void cTextureManager::setPosition(std::string strKey, D3DXVECTOR3 position)
{
	Bitmap* bitmap = findTexture(strKey);

	bitmap->setPosition(position);
}

D3DXVECTOR3 cTextureManager::GetPosition(std::string strKey)
{
	Bitmap* bitmap = findTexture(strKey);

	return bitmap->GetPosition();
}
void cTextureManager::setTexture(std::string strKey ,LPDIRECT3DTEXTURE9 texture)
{
	Bitmap* bitmap = findTexture(strKey);

	return bitmap->setTexture(texture);
}
LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(const char* szFullPath)
{
	if (m_mapTexture.find(szFullPath) == m_mapTexture.end())
	{
		D3DXCreateTextureFromFile(g_pD3DDevice, szFullPath, &m_mapTexture[szFullPath]);
	}

	return m_mapTexture[szFullPath];
}

LPDIRECT3DTEXTURE9 cTextureManager::getTexture(std::string strKey)
{
	Bitmap* bitmap = findTexture(strKey);

	return bitmap->GetTexture();
}

D3DXIMAGE_INFO cTextureManager::GetImageInfo(std::string strKey)
{
	Bitmap* bitmap = findTexture(strKey);

	return bitmap->GetImageInfo();
}

LPD3DXSPRITE cTextureManager::GetSprite(std::string strKey)
{
	Bitmap* bitmap = findTexture(strKey);

	return bitmap->GetSprite();
}

D3DXMATRIX& cTextureManager::GetWorldMatrix(std::string strKey)
{
	Bitmap* bitmap = findTexture(strKey);

	return bitmap->GetWolrdMatrix();
}

int cTextureManager::GetImageState(std::string strKey)
{
	Bitmap* bitmap = findTexture(strKey);

	return bitmap->GetIMAGEINDEX();
}
void cTextureManager::setCurrentFrame(std::string strKey, float index)
{
	Bitmap* bitmap = findTexture(strKey);

	bitmap->setCurrentFrame(index);

}
RECT cTextureManager::GetRect(std::string strKey)
{
	Bitmap* bitmap = findTexture(strKey);

	return bitmap->GetRect();
}