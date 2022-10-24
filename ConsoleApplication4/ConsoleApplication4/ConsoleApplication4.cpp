#include <iostream>
#include <string>

using namespace std;

class GameObject {
private:
	int id;

public:
	//Конструктор
	GameObject(int newId) {
		id = newId;
	}

	//get
	virtual int Id() {
		return id;
	}
	//set
	virtual void SetId(int newId) {
		id = newId;
	}

	virtual void Print() {
		cout << "id: " << id << endl;
	}

	virtual ~GameObject() {

	}
};

class PhysicObject : public virtual GameObject {
private:
	//масса
	int weight;

public:
	//Конструктор
	PhysicObject(int newId, int newWeight) : GameObject(newId) {
		weight = newWeight;
	}

protected:
	virtual void Print() {
		cout << "Масса: " << weight << endl;
	}
};

class GraphicObject : public virtual GameObject {
private:
	//текстура
	int texture;

public:
	//Конструктор
	GraphicObject(int newId, int newTexture) : GameObject(newId) {
		texture = newTexture;
	}

protected:
	virtual void Print() {
		cout << "Текстура: " << texture << endl;
	}
};

//снаряд
class Projectile : public virtual PhysicObject {
private:
	//калибр
	int caliber;

public:
	//конструктор
	Projectile(int newId, int newWeight, int newCaliber) : PhysicObject(newId, newWeight), GameObject(newId) {
		caliber = newCaliber;
	}

protected:
	virtual void Print() {
		GameObject::Print();
		PhysicObject::Print();
		cout << "Калибр: " << caliber << endl;
	}
};

//транспортное средство
class Vehicle : public virtual PhysicObject {
private:
	//мощность двигаетеля
	int enginePower;

public:
	//конструктор
	Vehicle(int newId, int newWeight, int newEnginePower) : PhysicObject(newId, newWeight), GameObject(newId) {
		enginePower = newEnginePower;
	}

protected:
	virtual void Print() {
		GameObject::Print();
		PhysicObject::Print();
		cout << "Мощность двигателя: " << enginePower << endl;
	}
};

class Tank : public virtual Vehicle, public virtual GraphicObject {
private:
	//толщина брони
	int armor;

public:
	//конструктор
	Tank(int newId, int newWeight, int newEnginePower, int newTexture, int newArmor) :
		Vehicle(newId, newWeight, newEnginePower), PhysicObject(newId, newWeight), GraphicObject(newId, newTexture), GameObject(newId) {
		armor = newArmor;
	}

protected:
	virtual void Print() {
		Vehicle::Print();
		GraphicObject::Print();
		cout << "Толщина брони: " << armor << endl;
	}
};


class Airplane : public virtual Vehicle, public virtual GraphicObject {
private:
	//грузоподъемность
	int capacity;

public:
	//конструктор
	Airplane(int newId, int newWeight, int newEnginePower, int newTexture, int newCapacity) :
		Vehicle(newId, newWeight, newEnginePower), PhysicObject(newId, newWeight), GraphicObject(newId, newTexture), GameObject(newId) {
		capacity = newCapacity;
	}

protected:
	virtual void Print() {
		Vehicle::Print();
		GraphicObject::Print();
		cout << "Грузоподъемность: " << capacity << endl;
	}
};

struct TNode
{
	GameObject* Data;
	TNode* Left;
	TNode* Right;

};
typedef TNode* PNode;

void Insert(PNode& Root, int id, int weight, int caliber) {
	if (!Root) {
		PNode newElem = new TNode;
		newElem->Data = new Projectile(id, weight, caliber);
		newElem->Left = nullptr;
		newElem->Right = nullptr;
		Root = newElem;
		return;
	}

	if (id < Root->Data->Id())
		Insert(Root->Left, id, weight, caliber);
	else if (id > Root->Data->Id())
		Insert(Root->Right, id, weight, caliber);
}


void InsertT(PNode& Root, int choice, int id, int weight, int texture, int enginePower, int TransportCharacter) {
	if (!Root) {
		PNode newElem = new TNode;
		newElem->Data = new Tank(id, weight, texture, enginePower, TransportCharacter);
		newElem->Left = nullptr;
		newElem->Right = nullptr;
		Root = newElem;
		return;
	}

	if (id < Root->Data->Id())
		InsertT(Root->Left, choice, id, weight, texture, enginePower, TransportCharacter);
	else if (id > Root->Data->Id())
		InsertT(Root->Right, choice, id, weight, texture, enginePower, TransportCharacter);
}

void InsertA(PNode& Root, int choice, int id, int weight, int texture, int enginePower, int TransportCharacter) {
	if (!Root) {
		PNode newElem = new TNode;
		newElem->Data = new Airplane(id, weight, texture, enginePower, TransportCharacter);
		newElem->Left = nullptr;
		newElem->Right = nullptr;
		Root = newElem;
		return;
	}

	if (id < Root->Data->Id())
		InsertA(Root->Left, choice, id, weight, texture, enginePower, TransportCharacter);
	else if (id > Root->Data->Id())
		InsertA(Root->Right, choice, id, weight, texture, enginePower, TransportCharacter);
}

