#pragma once
#include "stdafx.h"

inline float GetAngle(float x1, float y1, float x2, float y2)
{
	float x = x2 - x1;
	float y = y2 - y1;

	float distance = sqrtf(x * x + y * y);

	float angle = acosf(x / distance);

	if (y2 > y1)
	{
		angle = D3DX_PI - angle;
		if (angle >= D3DX_PI) angle -= D3DX_PI;
	}

	return angle;
}

inline float GetAngle(D3DXVECTOR3 v1, D3DXVECTOR3 v2)
{
	float dx = v2.x - v1.x;
	float dz = v2.z - v1.z;

	return atan2(dx, dz);

}

inline RECT MakeRectLT(float left, float top, float width, float height)
{
	RECT rc;
	rc.left = left;
	rc.top = top;
	rc.right = left + width;
	rc.bottom = top + height;
	return rc;
}