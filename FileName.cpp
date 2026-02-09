#include<iostream>
#include <cstdlib>
#include <ctime>
#include<memory>
#include<vector>
#include<string>
#include<unordered_map>
#include<algorithm>
#include<fstream>





class Quest {
protected:
	std::string name;
	std::string description;
	int reward;
	bool complete;
public:
	Quest(std::string n, std::string des, int rew0) {
		name = n;
		description = des;
		reward = rew0;
		complete = false;


	}
	virtual ~Quest()noexcept {}

};



class Item {
protected:
	std::string name;
	int value;
public:
	Item(std::string name0, int value0) :name(name0), value(value0) {}
	virtual ~Item() = default;

	virtual void display() const = 0;
	virtual std::string getType() const = 0;

	std::string getName() const { return name; }
	int getValue() const { return value; }
};
class Weapon : public Item {
private:
	int damage;
	std::string weaponType;
public:
	Weapon(std::string name, int value, int dmg, std::string type) :Item(name, value) {
		damage = dmg;
		weaponType = type;

	}
	void display() const override {
		std::cout << "Item:" << name << std::endl;
		std::cout << "Type:" << weaponType << std::endl;

	}
	std::string getType() const override { return "Weapon"; }

	int getDamage() const { return damage; }
	std::string getWeaponType() const { return weaponType; }
};
class Armor : public Item {
private:
	int defense;
	std::string armorType;
public:
	Armor(std::string name, int value, int def, std::string type) :Item(name, value) {
		defense = def;
		armorType = type;

	}
	void display() const override {
		std::cout << "Item:" << name << std::endl;
		std::cout << "Type:" << armorType << std::endl;
	}
	std::string getType() const override { return "Armor"; }

	int getDefense() const { return defense; }
};

class Inverary {
private:
	std::vector<std::unique_ptr<Item>> items;
	int maxSlots;
	int slots;
public:
	
	Inverary() :maxSlots(7), slots(0) {}
	bool addItem(std::unique_ptr<Item> newItem) {
		if (slots <= maxSlots) {
			items.emplace_back(std::move(newItem));
			slots++;
			return true;

		}
		else {
			std::cout << "Not enought space\n";
			return false;

		}
	}

	std::unique_ptr<Item> DeleteItem(std::string nameItem) {
		int index = 0;
		for (auto& p : items) {
			if (p->getName() == nameItem) {
				std::unique_ptr<Item> NewPtr = std::move(p);
				items.erase(items.begin() + index);
				return NewPtr;




			}
			index++;
		}
		return nullptr;

	}
	Item* findItem(std::string findName) {
		for (auto it = items.begin(); it != items.end(); it++) {
			if ((*it)->getName() == findName) {
				return it->get();
			}
		}
		return nullptr;

	}
	void display() const {
		for (auto& p : items) {
			p->display();
			printf("\n");

		}

	}
	int countItems(std::string itemName,int* amount ) {
		for (auto it = items.begin(); it != items.end(); it++) {
			if ((*it)->getName() == itemName) {
				(*amount)++;
				
			}
		}
		return *amount;
	}

	


};

