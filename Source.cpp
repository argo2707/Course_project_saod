#include <istream>
#include <string> 
#include <cstdlib>
#include <stdio.h>
#include <ctime>
#include <time.h>
#include "windows.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <string.h>
#include <regex>
#include <map>
#include <iomanip> 

using namespace std;

struct reader
{
	reader* pnext=NULL;
	string nombtick = ""; //номер билета
	string fio=""; //фио
	int yearbirt = 0; //год рождения
	string adres=""; //адрес 
	string place=""; // место работы/учебы
	string ciph[20];
	void add(int numb)
	{
		cin.clear();
		cin.get();
		cout << "Введите ФИО: ";
		getline(cin,fio);
		while (true)
		{
			int i;
			for (i = 0; i < fio.length(); i++)
			{
				if (!((fio[i] >= 'А' && fio[i] <= 'Я') || (fio[i] >= 'а' && fio[i] <= 'я') || (fio[i] == ' ')))
				{
					cout << "Введите ФИО русским алфавитом без символов\n";
					getline(cin, fio);
					break;
				}					
			}
			if (i == fio.length())
				break;
		}
		cout << "Введите год рождения: ";
		cin >> yearbirt;
		while (!(yearbirt<=2007 && yearbirt >= 1900))
		{
			cout << "Введите год рождения правильно (пример: 2001)!\n";
			cout << "Замечание! Выдаем книги лицам с 14 лет.\n";
			cin >> yearbirt;
		}
		cin.get();
		cout << "Введите адрес: ";
		getline(cin, adres);
		while (true)
		{
			int i;
			for (i = 0; i < adres.length(); i++)
			{
				if (!((adres[i] >= 'А' && adres[i] <= 'Я') || (adres[i] >= 'а' && adres[i] <= 'я') || (adres[i] == ' ')
					|| (adres[i] == ',') || (adres[i] == '.') || (adres[i] == '-') || (adres[i] >= '0' && adres[i] <= '9')))
				{
					cin.get();
					cout << "Введите адрес русским алфавитом и цифрами(символы для ввода: -., )\n";
					getline(cin, adres);
					break;
				}
			}
			if (i == adres.length())
				break;
		}
		cout << "Введите место работы: ";
		cin.get();
		getline(cin, place);
		while (true)
		{
			int i;
			for (i = 0; i < place.length(); i++)
			{
				if (!((place[i] >= 'А' && place[i] <= 'Я') || (place[i] >= 'а' && place[i] <= 'я') || (place[i] == ' ')
					|| (place[i] == ',') || (place[i] == '.') || (place[i] == '-') || (place[i] >= '0' && place[i] <= '9')))
				{
					cin.get();
					cout << "Введите место работы русским алфавитом и цифрами(символы для ввода: -., )\n";
					getline(cin, place);
					break;
				}
			}
			if (i == place.length())
				break;
		}
		cout << "Введите А – только абонемент, Ч – только читальный зал, В – читальный зал и абонемент: ";
		cin >> nombtick;
		while (!(nombtick == "А" || nombtick == "Ч" || nombtick == "В"))
		{
			cout << "Введите А – только абонемент, Ч – только читальный зал, В – читальный зал и абонемент\n";
			cin >> nombtick;
		}
		nombtick += "000";
		nombtick += to_string(numb);
		nombtick += "-21";
		cout << "Пользователь:" << nombtick;
		cout << "\nУспешно добавлен" <<endl;
		cin.clear();
	}
};

struct book
{
	string cipher; //шифр
	string author; //автор
	string title; //название
	string publicHouse; //издательство
	int yearpubl; //год издания
	int quantitotal; //кол-во всего
	int quantiavailab; //в наличии
	int height = 1; //высота узла АВЛ-дерева
	book* left = NULL;//указатель на левое поддерево
	book* right = NULL;//указатель на правое поддерево
};

struct hesh
{
	const int segm = 10;
	int key = 1;
	reader** heshtable = new reader*[segm];
	hesh()
	{
		for (int i = 0; i < segm; i++)
		{
			heshtable[i] = NULL;
		}
	}

};

struct issrec
{
	string nombtick;
	string cipher;
	string dateis="";
	string dateret="";
	issrec* pnext1=NULL;
	issrec* pnext3 = NULL;
};

int convertBookCode(string bookCode);
void menu();
hesh myhesh; //хеш-таблица
book* listbook; //данные о книге
issrec* lib; // данные овыдаче и возврате

int heshir(string keystri)
{
		int keyint = 0;
		keyint = ((int)keystri[7] * (int)keystri[2] + (int)keystri[0] * (int)keystri[3] +
			(int)keystri[3] * (int)keystri[4] + (int)keystri[1] * (int)keystri[5] +
			(int)keystri[3] * (int)keystri[5] + (int)keystri[6] * (int)keystri[2]+(int)keystri[5] * (int)keystri[0]) % myhesh.segm;
		return keyint;
}

