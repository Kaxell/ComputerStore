/**
 * @file ComputerStore.cpp
 *
 * @brief  Computer Store app
 *
 * @author Ertugrul Akay
 */

#include "ComputerStore.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cassert>
#include <limits.h>

using namespace std;


class Manufacturer
{
protected:
	string name;

public:
	Manufacturer(string name)
	{
		this->name = name;
	}
	~Manufacturer()
	{
		cout << "memory freed" << endl;
	}

	string GetDescription() 
	{
		return "Manufacturer: " + name;
	}

	string GetName()
	{
		return name;
	}
};

class CPU
{

public:
	string brand;
	string model;
	int price;


	CPU(string brand, string model)
	{
		this->brand = brand;
		this->model = model;
		this->price = 0;
	}

	CPU(string brand, string model, int price)
	{
		this->brand = brand;
		this->model = model;
		this->price = price;
	}

	~CPU() 
	{
		cout << "memory freed" << endl;
	}

	string GetDescription()
	{
		string description = "CPU Brand: " + brand + "\nCPU Model: " + model;
		return description;
	}
};

class GPU
{

public:
	string brand;
	string model;
	int price;

	GPU(string brand, string model)
	{
		this->brand = brand;
		this->model = model;
	}
	
	GPU(string brand, string model, int price)
	{
		this->brand = brand;
		this->model = model;
		this->price = price;
	}

	~GPU()
	{
		cout << "memory freed" << endl;
	}

	string GetDescription()
	{
		string description = "GPU Brand: " + brand + "\nGPU Model: " + model;
		return description;
	}

};

string GetOSDescription(OSType type)
{
	if ((int)type == 1)
	{
		return "SSD";
	}
	else if ((int)type == 2)
	{
		return "HDD";
	}
	else if ((int)type == 3)
	{
		return "SSHD";
	}
	return "N/A";
}

string GetHDDescription(HDType type)
{
	if ((int)type == 1)
	{
		return "Win";
	}
	else if ((int)type == 2)
	{
		return "Linux";
	}
	else if ((int)type == 3)
	{
		return "Mac";
	}
	return "N/A";
}

string GetScreenSizeDescription(ScreenSize type)
{
	if ((int)type == 1)
	{
		return "11.1 inch";
	}
	else if ((int)type == 2)
	{
		return "12 inch";
	}
	else if ((int)type == 3)
	{
		return "13.3 inch";
	}
	else if ((int)type == 4)
	{
		return "14 inch";
	}
	else if ((int)type == 5)
	{
		return "15.6 inch";
	}
	else if ((int)type == 6)
	{
		return "17.3 inch";
	}
	return "N/A";
}


class Computer //Super Class & Abstract Class
{

protected:
	int ID;
	CPU* cpu;
	GPU* gpu;
	int memory;
	OSType osType;
	HDType hdType;
	int hdCapacity;
	double price;

	Computer(int ID, CPU* cpu, GPU* gpu, int memory, OSType osType, HDType hdType, int hdCapacity, double price)
	{
		this->ID = ID;
		this->cpu = cpu;
		this->gpu = gpu;
		this->memory = memory;
		this->osType = osType;
		this->hdType = hdType;
		this->hdCapacity = hdCapacity;
		this->price = price;
	}

	Computer()
	{
	}

	~Computer()
	{
	}


public:
	virtual string GetDescription() = 0;
	virtual int GetID() = 0;
	virtual int GetPrice() = 0;


};

class Laptop : Computer //Subclass
{
protected:
	Manufacturer* manufacturer;
	ScreenSize screenSize;
	const int MAXCPU = 1;
	const int MAXGPU = 1;
	int cpuCount;
	int gpuCount;

public:
	Laptop(int ID, CPU* cpu, GPU* gpu, int memory, OSType osType, HDType hdType, int hdCapacity, double price,
		Manufacturer* manufacturer, ScreenSize screenSize, int cpuCount, int gpuCount) :
		Computer(ID, cpu, gpu, memory, osType, hdType, hdCapacity, price)
	{
		this->manufacturer = manufacturer;
		this->screenSize = screenSize;
		this->cpuCount = cpuCount;
		this->gpuCount = gpuCount;
	}
	
	Laptop()
	{
	}

