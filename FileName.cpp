#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include <cstring>
#include<algorithm>
  



using namespace std;




class Device;//forward declar



//INTERFESES
class IPovered {
public:
	virtual void turnOn()=0;
	virtual void turnOff() = 0;
	virtual bool isPoverd()const = 0;
	virtual ~IPovered() {};


};
class IConect {
public:
	virtual void conect(const char* str) = 0;
	virtual void disconetc() = 0;
	virtual bool isconected() const = 0;
	virtual const char* get_network()const  = 0;
	virtual ~IConect() {};


};
class ISecurable {
public:
	virtual void lock() = 0;
	virtual void unlock() = 0;
	virtual bool isLocked() const = 0;
	virtual bool authenticate(const Device& another) = 0;
	virtual void addAuthorizedCard(const Device& another) = 0;
	virtual void delete_(const Device& another) = 0;
	virtual ~ISecurable() {}
};
class Device  {
protected:
	char* location;
	bool powered;
public:
	char* deviceId;
	Device() {//default by standart
		deviceId = nullptr;
		location = nullptr;
        powered = false;
	}
	Device(const char* id, const char* loc) {
		int len0 = strlen(id) + 1;//+1 because of '\0'
		deviceId = new char[len0];
		strcpy(deviceId, id);
		int len1 = strlen(loc) + 1;
		location = new char[len1];
		strcpy(location, loc);
		powered = false;

	}
	virtual ~Device() {
		delete[] deviceId;
		delete[] location;

	}
	Device(const Device& another) {
		int len0 = strlen(another.deviceId) + 1;
		deviceId = new char[len0];
		strcpy(deviceId,another.deviceId);
		int len1 = strlen(another.location) + 1;
		location = new char[len1];
		strcpy(location, another.location);
		powered =another.powered;

	}
	Device& operator=(const Device& another) {
		if (this == &another)return *this;//self-cheak
		delete[] deviceId;
		delete[] location;
		int len0 = strlen(another.deviceId) + 1;
		deviceId = new char[len0];
		strcpy(deviceId, another.deviceId);
		int len1 = strlen(another.location) + 1;
		location = new char[len1];
		strcpy(location, another.location);
		powered = another.powered;
		return *this;




	}
	virtual void Display_Info() const{
		cout << "Device ID: " << deviceId << endl;
		cout << "Location: " << location << endl;
		cout << "Powered: " << (powered ? "YES" : "NO") << endl;

	}
	
	const char* getId() const{
		return deviceId;


	}
	const char* getLoc()const {
		return location;



	}
	bool power()const {
		return powered;
	}
	

     
};

class SmartDoor: public Device, public IPovered, public ISecurable {
protected:
	char** authorizedCards;
	bool locked;
	int count;
	int capticity;
public:
	
	SmartDoor(const char* id, const char* loc,int n):Device(id,loc) {//Using device constructor
		locked = true;
		capticity = n;
		count = 0;
		authorizedCards = new char* [capticity];



	}
	~SmartDoor() {
		for (int i = 0; i < count; i++) {
			delete authorizedCards[i];

		}
		delete[] authorizedCards;

	}
	SmartDoor(const SmartDoor& another): Device(another) {
		locked = another.locked;
		capticity = another.capticity;
		count = another.count;
		authorizedCards = new char* [capticity];
		for (int i = 0; i < count; i++) {
			int len = strlen(another.authorizedCards[i]) + 1;
			authorizedCards[i] = new char[len]; 
			strcpy(authorizedCards[i], another.authorizedCards[i]);

		}


	}

	SmartDoor& operator=(const SmartDoor& another) {
		if (this == &another)return *this;
		Device::operator=(another);
		for (int i = 0; i < count; i++) {
			delete authorizedCards[i];

		}
		delete[] authorizedCards;
		locked = another.locked;
		capticity = another.capticity;
		count = another.capticity;
		authorizedCards = new char* [capticity];
		for (int i = 0; i < count; i++) {
			int len = strlen(another.authorizedCards[i]) + 1;
			authorizedCards[i] = new char[len];  
			strcpy(authorizedCards[i], another.authorizedCards[i]);

		}
		return *this;

	}
	
	void turnOn() override {
		powered = true;
		cout << "[" << deviceId << "] Door power ON" << endl;
	}

