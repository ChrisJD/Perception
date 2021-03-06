/********************************************************************
HMD-Stereoificator
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

#ifndef VIEWADJUSTMENT_H_INCLUDED
#define VIEWADJUSTMENT_H_INCLUDED

#include <string>
#include <memory>
#include <unordered_map>
#include "d3d9.h"
#include "d3dx9.h"
#include "HMDisplayInfo.h"
#include "Stereoificator.h"
#include "ProxyHelper.h"
#include "LimitedRangeValue.h"


#define LEFT_CONSTANT -1
#define RIGHT_CONSTANT 1




class ViewAdjustment
{
public:	
	ViewAdjustment(std::shared_ptr<HMDisplayInfo> hmdInfo, float metersToWorldUnits, bool enableRoll);
	virtual ~ViewAdjustment();


	// m_basicAdustments should contain an entry for each enum value here
	enum BasicAdjustments
	{
		SEPARATION_ADJUSTMENT,
		WORLD_SCALE,
		HUD_DISTANCE,
		HUD_SCALE
	};

	enum HUDDistanceModes
	{
		HDM_DISTANCE = 0,
		HDM_SEPARATION_ADJUSTMENT = 1
	};

	void Load(ProxyHelper::ProxyConfig& cfg);
	void Save(ProxyHelper::ProxyConfig& cfg);

	void UpdateProjectionMatrices(/*float separation, float convergence,*/ float aspectRatio);
	void UpdateRoll(float roll);
	void ComputeViewTransforms();
	
	// Unprojects, shifts view position left/right (using same matricies as (Left/Right)ViewRollAndShift) and reprojects using left/right projection
	D3DXMATRIX LeftAdjustmentMatrix();
	D3DXMATRIX RightAdjustmentMatrix();

	// The matricies used to roll (if roll enabled) and shift view for ipd
	D3DXMATRIX LeftViewTransform();
	D3DXMATRIX RightViewTransform();

	// projection * This shift = left/right shifted projection
	D3DXMATRIX LeftShiftProjection();
	D3DXMATRIX RightShiftProjection();

	D3DXMATRIX LeftOrthoReproject();
	D3DXMATRIX RightOrthoReproject();

	D3DXMATRIX TransformHUDLeft();
	D3DXMATRIX TransformHUDRight();

	D3DXMATRIX Projection();
	D3DXMATRIX ProjectionInverse();

	
	float ChangeBasicAdjustment(BasicAdjustments adjustment, float toAdd);
	void  ResetBasicAdjustment(BasicAdjustments adjustment);
	float BasicAdjustmentValue(BasicAdjustments adjustment);

	

	// returns the separation being used for view adjustments in game units
	float SeparationInWorldUnits();

	bool RollEnabled();

	std::shared_ptr<HMDisplayInfo> HMDInfo();
	
	
	


	void RecalculateAll();
private:

	std::unordered_map<BasicAdjustments, LimitedRangeValue> m_basicAdustments;

	HUDDistanceModes hudDistanceMode;
	
	
	// Projection Matrix variables
	float n;	//Minimum z-value of the view volume
	float f;	//Maximum z-value of the view volume
	float l;	//Minimum x-value of the view volume
	float r;	//Maximum x-value of the view volume
	float t;	//Minimum y-value of the view volume
	float b;	//Maximum y-value of the view volume

	D3DXMATRIX matProjection;
	D3DXMATRIX matProjectionInv;

	// The translation applied to projection to shift it left/right to get project(Left/Right)
	D3DXMATRIX leftShiftProjection;
	D3DXMATRIX rightShiftProjection;

	// The shifted left and right projection matricies
	D3DXMATRIX projectLeft;
	D3DXMATRIX projectRight;

	D3DXMATRIX rollMatrix;

	D3DXMATRIX transformLeft;
	D3DXMATRIX transformRight;

	D3DXMATRIX matViewProjTransformLeft;
	D3DXMATRIX matViewProjTransformRight;

	//Use to reproject orthographicly projected elements into 3d space.
	D3DXMATRIX orthoToPersViewProjTransformLeft;
	D3DXMATRIX orthoToPersViewProjTransformRight;

	// Use to transform a scaleform UI by adjusting separation and scale
	D3DXMATRIX transformHUDLeft;
	D3DXMATRIX transformHUDRight;
	

	std::shared_ptr<HMDisplayInfo> hmdInfo;

	bool rollEnabled;
	float ipd;
};



#endif