	~Laptop()
	{
		cout << "memory freed" << endl;
	}

	string GetDescription() override
	{
		string str;

		str += "\nType: Laptop";
		str += "\nID: " + to_string(this->GetID());
		str += "\n" + this->cpu->GetDescription();
		str += "\n" + this->gpu->GetDescription();
		str += "\nMemory: " + to_string(this->memory);
		str += "\nOSType: " + GetOSDescription(this->osType);
		str += "\nHDType: " + GetHDDescription(this->hdType);
		str += "\nHDCapacity " + to_string(this->hdCapacity);
		str += "\nPrice: " + to_string(this->GetPrice());
		str += "\n" + this->manufacturer->GetDescription();
		str += "\nScreen Size: " + GetScreenSizeDescription(this->screenSize);
		str += "\nCPU Count: " + to_string(this->cpuCount);
		str += "\nGPU Count: " + to_string(this->gpuCount);

		return str;
	}

	int GetID() override
	{
		return this->ID;
	}

	int GetPrice() override 
	{
		return this->price;
	}

	ScreenSize GetScreenSize() 
	{
		return this->screenSize;
	}

	string GetManufacturerName()
	{
		return this->manufacturer->GetName();
	}

	int GetCpuCount() 
	{
		return this->cpuCount;
	}

	int GetGpuCount()
	{
		return this->gpuCount;
	}

	friend ostream& operator << (ostream& out, const Laptop& obj)
	{
		out << obj.ID << "\n" << obj.cpu->brand << "\n" << obj.cpu->model << "\n" << obj.gpu->brand << "\n" << obj.gpu->model
			<< "\n" << obj.memory << "\n" << (int)obj.osType << "\n" << (int)obj.hdType << "\n" << obj.hdCapacity << "\n"
			<< obj.price << "\n" << obj.manufacturer->GetName() << "\n" << (int)obj.screenSize << "\n" << obj.cpuCount << "\n" << obj.gpuCount << endl;
		return out;

	}

	friend istream& operator >> (istream& in, Laptop& obj)
	{
		int osType;
		int hdType;
		int screenType;
		string cpuBrand;
		string cpuModel;
		string gpuBrand;
		string gpuModel;
		string manuName;

		in >> obj.ID;
		in >> cpuBrand;
		in >> cpuModel;
		in >> gpuBrand;
		in >> gpuModel;
		in >> obj.memory;
		in >> osType;
		in >> hdType;
		in >> obj.hdCapacity;
		in >> obj.price;
		in >> manuName;
		in >> screenType;
		in >> obj.cpuCount;
		in >> obj.gpuCount;

		obj.osType = static_cast<OSType>(osType);
		obj.hdType = static_cast<HDType>(hdType);
		obj.screenSize = static_cast<ScreenSize>(screenType);
		obj.cpu = new CPU(cpuBrand, cpuModel);
		obj.gpu = new GPU(gpuBrand, gpuModel);
		obj.manufacturer = new Manufacturer(manuName);

		return in;
	}


};

class Desktop : Computer //Subclass
{
protected:
	const int MAXCPU = 2;
        const int MAXGPU = 2;
	int cpuCount;
	int gpuCount;

public:
	Desktop(int ID, CPU* cpu, GPU* gpu, int memory, OSType osType, HDType hdType, int hdCapacity, double basePrice,
		int cpuCount, int gpuCount) : Computer(ID, cpu, gpu, memory, osType, hdType, hdCapacity, basePrice)
	{
		this->cpuCount = cpuCount;
		this->gpuCount = gpuCount;
	}

	Desktop()
	{
	}

	~Desktop()
	{
		cout << "memory freed" << endl;
	}

	string GetDescription() override
	{
		string str;

		str += "\nType: Desktop";
		str += "\nID: " + to_string(this->GetID());
		str += "\n" + this->cpu->GetDescription();
		str += "\n" + this->gpu->GetDescription();
		str += "\nMemory: " + to_string(this->memory);
		str += "\nOSType: " + GetOSDescription(this->osType);
		str += "\nHDType: " + GetHDDescription(this->hdType);
		str += "\nHDCapacity " + to_string(this->hdCapacity);
		str += "\nTotal Price (CPU + GPU + Base) " + to_string(this->GetPrice());
		str += "\nCPU Count: " + to_string(this->cpuCount);
		str += "\nGPU Count: " + to_string(this->gpuCount);

		return str;
	}