	void turnOff() override {
		powered = false;
		cout << "[" << deviceId << "] Door power OFF" << endl;
	}

	bool isPoverd() const override {  
		return powered;
	}

	void lock() override {
		if (!powered) {
			cout << "[" << deviceId << "] Cannot lock - no power!" << endl;
			return;
		}
		locked = true;
		cout << "[" << deviceId << "]  Door LOCKED" << endl;
	}

	void unlock() override {
		if (!powered) {
			cout << "[" << deviceId << "] Cannot unlock - no power!" << endl;
			return;
		}
		locked = false;
		cout << "[" << deviceId << "]  Door UNLOCKED" << endl;
	}

	bool isLocked() const override {
		return locked;
	}

	bool authenticate(const Device& another) override {
		for (int i = 0; i < count; i++) {
			if (strcmp(authorizedCards[i], another.deviceId) == 0) {
				return true;

			}
		}
		return false;
	}

	
	void addAuthorizedCard(const Device& another) override {
		if (authenticate(another)) {
			cout << "Already exist" << endl;
			return;
		}
		else {
			if (count < capticity) {
				int len = strlen(another.deviceId) + 1;
				authorizedCards[count] = new char[len];
				strcpy(authorizedCards[count], another.deviceId);
				count++;
			}
			else {
				int new_cap = capticity * 2;

				char** authorizedCards1 = new char* [new_cap];
				for (int i = 0; i < count; i++) {
					authorizedCards1[i] = authorizedCards[i];

				}
				delete[] authorizedCards;
				capticity = new_cap;
				authorizedCards = authorizedCards1;
				int len0 = strlen(another.deviceId) + 1;
				authorizedCards[count] = new char[len0];
				strcpy(authorizedCards[count], another.deviceId);
				count++;



			}
		}
		
		
		
		
	}
	void delete_(const Device& another)override {
		int index=-1;
		for (int i = 0; i < count; i++) {
			if (strcmp(authorizedCards[i], another.deviceId) == 0) {
				index = i;
				break;

			}
		}
		if (index==-1) {
			cout << "Not found" << endl;
			return;

		}
		delete[] authorizedCards[index];
		for (int i = index; i < count - 1; i++) {
			authorizedCards[i] = authorizedCards[i + 1];

		}
		count--;
		
		
		

	}

	void Display_Info() const override {
		Device::Display_Info();  
		cout << "Locked: " << (locked ? "YES" : "NO") << endl;
		cout << "Authorized cards: " << count << endl;
		for (int i = 0; i < count; i++) {
			cout << "  - " << authorizedCards[i] << endl;
		}
	}

};


class User: public Device {
protected:
	char* name;
	int accessLevel;
public:
	User():Device() {
		name = nullptr;
		accessLevel = -1;

	}
    virtual ~User() {
		delete[] name;
	}
	User( const char* id,const char* loc,const char* n, int l):Device(id,loc) {
		accessLevel = l;
		int len = strlen(n) + 1;
		name = new char[len];
		strcpy(name, n);

	}
	User(const User& another): Device(another) {
		accessLevel = another.accessLevel;
		int len = strlen(another.name) + 1;
		name = new char[len];
		strcpy(name, another.name);
		

	}
	User& operator=(const User& another) {
		if (this == &another)return *this;
		delete[] name;
		Device::operator=(another);
		accessLevel = another.accessLevel;
		int len = strlen(another.name) + 1;
		name = new char[len];
		strcpy(name, another.name);
		
		return *this;







	}
	virtual void displayInfo() const {
		Device::Display_Info();
		cout << "=== USER INFO ===" << endl;
		cout << "Name: " << name << endl;
		cout << "Access Level: " << accessLevel << endl;
	}
	

	virtual bool canAccess(int requiredLevel) const {
		return accessLevel >= requiredLevel;
	}

	
	const char* getName() const {
		return name;
	}
	
	int getAccessLevel() const { 
		return accessLevel; 
	}



	


};

