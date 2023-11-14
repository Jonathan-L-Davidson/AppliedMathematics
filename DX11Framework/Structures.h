#pragma once

#ifndef STRUCTURES_H
#define STRUCTURES_H
#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#define DELETED3D(x)	if(x)	x->Release(); 

using namespace DirectX;

struct SimpleLight {
	XMFLOAT4 Position;		// 16
	XMFLOAT3 Rotation;		// 12
	int Type;				// 4 - 16
	float FallOff;			// 4

	XMFLOAT3 Color; // Diffuse mat
	
};

struct SimpleVertex
{
	XMFLOAT3 Position;
	XMFLOAT3 Normal;
	XMFLOAT2 TexCoord;
};

struct ConstantBuffer
{
	XMMATRIX Projection;
	XMMATRIX View;
	XMMATRIX World;

	XMFLOAT4 AmbientLight;
	XMFLOAT4 DiffuseLight;
	XMFLOAT4 DiffuseMaterial;

	XMFLOAT4 LightPosition;
	XMFLOAT3 LightRotation;
	float	 LightFallOff;

	XMFLOAT4 SpecularLight;
	XMFLOAT4 SpecularMaterial;
	float    SpecPower;

	XMFLOAT3 CameraPos;

	unsigned int UseTexture;
	unsigned int UseDiffuse;
	unsigned int UseDisplacement;
	unsigned int UseNormal;
	unsigned int UseSpecular;

};

struct Rect{
	int x;
	int y;
};

#endif