#include "stdafx.h"
#include "Souheil.h"
#include "ExtraVectors.h"
using namespace ExtraVectors;



Pet::Pet(bool trial) {
	this->trial = trial;
	moving = false;
}
Pet::Pet() {
	trial = false;
	moving = false;
}

void Pet::SetMoving(bool moving) {
	if (this->moving != moving) { 
		this->moving = moving; 
		if (moving) {
			if(facing) sprite->SetAnimation("walk right");
			else sprite->SetAnimation("walk left");
		}
		else {
			if (facing) sprite->SetAnimation("idle right");
			else sprite->SetAnimation("idle left");
		}
	}
}

void Pet::SetFood(int food) {
	if (this->food != food) {
		this->food = food;
		if (this->food <= 20) emotion->SetAnimation("hungry");
		else if (this->happiness >= 80 && this->food >= 80) emotion->SetAnimation("happy");
	}
}

void Pet::SetHappiness(int happiness) {
	if (this->happiness != happiness) {
		this->happiness = happiness;
		if (this->happiness <= 20) emotion->SetAnimation("sad");
		else if (this->happiness >= 80 && this->food >= 80) emotion->SetAnimation("happy");
	}
}

void Pet::SetAnimation(char* anim) {
	sprite->SetAnimation(anim);
}

void Dobermann::InitializeAnimations() {
	sprite->AddImage("Dobermann Walk Right.png", "walk right", 6, 1, 0, 0, 5, 0, CColor::Blue());
	sprite->AddImage("Dobermann Walk Left.png", "walk left", 6, 1, 0, 0, 5, 0, CColor::Blue());
	sprite->AddImage("Dobermann Idle Right.png", "idle right", 4, 1, 0, 0, 3, 0, CColor::Blue());
	sprite->AddImage("Dobermann Idle Left.png", "idle left", 4, 1, 0, 0, 3, 0, CColor::Blue());
	
	sprite->AddImage("Dobermann Death Left.png", "die left", 4, 1, 0, 0, 3, 0, CColor::Blue());
	sprite->AddImage("Dobermann Death Right.png", "die right", 4, 1, 0, 0, 3, 0, CColor::Blue());
	
	sprite->AddImage("Dobermann Death Left.png", "die left idle", 4, 1, 3, 0, 3, 0, CColor::Blue());
	sprite->AddImage("Dobermann Death Right.png", "die right idle", 4, 1, 3, 0, 3, 0, CColor::Blue());

	emotion->AddImage("EmojiHappy.png", "happy", 4, 1, 0, 0, 3, 0, CColor::Blue());
	emotion->AddImage("EmojiHungry.png", "hungry", 8, 1, 0, 0, 7, 0, CColor::Blue());
	emotion->AddImage("EmojiSad.png", "sad", 7, 1, 0, 0, 6, 0, CColor::Blue());

	emotionBubble->AddImage("EmojiBubble.png", "buobel", 1, 1, 0, 0, 0, 0, CColor::Blue());


	sprite->SetAnimation("idle");
	emotionBubble->SetAnimation("buobel");
	emotion->SetAnimation("happy");
}
void Dobermann::Die() {
	dead = true;
	if (facing) sprite->SetAnimation("die right", 10, 0, 4);
	else sprite->SetAnimation("die left", 10, 0, 4);
}
void Dobermann::Update(float t) {
	sprite->SetPos(position);
	emotionBubble->SetPos(position + sprite->GetSize() / 2);
	emotion->SetPos(position + sprite->GetSize() / 2 + CVector(1, 5));
	
	sprite->Update(t);
	emotion->Update(t);
	emotionBubble->Update(t);

	if (dead && sprite->GetCurrentAnimationFrame() >= 3) {
		if (facing) sprite->SetAnimation("die right idle");
		else sprite->SetAnimation("die left idle");
	}
}