class Student: public User{
private:
	int studtId;
	char* facility;
public:
	Student(const char* id,const char* loc,const char* n, int l, int stId, const char* fac): User(id,loc,n, 1) {
		studtId = stId;
		int len = strlen(fac) + 1;
		facility = new char[len];
		strcpy(facility, fac);



	}
	~Student() override{
		delete[] facility;

	}
	Student(const Student& another) :User(another) {
		studtId = another.studtId;
		int len = strlen(another.facility) + 1;
		facility = new char[len];
		strcpy(facility, another.facility);

	}
	Student& operator=(const Student& another) {
		if (this == &another) {
			return *this;
		}
		delete[] facility;
		User::operator=(another);
		studtId = another.studtId;
		int len = strlen(another.facility) + 1;
		facility = new char[len];
		strcpy(facility, another.facility);

		return *this;



	}

	void displayInfo()const override {
		User::displayInfo();
		cout << "Student ID: " << studtId << endl;
		cout << "Faculty: " << facility << endl;
	}
	int getStudentId() const { return studtId; }
	const char* getFaculty() const { return facility; }

};

class Teacher : public User {
private:
	char* department;
	int officeNum;
public:
	Teacher(const char* id,const char* loc,const char* n, int l, int num, const char* dep) : User(id,loc,n,2) {
		officeNum = num;
		int len = strlen(dep) + 1;
		department = new char[len];
		strcpy(department, dep);

	}
	~Teacher() override {
		delete[] department;


	}
	Teacher(const Teacher& another) : User(another){
		officeNum =another.officeNum;
		int len = strlen(another.department) + 1;
		department = new char[len];
		strcpy(department, another.department);

	}
	Teacher& operator=(const Teacher& another) {
		if (this == &another) {
			return *this;

		}
		delete[] department;
		User::operator=(another);
		officeNum = another.officeNum;
		int len = strlen(another.department) + 1;
		department = new char[len];
		strcpy(department, another.department);
		return *this;
		
		
			
		
		
	}
	void displayInfo() const override {
		User::displayInfo();
		cout << "Department: " << department << endl;
		cout << "Office: " << officeNum << endl;
	}


};