class Character {
protected:
	std::string name;
	int level;
    int hp;
	int maxHp;
	int mp;
	int maxMp;
	int attack;
	int defense;
	std::unique_ptr<Inverary> myInventary;
	std::shared_ptr<Weapon> curWeapon;
	std::shared_ptr<Armor> curArmor;
	std::vector<std::shared_ptr<Quest>> qusests;


public:
	Character(std::string name0, int level0, int hp0, int mp0, int atk0, int def0) {
		name = name0;
		level = level0;
		hp = hp0;
		maxHp = hp0;
		attack = atk0;
		defense = def0;
		curWeapon = nullptr;
		curArmor = nullptr;
		myInventary = nullptr;

	}
	virtual void useAbility() = 0;
	virtual std::string getClassName() const = 0;
	virtual void displayStats() const {
	    std::cout << "[" << getClassName() << "] " << name
		<< " (Level " << level << ")" << std::endl;
		std::cout << "HP: " << hp << "/" << maxHp
		<< " | MP: " << mp << "/" << maxMp << std::endl;
		std::cout << "ATK: " << attack << " | DEF: " << defense << std::endl;
		
	}
	virtual double calculateDamage() const = 0;
	void takeDamage(int damage) {
		hp -= damage;

	}
	void heal(int amount) {
		if (hp < maxHp) {
			int tempHp = hp + amount;
			if (tempHp > maxHp) {
				hp = maxHp;
				return;
			}
			else {
				hp = tempHp;
				return;

			}
		}
		else {
			std::cout << "Hp is on max level\n";
			return;
		}
	}
	bool isAlive() const {
		return hp > 0;
	}
	virtual void createInvertar(std::unique_ptr<Inverary> In) = 0;
	virtual void take_weapon(std::string weaponName) = 0;
	virtual void lost_wepon() = 0;
	virtual void take_armor(std::string arnorName) = 0;
	virtual void lost_armor() = 0;
	virtual void displayEqip()const = 0;
	virtual Inverary* getInvertar() = 0;
	virtual void addQuset(std::shared_ptr<Quest> newQuset) = 0;
	virtual std::shared_ptr<Quest>  getLastQ() = 0;
	virtual ~Character() = default;
	virtual std::string getName() = 0;
	virtual int getLevel() = 0;
};
class Warior:public Character {
private:
	int rage;
	int maxRage;
public:
	Warior(std::string name0, int level) :Character(name0, level, level * 120, level * 20, level * 15, level * 12), rage(0), maxRage(100) {}

	void useAbility() override {
		if (rage >= 30) {
			rage -= 30;

		}
		else {
			std::cout << "Not enought rage\n";

		}
	}
	std::string getClassName() const override {
		return "Warior";

	}
	double calculateDamage() const override {
		return  attack * (1 + rage / 100.0);


	}
	void displayStats() const override {
		Character::displayStats();
		std::cout << "Rage:" << rage << std::endl;

	}
	void createInvertar(std::unique_ptr<Inverary> In) override {
		myInventary = std::move(In);
	}
	Inverary* getInvertar() override {
		return myInventary.get();
	}
	void take_weapon(std::string weaponName) override {
		Item* item = myInventary->findItem(weaponName);

		if (!item) {
			std::cout << "Weapon not found\n";
			return;

		}
		Weapon* weapon = dynamic_cast<Weapon*>(item);

		if (!weapon) {
			std::cout << "Item:" << weaponName << " is not a weapon\n";
			return;

		}
		curWeapon =std::make_shared<Weapon>(*weapon);




	}
	void lost_wepon() override {
		curWeapon = nullptr;

	}
	void take_armor(std::string arnorName)override {
		Item* item = myInventary->findItem(arnorName);

		if (!item) {
			std::cout << "Armor not found\n";
			return;

		}
		Armor* armor = dynamic_cast<Armor*>(item);

		if (!armor) {
			std::cout << "Item:" << arnorName << " is not a armor\n";
			return;

		}
		curArmor = std::make_shared<Armor>(*armor);
	}
	void lost_armor() override {
		curArmor = nullptr;

	}
	void displayEqip()const override {
		std::cout << "Current weapon:" << std::endl;
		curWeapon->display();
		std::cout << "Current armor:" << std::endl;
		curArmor->display();

	}
	void addQuset(std::shared_ptr<Quest> newQuset) override {
		qusests.emplace_back(newQuset);

	}
	std::shared_ptr<Quest>  getLastQ() override {
		std::shared_ptr<Quest> temp = qusests.back();
		qusests.pop_back();
		return temp;
	}
	std::string getName() override {
		return name;
	}
	int getLevel() {
		return level;

	}
	

};
class Mage: public Character {
private:
	int intelect;
public:
	Mage(std::string name0, int level) : Character(name0, level, level * 80, level * 150, level * 8, level * 5), intelect(level*20){}
	void useAbility() override {
		if (mp < 50) {
			std::cout << "Not enought mana\n";

		}
		else {
			mp -= 50;

		}

	}
	 std::string getClassName()const  override {
		 return "Mage";


	 }
	double calculateDamage() const override {
		 return attack + (intelect * 2);
	}
	 void displayStats() const override {
		 Character::displayStats();
		 std::cout << "Intelect:" << intelect << std::endl;

	 }
	 void createInvertar(std::unique_ptr<Inverary> In) override {
		 myInventary = std::move(In);
	 }
	 Inverary* getInvertar() override {
		 return myInventary.get();
	 }
	 void take_weapon(std::string weaponName) override {
		 Item* item = myInventary->findItem(weaponName);

		 if (!item) {
			 std::cout << "Weapon not found\n";
			 return;

		 }
		 Weapon* weapon = dynamic_cast<Weapon*>(item);

		 if (!weapon) {
			 std::cout << "Item:" << weaponName << " is not a weapon\n";
			 return;

		 }
		 curWeapon = std::make_shared<Weapon>(*weapon);




	 }
	 void lost_wepon() override {
		 curWeapon = nullptr;

	 }
	 void take_armor(std::string arnorName)override {
		 Item* item = myInventary->findItem(arnorName);

		 if (!item) {
			 std::cout << "Armor not found\n";
			 return;

		 }
		 Armor* armor = dynamic_cast<Armor*>(item);

		 if (!armor) {
			 std::cout << "Item:" << arnorName << " is not a armor\n";
			 return;

		 }
		 curArmor = std::make_shared<Armor>(*armor);
	 }
	 void lost_armor() override {
		 curArmor = nullptr;

	 }
	 void displayEqip()const override {
		 std::cout << "Current weapon:" << std::endl;
		 curWeapon->display();
		 std::cout << "Current armor:" << std::endl;
		 curArmor->display();

	 }
	 void addQuset(std::shared_ptr<Quest> newQuset) override {
		 qusests.emplace_back(newQuset);

	 }
	 std::shared_ptr<Quest>  getLastQ() override {
		 std::shared_ptr<Quest> temp = qusests.back();
		 qusests.pop_back();
		 return temp;
	 }
	 std::string getName()override {
		 return name;
	 }
	 int getLevel() {
		 return level;

	 }
};
class Rouge:public Character {
private:
	double critChance;
public:

