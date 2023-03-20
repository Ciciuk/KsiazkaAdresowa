// KsiazkaAdresowa.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

struct dataStorage {
	int id = 0;
	string phoneNumber, name, surname, address, email;
};


void displayMenu() {
	cout << "1. Dodaj adresata" << endl;
	cout << "2. Wyszukaj po imieniu" << endl;
	cout << "3. Wyszukaj po nazwisku" << endl;
	cout << "4. Wyswietl wszystkich adresatow" << endl;
	cout << "5. Usun adresata" << endl;
	cout << "6. Edytuj adresata" << endl;
	cout << "9. Wyjdz" << endl;
}
void displayEditMenu() {
	cout << "1. Edytuj imie" << endl;
	cout << "2. Edytuj nazwisko" << endl;
	cout << "3. Edytuj numer telefonu" << endl;
	cout << "4. Edytuj adres email" << endl;
	cout << "5. Edytuj adres zamieszkania" << endl;
	cout << "6. Wyjdz" << endl;
}
void displayRecord(vector <dataStorage>::iterator placeInStructureToDisplay) {
	cout << left << setw(20) << "ID:" << placeInStructureToDisplay->id << endl;
	cout << left << setw(20) << "Imie:" << placeInStructureToDisplay->name << endl;
	cout << left << setw(20) << "Nazwisko:" << placeInStructureToDisplay->surname << endl;
	cout << left << setw(20) << "Nr.tel:" << placeInStructureToDisplay->phoneNumber << endl;
	cout << left << setw(20) << "Adres e-mail:" << placeInStructureToDisplay->email << endl;
	cout << left << setw(20) << "Adres:" << placeInStructureToDisplay->address << endl;
	cout << endl;
}
void displayHoldMesage() {
	cout << "Nacisnij dowolny klawisz zeby kontynuowac ";
	system("pause");
}

bool checkIfEmpty(vector <dataStorage> contacts) {
	if (contacts.empty()) {
		cout << "Brak kontaktow ";
		displayHoldMesage();
		return true;
	}
	return false;
}

string getHoleLine() {
	string line;
	//cin.ignore();
	getline(cin, line);
	return line;
}

dataStorage dataGathering() {
	dataStorage data;

	cout << "Podaj imie: ";
	data.name = getHoleLine();
	cout << "Podaj nazwisko: ";
	data.surname = getHoleLine();
	cout << "Podaj nr. tel ";
	data.phoneNumber = getHoleLine();
	cout << "Podaj email: ";
	data.email = getHoleLine();
	cout << "Podaj adres: ";
	data.address = getHoleLine();
	cout << endl;
	return data;
}
void insertNewRecord(vector <dataStorage>& contacts) {
	dataStorage data;

	data = dataGathering();

	if (contacts.empty())
		data.id = 1;
	else
		data.id = contacts.back().id + 1;

	contacts.push_back(data);

}
void displayRecordByName(vector <dataStorage> contacts) {
	if (checkIfEmpty(contacts))
		return;
	string searchingName;
	cout << "Podaj Imie ktore chcesz wyszukac: ";
	cin >> searchingName;
	system("cls");
	vector <dataStorage>::iterator i;

	for (i = contacts.begin(); i < contacts.end(); i++) {
		if (i->name == searchingName)
			displayRecord(i);
	}
	displayHoldMesage();
}
void displayRecordBySurname(vector <dataStorage> contacts) {
	if (checkIfEmpty(contacts))
		return;
	string searchingSurname;
	cout << "Podaj Nazwisko ktore chcesz wyszukac: ";
	cin >> searchingSurname;
	system("cls");
	vector <dataStorage>::iterator i;

	for (i = contacts.begin(); i < contacts.end(); i++) {
		if (i->surname == searchingSurname)
			displayRecord(i);
	}
	displayHoldMesage();
}
void displayAllRecords(vector <dataStorage> contacts) {
	if (checkIfEmpty(contacts))
		return;
	system("cls");
	vector <dataStorage>::iterator i;

	for (i = contacts.begin(); i < contacts.end(); i++) {
		displayRecord(i);
	}
	displayHoldMesage();
}
void safeInToFile(vector <dataStorage> contacts) {
	fstream file;
	file.open("ksiazkaAdresowa.txt", ios::out | ios::trunc);
	for (auto i = contacts.begin(); i < contacts.end(); i++) {
		file << i->id << '|';
		file << i->name << '|';
		file << i->surname << '|';
		file << i->phoneNumber << '|';
		file << i->email << '|';
		file << i->address << '|';
		if (i != contacts.end() - 1)
			file << endl;
	}
	file.close();
}
void loadFromFile(vector <dataStorage>& contacts) {
	fstream file;
	file.open("ksiazkaAdresowa.txt", ios::in);
	string line, untilStopSign;
	dataStorage data;
	while (getline(file, line, '|')) {
		data.id = atoi(line.c_str());
		getline(file, data.name, '|');
		getline(file, data.surname, '|');
		getline(file, data.phoneNumber, '|');
		getline(file, data.email, '|');
		getline(file, data.address, '|');
		contacts.push_back(dataStorage(data));
	}
}
char getOneChar() {
	string input = "";
	char sign = { 0 };

	while (true) {
		getline(cin, input);
		if (input.length() == 1) {
			sign = input[0];
			break;
		}
		cout << "To nie jest pojedynczy znak. Wpisz ponownie." << endl;
	}
	return sign;
}

