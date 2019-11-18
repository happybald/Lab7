#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <conio.h>
#include <ctime>
#include <windows.h>
#include <string>
using namespace std;


#define COLD_WATER 15
#define HOT_WATER 25
#define COM_POSL 150
#define ELECTRO 40


typedef chrono::system_clock Clock;


double fRand(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
};

class Termin {
public:
	int Tyear;
	int Tmonth;
	Termin() {
		this->Tyear = 2000 + rand() % 20 + 1;
		this->Tmonth = rand() % 12 + 1;
	}
	Termin(const Termin& right) {
		this->Tmonth = right.Tmonth;
		this->Tyear = right.Tyear;
	}
	void Show() {
		cout << "Year : " << this->Tyear << "\tMonth : " << this->Tmonth << endl;
	}
};

class Date {
public:
	int year;
	int month;
	int day;
	Date() {
		this->year = 2000 + rand() % 20 + 1;
		this->month = rand() % 12 + 1;
		this->day = rand() % 31 + 1;
	}
	Date(const Date& right) {
		this->day = right.day;
		this->month = right.month;
		this->year = right.year;
	}
	void Show() {
		cout << this->day << "." << this->month << "." << this->year << endl;
	}
};

class Human {
public:
	Date birhtday;
	char name[25];
	//	string name1;
	char surname[25];
	Human *getHuman() {
		return this;
	}
	Human() {
		char temp[25];
		if (rand() % 100 < 50) {
			ifstream names("lib/Mnames.txt");
			int count = rand() % 1219 + 1;
			for (int i = 0; i < count; i++) {
				names.getline(temp, 25, '\n');
			}
			strcpy(this->name, temp);
			//			name1 = temp;
			names.close();

		}
		else {
			ifstream names("lib/Fnames.txt");
			int count = rand() % 4275 + 1;
			for (int i = 0; i < count; i++) {
				names.getline(temp, 25, '\n');
			}
			strcpy(this->name, temp);
			names.close();
		}
		ifstream names("lib/Lnames.txt");
		int count = rand() % 88799 + 1;
		for (int i = 0; i < count; i++) {
			names.getline(temp, 25, '\n');
		}
		strcpy(this->surname, temp);
		names.close();
		this->birhtday.year = 1980 + rand() % 25;
		this->birhtday.month = rand() % 12 + 1;
		this->birhtday.day = rand() % 31 + 1;
	}
	Human(const Human& right) {
		strcpy(this->surname, right.surname);
		strcpy(this->name, right.name);
		this->birhtday.day = right.birhtday.day;
		this->birhtday.month = right.birhtday.month;
		this->birhtday.year = right.birhtday.year;

	}
	void Show() {
		cout << this->name << "\t" << this->surname << endl;
		cout << this->birhtday.day << "." << this->birhtday.month << "." << this->birhtday.year << endl;
	}
};

class Adress {
public:
	char street[25];
	int build;
	int flat;
	Adress() {
		char temp[25];
		ifstream streets("lib/streets.txt");
		int count = rand() % 6 + 1;
		for (int i = 0; i < count; i++) {
			streets.getline(temp, 25, '\n');
		}
		strcpy(this->street, temp);
		streets.close();
		this->build = rand() % 15 + 1;
		this->flat = rand() % 200 + 1;
	}
	Adress(const Adress& right) {
		strcpy(this->street, right.street);
		this->flat = right.flat;
		this->build = right.build;
	}
	void Show() {
		cout << this->street << ", " << this->build << "\t flat : " << this->flat << endl;
	}
};

class Habitant : public Human, public Adress {
public:
	Date pos;
	Habitant() {
		this->pos.year = 2000 + rand() % 15 + 1;
		this->pos.month = rand() % 12;
		this->pos.day = rand() % 31;
	};
	Habitant(const Habitant& right) {
		strcpy(this->surname, right.surname);
		strcpy(this->name, right.name);
		strcpy(this->street, right.street);
		this->birhtday.day = right.birhtday.day;
		this->birhtday.month = right.birhtday.month;
		this->birhtday.year = right.birhtday.year;
		this->pos.day = right.pos.day;
		this->pos.month = right.pos.month;
		this->pos.year = right.pos.year;
		this->flat = right.flat;
		this->build = right.build;
	}
	void Show() {
		cout << this->name << "\t" << this->surname << endl;
		cout << this->Human::birhtday.day << "." << this->Human::birhtday.month << "." << this->Human::birhtday.year << endl;
		cout << this->street << ", " << this->build << "\t flat : " << this->flat << endl;
		cout << "Pos date : " << this->pos.day << "." << this->pos.month << "." << this->pos.year << endl;
	}
};