void addread()
{
		reader* tempi;
		reader* tempread;
		tempi = new reader;
		tempread = tempi;
		tempi->add(myhesh.key);
		myhesh.key += 1;
		int tempint = heshir(tempi->nombtick);
		if (myhesh.heshtable[tempint] == NULL)
		{
			myhesh.heshtable[tempint] = tempi;
		}
		else
		{
			if(myhesh.heshtable[tempint]->pnext==nullptr)
				myhesh.heshtable[tempint]->pnext = tempi;
			else 
			{
				tempread = myhesh.heshtable[tempint];
				do
				{
					tempread = tempread->pnext;
					if (tempread->pnext == nullptr)
					{
						tempread->pnext = tempi;
						break;
					}
				} while (tempread->pnext != nullptr);
			}
		}
		for (int i = 0; i < myhesh.segm; i++)
		{
			if (myhesh.heshtable[i] == NULL)
				cout << "[" << i << "]" << " - " << endl;
			else
				if (myhesh.heshtable[i]->pnext == NULL)
					cout << "[" << i << "]" << " - " << myhesh.heshtable[i]->nombtick << endl;
				else
				{
					tempi = myhesh.heshtable[i];
					cout << "[" << i << "]" << " - " <<tempi->nombtick;
					do
					{
						tempi = tempi->pnext;
						cout << " -> " << tempi->nombtick;
						
					} while (tempi->pnext != NULL);
					cout << endl;
				}
		}
		cout << "1 - Вернуться в меню\n";
		cout << "2 - Добавить ещё\n";
		int temp;
		cin >> temp;
		switch (temp)
		{
		case 1:
			system("cls");
			menu();
			break;
		case 2:
			system("cls");
			addread();
			break;
		default:
			system("cls");
			cout << "1 - Вернуться в меню\n";
			cout << "2 - Добавить ещё\n";
			int temp;
			cin >> temp;
			switch (temp)
			{
			case 1:
				system("cls");
				menu();
				break;
			case 2:
				system("cls");
				addread();
				break;
			default:
				system("cls");
				break;
			}
			break;
		}
}

void viewing()
{
	reader* tempi;
	int acc=0;
	for (int i = 0; i < myhesh.segm; i++)
	{
		if (myhesh.heshtable[i] != NULL)
		{
			if (myhesh.heshtable[i]->pnext == NULL)
			{
				acc++;
				cout << acc << " - " << myhesh.heshtable[i]->nombtick << "\nФИО: " << myhesh.heshtable[i]->fio << "\nГод рождения: " << myhesh.heshtable[i]->yearbirt << endl;
				
			}
			else
			{
				acc++;
				tempi = myhesh.heshtable[i];
				cout << acc << " - " << tempi->nombtick << "\nФИО: " << tempi->fio << "\nГод рождения: " << tempi->yearbirt << endl;
				
				do
				{
					acc++;
					tempi = tempi->pnext;
					cout << acc << " - " << tempi->nombtick << "\nФИО: " << tempi->fio << "\nГод рождения: " << tempi->yearbirt << endl;
				} while (tempi->pnext != NULL);
				cout << endl;
				
			}
		}
	}
	cout << "0 - Вернуться в меню\n";
	int temp;
	cin >> temp;
	switch (temp)
	{
	case 0:
		system("cls");
		menu();
		break;
	default:
		system("cls");
		cout << "0 - Вернуться в меню\n";
		int temp;
		cin >> temp;
		switch (temp)
		{
		case 0:
			menu();
			break;
		}
		break;
	}
}

reader* searchnom()
{
	issrec* templib;
	reader* tempi;
	string nom;
	int k = -1;
	cin.get();
	cout << "Введите номер читательского билета: ";
	getline(cin,nom);
	for (int i = 0; i < myhesh.segm; i++)
	{
		if (myhesh.heshtable[i] != NULL)
		{
			if (myhesh.heshtable[i]->pnext == NULL)
			{
				if (nom == myhesh.heshtable[i]->nombtick)
				{
					cout << myhesh.heshtable[i]->nombtick << endl;
					cout << myhesh.heshtable[i]->fio << endl;
					cout << myhesh.heshtable[i]->adres << endl;
					cout << myhesh.heshtable[i]->yearbirt << endl;
					cout << myhesh.heshtable[i]->place << endl;
					cout << "Книги: " << endl;
					templib = lib;
					while (templib != NULL)
					{
						if ((templib->nombtick == myhesh.heshtable[i]->nombtick) && (templib->dateret == ""))
							cout << templib->cipher << endl;
						templib = templib->pnext3;
					}
					k = 0;
					return myhesh.heshtable[i];
				}
			}
			else
			{
				tempi = myhesh.heshtable[i];
				if (nom == tempi->nombtick)
				{
					cout << tempi->nombtick << endl;
					cout << tempi->fio << endl;
					cout << tempi->adres << endl;
					cout << tempi->yearbirt << endl;
					cout << tempi->place << endl;
					cout << "Книги: " << endl;
					templib = lib;
					while (templib != NULL)
					{
						if ((templib->nombtick == tempi->nombtick) && (templib->dateret == ""))
							cout << templib->cipher << endl;
						templib = templib->pnext3;
					}
					k = 0;
					return myhesh.heshtable[i];
				}
				do
				{
					tempi = tempi->pnext;
					if (nom == tempi->nombtick)
					{
						cout << tempi->nombtick << endl;
						cout << tempi->fio << endl;
						cout << tempi->adres << endl;
						cout << tempi->yearbirt << endl;
						cout << tempi->place << endl;
						cout << "Книги: " << endl;
						templib = lib;
						while (templib != NULL)
						{
							if ((templib->nombtick == tempi->nombtick) && (templib->dateret == ""))
								cout << templib->cipher << endl;
							templib = templib->pnext3;
						}
						k = 0;
						return tempi;
					}
				} while (tempi->pnext != NULL);
			}
		}
	}
	if (k == -1)
	{
		cout << "Не найдено!\n";
		return NULL;
	}
	return 0;
}