void Dobermann::Draw(CGraphics* g) {
	sprite->Draw(g);
	if (!dead && ((GetHappiness() >= 80 && GetFood() >= 80) || GetHappiness() <= 20 || GetFood() <= 20)) {
		emotionBubble->Draw(g);
		emotion->Draw(g);
	}
}

void Dobermann::Wander() {
	if (position.Distance(destination) <= 10) {
		destination = CVector(rand() % 400 + 101, rand() % 500 + 101);
		waitCount = 200;
		SetMoving(false);
	}
	waitCount--;
	if (waitCount > 200) {
		position += (destination - position).Normalise() * speed;
		facing = (destination - position).Normalise().X() > 0 ? true : false;
		SetMoving(true);
	}
	else if (waitCount < 0) waitCount = 1000;

}

Dobermann::Dobermann() : Pet() {
	this->InitializeAnimations();
}
Dobermann::Dobermann(bool trial) : Pet(trial) {
	this->InitializeAnimations();
}

void ShibaInu::InitializeAnimations() {
	sprite->AddImage("Sheeb Walk Right.png", "walk right", 6, 1, 0, 0, 5, 0, CColor::Blue());
	sprite->AddImage("Sheeb Walk Left.png", "walk left", 6, 1, 0, 0, 5, 0, CColor::Blue());
	sprite->AddImage("Sheeb Idle Right.png", "idle right", 4, 1, 0, 0, 3, 0, CColor::Blue());
	sprite->AddImage("Sheeb Idle Left.png", "idle left", 4, 1, 0, 0, 3, 0, CColor::Blue());

	sprite->AddImage("Sheeb Death Left.png", "die left", 4, 1, 0, 0, 3, 0, CColor::Blue());
	sprite->AddImage("Sheeb Death Right.png", "die right", 4, 1, 0, 0, 3, 0, CColor::Blue());

	sprite->AddImage("Sheeb Death Left.png", "die left idle", 4, 1, 3, 0, 3, 0, CColor::Blue());
	sprite->AddImage("Sheeb Death Right.png", "die right idle", 4, 1, 3, 0, 3, 0, CColor::Blue());

	emotion->AddImage("EmojiHappy.png", "happy", 4, 1, 0, 0, 3, 0, CColor::Blue());
	emotion->AddImage("EmojiHungry.png", "hungry", 8, 1, 0, 0, 7, 0, CColor::Blue());
	emotion->AddImage("EmojiSad.png", "sad", 7, 1, 0, 0, 6, 0, CColor::Blue());

	emotionBubble->AddImage("EmojiBubble.png", "buobel", 1, 1, 0, 0, 0, 0, CColor::Blue());


	sprite->SetAnimation("idle");
	emotionBubble->SetAnimation("buobel");
	emotion->SetAnimation("happy");
}


void ShibaInu::Update(float t) {
	sprite->SetPos(position);
	emotionBubble->SetPos(position + sprite->GetSize() / 2);
	emotion->SetPos(position + sprite->GetSize() / 2 + CVector(1, 5));

	sprite->Update(t);
	emotion->Update(t);
	emotionBubble->Update(t);
	
	if (dead && sprite->GetCurrentAnimationFrame() >= 3) {
		if (facing) sprite->SetAnimation("die right idle");
		else sprite->SetAnimation("die left idle");
	}

}

void ShibaInu::Draw(CGraphics* g) {
	sprite->Draw(g);
	if (!dead && ((GetHappiness() >= 80 && GetFood() >= 80) || GetHappiness() <= 20 || GetFood() <= 20)) {
		emotionBubble->Draw(g);
		emotion->Draw(g);
	}
}

void ShibaInu::Die() {
	dead = true;
	if (facing) sprite->SetAnimation("die right", 10, 0, 4);
	else sprite->SetAnimation("die left", 10, 0, 4);
}

void ShibaInu::Wander() {
	if (position.Distance(destination) <= 10) {
		destination = CVector(rand() % 400 + 101, rand() % 500 + 101);
		waitCount = 200;
		SetMoving(false);
	}
	waitCount--;
	if (waitCount > 200) {
		position += (destination - position).Normalise() * speed;
		facing = (destination - position).Normalise().X() > 0 ? true : false;
		SetMoving(true);
	}
	else if (waitCount < 0) waitCount = 1000;

}

