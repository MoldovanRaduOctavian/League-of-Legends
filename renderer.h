#pragma once

#include "hook.h"
#include "read.h"
#include "types.h"
#include "offsets.h"
#include <directxmath.h>



class Renderer
{
public:
	int width;
	int height;

	float viewMatrix[16];
	float projectionMatrix[16];
	float viewProjMatrix[16];

	/*DirectX::XMMATRIX viewMatrix;
	DirectX::XMMATRIX projectionMatrix;
	DirectX::XMMATRIX viewProjMatrix;*/

	Renderer();
	~Renderer();

	void readMatrix();
	//vec2 worldToScreen(vec3 coord);
	vec2 worldToScreen(const vec3& pos) const;
	bool worldOnScreen(vec3 coord);
	bool screenOnScreen(vec2 coord);
	void mulMatrix(float* dest, float* src1, float* src2);
};
