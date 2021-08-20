#pragma once
#include"Unit.h"

class Dealer : public Unit
{
public:
	Dealer();

	const RectangleShape* getBox() const;
	void loadImage() override;
	void update() override;
};