ShibaInu::ShibaInu() : Pet() {
	this->InitializeAnimations();
}
ShibaInu::ShibaInu(bool trial) : Pet(trial) {
	this->InitializeAnimations();
}

void Cat::InitializeAnimations() {
	sprite->AddImage("Cat Walk Right.png", "walk right", 6, 1, 0, 0, 5, 0, CColor::Blue());
	sprite->AddImage("Cat Walk Left.png", "walk left", 6, 1, 0, 0, 5, 0, CColor::Blue());
	sprite->AddImage("Cat Idle Right.png", "idle right", 4, 1, 0, 0, 3, 0, CColor::Blue());
	sprite->AddImage("Cat Idle Left.png", "idle left", 4, 1, 0, 0, 3, 0, CColor::Blue());

	sprite->AddImage("Cat Death Left.png", "die left", 4, 1, 0, 0, 3, 0, CColor::Blue());
	sprite->AddImage("Cat Death Right.png", "die right", 4, 1, 0, 0, 3, 0, CColor::Blue());

	sprite->AddImage("Cat Death Left.png", "die left idle", 4, 1, 3, 0, 3, 0, CColor::Blue());
	sprite->AddImage("Cat Death Right.png", "die right idle", 4, 1, 3, 0, 3, 0, CColor::Blue());

	emotion->AddImage("EmojiHappy.png", "happy", 4, 1, 0, 0, 3, 0, CColor::Blue());
	emotion->AddImage("EmojiHungry.png", "hungry", 8, 1, 0, 0, 7, 0, CColor::Blue());
	emotion->AddImage("EmojiSad.png", "sad", 7, 1, 0, 0, 6, 0, CColor::Blue());

	emotionBubble->AddImage("EmojiBubble.png", "buobel", 1, 1, 0, 0, 0, 0, CColor::Blue());


	sprite->SetAnimation("idle");
	emotionBubble->SetAnimation("buobel");
	emotion->SetAnimation("happy");
}
void Cat::Die() {
	dead = true;
	if (facing) sprite->SetAnimation("die right", 10, 0, 4);
	else sprite->SetAnimation("die left", 10, 0, 4);
}
void Cat::Update(float t) {
	sprite->SetPos(position);
	emotionBubble->SetPos(position + sprite->GetSize() / 2);
	emotion->SetPos(position + sprite->GetSize() / 2 + CVector(1, 5));

	sprite->Update(t);
	emotion->Update(t);
	emotionBubble->Update(t);

	if (dead && sprite->GetCurrentAnimationFrame() >= 3) {
		if (facing) sprite->SetAnimation("die right idle");
		else sprite->SetAnimation("die left idle");
	}
}

void Cat::Draw(CGraphics* g) {
	sprite->Draw(g);
	if (!dead && ((GetHappiness() >= 80 && GetFood() >= 80) || GetHappiness() <= 20 || GetFood() <= 20)) {
		emotionBubble->Draw(g);
		emotion->Draw(g);
	}
}

void Cat::Wander() {
	if (position.Distance(destination) <= 10) {
		destination = CVector(rand() % 400 + 101, rand() % 500 + 101);
		waitCount = 200;
		SetMoving(false);
	}
	waitCount--;
	if (waitCount > 200) {
		position += (destination - position).Normalise() * speed;
		facing = (destination - position).Normalise().X() > 0 ? true : false;
		SetMoving(true);
	}
	else if (waitCount < 0) waitCount = 1000;

}

Cat::Cat() : Pet() {
	this->InitializeAnimations();
}
Cat::Cat(bool trial) : Pet(trial) {
	this->InitializeAnimations();
}