void searchfio()
{
	reader* tempi;
	string tfio;
	int k = -1;
	cin.get();
	cout << "Введите ФИО" << endl;
	getline(cin, tfio);
	for (int i = 0; i < myhesh.segm; i++)
	{
		if (myhesh.heshtable[i] != NULL)
		{
			if (myhesh.heshtable[i]->pnext == NULL)
			{
				if (myhesh.heshtable[i]->fio.find(tfio) != string::npos )
				{
					cout << myhesh.heshtable[i]->nombtick << endl;
					cout << myhesh.heshtable[i]->fio << endl;
					cout << endl;
					k = 0;
				}
			}
			else
			{
				tempi = myhesh.heshtable[i];
				if (tempi->fio.find(tfio) != string::npos)
				{
					cout << tempi->nombtick << endl;
					cout << tempi->fio << endl;
					cout << endl;
					k = 0;
				}
				do
				{
					tempi = tempi->pnext;
					if (tempi->fio.find(tfio) != string::npos)
					{
						cout << tempi->nombtick << endl;
						cout << tempi->fio << endl;
						cout << endl;
						k = 0;
					}
				} while (tempi->pnext != NULL);
			}
		}
	}
	if (k == -1)
	{
		cout << "Не найдено!\n";
	}
	cout << "0 - Вернуться в меню\n";
	int temp;
	cin >> temp;
	switch (temp)
	{
	case 0:
		system("cls");
		menu();
		break;
	default:
		system("cls");
		cout << "0 - Вернуться в меню\n";
		int temp;
		cin >> temp;
		switch (temp)
		{
		case 0:
			menu();
			break;
		}
		break;
	}
}

void takeoff()
{
	issrec* templib=lib;
	reader* tempi=NULL;
	reader* tempi2=NULL;
	reader* del=NULL;
	string nom="";
	int delnom=-1,k=0;
	cin.get();
	cout << "Введите номер читательского билета для снятия с учета" << endl;
	getline(cin, nom);
	for (int i = 0; i < myhesh.segm; i++)
	{
		if (myhesh.heshtable[i] != NULL)
		{
			if (myhesh.heshtable[i]->pnext == NULL)
			{
				if (nom == myhesh.heshtable[i]->nombtick)
				{
					del = myhesh.heshtable[i];
					delnom = i;
					break;
				}
			}
			else
			{
				tempi = myhesh.heshtable[i];
				if (nom == tempi->nombtick)
				{
					del = tempi;
					delnom = i;
					break;
				}
				do
				{
					tempi = tempi->pnext;
					if (nom == tempi->nombtick)
					{
						del = tempi;
						delnom = i;
						break;
					}
				} while (tempi->pnext != NULL);
			}
		}
	}
	if (delnom == -1)
		cout << "Не найдено" << endl;
	else
	{
		while (templib != NULL)
		{
			if ((templib->nombtick == del->nombtick) && (templib->dateret == ""))
				k++;
			templib = templib->pnext3;
		}
		if (k > 0)
			cout << "У читателя есть несданные книги, удаление невозможно!" << endl;
		else
		{
			if (myhesh.heshtable[delnom]->pnext == NULL)
			{
				myhesh.heshtable[delnom] = NULL;
			}
			else
			{
				tempi = myhesh.heshtable[delnom];
				if (nom == tempi->nombtick)
				{
					myhesh.heshtable[delnom] = myhesh.heshtable[delnom]->pnext;
				}
				do
				{
					tempi2 = tempi->pnext;
					if ((tempi2->pnext != nullptr) && (tempi2->nombtick == nom))
					{
						tempi->pnext = tempi2->pnext;
						break;
					}
					if ((tempi2->pnext == nullptr) && (tempi2->nombtick == nom))
					{
						tempi->pnext = NULL;
						break;
					}
					tempi = tempi->pnext;
				} while (tempi->pnext != NULL);
			}
			cout << "Читатель " << nom << " успешно удален!" << endl;
		}
	}
	cout << "0 - Вернуться в меню\n";
	int temp;
	cin >> temp;
	switch (temp)
	{
	case 0:
		system("cls");
		menu();
		break;
	default:
		system("cls");
		cout << "0 - Вернуться в меню\n";
		int temp;
		cin >> temp;
		switch (temp)
		{
		case 0:
			menu();
			break;
		}
		break;
	}
}

void cleanreader()
{
	issrec* templib;
	reader* tempi;
	reader* tempi2;
	int k = 0;
	system("cls");
	cout << "Список читателей с несданными книгами" << endl;
	for (int i = 0; i < myhesh.segm; i++)
	{
		if (myhesh.heshtable[i] != NULL)
		{
			if (myhesh.heshtable[i]->pnext == NULL)
			{
				k = 0;
				templib = lib;
				while (templib != NULL)
				{
					if ((templib->nombtick == myhesh.heshtable[i]->nombtick) && (templib->dateret == ""))
						k++;
					templib = templib->pnext3;
				}
				if (k>0)
				{
					cout << myhesh.heshtable[i]->fio << endl;
					cout << endl;
				}
				else
					myhesh.heshtable[i] = NULL;
			}
			else
			{
				tempi = myhesh.heshtable[i];
				k = 0;
				templib = lib;
				while (templib != NULL)
				{
					if ((templib->nombtick == myhesh.heshtable[i]->nombtick) && (templib->dateret == ""))
						k++;
					templib = templib->pnext3;
				}
				if (k>0)
				{
					cout << myhesh.heshtable[i]->fio << endl;
					cout << endl;
				}
				else
					myhesh.heshtable[i] = myhesh.heshtable[i]->pnext;
				do
				{
					tempi2 = tempi->pnext;
					if (tempi2->pnext != nullptr)
					{
						k = 0;
						templib = lib;
						while (templib != NULL)
						{
							if ((templib->nombtick == tempi->nombtick) && (templib->dateret == ""))
								k++;
							templib = templib->pnext3;
						}
						if (k > 0)
						{
							cout << tempi->fio << endl;
							cout  << endl;
						}
						else
						{
							tempi->pnext = tempi2->pnext;
							break;
						}
					}
					if (tempi2->pnext == nullptr) 
					{
						k = 0;
						templib = lib;
						while (templib != NULL)
						{
							if ((templib->nombtick == tempi->nombtick) && (templib->dateret == ""))
								k++;
							templib = templib->pnext3;
						}
						if (k > 0)
						{
							cout << tempi->fio << endl;
						}
						else
						{
							tempi->pnext = NULL;
							break;
						}
					}
					tempi = tempi->pnext;
				} while (tempi->pnext != NULL);
			}
		}
	}
	cout << "0 - Вернуться в меню\n";
	int temp;
	cin >> temp;
	switch (temp)
	{
	case 0:
		system("cls");
		menu();
		break;
	default:
		system("cls");
		cout << "0 - Вернуться в меню\n";
		int temp;
		cin >> temp;
		switch (temp)
		{
		case 0:
			menu();
			break;
		}
		break;
	}
}

