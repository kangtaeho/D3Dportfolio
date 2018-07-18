#pragma once
#include "Bitmap.h"


#define g_pTextureManager cTextureManager::GetInstance()

class cTextureManager
{
private:
	SINGLETONE(cTextureManager);

	typedef std::map<std::string, Bitmap*> mapTextureList;
	typedef std::map<std::string, Bitmap*>::iterator mapTextureIter;

	std::map<std::string, LPDIRECT3DTEXTURE9> m_mapTexture;
	std::map<std::string, Bitmap> m_maptexture;
	std::map<std::string, Bitmap>::iterator  m_mapiter;
	Bitmap* m_items;
private:
	mapTextureList m_textureList;
public:
	Bitmap* setUp(std::string textureName,std::string fileName, int index, int state);

	Bitmap * addTexture(std::string strKey, const char* textureFileName, int imageIndex, int imageState);
	//아이템,ui설정용으로 3,4번째 인자넣음, 이외의 텍스쳐 사용시 NULL넣어주세요.
	Bitmap* addTexture(std::string strKey, const char* textureFileName, int imageIndex, int frameWidth, int frameHeight);
	Bitmap* findTexture(std::string strKey);

	Bitmap findAllocatedTexture(std::string strKey);
	void updateAllocatedTexture(std::string strKey);
	void renderAllocatedTexture(std::string strKey);

	int GetImageState(std::string strKey);
	LPD3DXSPRITE GetSprite(std::string strKey);
	D3DXIMAGE_INFO GetImageInfo(std::string strKey);
	LPDIRECT3DTEXTURE9 getTexture(std::string strKey);
	LPDIRECT3DTEXTURE9 GetTexture(const char* szFullPath);
	void setTexture(std::string strKey, LPDIRECT3DTEXTURE9 texture);


	D3DXMATRIX& GetWorldMatrix(std::string strKey);

	void setCurrentFrame(std::string strKey, float index);
	RECT GetRect(std::string strKey);
	void setScale(std::string strKey, D3DXVECTOR3 scale);
	void setPosition(std::string strKey, D3DXVECTOR3 position);
	D3DXVECTOR3 GetPosition(std::string strKey);
	void render(std::string strKey);
	void render();
	void aniRender(std::string strKey);
	void update(std::string strKey);
	void update(std::string strKey, float dt);
	void release();
	BOOL deleteAll();
};