	int GetID() override
	{
		return this->ID;
	}

	int GetPrice() override
	{
		return ((cpuCount * cpu->price) + (gpuCount * gpu->price) + this->price);
	}

	int GetCpuCount()
	{
		return this->cpuCount;
	}

	int GetGpuCount()
	{
		return this->gpuCount;
	}

	friend ostream& operator << (ostream& out, const Desktop& obj)
	{
		out << obj.ID << "\n" << obj.cpu->brand << "\n" << obj.cpu->model << "\n"<< obj.cpu->price << "\n" << obj.gpu->brand << "\n" << obj.gpu->model << "\n" << obj.gpu->price << "\n" 
			<< "\n" << obj.memory << "\n" << (int)obj.osType << "\n" << (int)obj.hdType << "\n" << obj.hdCapacity << "\n" 
			<< obj.price << "\n" << obj.cpuCount << "\n" << obj.gpuCount <<  endl;
		return out;
	}

	friend istream& operator >> (istream& in, Desktop& obj)
	{
		int osType;
		int hdType;
		string cpuBrand;
		string cpuModel;
		int cpuPrice;
		string gpuBrand;
		string gpuModel;
		int gpuPrice;

		in >> obj.ID;
		in >> cpuBrand;
		in >> cpuModel;
		in >> cpuPrice;
		in >> gpuBrand;
		in >> gpuModel;
		in >> gpuPrice;
		in >> obj.memory;
		in >> osType;
		in >> hdType;
		in >> obj.hdCapacity;
		in >> obj.price;
		in >> obj.cpuCount;
		in >> obj.gpuCount;
		
		obj.osType = static_cast<OSType>(osType);
		obj.hdType = static_cast<HDType>(hdType);
		obj.cpu = new CPU(cpuBrand, cpuModel, cpuPrice);
		obj.gpu = new GPU(gpuBrand, gpuModel, gpuPrice);

		return in;
	}

};


class Server : Computer //Subclass
{
protected:
    	Manufacturer* manufacturer;
    	const int MAXGPU = 4;
	const int MAXCPU = 4;
	int cpuCount;
	int gpuCount;

public:
	Server(int ID, CPU* cpu, GPU* gpu, int memory, OSType osType, HDType hdType, int hdCapacity, double price,
		Manufacturer* manufacturer, int cpuCount, int gpuCount) : Computer(ID, cpu, gpu, memory, osType, hdType, hdCapacity, price)
	{
		this->manufacturer = manufacturer;
		this->cpuCount = cpuCount;
		this->gpuCount = gpuCount;
	}
	
	Server()
	{
	}

	~Server()
	{
		cout << "memory freed" << endl;
	}

	string GetDescription() override
	{
		string str;

		str += "\nType: Server";
		str += "\nID: " + to_string(this->GetID());
		str += "\n" + this->cpu->GetDescription();
		str += "\n" + this->gpu->GetDescription();
		str += "\nMemory: " + to_string(this->memory);
		str += "\nOSType: " + GetOSDescription(this->osType);
		str += "\nHDType: " + GetHDDescription(this->hdType);
		str += "\nHDCapacity " + to_string(this->hdCapacity);
		str += "\nPrice: " + to_string(this->GetPrice());
		str += "\n" + this->manufacturer->GetDescription();
		str += "\nCPU Count: " + to_string(this->cpuCount);
		str += "\nGPU Count: " + to_string(this->gpuCount);

		return str;
	}

	int GetID() override 
	{
		return this->ID;
	}

	int GetPrice() override
	{
		return this->price;
	}

	string GetManufacturerName()
	{
		return this->manufacturer->GetName();
	}

	int GetCpuCount()
	{
		return this->cpuCount;
	}

	int GetGpuCount()
	{
		return this->gpuCount;
	}

