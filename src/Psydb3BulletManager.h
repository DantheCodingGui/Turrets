#pragma once

class Psydb3Engine;

class Psydb3BulletManager
{
public:
	Psydb3BulletManager(Psydb3Engine* pEngine, int BulletNumber);
	~Psydb3BulletManager();
	int RequestToFire();
private:
	int m_numberOfBullets;
	Psydb3Engine* m_pEngine;
};

