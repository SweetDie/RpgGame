#pragma once
#include"Atribute.h"
#include"Object.h"

class Resources : public Object
{
public:
	virtual string getName();
	virtual int getDurability();
	virtual bool getAlive();
	virtual int mine(int damage);
	virtual int getGid();
protected:
	int gid;
	string name;
	int durability;
	Atribute<int>* damageToLoot2;
};