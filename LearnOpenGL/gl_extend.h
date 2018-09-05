#pragma once

struct Color3
{
	float r;
	float g;
	float b;
};

struct Color4
{
	float r;
	float g;
	float b;
	float a;
};

inline Color4 GetColor4(const float r, const float g, const float b, const float a)
{
	Color4 color;
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;

	return color;

}

inline Color3 GetColor3(const float r, const float g, const float b)
{
	Color3 color;
	color.r = r;
	color.g = g;
	color.b = b;

	return color;

}