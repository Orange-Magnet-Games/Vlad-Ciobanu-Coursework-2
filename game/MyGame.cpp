#include "stdafx.h"
#include "MyGame.h"

CMyGame::CMyGame(void)
{
	shop.AddImage("shop.bmp", "shope", 1, 1, 0, 0, 0, 0, CColor::Blue());
	home.AddImage("home.png", "homey", 1, 1, 0, 0, 0, 0, CColor::Blue());
	arrowLeft.AddImage("arrow left.png", "arro", 1, 1, 0, 0, 0, 0, CColor::Blue());
	arrowRight.AddImage("arrow right.png", "arro", 1, 1, 0, 0, 0, 0, CColor::Blue());
	shop.SetAnimation("shope");
	home.SetAnimation("homey");
	arrowLeft.SetAnimation("arro");
	arrowRight.SetAnimation("arro");
	for (auto i : petsInShop) { 
		i->InitializeAnimations();
		i->SetAnimation("idle left");
	}
	srand(time(NULL));
}

CMyGame::~CMyGame(void)
{
	// TODO: add destruction code here
}

/////////////////////////////////////////////////////
// Per-Frame Callback Funtions (must be implemented!)
void CMyGame::OnUpdate()
{
	Uint32 t = GetTime();
	if (gameMode == HOME) {
		
		coin.Update(t);
		shop.Update(t);
		for (auto i : coinParticles) {
			i->SetSize(i->GetSize() - CVector(0.75, 0.75));
			if (i->GetSize().X() < 0) {
				i->Delete();
			}
			i->Update(t);
		}
		for (auto i : petParticles) {
			i->SetSize(i->GetSize() - CVector(0.75, 0.75));
			if (i->GetSize().X() < 0) {
				i->Delete();
			}
			i->Update(t);
		}
		coinParticles.delete_if(deleted);
		
		tick--;
		int i = 0;
		for (auto pet : *player->Pets()) {
			if (pet->GetFood() <= 0 && !pet->IsDead()) pet->Die();
			if(!pet->IsDead()) pet->Wander();
			if (tick == 180) {
				if (pet->GetHappiness() < 20) pet->SetFood(pet->GetFood() - rand() % 10 + 1);
				else pet->SetHappiness(pet->GetHappiness() - rand() % 10 + 1);
			}
			if (tick <= 0) {
				
				pet->SetHappiness(pet->GetHappiness() - rand() % 10 + 1);
				pet->SetFood(pet->GetFood() - rand() % 10 + 1);
			}
			pet->Update(t);
			if (pet->GetTrial()) {
				pet->trialPeriod--;
				if (pet->trialPeriod <= 0) player->Pets()->erase(player->Pets()->begin() + i);
				i--;
			}
			i++;
		}
		if (tick <= 0) tick = 320;
	}
	else if (gameMode == SHOP) {
		home.Update(t);
		arrowRight.Update(t);
		arrowLeft.Update(t);
		buyButton.Update(t);
		int count = 0;
		for (auto i : petsInShop) {
			i->Update(t);
			i->SetPos(CVector((count - petSelected + 2) * 200, 300));
			count++;
		}
	}
}

void CMyGame::OnDraw(CGraphics* g)
{
	background.Draw(g);
	if (gameMode == HOME) {
		coin.Draw(g);
		shop.Draw(g);

		for (auto pet : *player->Pets()) pet->Draw(g);
		for (auto i : coinParticles) i->Draw(g);
		for (auto i : petParticles) i->Draw(g);
		
	}
	else if (gameMode == SHOP) {
		home.Draw(g);
		arrowLeft.Draw(g);
		arrowRight.Draw(g);
		buyButton.Draw(g);
		for (auto i : petsInShop) {
			i->SetHappiness(50);
			i->Draw(g);
		}
		if (petsInShop.size() > 0) {
			*g << font("ARIAL.TTF", 50) << xy(200, 500) << petsInShop[petSelected]->type() << font("ARIAL.TTF", 18);
			if (petsInShop[petSelected]->GetTrial()) {
				*g << font("ARIAL.TTF", 50) << xy(150, 450) << "On Trial: 6 mins" << font("ARIAL.TTF", 18);
				*g << font("ARIAL.TTF", 50) << xy(200, 350) << "Price: Free" << font("ARIAL.TTF", 18);
			}
			else *g << font("ARIAL.TTF", 50) << xy(200, 350) << "Price: " << petsInShop[petSelected]->GetPrice() << font("ARIAL.TTF", 18);
		}
	}
	*g << bottom << left << "Money: " << player->money;
}