	friend ostream& operator << (ostream& out, const Server& obj)
	{
		out << obj.ID << "\n" << obj.cpu->brand << "\n" << obj.cpu->model << "\n" << obj.gpu->brand << "\n" << obj.gpu->model
			<< "\n" << obj.memory << "\n" << (int)obj.osType << "\n" << (int)obj.hdType << "\n" << obj.hdCapacity << "\n"
			<< obj.price << "\n" << obj.manufacturer->GetName() << "\n" << obj.cpuCount << "\n" << obj.gpuCount << endl;
		return out;

	}

	friend istream& operator >> (istream& in, Server& obj)
	{
		int osType;
		int hdType;
		string cpuBrand;
		string cpuModel;
		string gpuBrand;
		string gpuModel;
		string manuName;

		in >> obj.ID;
		in >> cpuBrand;
		in >> cpuModel;
		in >> gpuBrand;
		in >> gpuModel;
		in >> obj.memory;
		in >> osType;
		in >> hdType;
		in >> obj.hdCapacity;
		in >> obj.price;
		in >> manuName;
		in >> obj.cpuCount;
		in >> obj.gpuCount;

		obj.osType = static_cast<OSType>(osType);
		obj.hdType = static_cast<HDType>(hdType);
		obj.cpu = new CPU(cpuBrand, cpuModel);
		obj.gpu = new GPU(gpuBrand, gpuModel);
		obj.manufacturer = new Manufacturer(manuName);

		return in;
	}


};

class StoreInventory 
{
private:
	vector<Laptop*> laptops;
	vector<Desktop*> desktops;
	vector<Server*> servers;


public:
	StoreInventory() 
	{
	}

	~StoreInventory()
	{
		cout << "memory freed" << endl;
	}

	void SaveInventoryItemsToFile() 
	{
		ofstream out("computers.txt");

		vector<Laptop*>::iterator lPtr;
		vector<Desktop*>::iterator dPtr;
		vector<Server*>::iterator sPtr;

		string laptopCount = to_string(laptops.size()) + "\n";
		out << laptopCount;
		for (lPtr = laptops.begin(); lPtr < laptops.end(); lPtr++)
		{
			out << (**lPtr);
		}

		string desktopCount = to_string(desktops.size())+ "\n";
		out << desktopCount;
		for (dPtr = desktops.begin(); dPtr < desktops.end(); dPtr++)
		{			
			out << (**dPtr);
		}

		string serverCount = to_string(servers.size()) + "\n";
		out << serverCount;
		for (sPtr = servers.begin(); sPtr < servers.end(); sPtr++)
		{
			out << (**sPtr);
		}

		out.close();
	}

	void ClearInventoryItems()
	{
		vector<Laptop*>::iterator lPtr;
		vector<Desktop*>::iterator dPtr;
		vector<Server*>::iterator sPtr;
		
		for(lPtr = laptops.begin(); lPtr < laptops.end(); lPtr++) 
		{
			delete *lPtr;
		}

		for (dPtr = desktops.begin(); dPtr < desktops.end(); dPtr++)
		{			
			delete *dPtr;
		}

		for (sPtr = servers.begin(); sPtr < servers.end(); sPtr++)
		{
			delete* sPtr;
		}
	}

	void AddALaptop(Laptop *laptop) 
	{
		laptops.insert(laptops.end(), laptop);
	}

	void AddADesktop(Desktop* desktop)
	{
		desktops.insert(desktops.end(), desktop);
	}

	void AddAServer(Server* server)
	{
		servers.insert(servers.end(), server);
	}

	bool RemoveAComputer(int id)
	{
		vector<Laptop*>::iterator lPtr;

		// Displaying vector elements using begin() and end() 
		for (lPtr = laptops.begin(); lPtr < laptops.end(); lPtr++)
		{
			if ((*lPtr)->GetID() == id)
			{
				laptops.erase(lPtr);
				return true;
			}
		}

		vector<Desktop*>::iterator dPtr;

		// Displaying vector elements using begin() and end() 
		for (dPtr = desktops.begin(); dPtr < desktops.end(); dPtr++)
		{
			if ((*dPtr)->GetID() == id)
			{
				desktops.erase(dPtr);
				return true;
			}
		}

		vector<Server*>::iterator sPtr;

		// Displaying vector elements using begin() and end() 
		for (sPtr = servers.begin(); sPtr < servers.end(); sPtr++)
		{
			if ((*sPtr)->GetID() == id)
			{
				servers.erase(sPtr);
				return true;
			}
		}

		return false;
	}

