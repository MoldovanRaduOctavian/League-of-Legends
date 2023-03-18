#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture() {};
Texture::~Texture() 
{
	resourceView->Release();
};

Texture* Texture::loadTexture(ID3D11Device* dxDevice, const char* file)
{
	Texture* ret = new Texture();
	
	int auxWidth, auxHeight;
	unsigned char* data = stbi_load(file, &auxWidth, &auxHeight, NULL, 4);

	if (data == NULL) return nullptr;

	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));

	desc.Width = auxWidth;
	desc.Height = auxHeight;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;

	ID3D11Texture2D* dxTexture = NULL;
	D3D11_SUBRESOURCE_DATA subResource;
	subResource.pSysMem = data;
	subResource.SysMemPitch = desc.Width * 4;
	subResource.SysMemSlicePitch = 0;
	dxDevice->CreateTexture2D(&desc, &subResource, &dxTexture);

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));

	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = desc.MipLevels;
	srvDesc.Texture2D.MostDetailedMip = 0;
	dxDevice->CreateShaderResourceView(dxTexture, &srvDesc, &ret->resourceView);
	dxTexture->Release();

	ret->width = auxWidth;
	ret->height = auxHeight;
	stbi_image_free(data);


	return ret;
}