/////////////////////////////////////////////////////
// Game Life Cycle

// one time initialisation
void CMyGame::OnInitialize()
{

}

// called when a new game is requested (e.g. when F2 pressed)
// use this function to prepare a menu or a welcome screen
void CMyGame::OnDisplayMenu()
{
	StartGame();	// exits the menu mode and starts the game mode
}

// called when a new game is started
// as a second phase after a menu or a welcome screen
void CMyGame::OnStartGame()
{
}

// called when a new level started - first call for nLevel = 1
void CMyGame::OnStartLevel(Sint16 nLevel)
{
}

// called when the game is over
void CMyGame::OnGameOver()
{
}

// one time termination code
void CMyGame::OnTerminate()
{
}

/////////////////////////////////////////////////////
// Keyboard Event Handlers

void CMyGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (sym == SDLK_RIGHT && petSelected < 4) petSelected++;
	if (sym == SDLK_LEFT && petSelected > 0) petSelected--;
	if (sym == SDLK_F4 && (mod & (KMOD_LALT | KMOD_RALT)))
		StopGame();
	if (sym == SDLK_SPACE)
		PauseGame();
	if (sym == SDLK_F2)
		NewGame();
}

void CMyGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
}


/////////////////////////////////////////////////////
// Mouse Events Handlers

void CMyGame::OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle)
{
}

void CMyGame::OnLButtonDown(Uint16 x,Uint16 y)
{
	if (gameMode == HOME) {
		if (coin.HitTest(x, y)) {
			player->money += 10 + player->Pets()->size();
			coin.SetSize(182, 182);
			coinParticles.push_back(new CSprite(rand() % 125 + 646, -50, "coinAdded.png", CColor::Black(), GetTime()));
			coinParticles.back()->SetVelocity(0, 400);
		}
		if (shop.HitTest(x, y)) gameMode = SHOP;
		for (auto i : *player->Pets()) {
			if (i->Sprite()->HitTest(x, y)) {
				int moneyToTake = 200 - i->GetFood() - i->GetHappiness();
				if (player->money >= moneyToTake && moneyToTake > 0) {
					player->money -= moneyToTake;
					i->SetHappiness(100);
					i->SetFood(100);
					petParticles.push_back(new CSprite(rand() % 100 - 50 + x, rand() % 100 - 50 + y, "foodPart.png", CColor::Black(), GetTime()));
					petParticles.back()->SetVelocity(0, 50);
					petParticles.push_back(new CSprite(rand() % 100 - 50 + x, rand() % 100 - 50 + y, "happPart.png", CColor::Black(), GetTime()));
					petParticles.back()->SetVelocity(0, 50);

				}
			}
		}
	}
	else if (gameMode == SHOP) {
		if (home.HitTest(x, y)) gameMode = HOME;

		if (buyButton.HitTest(x, y) && petsInShop.size() > 0) {
			if (petsInShop[petSelected]->GetTrial() || player->money >= petsInShop[petSelected]->GetPrice()) {
				if (!petsInShop[petSelected]->GetTrial()) player->money -= petsInShop[petSelected]->GetPrice();
				
				player->AddPet(petsInShop[petSelected]);
				player->Pets()->back()->SetHappiness(100);
				player->Pets()->back()->SetFood(100);
				petsInShop.erase(petsInShop.begin() + petSelected);
			}
		}
		if (arrowLeft.HitTest(x, y) && petSelected > 0) petSelected--;
		if (arrowRight.HitTest(x, y) && petSelected < petsInShop.size()-1) petSelected++;
		
	}
}

void CMyGame::OnLButtonUp(Uint16 x,Uint16 y)
{
	coin.SetSize(192, 192);
}

void CMyGame::OnRButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonUp(Uint16 x,Uint16 y)
{
}