	int GetAvailableID()
	{
		vector<Laptop*>::iterator lPtr;
		vector<Desktop*>::iterator dPtr;
		vector<Server*>::iterator sPtr;
		int id = 0;
		bool isIDUnique;

		do
		{
			isIDUnique = true;
			for (lPtr = laptops.begin(); lPtr < laptops.end(); lPtr++)
			{
				if ((*lPtr)->GetID() == id)
				{
					isIDUnique = false;
					break;
				}
			}

			for (dPtr = desktops.begin(); dPtr < desktops.end(); dPtr++)
			{
				if ((*dPtr)->GetID() == id)
				{
					isIDUnique = false;
					break;
				}
			}

			for (sPtr = servers.begin(); sPtr < servers.end(); sPtr++)
			{
				if ((*sPtr)->GetID() == id)
				{
					isIDUnique = false;
					break;
				}
			}

			if (!isIDUnique) 
			{
				id++;
			}

		} while (!isIDUnique);

		return id;
	}

	void PrintRequestedComputersInfos(int type = -1, int id = -1, int minPrice = INT_MIN, int maxPrice = INT_MAX)
	{
		//Containers
		vector<Laptop*>::iterator lPtr;
		vector<Desktop*>::iterator dPtr;
		vector<Server*>::iterator sPtr;
		if (minPrice < 0 && maxPrice < 0 || minPrice > maxPrice) 
		{
			minPrice = INT_MIN;
			maxPrice = INT_MAX;
		}

		if (type == -1 || type == 1) 
		{		
			for (lPtr = laptops.begin(); lPtr < laptops.end(); lPtr++)
			{
				if (id == -1 || ((*lPtr)->GetID() == id))
				{
					if (((*lPtr)->GetPrice() > minPrice && (*lPtr)->GetPrice() < maxPrice))						
					{
						cout << (*lPtr)->GetDescription() << endl;
					}
				}
			}
		}
		if (type == -1 || type == 2)
		{
			for (dPtr = desktops.begin(); dPtr < desktops.end(); dPtr++)
			{
				if (id == -1 || ((*dPtr)->GetID() == id))
				{
					if ((*dPtr)->GetPrice() > minPrice && (*dPtr)->GetPrice() < maxPrice)
					{
						cout << (*dPtr)->GetDescription() << endl;
					}
				}			
			}
		}
		if (type == -1 || type == 3)
		{
			for (sPtr = servers.begin(); sPtr < servers.end(); sPtr++)
			{
				if (id == -1 || ((*sPtr)->GetID() == id))
				{
					if ((*sPtr)->GetPrice() > minPrice && (*sPtr)->GetPrice() < maxPrice) 
					{
						cout << (*sPtr)->GetDescription() << endl;
					}
				}
			}
		}
	}
	
	void PrintSpecificComputersInfo(int type, string manufacturerName = "", int screenSize = -1, int CPUCount = -1, int GPUCount = -1)
	{
		//Containers
		vector<Laptop*>::iterator lPtr;
		vector<Desktop*>::iterator dPtr;
		vector<Server*>::iterator sPtr;

		if (type == 1)
		{
			for (lPtr = laptops.begin(); lPtr < laptops.end(); lPtr++)
			{
				if (((*lPtr)->GetManufacturerName() == manufacturerName || manufacturerName == "") && 
					((static_cast<ScreenSize>(screenSize) == (*lPtr)->GetScreenSize() || screenSize == -1) &&
					((*lPtr)->GetCpuCount() == CPUCount || CPUCount == -1)) &&
					((*lPtr)->GetGpuCount() == GPUCount || GPUCount == -1))
				{			
					cout << (*lPtr)->GetDescription() << endl;						
				}
			}
		}
		else if (type == 2)
		{
			for (dPtr = desktops.begin(); dPtr < desktops.end(); dPtr++)
			{
				if (((*dPtr)->GetCpuCount() == CPUCount || CPUCount == -1) &&
					((*dPtr)->GetGpuCount() == GPUCount || GPUCount == -1))
				{
					cout << (*dPtr)->GetDescription() << endl;
				}
			}
		}
		else if (type == 3)
		{
			for (sPtr = servers.begin(); sPtr < servers.end(); sPtr++)
			{
				if (((*sPtr)->GetManufacturerName() == manufacturerName || manufacturerName == "") &&
					((*sPtr)->GetCpuCount() == CPUCount || CPUCount == -1) &&
					((*sPtr)->GetGpuCount() == GPUCount || GPUCount == -1))
				{
					cout << (*sPtr)->GetDescription() << endl;
				}
			}
		}
	}