class Admin : public User {
private:
	char* role;
public:
	Admin(const char* id,const char* loc,const char* n, int l, const char* r) : User(id,loc,n, 3) {
		int len = strlen(r) + 1;
		role = new char[len];
		strcpy(role, r);


	}
	~Admin() override {
		delete[] role;


	}
	Admin(const Admin& another): User(another) {
		int len = strlen(another.role) + 1;
		role = new char[len];
		strcpy(role, another.role);


	}
	Admin& operator = (const Admin& another) {
		if (this == &another) {
			return *this;

		}
		delete[] role;
		User::operator=(another);
		int len = strlen(another.role) + 1;
		role = new char[len];
		strcpy(role, another.role);
		return *this;



	}
	void displayInfo() const override {
		User::displayInfo();
		cout << "Role: " << role << endl;
		cout << " ADMIN ACCESS - Full privileges" << endl;
	}
	bool canAccess(int requiredLevel) const override {
		return true;  
	}
	const char* getRole() const { return role; }
	
};
int main() {//test  code 
	cout << "=== SMART CAMPUS ACCESS CONTROL SYSTEM ===" << endl;

	
	cout << "\n--- Creating Users ---" << endl;

	Student alice("CARD001", "Student", "Alice Johnson", 1, 12345, "Computer Science");
	Student bob("CARD002", "Student", "Bob Smith", 1, 12346, "Engineering");
	Teacher drWilson("CARD101", "Teacher", "Dr. Wilson", 2, 305, "Mathematics");
	Admin security("CARD999", "Admin", "John Doe", 3, "Security");

	cout << " Users created successfully!" << endl;

	
	cout << "\n--- Creating Doors ---" << endl;

	SmartDoor mainDoor("DOOR001", "Main Entrance", 5);
	SmartDoor labDoor("DOOR002", "CS Lab", 5);
	SmartDoor adminDoor("DOOR003", "Admin Office", 3);

	cout << " Doors created successfully!" << endl;


	cout << "\n--- Powering On Doors ---" << endl;
	mainDoor.turnOn();
	labDoor.turnOn();
	adminDoor.turnOn();


	cout << "\n--- Setting Up Access Control ---" << endl;


	cout << "\nMain Door access:" << endl;
	mainDoor.addAuthorizedCard(alice);
	mainDoor.addAuthorizedCard(bob);
	mainDoor.addAuthorizedCard(drWilson);
	mainDoor.addAuthorizedCard(security);


	cout << "\nLab Door access:" << endl;
	labDoor.addAuthorizedCard(alice);     
	labDoor.addAuthorizedCard(drWilson);  
	

	cout << "\nAdmin Door access:" << endl;
	adminDoor.addAuthorizedCard(security);

	
	cout << "\n=== DOORS CONFIGURATION ===" << endl;

	cout << "\n--- Main Door ---" << endl;
	mainDoor.Display_Info();

	cout << "\n--- Lab Door ---" << endl;
	labDoor.Display_Info();

	cout << "\n--- Admin Door ---" << endl;
	adminDoor.Display_Info();


	cout << "\n=== ACCESS TESTS - ALICE ===" << endl;

	cout << "\nAlice tries Main Door: ";
	if (mainDoor.authenticate(alice)) {
		cout << " AUTHENTICATED" << endl;
		mainDoor.unlock();
		cout << "Alice entered Main Entrance" << endl;
		mainDoor.lock();
	}
	else {
		cout << " ACCESS DENIED" << endl;
	}

	cout << "\nAlice tries Lab Door: ";
	if (labDoor.authenticate(alice)) {
		cout << " AUTHENTICATED" << endl;
		labDoor.unlock();
		cout << "Alice entered CS Lab" << endl;
		labDoor.lock();
	}
	else {
		cout << " ACCESS DENIED" << endl;
	}

	cout << "\nAlice tries Admin Door: ";
	if (adminDoor.authenticate(alice)) {
		cout << " AUTHENTICATED" << endl;
		adminDoor.unlock();
	}
	else {
		cout << " ACCESS DENIED (Student cannot access Admin area)" << endl;
	}

	
	cout << "\n=== ACCESS TESTS - BOB ===" << endl;

	cout << "\nBob tries Main Door: ";
	cout << (mainDoor.authenticate(bob) ? " ACCESS" : " DENIED") << endl;

	cout << "Bob tries Lab Door: ";
	cout << (labDoor.authenticate(bob) ? " ACCESS" : " DENIED (Not CS student)") << endl;

	cout << "Bob tries Admin Door: ";
	cout << (adminDoor.authenticate(bob) ? " ACCESS" : " DENIED") << endl;

	
	cout << "\n=== ACCESS TESTS - DR. WILSON ===" << endl;

	cout << "\nDr. Wilson tries Main Door: ";
	cout << (mainDoor.authenticate(drWilson) ? " ACCESS" : " DENIED") << endl;

	cout << "Dr. Wilson tries Lab Door: ";
	cout << (labDoor.authenticate(drWilson) ? " ACCESS" : " DENIED") << endl;

	cout << "Dr. Wilson tries Admin Door: ";
	cout << (adminDoor.authenticate(drWilson) ? " ACCESS" : " DENIED (Teacher)") << endl;

	
	cout << "\n=== ACCESS TESTS - ADMIN ===" << endl;

	cout << "\nAdmin tries Main Door: ";
	cout << (mainDoor.authenticate(security) ? " ACCESS" : " DENIED") << endl;

	cout << "Admin tries Lab Door: ";
	cout << (labDoor.authenticate(security) ? " ACCESS (not in list)" : " DENIED") << endl;

	cout << "Admin tries Admin Door: ";
	cout << (adminDoor.authenticate(security) ? " ACCESS" : "❌ DENIED") << endl;

	
	cout << "\n=== USERS IN SYSTEM ===" << endl;

	cout << "\n--- Student 1 ---" << endl;
	alice.displayInfo();

	cout << "\n--- Student 2 ---" << endl;
	bob.displayInfo();

	cout << "\n--- Teacher ---" << endl;
	drWilson.displayInfo();

	cout << "\n--- Administrator ---" << endl;
	security.displayInfo();

	
	cout << "\n=== POLYMORPHISM TEST ===" << endl;
	Device* devices[7];
	devices[0] = &mainDoor;
	devices[1] = &labDoor;
	devices[2] = &adminDoor;
	devices[3] = &alice;
	devices[4] = &bob;
	devices[5] = &drWilson;
	devices[6] = &security;

	cout << "\nAll devices in system:" << endl;
	for (int i = 0; i < 7; i++) {
		cout << (i + 1) << ". ID: " << devices[i]->getId()
			<< " | Location: " << devices[i]->getLoc() << endl;
	}

	cout << "\n=== SYSTEM TEST COMPLETE ===" << endl;

	return 0;
}