	Rouge(std::string name, int level) : Character(name, level, level * 100, level * 50, level * 18, level * 7) {
		critChance =25;

	}

	double calculateDamage() const override {
		return rand() % 100 < critChance ? attack * 2 : attack;

	}
	void useAbility() override {
		attack = calculateDamage() * 2;


	}
	std::string getClassName()const  override {
		return "Rouge";


	}


	void displayStats() const override {
		Character::displayStats();
		printf("%.2lf", critChance);


	}
	void createInvertar(std::unique_ptr<Inverary> In) override {
		myInventary = std::move(In);
	}
	Inverary* getInvertar() override {
		return myInventary.get();
	}
	void take_weapon(std::string weaponName) override {
		Item* item = myInventary->findItem(weaponName);

		if (!item) {
			std::cout << "Weapon not found\n";
			return;

		}
		Weapon* weapon = dynamic_cast<Weapon*>(item);

		if (!weapon) {
			std::cout << "Item:" << weaponName << " is not a weapon\n";
			return;

		}
		curWeapon = std::make_shared<Weapon>(*weapon);




	}
	void lost_wepon() override {
		curWeapon = nullptr;

	}
	void take_armor(std::string arnorName)override {
		Item* item = myInventary->findItem(arnorName);

		if (!item) {
			std::cout << "Armor not found\n";
			return;

		}
		Armor* armor = dynamic_cast<Armor*>(item);

		if (!armor) {
			std::cout << "Item:" << arnorName << " is not a armor\n";
			return;

		}
		curArmor = std::make_shared<Armor>(*armor);
	}
	void lost_armor() override {
		curArmor = nullptr;

	}
	void displayEqip()const override {
		std::cout << "Current weapon:" << std::endl;
		curWeapon->display();
		std::cout << "Current armor:" << std::endl;
		curArmor->display();

	}
	void addQuset(std::shared_ptr<Quest> newQuset) override {
		qusests.emplace_back(newQuset);

	}
	std::shared_ptr<Quest>  getLastQ() override {
		std::shared_ptr<Quest> temp = qusests.back();
		qusests.pop_back();
		return temp;
	}
	std::string getName() override {
		return name;
	}
	int getLevel() {
		return level;

	}
};


class QuestException :public std::exception {
protected:
	std::string msg;
public:
	QuestException() {}
	QuestException(std::string msg0) :msg(msg0) {}

	const char* what()const noexcept override {

		return msg.c_str();

	}



};
class QuestNotFoundException :public QuestException {
public:
	QuestNotFoundException(std::string questName) : QuestException("Quest not found:" + questName) {
		;

	}
};
class QuestNotCompletedException :public QuestException {
public:
	QuestNotCompletedException(std::string questName) : QuestException("Quest not completed yet:" + questName) {

	}


};