int getId() {
	return int(getOneChar() - '0');
}
void removeRecordSequence(vector <dataStorage>& contacts) {
	if (checkIfEmpty(contacts))
		return;
	displayAllRecords(contacts);
	cout << endl;
	cout << "Podaj ID kontaktu ktory chcesz usunac: ";
	int idToDelete = getId();
	system("cls");
	vector <dataStorage>::iterator contactToRemove;
	contactToRemove = find_if(contacts.begin(), contacts.end(), [idToDelete](const dataStorage& vi) //you want to compare an item
		{return vi.id == idToDelete; });
	if (contactToRemove == contacts.end()) {
		cout << "Nie znaleziono takiego ID ";
		displayHoldMesage();
		return;
	}

	displayRecord(contactToRemove);
	cout << endl;
	cout << "Jesli chcesz usunac powyzszy kontakt wcisnij 't' ";
	if (getOneChar() == 't') {
		contacts.erase(contactToRemove);
		cout << "Kontakt został usuniety ";
		displayHoldMesage();
	}

}
void editRecord(vector <dataStorage>& contacts, vector <dataStorage>::iterator contactToEdit) {
	char editChoice;
	while (1) {
		system("cls");
		displayRecord(contactToEdit);
		displayEditMenu();
		editChoice = getOneChar();
		switch (editChoice) {
		case '1':
			contactToEdit->name = getHoleLine();
			break;
		case '2':
			contactToEdit->surname = getHoleLine();
			break;
		case '3':
			contactToEdit->phoneNumber = getHoleLine();
			break;
		case '4':
			contactToEdit->email = getHoleLine();
			break;
		case '5':
			contactToEdit->address = getHoleLine();
			break;
		case '6':
			return;
			break;
		default:
			break;
		}
	}
}
void editRecordSequence(vector <dataStorage>& contacts) {
	if (checkIfEmpty(contacts))
		return;
	displayAllRecords(contacts);
	cout << endl;
	cout << "Podaj ID kontaktu ktory chcesz edytowac: ";
	int idToEdit = getId();
	system("cls");
	vector <dataStorage>::iterator contactToEdit;
	contactToEdit = find_if(contacts.begin(), contacts.end(), [idToEdit](const dataStorage& vi) {return vi.id == idToEdit; });
	if (contactToEdit == contacts.end()) {
		cout << "Nie znaleziono takiego ID ";
		displayHoldMesage();
		return;
	}
	editRecord(contacts, contactToEdit);
}

int main() {
	vector <dataStorage> contacts;
	char menuChoice;
	loadFromFile(contacts);
	while (1) {
		system("cls");
		displayMenu();
		menuChoice = getOneChar();
		switch (menuChoice) {
		case '1':
			insertNewRecord(contacts);
			safeInToFile(contacts);
			break;
		case '2':
			displayRecordByName(contacts);
			break;
		case '3':
			displayRecordBySurname(contacts);
			break;
		case '4':
			displayAllRecords(contacts);
			break;
		case '5':
			removeRecordSequence(contacts);
			break;
		case '6':
			editRecordSequence(contacts);
			safeInToFile(contacts);
			break;
		case '9':
			safeInToFile(contacts);
			exit(0);
		default:
			break;
		}
	}
	return 0;
}
// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
