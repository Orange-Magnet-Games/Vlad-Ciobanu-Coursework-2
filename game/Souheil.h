#pragma once
using namespace std;

class Pet {
private:
	bool moving = false;
	int food = 100;
	int happiness = 100;

protected:
	CSprite* sprite = new CSprite(400, 40, "", CColor::Blue(), 0);
	CSprite* emotion = new CSprite(400, 40, "", CColor::Blue(), 0);
	CSprite* emotionBubble = new CSprite(400, 40, "", CColor(0,0,255), 0);

	bool trial;
	

	CVector position = CVector(400, 300);
	CVector destination = CVector(rand() % 400 + 101, rand() % 500 + 101);

	bool dead = false;

	bool facing = true;

	void SetMoving(bool moving);

	bool GetMoving()                          { return moving; }

public:

	int trialPeriod = 10800;

	Pet(bool trial);
	Pet();

	virtual void InitializeAnimations() = 0;
	virtual void Die()= 0;
	virtual float GetPrice() = 0;
	virtual void Wander() = 0;

	CSprite* Sprite() { return sprite; }


	virtual void Update(float t) = 0;
	virtual void Draw(CGraphics* g) = 0;

	virtual string type() = 0;

	void SetFood(int food);
	void SetAnimation(char* anim);
	void SetPos(CVector position);
	void SetHappiness(int happiness); 
	
	bool IsDead()                             { return dead; }
	CVector GetPos()                          { return position; }
	int GetFood()                             { return food; }
	int GetHappiness()                        { return happiness; }
	bool GetTrial()                           { return trial; }
};


class Dobermann : virtual public Pet {
protected:
	int speed = 3;
	int waitCount = 1000;

public:

	void InitializeAnimations();
	void Die();
	void Update(float t);
	void Draw(CGraphics* g);

	Dobermann();
	Dobermann(bool trial);

	float GetPrice() { return 300; }

	void Wander();

	//string description() { return "A fitting pet for a certain pair of old men. One donning a stiking red suit, the other a dashing blue one. A truly loyal build, though it can be quite stubborn."; } //virtual readonly (at least that's what I'd call this)
	string type() { return "Dobermann"; }

};

class ShibaInu : virtual public Pet {
protected:
	int speed = 3;
	int waitCount = 1000;

public:

	void InitializeAnimations();
	void Die();
	void Update(float t);
	void Draw(CGraphics* g);

	ShibaInu();
	ShibaInu(bool trial);

	float GetPrice() { return 500; }

	void Wander();

	//string description() { return "This breed is very popular with younger generations. Though they can be quite pricey. Very energetic and curious by nature. They do require a lot of attention though."; } //virtual readonly (at least that's what I'd call this)
	string type() { return "Shiba Inu"; }

};


class Cat : virtual public Pet {
protected:
	int speed = 3;
	int waitCount = 1000;

public:

	void InitializeAnimations();
	void Die();
	void Update(float t);
	void Draw(CGraphics* g);

	Cat();
	Cat(bool trial);

	float GetPrice() { return 1500; }

	void Wander();

	//string description() { return "This breed is very popular with younger generations. Though they can be quite pricey. Very energetic and curious by nature. They do require a lot of attention though."; } //virtual readonly (at least that's what I'd call this)
	string type() { return "Cat"; }

};

class Raven : virtual public Pet {
protected:
	int speed = 3;
	int waitCount = 1000;

public:

	void InitializeAnimations();
	void Die();
	void Update(float t);
	void Draw(CGraphics* g);

	Raven();
	Raven(bool trial);

	float GetPrice() { return 2000; }

	void Wander();

	//string description() { return "This breed is very popular with younger generations. Though they can be quite pricey. Very energetic and curious by nature. They do require a lot of attention though."; } //virtual readonly (at least that's what I'd call this)
	string type() { return "Raven"; }

};


class Customer {
protected:
	vector<Pet*>* petsOwned;
	string address;

public:

	int money;
	void AddPet(Pet* pet);
	bool RemovePet(Pet* pet);
	vector<Pet*>* Pets() { return petsOwned; }

	Customer(string address);
	Customer(vector<Pet*>* petsOwned, string address);


};