class Price {
public:
	double ComPosl;
	double HolVod;
	double GarVod;
	double ElPost;
	Price() {
		this->ComPosl = COM_POSL;
		this->HolVod = COLD_WATER;
		this->GarVod = HOT_WATER;
		this->ElPost = ELECTRO;
	};
	Price(const Price& obj) {
		this->ComPosl = obj.ComPosl;
		this->HolVod = obj.HolVod;
		this->GarVod = obj.GarVod;
		this->ElPost = obj.ElPost;
	}
	void Show() {
		cout << "Com Posl = " << this->ComPosl << endl;
		cout << "Cold Water = " << this->HolVod << endl;
		cout << "Hot Water = " << this->GarVod << endl;
		cout << "Electro Posl = " << this->ElPost << endl;
	}
};

class FlatPay :public Habitant, public Price, public Termin {
public:
	double HolVodValue;
	double GarVodValue;
	double ElPostValue;
	double TotalPrice;
	Date date;
	FlatPay() {
		auto now = Clock::now();
		std::time_t now_c = Clock::to_time_t(now);
		struct tm* parts = std::localtime(&now_c);
		this->date.year = 1900 + parts->tm_year;
		this->date.month = 1 + parts->tm_mon;
		this->date.day = parts->tm_mday;
		this->Tyear = this->Habitant::pos.year + rand() % 10 + 1;
		this->Tmonth = rand() % 12 + 1;
		this->HolVodValue = fRand(0, 80);
		this->GarVodValue = fRand(0, 80);
		this->ElPostValue = fRand(0, 150);
		this->TotalPrice = (this->HolVodValue * this->HolVod + this->GarVodValue * this->GarVod + this->ElPostValue * this->ElPost + ComPosl);
	};

	FlatPay(const FlatPay& right) {
		this->Tyear = right.Tyear;
		this->Tmonth = right.Tmonth;
		this->date.year = right.date.year;
		this->date.day = right.date.day;
		this->date.month = right.date.month;
		strcpy(this->surname, right.surname);
		strcpy(this->name, right.name);
		strcpy(this->street, right.street);
		this->birhtday.day = right.birhtday.day;
		this->birhtday.month = right.birhtday.month;
		this->birhtday.year = right.birhtday.year;
		this->pos.day = right.pos.day;
		this->pos.month = right.pos.month;
		this->pos.year = right.pos.year;
		this->TotalPrice = right.TotalPrice;
		this->flat = right.flat;
		this->build = right.build;
		this->ElPostValue = right.ElPostValue;
		this->GarVodValue = right.GarVodValue;
		this->HolVodValue = right.HolVodValue;
	}

	void Show() {
		cout << fixed << setprecision(2) << setw(10) << "Name" << setw(15) << "Surname" << setw(15) << "Birthday" << setw(15) << "Pos Date" << endl;
		cout << setw(10) << this->name << setw(15) << this->surname << setw(10) << this->Human::birhtday.day << "." << this->Human::birhtday.month << "." << this->Human::birhtday.year << setw(8) << this->FlatPay::Habitant::pos.day << "." << this->FlatPay::Habitant::pos.month << "." << this->FlatPay::Habitant::pos.year << endl;
		cout << setw(15) << this->street << setw(5) << this->build << setw(5) << "  flat: " << this->flat << endl;
		cout << endl;
		cout << setw(2) << "Receipt From : " << setw(9) << this->FlatPay::Termin::Tmonth << "." << this->FlatPay::Termin::Tyear << endl;
		cout << setw(2) << "Cold Water : " << setw(15) << this->HolVodValue << " Mul " << this->HolVod << " = " << this->HolVod * this->HolVodValue << endl;
		cout << setw(2) << "Hot Water : " << setw(16) << this->GarVodValue << " Mul " << this->GarVod << " = " << this->GarVod * this->GarVodValue << endl;
		cout << setw(2) << "Electro : " << setw(18) << this->ElPostValue << " Mul " << this->ElPost << " = " << this->ElPost * this->ElPostValue << endl;
		cout << setw(2) << "ComPosl : " << setw(19) << this->ComPosl << endl;
		cout << setw(2) << "In Total : " << setw(19) << this->TotalPrice << endl;
		cout << setw(2) << "Today date : " << setw(14) << this->FlatPay::date.day << "." << this->FlatPay::date.month << "." << this->FlatPay::date.year << endl;
		for (int i = 0; i <= 60; i++) {
			cout << "-";
		}
		cout << endl << endl;
	};
	FlatPay& operator=(const FlatPay& right) {
		if (this == &right) {
			return *this;
		}
		this->Tyear = right.Tyear;
		this->Tmonth = right.Tmonth;
		this->date.year = right.date.year;
		this->date.day = right.date.day;
		this->date.month = right.date.month;
		strcpy(this->surname, right.surname);
		strcpy(this->name, right.name);
		strcpy(this->street, right.street);
		this->birhtday.day = right.birhtday.day;
		this->birhtday.month = right.birhtday.month;
		this->birhtday.year = right.birhtday.year;
		this->pos.day = right.pos.day;
		this->pos.month = right.pos.month;
		this->pos.year = right.pos.year;
		this->TotalPrice = right.TotalPrice;
		this->flat = right.flat;
		this->build = right.build;
		this->ElPostValue = right.ElPostValue;
		this->GarVodValue = right.GarVodValue;
		this->HolVodValue = right.HolVodValue;
		//this->name1 = right.name1;
		return *this;
	}
	void ShowName() {
		cout << this->name << endl;
	}
	/*void ShowName1() {
		cout << this->name1 << endl;
	}*/
};

