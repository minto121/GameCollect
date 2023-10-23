#pragma once
#include"AbstractScene.h"
class Hanahuda:
	public AbstractScene
{
	int HudaImg[47];
	int Stage;
	
private:


public:
	Hanahuda();
	~Hanahuda();
	virtual AbstractScene* Update()override;
	void Draw()const override;
	int Kas();
	int Tan();
	int Tane();
	int Akatan();
	int Aotan();
	int Inosikatyou();
	int Hanami();
	int Tukimi();
	int Sankou();
	int Sikou();
	int Amesikou();
	int Gokou();
	int Koikoi();
	int Syobu();
};
