#pragma once

class Bitmap
{
protected:
	typedef struct tagTextureInfo
	{
		D3DXVECTOR3 Scale, Position;
		D3DXMATRIX matT, matS, matWorld;
		LPD3DXSPRITE Sprite;
		D3DXIMAGE_INFO ImageInfo;
		LPDIRECT3DTEXTURE9 texture;
		RECT rc;
		
		ST_UI_SIZE m_stSize;
		//��������Ʈ �ִϸ��̼�;
		RECT rectFrameSize;
		int nFrameCountWidth;
		int nFrameCountHeight;
		int nFrameCountAll;
		int niCurrentFrameNum;
		D3DXVECTOR3 vAniCenter;
		D3DXVECTOR3 vAniPosition;
		float fAccumTime; //�����ð�;
		float fFrameTime; //������ ����ð�;
		RECT rectRenderFrame; //�׷��� ������ ��ġ;

		tagTextureInfo()
		{
			Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			Position = D3DXVECTOR3(0, 0, 0);
			Sprite = NULL;
			texture = NULL;
		}
	}TEXTURE_INFO, *LPTEXTURE_INFO;

protected:
	LPTEXTURE_INFO texture_Info;
	SYNTHESIZE(Bitmap*, m_pParent, Parent);


private:
	SYNTHESIZE(int, alphaValue, alphavalue);
	SYNTHESIZE_REF(int, imageIndex, IMAGEINDEX);
	SYNTHESIZE_REF(int, imageState, IMAGESTATE);
public:
	Bitmap();
	~Bitmap();
	HRESULT addTexture(const char* textFileName);
	HRESULT addTexture(const char* textFileName, int frameWidth, int frameHeight);

	
	void Render();
	void aniRender();
	void release();

	void update();
	void update(float _dt);


	ST_UI_SIZE GetUiSize() { return texture_Info->m_stSize; }

	RECT GetRect() { return texture_Info->rc; }
	D3DXMATRIX &GetWolrdMatrix() { return texture_Info->matWorld; }

	LPD3DXSPRITE GetSprite() { return texture_Info->Sprite; }
	void setWorldMatrix(D3DXMATRIX matrix) { texture_Info->matWorld = matrix; }
	int GetIndex() { return imageIndex; }
	void setIndex(int index) { imageIndex = index; }
	void setImageState(int state) { imageState = state; }
	D3DXIMAGE_INFO GetImageInfo() { return texture_Info->ImageInfo; }
	LPDIRECT3DTEXTURE9 GetTexture() { return texture_Info->texture; }
	void setTexture(LPDIRECT3DTEXTURE9 texture) { texture_Info->texture = texture; }
	
	void setScale(D3DXVECTOR3 scale) { texture_Info->Scale = scale; }
	void setPosition(D3DXVECTOR3 position) { texture_Info->Position = position; }
	D3DXVECTOR3 GetPosition() { return texture_Info->Position; }
	D3DXVECTOR3* Getposition() { return &texture_Info->Position; }

	D3DXVECTOR3 GetAniPosition() { return texture_Info->vAniPosition; }
	RECT* GetrectFrameSize() { return  &texture_Info->rectFrameSize; }
	void SetRectFrameSize(RECT rc) { texture_Info->rectFrameSize = rc; }
	void setCurrentFrame(float index) { texture_Info->niCurrentFrameNum = index; }
};