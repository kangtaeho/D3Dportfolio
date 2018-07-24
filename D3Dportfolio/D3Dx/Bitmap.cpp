#include "stdafx.h"
#include "Bitmap.h"


Bitmap::Bitmap()
	: texture_Info(NULL),
	alphaValue(255),
	imageIndex(UI)
{

}

Bitmap::~Bitmap()
{
	release();
}


HRESULT Bitmap::addTexture(const char* textFileName)
{
	if (texture_Info != NULL) release();

	texture_Info = new TEXTURE_INFO;

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
		D3DXCOLOR(255, 255, 255, 255),
		&texture_Info->ImageInfo,
		0,
		&texture_Info->texture);

	D3DXCreateSprite(g_pD3DDevice, &texture_Info->Sprite);
	SetRect(&texture_Info->rc, 0, 0, texture_Info->ImageInfo.Width, texture_Info->ImageInfo.Height);

	D3DXMatrixIdentity(&texture_Info->matWorld);

	texture_Info->m_stSize.nWidth = texture_Info->ImageInfo.Width;
	texture_Info->m_stSize.nHeight = texture_Info->ImageInfo.Height;

	if (texture_Info->texture == NULL)
	{
		release();

		return E_FAIL;
	}

	return S_OK;
}
HRESULT Bitmap::addTexture(const char* textFileName, int frameWidth, int frameHeight)
{
	if (texture_Info != NULL) release();

	texture_Info = new TEXTURE_INFO;

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
		D3DXCOLOR(255, 255, 255, 255),
		&texture_Info->ImageInfo,
		0,
		&texture_Info->texture);

	D3DXCreateSprite(g_pD3DDevice, &texture_Info->Sprite);

	D3DXMatrixIdentity(&texture_Info->matWorld);


	if (texture_Info->texture == NULL)
	{
		release();

		return E_FAIL;
	}
	ST_UI_SIZE stSize;

	stSize.nWidth = texture_Info->ImageInfo.Width;
	stSize.nHeight = texture_Info->ImageInfo.Height;

	SetRect(&texture_Info->rectFrameSize, 0, 0, stSize.nWidth / frameWidth, stSize.nHeight / frameHeight);

	texture_Info->fAccumTime = 0.0f;
	texture_Info->fFrameTime = 0.0f;
	texture_Info->niCurrentFrameNum = 0.0f;
	texture_Info->nFrameCountAll = 0.0f;
	texture_Info->nFrameCountHeight = 0.0f;
	texture_Info->nFrameCountWidth = 0.0f;

	texture_Info->nFrameCountWidth = frameWidth;
	texture_Info->nFrameCountHeight = frameHeight;

	texture_Info->nFrameCountAll = texture_Info->nFrameCountWidth * texture_Info->nFrameCountHeight;
	texture_Info->fFrameTime = 1.0f / texture_Info->nFrameCountAll;

	texture_Info->vAniCenter =
	{
		texture_Info->rectFrameSize.right / 2.0f,
		texture_Info->rectFrameSize.bottom / 2.0f,
		0.0f
	};

	texture_Info->Position = { 0.0f,0.0f,0.0f };
	return S_OK;
}
void Bitmap::update()
{
	if (texture_Info != NULL && imageIndex != ITEM)
	{
		D3DXMatrixScaling(&texture_Info->matS, texture_Info->Scale.x, texture_Info->Scale.y, texture_Info->Scale.z);
		D3DXMatrixTranslation(&texture_Info->matT, texture_Info->Position.x, texture_Info->Position.y, texture_Info->Position.z);

		texture_Info->matWorld = texture_Info->matS * texture_Info->matT;
	}
}
void Bitmap::update(float _dt)
{
	texture_Info->fAccumTime += _dt;

	if (texture_Info->fAccumTime >= texture_Info->fFrameTime)
	{
		int x, y;
		texture_Info->fAccumTime = 0.0f;
		++texture_Info->niCurrentFrameNum;

		if (texture_Info->niCurrentFrameNum >= texture_Info->nFrameCountAll)
			texture_Info->niCurrentFrameNum = 0;

		x = (texture_Info->niCurrentFrameNum % texture_Info->nFrameCountWidth) * texture_Info->rectFrameSize.right;
		//y = (texture_Info->niCurrentFrameNum / texture_Info->nFrameCountHeight) * texture_Info->rectFrameSize.top;
		y = 1;
		SetRect(&texture_Info->rectRenderFrame, x, y, x + texture_Info->rectFrameSize.right, y + texture_Info->rectFrameSize.bottom);

		int a = 0;
	}
	else
	{
		int x = (texture_Info->niCurrentFrameNum % texture_Info->nFrameCountWidth) * texture_Info->rectFrameSize.right;
		int y = 1; //(texture_Info->niCurrentFrameNum / texture_Info->nFrameCountHeight) * texture_Info->rectFrameSize.top;

		SetRect(&texture_Info->rectRenderFrame, x, y, x + texture_Info->rectFrameSize.right, y + texture_Info->rectFrameSize.bottom);
	}
}
void Bitmap::Render()
{
	if (texture_Info != NULL)
	{
		if (imageIndex == ITEM || imageIndex == SUBUI)
		{
			D3DXMatrixScaling(&texture_Info->matS, texture_Info->Scale.x, texture_Info->Scale.y, texture_Info->Scale.z);
			D3DXMatrixTranslation(&texture_Info->matT, texture_Info->Position.x, texture_Info->Position.y, texture_Info->Position.z);

			texture_Info->matWorld = texture_Info->matS * texture_Info->matT;
		}
		texture_Info->Sprite->SetTransform(&texture_Info->matWorld);

		SetRect(&texture_Info->rc, 0, 0, texture_Info->ImageInfo.Width, texture_Info->ImageInfo.Height);

		texture_Info->Sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

		texture_Info->Sprite->Draw(
			texture_Info->texture,
			&texture_Info->rc,
			&D3DXVECTOR3(texture_Info->Position.x, texture_Info->Position.y, 0),
			&D3DXVECTOR3(texture_Info->Position.x, texture_Info->Position.y, 0),
			D3DCOLOR_ARGB(alphaValue, 255, 255, 255));

		texture_Info->Sprite->End();
	}
}
void Bitmap::aniRender()
{
	if (texture_Info != NULL)
	{
		D3DXMatrixScaling(&texture_Info->matS, texture_Info->Scale.x, texture_Info->Scale.y, texture_Info->Scale.z);
		D3DXMatrixTranslation(&texture_Info->matT, texture_Info->Position.x, texture_Info->Position.y, texture_Info->Position.z);
		texture_Info->matWorld = texture_Info->matS * texture_Info->matT;

		texture_Info->Sprite->SetTransform(&texture_Info->matWorld);

		texture_Info->Sprite->Begin(D3DXSPRITE_ALPHABLEND);

		texture_Info->Sprite->Draw(
			texture_Info->texture,
			&texture_Info->rectRenderFrame,
			&texture_Info->Position,
			&texture_Info->Position,
			D3DCOLOR_ARGB(alphaValue, 255, 255, 255));

		texture_Info->Sprite->End();
	}
}
void Bitmap::release()
{
	if (texture_Info)
	{
		SAFE_RELEASE(texture_Info->texture);
		SAFE_RELEASE(texture_Info->Sprite);

		SAFE_DELETE(texture_Info);
	}
}