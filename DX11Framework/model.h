#pragma once

#ifndef MODEL_H
#define MODEL_H
#include "ModelHelpers.h"
#include <string>

class Shader;
class ShaderManager;
class Buffer;
class Texture;
class Transform;

class Model
{
public:
	Model(ID3D11Device* device);
	Model(ID3D11Device* device, std::vector<SimpleVertex> verts, std::vector<WORD> indices);
	~Model();
	int GetIndices() { return _modelBuffer->GetIndBuffer()->GetCount(); };
	ModelBuffer* GetModelBuffer() { return _modelBuffer; };
	
	Shader* GetShader() { return _shader; };
	void SetShader(Shader* shader) { _shader = shader; };
	void SetShader(std::string shaderFile);

	ShaderManager* GetShaderManager() { return _shaderManager; };
	void SetShaderManager(ShaderManager* manager) { _shaderManager = manager; };
	void SetupInput(ID3D11DeviceContext* context);
	void SetupTextures(ID3D11DeviceContext* context);
	void Render(ID3D11DeviceContext* context);
	void UpdateCBData(ConstantBuffer* cbData);

	Texture* GetTexture() { return _texture; }
	void SetTexture(Texture* texture) { _texture = texture; }

	Transform* transform;
private:

	ModelBuffer* _modelBuffer;
	XMFLOAT4 _diffuseLight = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	XMFLOAT4 _diffuseMaterial = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	
	SimpleLight _light = {
		XMFLOAT4(10.0f, 0.0f, 0.0f, 1.0f), // Position
		XMFLOAT3(0.0f, 0.5f, -0.5f), // Rotation
		int(0), // Type
		float(0.5f) }; // falloff -- NOTE: 1.0f can reach end of either plane. Less means less distance.
	XMFLOAT4 _specularLight = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	XMFLOAT4 _specularMaterial = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	float _specPower = 15.0f;

	unsigned int _useTexture = 0;

	Shader* _shader;
	ShaderManager* _shaderManager;

	Texture* _texture;
};

#endif
