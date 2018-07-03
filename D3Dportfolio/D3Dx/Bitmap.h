#pragma once

#define BITMAP Bitmap::GetInstance()

class Bitmap
{
private:
	SINGLETONE(Bitmap)

private:
	enum {
		UI = 0,
		ITEM = 1
	};

	struct tagMap
	{
		std::map<std::string, D3DXMATRIX>			m_mapMatrixT;
		std::map<std::string, D3DXMATRIX>			m_mapMatrixS;
		std::map<std::string, LPD3DXSPRITE>			m_mapSprite;
		std::map<std::string, D3DXIMAGE_INFO>		m_mapImageInfo;
		std::map<std::string, LPDIRECT3DTEXTURE9>   m_mapTexture;
		std::map<std::string, D3DXMATRIX>			m_mapWorld;
		std::map<std::string, RECT>					m_mapRect;
		std::map<std::string, D3DXVECTOR3>			m_mapScale;
		std::map<std::string, D3DXVECTOR3>			m_mapPosition;
	}m_map;


private:
	const char* szItemName;
	const char* szUiName;
	D3DXMATRIX matT, matS;
	D3DXMATRIX mat_World;
	LPD3DXSPRITE	m_pSprite;
	RECT rc;


	std::map<std::string, D3DXVECTOR3> m_mapScale;
	std::map<std::string, D3DXVECTOR3> m_mapPosition;

	std::map<int, tagMap> m_Map;

	SYNTHESIZE_REF(unsigned int, alphaValue, alphavalue);
	D3DXVECTOR3 scale;
	D3DXVECTOR3 Position;
	
	SYNTHESIZE_REF(int, imageIndex, IMAGEINDEX);

public:
	LPDIRECT3DTEXTURE9 addTexture(const char* textFileName);
	void Render(const char* textFileName);
	void Destroy();
	void setScale(const char* textFileName, D3DXVECTOR3 scale);
	void setPosition(const char* textFileName,D3DXVECTOR3 position);

	std::map<std::string, RECT> GetRect() { return m_map.m_mapRect; }

};