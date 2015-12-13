#pragma once


// E-POD


class Player {
public:

    int deadCount = 0;

	float fireRateModifier = 1.0f;
	float damageModifier = 1.0f;
	float accumulator = 0;
	float spawnRateModifier = 1.0f;

	static const float baseSpawnRate; // 0.3f


};












