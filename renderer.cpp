#include "renderer.h"

Renderer::Renderer() {};
Renderer::~Renderer() {};

void Renderer::readMatrix()
{
	char buf[1000];
	int rendP;

	readMem(baseEx + RendererOff, &rendP, sizeof(int));
	readMem(rendP, buf, 200);
	memcpy(&width, &buf[RendererWidth], sizeof(float));
	memcpy(&height, &buf[RendererHeight], sizeof(float));

	readMem(baseEx + ViewProjMatrices, buf, 200);
	memcpy(viewMatrix, buf, 16 * sizeof(float));
	memcpy(projectionMatrix, buf + 16 * sizeof(float), 16 * sizeof(float));

	mulMatrix(viewProjMatrix, viewMatrix, projectionMatrix);
}

/*void Renderer::readMatrix()
{
	char buf[1000];
	int rendP;

	readMem(baseEx + RendererOff, &rendP, sizeof(int));
	readMem(rendP, buf, 200);
	memcpy(&width, &buf[RendererWidth], sizeof(float));
	memcpy(&height, &buf[RendererHeight], sizeof(float));

	readMem(baseEx + ViewProjMatrices, buf, 200);
	memcpy(&viewMatrix, buf, 16 * sizeof(float));
	memcpy(&projectionMatrix, buf + 16 * sizeof(float), 16 * sizeof(float));
	viewProjMatrix.
}*/

void Renderer::mulMatrix(float* dest, float* src1, float* src2)
{
	float aux;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			dest[i * 4 + j] = 0.f;
			for (int k = 0; k < 4; k++)
				dest[i * 4 + j] += src1[i * 4 + k] * src2[k * 4 + j];
		}
}

/*vec2 Renderer::worldToScreen(vec3 coord)
{
	vec2 ret = {0.f, 0.f};
	vec2 screen = { (float)width, (float)height };
	
	vec4 clip = {};
	clip.x = coord.x * viewProjMatrix[0] + coord.y * viewProjMatrix[4] + coord.z * viewProjMatrix[8] + viewProjMatrix[12];
	clip.y = coord.x * viewProjMatrix[1] + coord.y * viewProjMatrix[5] + coord.z * viewProjMatrix[9] + viewProjMatrix[13];
	clip.z = coord.x * viewProjMatrix[2] + coord.y * viewProjMatrix[6] + coord.z * viewProjMatrix[10] + viewProjMatrix[14];
	clip.w = coord.x * viewProjMatrix[3] + coord.y * viewProjMatrix[7] + coord.z * viewProjMatrix[11] + viewProjMatrix[15];
	
	if (clip.w < 0.1f) return ret;

	vec3 aux;
	aux.x = clip.x / clip.w;
	aux.y = clip.y / clip.w;
	aux.z = clip.z / clip.w;

	ret.x =  (screen.x / 2 * aux.x) + (aux.x + screen.x / 2);
	ret.y = -(screen.y / 2 * aux.y) + (aux.y + screen.y / 2);

	return ret;
}*/

vec2 Renderer::worldToScreen(const vec3& pos) const
{
	static vec4 c;
	c.x = pos.x * viewProjMatrix[0] + pos.y * viewProjMatrix[4] + pos.z * viewProjMatrix[8] + viewProjMatrix[12];
	c.y = pos.x * viewProjMatrix[1] + pos.y * viewProjMatrix[5] + pos.z * viewProjMatrix[9] + viewProjMatrix[13];
	c.z = pos.x * viewProjMatrix[2] + pos.y * viewProjMatrix[6] + pos.z * viewProjMatrix[10] + viewProjMatrix[14];
	c.w = pos.x * viewProjMatrix[3] + pos.y * viewProjMatrix[7] + pos.z * viewProjMatrix[11] + viewProjMatrix[15];

	const auto x = c.x / c.w;
	const auto y = c.y / c.w;

	return { width / 2 * x + (x + width / 2), -(height / 2 * y) + (y + height / 2) };
}

bool Renderer::screenOnScreen(vec2 coord)
{
	return coord.x > 0 && coord.x < width && coord.y > 0 && coord.y < height;
}

bool Renderer::worldOnScreen(vec3 coord)
{
	return screenOnScreen(worldToScreen(coord));
}