bool Find(PNode Root, int x)
{
	if (!Root) return false;
	if (Root->Data->Id() == x) return true;
	if (Root->Data->Id() > x)
		return Find(Root->Left, x);
	else
		return Find(Root->Right, x);
}

void Pryam(PNode Root) { //КЛП
	if (!Root) return;
	Root->Data->Print();
	Pryam(Root->Left);
	Pryam(Root->Right);
}

void Obrat(PNode Root) { //ЛКП
	if (!Root) return;
	Obrat(Root->Left);
	Root->Data->Print();
	Obrat(Root->Right);

}

void Conc(PNode Root) { //ЛПК
	if (!Root) return;
	Conc(Root->Left);
	Conc(Root->Right);
	Root->Data->Print();
}

PNode findmin(PNode p)
{
	if (p != nullptr)
		return p->Left ? findmin(p->Left) : p; // (!)
	else
		return nullptr;
}

// Удаление узла с минимальным ключом из дерева p
PNode removemin(PNode p)
{
	if (p != nullptr)
	{
		if (!(p->Left))
			return p->Right;
		p->Left = removemin(p->Left);
	}
	return p;
}

// Удаление ключа
void remove(PNode& p, int x)
{
	if (p != nullptr)
	{
		if (x < p->Data->Id())
			remove(p->Left, x);
		else if (x > p->Data->Id())
			remove(p->Right, x);
		else
		{
			PNode q = p->Left;
			PNode r = p->Right;

			if (r == nullptr) // && q == nullptr
			{
				p = q;
				return;
			}

			PNode min = findmin(r);
			min->Right = removemin(r);
			min->Left = q;
			p = min;
			return;
		}
	}
}

void DestroyTree(PNode& Root)
{
	if (!Root) return;
	if (Root->Left)
		DestroyTree(Root->Left);
	if (Root->Right)
		DestroyTree(Root->Right);
	delete Root->Data;
	delete Root;
}

void CreateObject(PNode& Root, int choice) {
	cout << "1 - Снаряд" << endl;
	cout << "2 - Танк" << endl;
	cout << "3 - Самолет" << endl;
	cout << "0 - Назад" << endl;
	int c, id, weight, armor, texture, enginePower, caliber, capacity;
	cin >> c;
	if (c == 0) return;
	cout << "id: ";
	cin >> id;

	if (Find(Root, id)) {
		cout << "Объект с идентификатором " << id << " уже создан" << endl;
		return;
	}
	cout << "Вес: ";
	cin >> weight;
	switch (c) {
	case 1:
		cout << "Калибр: ";
		cin >> caliber;
		Insert(Root, id, weight, caliber);
		break;

	case 2:
		cout << "Текстура: ";
		cin >> texture;
		cout << "Мощность двигателя: ";
		cin >> enginePower;
		cout << "Толщина брони: ";
		cin >> armor;
		InsertT(Root, c, id, weight, texture, enginePower, armor);
		break;
	case 3:
		cout << "Текстура: ";
		cin >> texture;
		cout << "Мощность двигателя: ";
		cin >> enginePower;
		cout << "Грузоподъемность: ";
		cin >> capacity;
		InsertA(Root, c, id, weight, texture, enginePower, capacity);

		break;
	}
}


void PrintTRee1(PNode Root)
{
	if (Root != NULL)
	{
		cout << Root->Data->Id();
		cout << " (";
		PrintTRee1(Root->Left);
		cout << ") ";
		cout << " (";
		PrintTRee1(Root->Right);
		cout << ") ";
	}
	else cout << "null";
}
void PrintTree(PNode Root) {
	cout << "1 - Прямой обход" << endl;
	cout << "2 - Обратный обход" << endl;
	cout << "3 - Концевой обход" << endl;
	int choice;
	cin >> choice;
	//cout << "---------------------" << endl;
	switch (choice) {
	case 1:
		Pryam(Root);
		PrintTRee1(Root);
		cout << endl;
		break;

	case 2:
		Obrat(Root);
		break;

	case 3:
		Conc(Root);
		break;
	}
	//cout << "---------------------" << endl;
}

int main() {
	setlocale(LC_ALL, "Russian");
	PNode Root = nullptr;

	while (true) {
		cout << "1 - Добавить объект" << endl;
		cout << "2 - Удалить объект" << endl;
		cout << "3 - Печать дерева" << endl;
		cout << "0 - Завершение программы" << endl;
		int choice;
		cin >> choice;
		switch (choice) {
		case 1:
			CreateObject(Root, choice);
			break;

		case 2:
			cout << "id объекта для удаления : ";
			int id;
			cin >> id;
			remove(Root, id);
			break;

		case 3:
			PrintTree(Root);
			break;

		case 0:
			DestroyTree(Root);
			exit(0);
			break;
		}
	}
}