	int GetLaptopCount() 
	{
		return laptops.size();
	}

	int GetDesktopCount()
	{
		return desktops.size();
	}

	int GetServerCount()
	{
		return servers.size();
	}

	int GetComputerCount() 
	{
		return laptops.size() + desktops.size() + servers.size();
	}

	void ListComputers()
	{
		for (Laptop* l : laptops) 
		{
			cout << l->GetDescription() << endl; 
		}
		for (Desktop* d : desktops)
		{
			cout << d->GetDescription() << endl;
		}
		for (Server* s : servers)
		{
			cout << s->GetDescription() << endl;
		}		
	}	
};

void DisplayAllComputers(StoreInventory* const inventory) 
{
	cout << "\nDisplaying all computers:" << endl;
	inventory->ListComputers();
}

void RemoveAComputer(StoreInventory* inventory) 
{
	int idToRemove;
	inventory->ListComputers();

	cout << "\nEnter an id to remove:" << endl;
	cin >> idToRemove;

	bool isSuccessfull = inventory->RemoveAComputer(idToRemove);
	if (isSuccessfull) 
	{
		cout << "Successfully deleted an item";
	}
	else 
	{
		cout << "id not found";
	}

}

void SearchAComputer(StoreInventory* const inventory)
{
	int type = -1;
	int id = -1;
	float minPrice;
	float maxPrice;

	cout << "Enter computer type = Laptop: 1, Desktop:2, Server 3 (Enter -1 for skip)" << endl;
	cin >> type;
	if (type == 0 || type < -1 || type > 3) 
	{
		type = -1;
	}

	cout << "Enter computer store ID: (Enter -1 for skip)" << endl;
	cin >> id;

	cout << "Enter minimum price (Enter -1 for skip)" << endl;
	cin >> minPrice;

	cout << "Enter maximum price (Enter -1 for skip)" << endl;
	cin >> maxPrice;

	if (minPrice < 0)
	{
		minPrice = INT_MIN;
	}
	if (maxPrice < 0) 
	{
		maxPrice = INT_MAX;
	}

	inventory->PrintRequestedComputersInfos(type, id, minPrice, maxPrice);
}

void SearchAComputerBySubtype(StoreInventory* const inventory)
{
	int type = -1;
	string manufacturerName;
	int screenSize = -1;
	int CPUCount = -1;
	int GPUCount = -1;

	cout << "Enter computer type = Laptop: 1, Desktop:2, Server 3" << endl;
	cin >> type;
	
	if (type < 1 || type > 3)
	{
		type = 1;
	}

	if (type == 1) 
	{
		cout << "Enter manufacturer name: (Enter none to skip)" << endl;
		cin >> manufacturerName;
		if (manufacturerName == "none") 
		{
			manufacturerName = "";
		}

		cout << "Enter Screen Size: 11.1inch: 1, 12inch: 2, 13.3inch: 3, 14inch: 4, 15.6inch: 5, 17.3inch: 6 (Enter -1 to skip)" << endl;
		cin >> screenSize;
		if (screenSize < 1 || screenSize > 6)
		{
			screenSize = -1;
		}
	}
	else if (type == 2)
	{
		cout << "Enter CPU Count (Max 2): (Enter -1 to skip)" << endl;
		cin >> CPUCount;

		cout << "Enter GPU Count (Max 2): (Enter -1 to skip)" << endl;
		cin >> GPUCount;
	}
	else if (type == 3) 
	{
		cout << "Enter manufacturer name: (Enter none to skip)" << endl;
		cin >> manufacturerName;
		if (manufacturerName == "none")
		{
			manufacturerName = "";
		}

		cout << "Enter CPU Count (Max 4): (Enter -1 to skip)" << endl;
		cin >> CPUCount;

		cout << "Enter GPU Count (Max 4): (Enter -1 to skip)" << endl;
		cin >> GPUCount;
	}

	inventory->PrintSpecificComputersInfo(type, manufacturerName, screenSize, CPUCount, GPUCount);
}

