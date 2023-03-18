#pragma once

#include <d3d11.h>


class Texture
{
public:

	Texture();
	~Texture();
	static Texture* loadTexture(ID3D11Device* dxDevice, const char* file);

	int width, height;
	ID3D11ShaderResourceView* resourceView;
};
