#include "stdafx.h"
#include "Bitmap.h"


Bitmap::Bitmap()
	:
	scale(1.0f,1.0f,1.0f),
	Position(0,0,0),
	alphaValue(255),
	imageIndex(3)
{
	szItemName = "./item";
	szUiName = "./testFile";
}


Bitmap::~Bitmap()
{
	Destroy();
	g_pD3DDevice->Release();
}


LPDIRECT3DTEXTURE9 Bitmap::addTexture(const char* textFileName)
{
	
	if (m_map.m_mapTexture.find(textFileName) == m_map.m_mapTexture.end() ||
		m_map.m_mapImageInfo.find(textFileName) == m_map.m_mapImageInfo.end())
	{
		D3DXCreateTextureFromFileEx(
			g_pD3DDevice,
			textFileName,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_DEFAULT,
			0,
			&m_map.m_mapImageInfo[textFileName],
			0,
			&m_map.m_mapTexture[textFileName]);
	}

	if (m_map.m_mapSprite.find(textFileName) == m_map.m_mapSprite.end())
	{
		D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
		m_map.m_mapSprite.insert(std::make_pair(textFileName, m_pSprite));
	}
	if (m_map.m_mapMatrixS.find(textFileName) == m_map.m_mapMatrixS.end())
	{
		m_map.m_mapMatrixS.insert(std::make_pair(textFileName, matS));
	}
	if (m_map.m_mapMatrixT.find(textFileName) == m_map.m_mapMatrixT.end())
	{
		m_map.m_mapMatrixT.insert(std::make_pair(textFileName, matT));
	}
	if (m_map.m_mapRect.find(textFileName) == m_map.m_mapRect.end())
	{
		m_map.m_mapRect.insert(std::make_pair(textFileName, rc));
	}
	if (m_mapScale.find(textFileName) == m_mapScale.end())
	{
		m_mapScale.insert(std::make_pair(textFileName, scale));
	}
	if (m_mapPosition.find(textFileName) == m_mapPosition.end())
	{
		m_mapPosition.insert(std::make_pair(textFileName, Position));
	}

	if (!strncmp(szItemName,textFileName,6))
	{
		imageIndex = ITEM;
		m_Map.insert(std::make_pair(imageIndex, m_map));
	}

	if (!strncmp(szUiName, textFileName, 10))
	{
		imageIndex = UI;
		m_Map.insert(std::make_pair(imageIndex, m_map));
	}

	

	for (auto p : m_Map)
	{
		return p.second.m_mapTexture[textFileName];
	}
	//return m_map.m_mapTexture[textFileName];
}

void Bitmap::setScale(const char* textFileName, D3DXVECTOR3 scale)
{
	/*for (auto p : m_Map)
	{
		p.second.m_mapScale[textFileName] = scale;
	}*/
	m_mapScale[textFileName] = scale;
}
void Bitmap::setPosition(const char* textFileName, D3DXVECTOR3 position)
{
	/*for (auto p : m_Map)
	{
		p.second.m_mapPosition[textFileName] = position;
	}*/
	m_mapPosition[textFileName] = position;
}
void Bitmap::Render(const char* textFileName)
{

	for (auto p : m_Map)
	{
		//p.second.m_mapScale[textFileName] = D3DXVECTOR3(0.5f, 0.5f, 0.5f);

		D3DXMatrixScaling(&p.second.m_mapMatrixS[textFileName], m_mapScale[textFileName].x, m_mapScale[textFileName].y, m_mapScale[textFileName].z);
		D3DXMatrixTranslation(&p.second.m_mapMatrixT[textFileName], m_mapPosition[textFileName].x, m_mapPosition[textFileName].y, m_mapPosition[textFileName].z);

		p.second.m_mapWorld[textFileName] = p.second.m_mapMatrixS[textFileName] * p.second.m_mapMatrixT[textFileName];

		if (p.second.m_mapSprite.find(textFileName) != p.second.m_mapSprite.end())
		{
			SetRect(&p.second.m_mapRect[textFileName], 0, 0, p.second.m_mapImageInfo[textFileName].Width, p.second.m_mapImageInfo[textFileName].Height);

			p.second.m_mapSprite[textFileName]->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

			p.second.m_mapSprite[textFileName]->Draw(
				p.second.m_mapTexture[textFileName],
				&p.second.m_mapRect[textFileName],
				&D3DXVECTOR3(0, 0, 0),
				&D3DXVECTOR3(0, 0, 0),
				D3DCOLOR_ARGB(alphaValue, 255, 255, 255));

			p.second.m_mapSprite[textFileName]->End();
		}
	}

	/*D3DXMatrixScaling(&m_map.m_mapMatrixS[textFileName], m_mapScale[textFileName].x, m_mapScale[textFileName].y,m_mapScale[textFileName].z);
	D3DXMatrixTranslation(&m_map.m_mapMatrixT[textFileName], m_mapPosition[textFileName].x,m_mapPosition[textFileName].y,m_mapPosition[textFileName].z);
	
	m_map.m_mapWorld[textFileName] = m_map.m_mapMatrixS[textFileName] * m_map.m_mapMatrixT[textFileName];

	if (m_map.m_mapSprite.find(textFileName) != m_map.m_mapSprite.end())
	{
		m_map.m_mapSprite[textFileName]->SetTransform(&m_map.m_mapWorld[textFileName]);
	
		SetRect(&m_map.m_mapRect[textFileName], 0, 0, m_map.m_mapImageInfo[textFileName].Width, m_map.m_mapImageInfo[textFileName].Height);
	
		m_map.m_mapSprite[textFileName]->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	
		m_map.m_mapSprite[textFileName]->Draw(
			m_map.m_mapTexture[textFileName],
			&m_map.m_mapRect[textFileName],
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			D3DCOLOR_ARGB(alphaValue, 255, 255, 255));
	
		m_map.m_mapSprite[textFileName]->End();
	}*/
}

void Bitmap::Destroy()
{
	for (auto p : m_map.m_mapSprite)
	{
		SAFE_RELEASE(p.second);
	}
	for (auto p : m_map.m_mapTexture)
	{
		SAFE_RELEASE(p.second);
	}

	m_map.m_mapMatrixS.clear();
	m_map.m_mapMatrixT.clear();
	m_map.m_mapRect.clear();
	m_map.m_mapSprite.clear();
	m_map.m_mapTexture.clear();
}