void AddAComputer(StoreInventory* inventory)
{
	bool isInvalid;
	int typeSelection = 0;
	string brand;
	string model;
	int memory;
	int osType;
	int hdType;
	int hdCapacity;
	double price;
	string manufacturerName;
	int cpuCount;
	int gpuCount;

	cout << "Enter memory (in GB)" << endl;
	cin >> memory;

	cout << "Enter Disk capacity (in GBs)" << endl;
	cin >> hdCapacity;
	cout << "Enter Price" << endl;
	cin >> price;

	do
	{
		cout << "Enter Operating System (Win: 1, Linux: 2, Mac: 3)" << endl;
		cin >> osType;
		cout << "Enter Hard Disk Type (SSD: 1, HDD: 2, SSHD: 3)" << endl;
		cin >> hdType;

		cout << "Enter the computer type:" << endl;
		cout << "1. Laptop" << endl;
		cout << "2. Desktop" << endl;
		cout << "3. Server" << endl;

		cin >> typeSelection;

		isInvalid = (typeSelection < '1' && typeSelection > '3') || (osType < '1' && osType > '3') || (hdType < '1' && hdType > '3');
		if (isInvalid)
		{
			cout << "Invalid OS Type / Hard Disk Type / Computer Type! Please try again." << endl;
		}
	} while (isInvalid);



	if (typeSelection == 1)
	{
		//Add a laptop
		int screenSize;

		cout << "Enter CPU Brand" << endl;
		cin >> brand;
		cout << "Enter CPU Model" << endl;
		cin >> model;

		CPU* cpu = new CPU(brand, model);

		cout << "Enter GPU Brand" << endl;
		cin >> brand;
		cout << "Enter GPU Model" << endl;
		cin >> model;

		GPU* gpu = new GPU(brand, model);


		cout << "Enter Laptop's Manufacturer Name:" << endl;
		cin >> manufacturerName;

		cout << "Enter Screen Size (11.1inch: 1, 12inch: 2, 13.3inch: 3, 14inch: 4, 15.6inch: 5, 17.3inch: 6)" << endl;
		cin >> screenSize;

		cpuCount = 1;
		gpuCount = 1;

		inventory->AddALaptop(new Laptop(inventory->GetAvailableID(), cpu, gpu, memory, static_cast<OSType>(osType), static_cast<HDType>(hdType), hdCapacity, price, new Manufacturer(manufacturerName), static_cast<ScreenSize>(screenSize), cpuCount, gpuCount));
		cout << "Added a Laptop:" << endl;
		cout << inventory->GetLaptopCount();
	}
	else if (typeSelection == 2)
	{
		//Add a Desktop			
		cout << "Enter CPU Brand" << endl;
		cin >> brand;
		cout << "Enter CPU Model" << endl;
		cin >> model;
		cout << "Enter CPU Price" << endl;
		cin >> price;

		CPU* cpu = new CPU(brand, model, price);

		cout << "Enter GPU Brand" << endl;
		cin >> brand;
		cout << "Enter GPU Model" << endl;
		cin >> model;
		cout << "Enter GPU Price" << endl;
		cin >> price;

		GPU* gpu = new GPU(brand, model, price);

		cout << "Enter CPU Count (Max 2)" << endl;
		cin >> cpuCount;
		cout << "Enter GPU Count (Max 2)" << endl;
		cin >> gpuCount;

		inventory->AddADesktop(new Desktop(inventory->GetAvailableID(), cpu, gpu, memory, static_cast<OSType>(osType), static_cast<HDType>(hdType), hdCapacity, price, cpuCount, gpuCount));
		cout << "Added a Desktop:" << endl;
		cout << inventory->GetDesktopCount();

	}
	else if (typeSelection == 3)
	{
		cout << "Enter CPU Brand" << endl;
		cin >> brand;
		cout << "Enter CPU Model" << endl;
		cin >> model;

		CPU* cpu = new CPU(brand, model);

		cout << "Enter GPU Brand" << endl;
		cin >> brand;
		cout << "Enter GPU Model" << endl;
		cin >> model;

		GPU* gpu = new GPU(brand, model);

		//Add a server	
		cout << "Enter Server's Manufacturer Name:" << endl;
		cin >> manufacturerName;
		
		cout << "Enter CPU Count (Max 4)" << endl;
		cin >> cpuCount;
		
		cout << "Enter GPU Count (Max 4):" << endl;
		cin >> gpuCount;


		inventory->AddAServer(new Server(inventory->GetAvailableID(), cpu, gpu, memory, static_cast<OSType>(osType), static_cast<HDType>(hdType), hdCapacity, price, new Manufacturer(manufacturerName), cpuCount, gpuCount));
		cout << "Added a Server:" << endl;
		cout << inventory->GetServerCount();
	}


}

