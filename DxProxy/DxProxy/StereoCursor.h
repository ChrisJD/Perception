/********************************************************************
Stereoificator
Copyright (C) 2013 Chris Drain

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
********************************************************************/

#ifndef STEREO_CURSOR_H_INCLUDED
#define STEREO_CURSOR_H_INCLUDED

#include <d3d9.h>
#include <d3dx9.h>

#include "D3DProxyDevice.h"


class StereoCursor
{
public:
	StereoCursor(D3DProxyDevice* pWrappedDevice);
	virtual ~StereoCursor();

	void SetPosition(int x,int y);
	void SetCursorSurface(UINT XHotSpot, UINT YHotSpot, IDirect3DSurface9* pCursorBitmap);
	void DrawCursor();


private:

	D3DProxyDevice* m_pWrappedDevice;

	IDirect3DTexture9* m_pCursorTexture;
	//IDirect3DSurface9* m_pCursorSurface;
	ID3DXSprite* m_pSprite;

	int m_x;
	int m_y;
};

#endif