class KillQuest :public Quest {
private:
	std::weak_ptr<Character> killTarget;
	std::weak_ptr<Character> curCharecter;
	std::string enemy;
	int amount_ofKills;
	int curKills;
public:
	KillQuest(std::string n, std::string des, int rew0, std::string en, int kills) :Quest(n, des, rew0) {
		enemy = en;
		amount_ofKills = kills;
		curKills = 0;
	}
	void setTarget(std::weak_ptr<Character> target) {
		killTarget = target;

	}
	void setCharacter(std::weak_ptr<Character> player) {
		curCharecter = player;
	}
	std::shared_ptr<Character> getTarget() {
		return  killTarget.lock();
	}
	std::shared_ptr<Character> getPlayer() {
		return  curCharecter.lock();
	}
	void KiLL() {
		if (!killTarget.lock()->isAlive()) {
			curKills++;
			if (curKills == amount_ofKills) {
				complete = true;
				std::cout << "Quest:" << name << " completed\n";

			}
		}
	}
	void displayQ()const {
		std::cout << "Type:" << description << std::endl;
		std::cout << "Need to kill:" << amount_ofKills << std::endl;

	}


};
class CollectQusest :public Quest {
private:

	std::string ItemName;
	int amount;
	int curAmount;
	std::weak_ptr<Character> curCharecter;
public:
	CollectQusest(std::string n, std::string des, int rew0, std::string name, int amount0) :Quest(n, des, rew0) {
		ItemName = name;
		amount = amount0;
		curAmount = 0;

	}
	void setChar(std::weak_ptr<Character> player) {
		curCharecter = player;

	}
	void Collect() {
		Inverary* ptr = curCharecter.lock()->getInvertar();
		ptr->countItems(ItemName, &curAmount);
		if (amount == curAmount) {
			std::cout << "Quest:" << description << " completed\n";
			complete = true;
			curAmount = 0;
			return;
		}
		
	}
	void displayQ()const {
		std::cout << "Type:" << description << std::endl;
		std::cout << "Need to collect:" << amount << std::endl;

	}

};


class Party {
private:
	std::unordered_map<std::string,std::shared_ptr<Character>> party;
	std::string partyName;
	int amountPlayers;
	int curpalyers;
public:

	Party(std::string n):partyName(n),amountPlayers(5),curpalyers(0){}

	bool addMember(std::shared_ptr<Character> newMember){
		if (curpalyers < amountPlayers) {
			auto ptr = party.find(newMember->getName());
			if (ptr != party.end()) {
				std::cout << "Member is already in a party\n";
				return false;

			}
			party[newMember->getName()] = newMember;
			curpalyers++;
			return true;

		}
		else {
			std::cout << "Party is full\n";
			return false;


		}

	}
	bool delMember(std::string& name) {
		auto ptr = party.find(name);
		if (ptr == party.end()) {
			std::cout << "Member doesn't exist\n";
			return false;

		}
		party.erase(name);
		curpalyers--;
		return true;

	}
	void showParty() {
		for (auto it = party.begin(); it != party.end(); it++) {
			(*it).second->displayStats();
			printf("\n");

		}
	}
	void ShowsortBylevel() {
		std::vector<std::shared_ptr<Character>> tempsort;
		tempsort.reserve(party.size());

		for (auto& p : party) {
			tempsort.emplace_back(p.second);

		}

		std::sort(tempsort.begin(), tempsort.end(), [](const std::shared_ptr<Character>& a1, const std::shared_ptr<Character>& a2) {
			return a1->getLevel() > a2->getLevel();
		});


		for (auto& p0 : tempsort) {
			p0->displayStats();
		}
	}
	std::shared_ptr<Character> findMember(std::string& name) {
		auto it = party.find(name);
		if (it != party.end()) {
			return (*it).second;

		}
		else {
			return nullptr;
		}


	}

	std::string getName() {
		return partyName;
	}
	int getCount(){
		return curpalyers;
	}
	std::vector<std::shared_ptr<Character>> getAllMembers() const {
		std::vector<std::shared_ptr<Character>> result;
		for (const auto& pair : party) {
			result.push_back(pair.second);
		}
		return result;
	}
};



int main() {
	/*main is empty*/

	return 0;

}