void SaveInventoryItemsToFile(StoreInventory* inventory)
{
	inventory->SaveInventoryItemsToFile();
}

void ClearStoreInventory(StoreInventory* inventory)
{
	inventory->ClearInventoryItems();
	delete inventory;
}

void ReadInventoryItemsFromFile(StoreInventory* inventory)
{
	cout << "reading computers.txt" << endl;
	ifstream in("computers.txt");

	int itemAdded = 0;

	int laptopCount = 0;
	in >> laptopCount;
	for (int i = 0; i < laptopCount; i++)
	{
		Laptop* laptop = new Laptop();
		in >> *laptop;
		inventory->AddALaptop(laptop);
		itemAdded++;
	}

	int desktopCount = 0;
	in >> desktopCount;
	for (int i = 0; i < desktopCount; i++)
	{
		Desktop* desktop = new Desktop();
		in >> *desktop;
		inventory->AddADesktop(desktop);
		itemAdded++;
	}

	int serverCount = 0;
	in >> serverCount;
	for (int i = 0; i < serverCount; i++)
	{
		Server* server = new Server();
		in >> *server;
		inventory->AddAServer(server);
		itemAdded++;
	}

	cout << "(Added " << itemAdded << " item(s) to the inventory from computers.txt)" << endl;
}

int main()
{
	StoreInventory* inventory;
	inventory = new StoreInventory();
	//Read File & Fill Store Inventory

	ReadInventoryItemsFromFile(inventory);

	
	char menuSelection;
	bool isMenuInvalid;

	bool isExitCalled = false;
	while (!isExitCalled)
	{
		//Logic
		do
		{
			//Menu 
			cout << "\n\n\n\n---------------------------------" << endl;
			cout << "-Computer Store-" << endl;
			cout << "Main Menu" << endl;
			cout << "---------------------------------" << endl;
			cout << "1. Search computer by type, store ID or price range" << endl;
			cout << "2. Search computer subtypes by details" << endl;
			cout << "3. Display all computers" << endl;
			cout << "4. Add a computer" << endl;
			cout << "5. Remove a computer" << endl;
			cout << "6. Save & Exit" << endl;

			cout << "Enter menu selection(1-6):" << endl;
			cin >> menuSelection;

			isMenuInvalid = menuSelection < 49 && menuSelection > 54;
			if (isMenuInvalid)
			{
				cout << "Invalid Entry! Please try again" << endl;
			}
		} while (isMenuInvalid);


		switch (menuSelection)
		{
		case ('1'):
			SearchAComputer(inventory);
			EnterToContinue();
			break;
		case ('2'):
			SearchAComputerBySubtype(inventory);
			EnterToContinue();
			break;
		case ('3'):
			DisplayAllComputers(inventory);
			EnterToContinue();
			break;
		case ('4'):
			AddAComputer(inventory);
			EnterToContinue();
			break;
		case ('5'):
			RemoveAComputer(inventory);
			EnterToContinue();
			break;
		case ('6'):			
			isExitCalled = true;
			SaveInventoryItemsToFile(inventory);
			cout << "Successfully saved. Closing the program.." << endl;
			ClearStoreInventory(inventory);
			break;
		}
	}	

}

void EnterToContinue()
{
	cout << "\nPress enter to continue!";
	cin.clear(); //clears the stream
	cin.ignore(50, '\n'); //ignores next line(enter)
	cin.get(); //“cin>>” expects at least one char input, just enter doesn’t work    
}


