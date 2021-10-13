#pragma once

class Time abstract sealed
{
public:
	static float time;
	static float deltaTime;
	static void Tick(const float& dt);
};



