#pragma once
#include "Souheil.h"
enum Mode {
	HOME,
	SHOP
};
class CMyGame : public CGame
{
	int tick = 360;
	Mode gameMode = HOME;
	// Define sprites and other instance variables here
	vector<Pet*> petsInShop = vector<Pet*> { 
		new Dobermann(true),
		new ShibaInu(true),
		new Cat(true),
		new Raven(true),
		new Dobermann(false),
		new ShibaInu(false),
		new Cat(false),
		new Raven(false)
	};
	int petSelected = 0;
	Customer* player = new Customer("penis");
	CSprite background = CSprite(400, 300, "b1.png", CColor::Black(), 0);
	CSprite coin = CSprite(700, 150, "coin.png", CColor::Black(), 0);
	CSprite shop = CSprite(700, 450, "shop.bmp", CColor::Blue(), 0);
	CSprite home = CSprite(650, 100, "home.png", CColor::Blue(), 0);
	CSprite arrowLeft = CSprite(100, 300, "arrow left.png", CColor::Blue(), 0);
	CSprite arrowRight = CSprite(700, 300, "arrow right.png", CColor::Blue(), 0);
	CSprite buyButton = CSprite(300, 100, "buy.png", CColor::Blue(), 0);
	CSpriteList coinParticles = CSpriteList();
	CSpriteList petParticles = CSpriteList();

public:
	CMyGame(void);
	~CMyGame(void);

	// Per-Frame Callback Funtions (must be implemented!)
	virtual void OnUpdate();
	virtual void OnDraw(CGraphics* g);

	// Game Life Cycle
	virtual void OnInitialize();
	virtual void OnDisplayMenu();
	virtual void OnStartGame();
	virtual void OnStartLevel(Sint16 nLevel);
	virtual void OnGameOver();
	virtual void OnTerminate();

	// Keyboard Event Handlers
	virtual void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	virtual void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

	// Mouse Events Handlers
	virtual void OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle);
	virtual void OnLButtonDown(Uint16 x,Uint16 y);
	virtual void OnLButtonUp(Uint16 x,Uint16 y);
	virtual void OnRButtonDown(Uint16 x,Uint16 y);
	virtual void OnRButtonUp(Uint16 x,Uint16 y);
	virtual void OnMButtonDown(Uint16 x,Uint16 y);
	virtual void OnMButtonUp(Uint16 x,Uint16 y);
};
