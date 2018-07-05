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