class MainCost {
private:
	int size;
	double TotalCost = 0;
public:
	FlatPay* list;
	MainCost() {
		this->size = 0;
		this->TotalCost = 0;
		this->list = NULL;
	}
	MainCost(const MainCost& obj) {
		this->size = obj.size;
		TotalCost = obj.TotalCost;
		this->list = new FlatPay[this->size];
		for (int i = 0; i < this->size; i++) {
			this->list[i] = obj.list[i];
		}
	}
	double GetTotalCost() {
		return TotalCost;
	}
	int getSize() {
		return size;
	}
	FlatPay* getFlatPayList() {
		return list;
	}
	MainCost(int size) {
		this->size = size;
		this->list = new FlatPay[this->size];
		for (int i = 0; i < this->size; i++) {
			this->TotalCost += (this->list + i)->TotalPrice;
		}
	};

	FlatPay& operator [](int index)
	{
		if (index < 0 || index > size)
		{
			cout << "Error!" << endl;
			_getch();
			exit(1);
		}
		return list[index];
	};

	template <typename T1, typename FlatPay>
	T1 AvgGarmonichne(T1 amount, FlatPay* arr)
	{
		double sum = 0;
		for (int i = 0; i < amount; i++)
		{
			sum += 1 / arr[i].TotalPrice;
		}
		return amount / sum;
	};
	void Sortchar() {
		FlatPay* temp = new FlatPay();
		for (int i = 0; i < this->getSize() - 1; i++) {
			for (int j = i + 1; j < this->getSize(); j++) {
				if (strcmp(this->list[i].name, this->list[j].name) > 0)
				{
					*temp = this->list[i];
					this->list[i] = this->list[j];
					this->list[j] = *temp;
				}
			}
		}
	}
	/*void Sortstr() {
		FlatPay* temp = new FlatPay();
		for (int i = 0; i < this->getSize() - 1; i++) {
			for (int j = i + 1; j < this->getSize(); j++) {
				if (this->list[i].name1.compare(this->list[j].name1) > 0) {
					*temp = this->list[i];
					this->list[i] = this->list[j];
					this->list[j] = *temp;
				}
			}
		}
	}*/


	friend ostream& operator<< (ostream& out, MainCost& point);
};
ostream& operator<< (ostream& out, MainCost& point) {
	out << "Total Price : " << point.GetTotalCost() << endl;
	return out;
}

template<typename TT>
class TEMP {
private:
	TT Temp;
public:
	TEMP(TT temp) :Temp(temp)
	{ }
	TT getTemp() {
		return Temp;
	}
};

int main() {
	srand(time(NULL));
	int ind;
	Human* pointer = new Human();
	MainCost* ptr = new MainCost();
	MainCost Main(2);
	do {
		cout << "1. Show all FlatPays;" << endl;
		cin >> ind;
		switch (ind)
		{
		case 1: {
			system("cls");
			for (int i = 0; i < Main.getSize(); i++) {
				Main[i].Show();
			}
			//double total = Main.AvgGarmonichne((double)Main.getSize(), Main.getFlatPayList());
			//cout << total << endl;
			break;
		}
		case 2: {
			unsigned int start_time = clock();
			Main.Sortchar();
			unsigned int end_time = clock();
			unsigned int search_time = end_time - start_time;
			cout << "Char time : " << search_time << endl;
			break;
		}
		case 3: {
			TEMP<MainCost>* tempclass = new TEMP<MainCost>(Main);
			*ptr = tempclass->getTemp();
			delete tempclass;
			for (int i = 0; i < ptr->getSize(); i++) {
				ptr->list[i].Show();
			}
			break;
		}
		case 4: {
			TEMP<Human>* tmpcl = new TEMP<Human>(*Main.list[0].getHuman());
			*pointer = tmpcl->getTemp();
			delete tmpcl;
			pointer->Show();
			break;
		}
		default:
			exit(0);
			break;
		}
	} while (true);
	system("pause");
	return 0;
}