int acc=0;//кол-во книг
	// Получение параметра высоты узла  
short height(book * p)
{
		if (p != NULL)
		{
			return p->height;
		}
		    else return 0;
}

// Вычисление баланс-фактора для балансировки дерева  
short balanceFactor(book* p)
{
	return height(p->right) - height(p->left);
}

	// Подсчёт высоты узла  
void calcHeight(book* p)
{
	short heightLeft = height(p->left);
	short heightRight = height(p->right);
	if (heightLeft > heightRight) {
		p->height = heightLeft + 1;

	}
	else p->height = heightRight + 1;
}

	// Поворот вправо, если баланс-фактор = 2  
book* rotateright(book* p) // правый поворот вокруг p  
{
	book* q = p->left;
	p->left = q->right;
	q->right = p;
	calcHeight(p);
	calcHeight(q);
	return q;
}
	// Поворот влево, если баланс-фактор = -2  
book* rotateleft(book* q) // левый поворот вокруг q  
{
	book* p = q->right;
	q->right = p->left;
	p->left = q;
	calcHeight(q);
	calcHeight(p);
	return p;
}

	// Балансировка дерева (для функций добавления и удаления)  
book* balance(book* p)
{
	calcHeight(p);
	if (balanceFactor(p) == 2)
	{
		if (balanceFactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (balanceFactor(p) == -2)
	{
		if (balanceFactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; // баланс не нужен  
}

//добавление в авл
book* insert(book* p, string cipher, string author, string title,string publishHouse, int yearpubl, int quantitotal, int quantiavailab)
{
	if (p==NULL)
	{
		book* newNode = new book;
		newNode->cipher = cipher;
		newNode->author = author;
		newNode->title = title;
		newNode->publicHouse = publishHouse;
		newNode->yearpubl = yearpubl;
		newNode->quantitotal = quantitotal;
		newNode->quantiavailab = quantiavailab;
		return newNode;
	}
	if (convertBookCode(cipher) < convertBookCode(p->cipher))
	{
		p->left = insert(p->left, cipher, author, title, publishHouse, yearpubl, quantitotal, quantiavailab);
	}
	else if (convertBookCode(cipher) > convertBookCode(p->cipher))
	{
		p->right = insert(p->right, cipher, author, title, publishHouse, yearpubl, quantitotal, quantiavailab);
	}
	else 
	{
		cout << "Данный ключ уже существует!\n";
		return p;
	}
	return balance(p);
}

// Блок для поиска 
book* searchNode(book* p, string cipher, int count = 0)
{
	if (p == NULL)
	{
		return 0;

	}
	else if (convertBookCode(p->cipher) == convertBookCode(cipher)) {
		cout << p->title << endl;
		cout << "   Автор: " << p->author << endl;
		cout << "   Шифр книги: " << p->cipher << endl;
		cout << "   Издатель: " << p->publicHouse << endl;
		cout << "   Год издания: " << p->yearpubl << endl;
		cout << "   Всего: " << p->quantitotal << endl;
		cout << "   В наличии: " << p->quantiavailab << endl << endl;
		return p;
	}
	if (convertBookCode(cipher) < convertBookCode(p->cipher)) {
		p=searchNode(p->left, cipher, count);
	}
	else {  
		p=searchNode(p->right, cipher, count);
	}
	return p;
}


int convertBookCode(string bookCode)
{
	string result;
	result = bookCode.substr(0, 3) + bookCode.substr(4, 3);
	return stoi(result);
}

// Обратный симметричный обход  
void printTree(book * root) 
{
	if (root == NULL)
		return;
	if (root != NULL) {
		printTree(root->left);

		cout << root->title << endl;
		cout << "   Автор: " << root->author << endl;
		cout << "   Шифр книги: " << root->cipher << endl;
		cout << "   Издатель: " << root->publicHouse << endl;
		cout << "   Год издания: " << root->yearpubl << endl;
		cout << "   Всего: " << root->quantitotal << endl;
		cout << "   В наличии: " << root->quantiavailab << endl << endl;

		printTree(root->right);

	}
}
// Вывод симметрично-обойдённго дерева  
void inorderPrint(book* root)
{
	if (root == NULL) {
		return;
	}

	inorderPrint(root->left);

	cout << root->cipher << "[" << root->title << "] "; // DATA  

	inorderPrint(root->right);
}

void addbook()
{
	string cipher; //шифр
	string author; //автор
	string title; //название
	string publicHouse; //издательство
	int yearpubl; //год издания
	int quantitotal; //кол-во всего
	int quantiavailab; //в наличии
	cin.clear();
	cin.get();
	cout << "Введите Автора(ов) через пробел: ";
	getline(cin, author);
	while (true)
	{
		int i;
		for (i = 0; i < author.length(); i++)
		{
			if (!((author[i] >= 'А' && author[i] <= 'Я') || (author[i] >= 'а' && author[i] <= 'я')
				|| (author[i] == ' ') || (author[i] == '.')))
			{
				cout << "Введите Автора(ов) русским алфавитом без запятых\n";
				getline(cin, author);
				break;
			}
		}
		if (i == author.length())
			break;
	}
	cout << "Введите название книги: ";
	getline(cin, title);
	while (true)
	{
		int i;
		for (i = 0; i < title.length(); i++)
		{
			if (!((title[i] >= 'А' && title[i] <= 'Я') || (title[i] >= 'а' && title[i] <= 'я') || (title[i] == ' ')
				|| (title[i] == ',') || (title[i] == '.') || (title[i] == '-') || (title[i] >= '0' && title[i] <= '9')))
			{
				cin.get();
				cout << "Введите название книги русским алфавитом и цифрами(символы для ввода: -., )\n";
				getline(cin, title);
				break;
			}
		}
		if (i == title.length())
			break;
	}
	cout << "Введите издательство: ";
	getline(cin, publicHouse);
	while (true)
	{
		int i;
		for (i = 0; i < publicHouse.length(); i++)
		{
			if (!((publicHouse[i] >= 'А' && publicHouse[i] <= 'Я') || (publicHouse[i] >= 'а' && publicHouse[i] <= 'я') || (publicHouse[i] == ' ')
				|| (publicHouse[i] == ',') || (publicHouse[i] == '.') || (publicHouse[i] == '-') || (publicHouse[i] >= '0' && publicHouse[i] <= '9')))
			{
				cin.get();
				cout << "Введите издательство книги русским алфавитом и цифрами(символы для ввода: -., )\n";
				getline(cin, publicHouse);
				break;
			}
		}
		if (i == publicHouse.length())
			break;
	}
	cout << "Введите год издания: ";
	cin >> yearpubl;
	while (!(yearpubl <=2021 && yearpubl >= 1457))
	{
		cout << "Введите год издания правильно (пример: 2001)!\n";
		cin >> yearpubl;
	}
	cin.get();
	cout << "Введите количество экземпляров: ";
	cin >> quantitotal;
	while (!(quantitotal >= 1))
	{
		cout << "Введите количество экземпляров больше 0!\n";
		cin >> quantitotal;
	}
	quantiavailab = quantitotal;
	acc++;
	
	cipher = "00" + to_string(rand()%9+1)+".";
	if (acc<10)
		cipher += "00" + to_string(acc);
	if (acc >= 10 && acc <= 99)
		cipher += "0" + to_string(acc);
	cout << "Книга:" << cipher;
	cout << "\nУспешно добавлен" << endl;
	listbook=insert(listbook, cipher, author, title, publicHouse, yearpubl, quantitotal, quantiavailab);
	cout << "1 - Вернуться в меню\n";
	cout << "2 - Добавить ещё\n";
	int temp;
	cin >> temp;
	switch (temp)
	{
	case 1:
		system("cls");
		menu();
		break;
	case 2:
		system("cls");
		addbook();
		break;
	default:
		system("cls");
		cout << "1 - Вернуться в меню\n";
		cout << "2 - Добавить ещё\n";
		int temp;
		cin >> temp;
		switch (temp)
		{
		case 1:
			system("cls");
			menu();
			break;
		case 2:
			system("cls");
			addbook();
			break;
		default:
			system("cls");
			break;
		}
		break;
	}
}

book* findMin(book* p)
{
	if (p->left != NULL) {
		return findMin(p->left);
	}
	else return p;
}

book* removemin(book* p)
{
	if (p->left == NULL)
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

book* deleteNode(book* p, string cipher)
{
	if (p == NULL) {
		cout << "Данного ключа нет в дереве!\n";
		return 0;

	}
	if (convertBookCode(cipher) < convertBookCode(p->cipher))
		p->left = deleteNode(p->left, cipher);
	else if (convertBookCode(cipher) > convertBookCode(p->cipher))
		p->right = deleteNode(p->right, cipher);
	else
	{
		if (p->quantiavailab == p->quantitotal)
		{
			book* q = p->left;
			book* r = p->right;
			delete p;
			if (r == NULL)
			{
				acc--;
				return q;
			}
			book* min = findMin(r);
			min->right = removemin(r);
			min->left = q;
			acc--;
			cout << "Книга " << cipher << " успешно удалена!" << endl;
			return balance(min);
		}
		else
		{
			cout << "Книга " << cipher << " не может быть удалена!" << endl;
			cout << "Не все экземпляры книг в наличии!" << endl;
		}
	}
	return balance(p);
}

book* tempbook;
book* deleteTree(book* p) {
	if (p == NULL)
		return 0;

	/* first delete both subtrees */
	deleteTree(p->left);
	deleteTree(p->right);

	/* then delete the node */
	if (p->quantiavailab == p->quantitotal)
		deleteNode(p, p->cipher);
	else
	{
		//tempbook = insert(tempbook, p->cipher, p->author, p->title, p->publicHouse, p->yearpubl, p->quantitotal, p->quantiavailab);
		cout << "Книга " << p->cipher << " не может быть удалена!" << endl;
		cout << "Не все экземпляры книг в наличии!" << endl;
	}
}

issrec* sorting(issrec* p);

//в списке авторов ищем по имени
bool searchWord(string source, string find)
{
	int sourceLen = source.size();
	int templateLen = find.size();
	if (templateLen > sourceLen) {
		return false;
	}

	std::map<char, int> offsetTable;
	for (int i = 0; i < templateLen - 1; i++) {
		offsetTable.insert(std::pair<char, int>(static_cast<char>(find[i]), templateLen - i - 1));
	}
	for (int i = 0; i <= 255; i++) {
		offsetTable.insert(std::make_pair(static_cast<char>(i), templateLen));
	}
	int i = templateLen - 1;
	int j = i;
	int k = i;
	while (j >= 0 && i <= sourceLen - 1) {
		j = templateLen - 1;
		k = i;
		while (j >= 0 && source[k] == find[j]) {
			k--;
			j--;
		}
		i += offsetTable.at(source[i]);
	}
	if (k >= sourceLen - templateLen) {
		return false;
	}
	else {
		return true;
	}
}

int search(book*p,string fio,int count=0)
{
	
	if (p == NULL)
	{
		return count;
	}
	else if (searchWord(p->author,fio)) 
	{
		cout << p->title << endl;
		cout << "   Автор(ы): " << p->author << endl;
		cout << "   Шифр книги: " << p->cipher << endl;
		cout << "   Издатель: " << p->publicHouse << endl;
		cout << "   Год издания: " << p->yearpubl << endl;
		cout << "   В наличии: " << p->quantiavailab << endl << endl;
		count++;
	} 
		count = search(p->left, fio, count);  
		count = search(p->right, fio, count);
	return count;
}

issrec* extradit(issrec* p,book*bo,reader*read, string nomb, string ciph, string date)
{
	if (bo->quantiavailab > 0)
	{
		if (p == NULL)
		{
			issrec* newlib = new issrec;
			newlib->nombtick = nomb;
			newlib->cipher = ciph;
			newlib->dateis = date;
			bo->quantiavailab = bo->quantiavailab - 1;
			cout << "Запись добавлена!" << endl;
			return newlib;
		}
		else
			p->pnext3=extradit(p->pnext3, bo, read, nomb, ciph, date);
		
		/*else
			if (p->cipher[2] == ciph[2])
			{
				if (p->pnext2 == nullptr)
				{
					issrec* remem = new issrec;
					remem->nombtick = nomb;
					remem->cipher = ciph;
					remem->dateis = date;
					bo->quantiavailab = bo->quantiavailab - 1;
					for (int i = 0; i < 20; i++)
					{
						if (read->ciph[i] == "")
						{
							read->ciph[i] = ciph;
							break;
						}
					}
					p->pnext2 = remem;
					if (p->pnext3 == nullptr)
					{
						p->pnext3 = remem;
					}
					else
					{
						issrec* remem2 = p->pnext3;
						p->pnext3 = remem;
						remem->pnext3 = remem2;
					}
					cout << "Запись добавлена!" << endl;
					return sorting(p);
				}
				else
					if ((p->pnext2)->pnext3 == nullptr)
					{
						issrec* remem = new issrec;
						remem->nombtick = nomb;
						remem->cipher = ciph;
						remem->dateis = date;
						bo->quantiavailab = bo->quantiavailab - 1;
						for (int i = 0; i < 20; i++)
						{
							if (read->ciph[i] == "")
							{
								read->ciph[i] = ciph;
								break;
							}
						}
						(p->pnext2)->pnext3 = remem;
						p->pnext2 = remem;
						cout << "Запись добавлена!" << endl;
						return sorting(p);
					}
					else
					{
						issrec* remem2;
						issrec* remem = new issrec;
						remem->nombtick = nomb;
						remem->cipher = ciph;
						remem->dateis = date;
						bo->quantiavailab = bo->quantiavailab - 1;
						for (int i = 0; i < 20; i++)
						{
							if (read->ciph[i] == "")
							{
								read->ciph[i] = ciph;
								break;
							}
						}
						remem2 = (p->pnext2)->pnext3;
						(p->pnext2)->pnext3 = remem;
						p->pnext2 = remem;
						remem->pnext3 = remem2;
						cout << "Запись добавлена!" << endl;
						return sorting(p);
					}
			}
			else
			{
			if (p->pnext1 == NULL)
			{
				issrec* remem = new issrec;
				remem->nombtick = nomb;
				remem->cipher = ciph;
				remem->dateis = date;
				bo->quantiavailab = bo->quantiavailab - 1;
				for (int i = 0; i < 20; i++)
				{
					if (read->ciph[i] == "")
					{
						read->ciph[i] = ciph;
						break;
					}
				}
				if (p->pnext2 == NULL)
				{
					p->pnext1 = remem;
					p->pnext3 = remem;
				}
				else
				{
					(p->pnext2)->pnext3 = remem;
				}
				cout << "Запись добавлена!" << endl;
				return sorting(p);
			}
			else
				p = extradit(p, bo,read, nomb, ciph, date);
			}*/
	}
	else
	{
		cout << "Книги нет в наличии!" << endl;
		return sorting(p);
	}
		return sorting(p);
}

int refundcip(issrec* p, book* bo, string ciph, int k=0)
{
	if (p == NULL)
	{
		return k;
	}
	else
		if (p->cipher == ciph)
		{	
			if (p->dateret=="")
			cout << " Читательский билет: " << p->nombtick<<endl;
			k++;
		}
	if (p->cipher[2] == ciph[2])
		k=refundcip(p->pnext3, bo, ciph,k);
	else
		k=refundcip(p->pnext1, bo, ciph,k);
	return k;
}

bool checkdata(string a, string b)
{
	int tempa=0, tempb=0;
	tempa = (a[0] - 48) * 10 + (a[1] - 48) + (a[3] - 48) * 1000 + (a[4] - 48) * 100 + (a[6] - 48) * 100000 + (a[7] - 48) * 10000;
	tempb = (b[0] - 48) * 10 + (b[1] - 48) + (b[3] - 48) * 1000 + (b[4] - 48) * 100 + (b[6] - 48) * 100000 + (b[7] - 48) * 10000;
	if (tempa < tempb)
		return true;
	else
		return false;
}

issrec* refund(issrec* p, book* bo, reader* read, string nomb, string ciph, string date)
{
	if (p == NULL)
	{
		return 0;
	}
	else
		if (p->cipher == ciph && p->nombtick == nomb)
		{
			if (checkdata(p->dateis, date))
			{
				p->dateret = date;
				bo->quantiavailab++;
				cout << "Книга: " << p->cipher << endl;
				cout << "Читатель: " << p->nombtick << endl;
				cout << "Дата выдачи: " << p->dateis << endl;
				cout << "Дата возврата: " << p->dateret << endl;
				cout << "Запись добавлена!\n" << endl;
				return p;
			}
			else
				cout << "Дата некорректна" << endl;
		}
	if (p->cipher[2] == ciph[2])
		refund(p->pnext3, bo, read, nomb, ciph, date);
	else
		refund(p->pnext1, bo, read, nomb, ciph, date);
	return 0;
}

issrec* sorting(issrec* p)
{
	string nombtick;
	string cipher;
	string dateis = "";
	string dateret = "";
	int k=0,i=0,j;
	if (p == NULL)
	{
		return 0;
	}
	issrec* temp;
	issrec* tempi;
	issrec* tempi2=p;
	while(tempi2!= NULL)
	{
		temp = p;
		k = 0;
		while (temp!= NULL)
		{
			j = 0;
			if ((p->cipher[2] < temp->cipher[2]) || (p->cipher[2] == temp->cipher[2])&&(j<i))
				k++;
			j++;
			temp = temp->pnext3;
		}
		tempi = p;
		while (tempi != NULL)
		{
			j = 0;
			if (k == j)
			{
				nombtick = tempi->nombtick;
				cipher = tempi->cipher;
				dateis = tempi->dateis;
				dateret = tempi->dateret;
				tempi->cipher = p->cipher;
				tempi->dateis = p->dateis;
				tempi->dateret = p->dateret;
				tempi->nombtick = p->nombtick;
				p->cipher = cipher;
				p->dateis=dateis;
				p->dateret=dateret;
				p->nombtick=nombtick;
				break;
			}
			j++;
			tempi = tempi->pnext3;
		}
		i++;
		tempi2 = tempi2->pnext3;
	}
	tempi2 = p;
	temp = p;
	while (tempi2->pnext3 != NULL)
	{
		if ((tempi2->cipher[2]) != ((tempi2->pnext3)->cipher[2]))
		{
			temp->pnext1 = tempi2->pnext3;
			temp = tempi2->pnext3;
			tempi2 = tempi2->pnext3;
		}
		else
			tempi2 = tempi2->pnext3;
	}
	return p;
}

void menu()
{	
	issrec* templib;
	reader* tread;
	int temp;
	string ciptemp;
	cout << "____________________________________________________\n";
	cout << "1 - Регистрация нового читателя\n";
	cout << "2 - Снятие с обслуживания читателя\n";
	cout << "3 - Просмотр всех зарегистрированных читателей\n";
	cout << "4 - Очистка данных о читателях\n";
	cout << "5 - Поиск читателя\n";
	cout << "6 - Добавление новой книги\n";
	cout << "7 - Удаление сведений о книге\n";
	cout << "8 - Просмотр всех имеющихся книг\n";
	cout << "9 - Очистка данных о книгах\n";
	cout << "10 - Поиск книги\n";
	cout << "11 - Регистрация выдачи экземпляра книги читателю\n";
	cout << "12 - Регистрация приёма экземпляра книги от читателя\n";
	cout << "____________________________________________________\n";
	cout << "Выберите пункт меню: ";
	cin >> temp;
	switch (temp)
	{
	case 1:
		system("cls");
		addread();
		break;
	case 2:
		system("cls");
		takeoff();
		break;
	case 3:
		system("cls");
		viewing();
		break;
	case 4:
		system("cls");
		cleanreader();
		break;
	case 5:
		system("cls");
		cout << "1 - Поиск читателя по номеру читательского билета\n";
		cout << "2 - Поиск читателя по ФИО\n";
		cin >> temp;
		switch (temp)
		{
		case 1:
			system("cls");
			searchnom();
			cout << "0 - Вернуться в меню\n";
			cin >> temp;
			switch (temp)
			{
			case 0:
				system("cls");
				menu();
				break;
			default:
				system("cls");
				cout << "0 - Вернуться в меню\n";
				cin >> temp;
				switch (temp)
				{
				case 0:
					menu();
					break;
				}
				break;
			}
			break;
		case 2:
			system("cls");
			searchfio();
			break;
			break;
		}
	case 6:
		system("cls");
		addbook();
		break;
	case 7:
		system("cls");
		cout << "Введите шифр книги для удаления\n";
		cin >> ciptemp;
		listbook=deleteNode(listbook, ciptemp);
		cout << "____________________________________________________\n";
		cout << "1 - Вернуться в меню\n";
		cin >> temp;
		switch (temp)
		{
		case 1:
			system("cls");
			menu();
			break;
		default:
			system("cls");
			cout << "1 - Вернуться в меню\n";
			cout << "2 - Добавить ещё\n";
			cin >> temp;
			switch (temp)
			{
			case 1:
				system("cls");
				menu();
				break;
			}
			break;
		}
		break;
	case 8:
		system("cls");
		if (listbook != NULL)
		{
			printTree(listbook);
			cout << "Симметричный обход: ";
			inorderPrint(listbook);
			cout << "\n";
			cout << "____________________________________________________\n";
			cout << "1 - Вернуться в меню\n";
			cin >> temp;
			switch (temp)
			{
			case 1:
				system("cls");
				menu();
				break;
			default:
				system("cls");
				cout << "1 - Вернуться в меню\n";
				cout << "2 - Добавить ещё\n";
				cin >> temp;
				switch (temp)
				{
				case 1:
					system("cls");
					menu();
					break;
				}
				break;
			}
		}
		else
		{
			cout << "Дерево пусто!\n";
			menu();
		}
		break;
	case 9:
		system("cls");
		if (listbook == NULL) {
			cout << "Дерево уже пустое!\n\n";
		}
		else
		{
			deleteTree(listbook);
			//listbook = tempbook;
		}
			cout << "____________________________________________________\n";
			cout << "1 - Вернуться в меню\n";
			cin >> temp;
			switch (temp)
			{
			case 1:
				system("cls");
				menu();
				break;
			default:
				system("cls");
				cout << "1 - Вернуться в меню\n";
				cout << "2 - Добавить ещё\n";
				cin >> temp;
				switch (temp)
				{
				case 1:
					system("cls");
					menu();
					break;
				}
				break;
		}
		break;
	case 10:
		system("cls");
		cout << "1 - Поиск читателя по шифру книги\n";
		cout << "2 - Поиск книги по ФИО автора(ов)\n";
		cin >> temp;
		switch (temp)
		{
		case 1:
			system("cls");
			cout << "Введите шифр книги для поиска: ";
			cin >> ciptemp;
			tempbook = searchNode(listbook, ciptemp);
			if (tempbook==NULL)
				cout << "Книга не найдена!\n";
			else
			{
				 temp=refundcip(lib,tempbook,ciptemp);
			}
			cout << "____________________________________________________\n";
			cout << "1 - Вернуться в меню\n";
			cin >> temp;
			switch (temp)
			{
			case 1:
				system("cls");
				menu();
				break;
			default:
				system("cls");
				cout << "1 - Вернуться в меню\n";
				cin >> temp;
				switch (temp)
				{
				case 1:
					system("cls");
					menu();
					break;
				}
				break;
			}
			break;
		case 2:
			system("cls");
			cout << "Введите ФИО автора(ов) для поиска: ";
			cin >> ciptemp;
			temp = search(listbook, ciptemp);
			if (temp == 0)
				cout << "Книга не найдена!\n";
			cout << "____________________________________________________\n";
			cout << "1 - Вернуться в меню\n";
			cin >> temp;
			switch (temp)
			{
			case 1:
				system("cls");
				menu();
				break;
			default:
				system("cls");
				cout << "1 - Вернуться в меню\n";
				cin >> temp;
				switch (temp)
				{
				case 1:
					system("cls");
					menu();
					break;
				}
				break;
			}
			break;
		}
		
		break;
	case 11:
		system("cls");
		cout << "Введите шифр книги" << endl;
		cin >> ciptemp;
		tempbook = searchNode(listbook, ciptemp);
		if (tempbook == NULL)
		{
			cout << "Книга не найдена!\n";
			cout << "1 - Вернуться в меню\n";
			cin >> temp;
			switch (temp)
			{
			case 1:
				system("cls");
				menu();
				break;
			}
			break;
		}
		else
		{
			tread = searchnom();
			if (tread == NULL)
			{
				cout << "1 - Вернуться в меню\n";
				cin >> temp;
				switch (temp)
				{
				case 1:
					system("cls");
					menu();
					break;
				}
				break;
			}
			else
			{
				cout << "Введите дату выдачи" << endl;
				cin >> ciptemp;
				templib = extradit(lib,tempbook,tread,tread->nombtick,tempbook->cipher,ciptemp);
				if (templib != NULL)
					lib = templib;
				cout << "1 - Вернуться в меню\n";
				cin >> temp;
				switch (temp)
				{
				case 1:
					system("cls");
					menu();
					break;
				}
				break;
			}
		}
		
		break;
	case 12:
		system("cls");
		cout << "Введите шифр книги" << endl;
		cin >> ciptemp;
		tempbook = searchNode(listbook, ciptemp);
		if (tempbook == 0)
		{
			cout << "Книга не найдена!\n";
			cout << "1 - Вернуться в меню\n";
			cin >> temp;
			switch (temp)
			{
			case 1:
				system("cls");
				menu();
				break;
			}
			break;
		}
		else
		{
			tread = searchnom();
			if (tread == NULL)
			{
				cout << "1 - Вернуться в меню\n";
				cin >> temp;
				switch (temp)
				{
				case 1:
					system("cls");
					menu();
					break;
				}
				break;
			}
			else
			{
				cout << "Введите дату приема" << endl;
				cin >> ciptemp;
				templib = refund(lib, tempbook, tread, tread->nombtick, tempbook->cipher, ciptemp);
				if (templib != NULL)
					lib = templib;
				else 
					cout << "Запись о выдаче не найдена!\n";
				cout << "1 - Вернуться в меню\n";
				cin >> temp;
				switch (temp)
				{
				case 1:
					system("cls");
					menu();
					break;
				}
				break;
			}
		}
		break;
	default:
		system("cls");
		menu();
		break;
	}
}
int main()
{
	srand(time(0));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	menu();
}