void Raven::InitializeAnimations() {
	sprite->AddImage("Crow Walk Right.png", "walk right", 6, 1, 0, 0, 5, 0, CColor::Blue());
	sprite->AddImage("Crow Walk Left.png", "walk left", 6, 1, 0, 0, 5, 0, CColor::Blue());
	sprite->AddImage("Crow Idle Right.png", "idle right", 4, 1, 0, 0, 3, 0, CColor::Blue());
	sprite->AddImage("Crow Idle Left.png", "idle left", 4, 1, 0, 0, 3, 0, CColor::Blue());

	sprite->AddImage("Crow Death Left.png", "die left", 4, 1, 0, 0, 3, 0, CColor::Blue());
	sprite->AddImage("Crow Death Right.png", "die right", 4, 1, 0, 0, 3, 0, CColor::Blue());

	sprite->AddImage("Crow Death Left.png", "die left idle", 4, 1, 3, 0, 3, 0, CColor::Blue());
	sprite->AddImage("Crow Death Right.png", "die right idle", 4, 1, 3, 0, 3, 0, CColor::Blue());

	emotion->AddImage("EmojiHappy.png", "happy", 4, 1, 0, 0, 3, 0, CColor::Blue());
	emotion->AddImage("EmojiHungry.png", "hungry", 8, 1, 0, 0, 7, 0, CColor::Blue());
	emotion->AddImage("EmojiSad.png", "sad", 7, 1, 0, 0, 6, 0, CColor::Blue());

	emotionBubble->AddImage("EmojiBubble.png", "buobel", 1, 1, 0, 0, 0, 0, CColor::Blue());


	sprite->SetAnimation("idle");
	emotionBubble->SetAnimation("buobel");
	emotion->SetAnimation("happy");
}
void Raven::Die() {
	dead = true;
	if (facing) sprite->SetAnimation("die right", 10, 0, 4);
	else sprite->SetAnimation("die left", 10, 0, 4);
}
void Raven::Update(float t) {
	sprite->SetPos(position);
	emotionBubble->SetPos(position + sprite->GetSize() / 2);
	emotion->SetPos(position + sprite->GetSize() / 2 + CVector(1, 5));

	sprite->Update(t);
	emotion->Update(t);
	emotionBubble->Update(t);

	if (dead && sprite->GetCurrentAnimationFrame() >= 3) {
		if (facing) sprite->SetAnimation("die right idle");
		else sprite->SetAnimation("die left idle");
	}
}

void Raven::Draw(CGraphics* g) {
	sprite->Draw(g);
	if (!dead && ((GetHappiness() >= 80 && GetFood() >= 80) || GetHappiness() <= 20 || GetFood() <= 20)) {
		emotionBubble->Draw(g);
		emotion->Draw(g);
	}
}

void Raven::Wander() {
	if (position.Distance(destination) <= 10) {
		destination = CVector(rand() % 400 + 101, rand() % 500 + 101);
		waitCount = 200;
		SetMoving(false);
	}
	waitCount--;
	if (waitCount > 200) {
		position += (destination - position).Normalise() * speed;
		facing = (destination - position).Normalise().X() > 0 ? true : false;
		SetMoving(true);
	}
	else if (waitCount < 0) waitCount = 1000;

}

Raven::Raven() : Pet() {
	this->InitializeAnimations();
}
Raven::Raven(bool trial) : Pet(trial) {
	this->InitializeAnimations();
}

void Customer::AddPet(Pet* pet) {
	petsOwned->push_back(pet);
}

bool Customer::RemovePet(Pet* pet) {
	for (int i = 0; i < petsOwned->size(); i++) {
		if (petsOwned->at(i) == pet) {
			delete find(*petsOwned, pet), pet;
			petsOwned->erase(petsOwned->begin() + i);
			return true;
		}
	}
	return false;
}

Customer::Customer(string address) {
	petsOwned = new vector<Pet*>();
	this->address = address;
	money = 0;
}
Customer::Customer(vector<Pet*>* petsOwned, string address) {
	this->petsOwned = petsOwned;
	this->address = address;
	money = 0;
}
void Pet::SetPos(CVector position) {
	this->position = position;
}