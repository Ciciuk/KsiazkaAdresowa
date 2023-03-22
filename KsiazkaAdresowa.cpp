// KsiazkaAdresowa.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

struct contactStorage {
	int id = 0;
	int userId = 0;
	string phoneNumber, name, surname, address, email;
};

struct userStorage {
	int userId = 0;
	string userName, userPassword;
};

void displayMainlMenu() {
	cout << "1. Logowanie" << endl;
	cout << "2. Rejestracja" << endl;
	cout << "9. Wyjdz" << endl;
}

void displayInternalMenu() {
	cout << "1. Dodaj adresata" << endl;
	cout << "2. Wyszukaj po imieniu" << endl;
	cout << "3. Wyszukaj po nazwisku" << endl;
	cout << "4. Wyswietl wszystkich adresatow" << endl;
	cout << "5. Usun adresata" << endl;
	cout << "6. Edytuj adresata" << endl;
	cout << "7. Zmien haslo" << endl;
	cout << "9. Wyloguj sie" << endl;
}
void displayEditMenu() {
	cout << "1. Edytuj imie" << endl;
	cout << "2. Edytuj nazwisko" << endl;
	cout << "3. Edytuj numer telefonu" << endl;
	cout << "4. Edytuj adres e-mail" << endl;
	cout << "5. Edytuj adres zamieszkania" << endl;
	cout << "6. Wyjdz" << endl;
}
void displayRecord(vector <contactStorage>::iterator placeInStructureToDisplay) {
	cout << left << setw(20) << "ID:" << placeInStructureToDisplay->id << endl;
	cout << left << setw(20) << "Imie:" << placeInStructureToDisplay->name << endl;
	cout << left << setw(20) << "Nazwisko:" << placeInStructureToDisplay->surname << endl;
	cout << left << setw(20) << "Nr.tel:" << placeInStructureToDisplay->phoneNumber << endl;
	cout << left << setw(20) << "Adres e-mail:" << placeInStructureToDisplay->email << endl;
	cout << left << setw(20) << "Adres:" << placeInStructureToDisplay->address << endl;
	cout << endl;
}
void displayHoldMesage() {
	system("pause");
}

string getHoleLine() {
	string line;
	getline(cin, line);
	return line;
}

bool checkIfEmptyUsers(vector <userStorage> users) {
	if (users.empty()) {
		cout << "Brak zarejestrowanych uzytkownikow ";
		displayHoldMesage();
		return true;
	}
	return false;
}

bool checkPassword(vector <userStorage>::iterator i) {
	string password;

	for (int j = 3; j > 0; j--) {
		cout << "Pozostalo Ci: " << j << " prob" << endl;
		cout << "Podaj haslo: " << endl;
		password = getHoleLine();
		if (password == i->userPassword) {
			cout << "Gratuluje, poprawne haslo" << endl;
			displayHoldMesage();
			return true;
		}
		else {
			cout << "Nieprawidlowe haslo" << endl;
			cout << endl;
			displayHoldMesage();
		}
	}
	cout << "Wykorzystano wszystkie proby, nastapi przekierowanie na ekran glowny" << endl;
	displayHoldMesage();
	return false;
}
void changePassword(vector <userStorage>& users, int actualUser) {

	vector <userStorage>::iterator i;
	i = find_if(users.begin(), users.end(), [actualUser](const userStorage& vi) {return vi.userId == actualUser; });
	cout << "Podaj nowe haslo: ";
	i->userPassword = getHoleLine();
	fstream file;
	file.open("uzytkownicy.txt", ios::out | ios::trunc);
	for (auto i = users.begin(); i < users.end(); i++) {
		file << i->userId << '|';
		file << i->userName << '|';
		file << i->userPassword << '|';
		file << endl;
	}
	file.close();
	cout << "Haslo zostalo zmienione: ";
}

int checkPaswordAndReturnUserId(vector <userStorage> users) {
	system("cls");
	userStorage data;
	if (checkIfEmptyUsers(users))
		return 0;
	cout << "Podaj login:  " << endl;
	data.userName = getHoleLine();

	for (vector <userStorage>::iterator i = users.begin(); i < users.end(); i++) {
		if (data.userName == i->userName)
			if (checkPassword(i))
				return i->userId;
			else
				break;
	}
	cout << "Brak loginu w bazie danych:  ";
	displayHoldMesage();
	return 0;
}


bool checkIfEmptyContacts(vector <contactStorage> contacts) {
	if (contacts.empty()) {
		cout << "Brak kontaktow ";
		displayHoldMesage();
		return true;
	}
	return false;
}

contactStorage contactDataGathering() {
	contactStorage data;

	cout << "Podaj imie: ";
	data.name = getHoleLine();
	cout << "Podaj nazwisko: ";
	data.surname = getHoleLine();
	cout << "Podaj nr. tel ";
	data.phoneNumber = getHoleLine();
	cout << "Podaj e-mail: ";
	data.email = getHoleLine();
	cout << "Podaj adres: ";
	data.address = getHoleLine();
	cout << endl;
	return data;
}

int readLastContactId() {
	fstream file;
	file.open("adresaci.txt", ios::in);
	if (!file.good())
		return 1;
	string line;
	contactStorage data;
	if (file.peek() == std::ifstream::traits_type::eof())
		return 1;
	while (getline(file, line, '|')) {
		if (line == "\n")
			break;
		data.id = atoi(line.c_str());
		getline(file, line, '|');
		data.userId = atoi(line.c_str());
		getline(file, data.name, '|');
		getline(file, data.surname, '|');
		getline(file, data.phoneNumber, '|');
		getline(file, data.email, '|');
		getline(file, data.address, '|');
	}
	return data.id + 1;
	file.close();
}
int readLastUserId() {
	fstream file;
	file.open("uzytkownicy.txt", ios::in);
	if (!file.good())
		return 1;
	string line;
	userStorage data;
	if (file.peek() == std::ifstream::traits_type::eof())
		return 1;
	while (getline(file, line, '|')) {
		if (line == "\n")
			break;
		data.userId = atoi(line.c_str());
		getline(file, data.userName, '|');
		getline(file, data.userPassword, '|');
	}
	return data.userId + 1;
	file.close();
}
userStorage userDataGathering() {
	userStorage data;

	cout << "Podaj login: ";
	data.userName = getHoleLine();
	cout << "Podaj haslo: ";
	data.userPassword = getHoleLine();
	cout << endl;
	return data;
}

void loadUsersFromFile(vector <userStorage>& users) {
	fstream file;
	file.open("uzytkownicy.txt", ios::in);
	string line;
	userStorage data;
	while (getline(file, line, '|')) {
		if (line == "\n")
			break;
		data.userId = atoi(line.c_str());
		getline(file, data.userName, '|');
		getline(file, data.userPassword, '|');
		users.push_back(userStorage(data));
	}
	file.close();
}
string mergeUserLine(userStorage data) {
	string line = "";
	line += to_string(data.userId) + '|';
	line += data.userName + '|';
	line += data.userPassword + '|';
	return line;
}
void saveNewUser(userStorage newUser) {
	fstream file;
	file.open("uzytkownicy.txt", ios::out | ios::app);
	file << mergeUserLine(newUser) << endl;
	file.close();
}
void insertNewUser(vector <userStorage>& users) {
	userStorage data;
	data = userDataGathering();
	if (users.empty())
		data.userId = 1;
	else
		data.userId = users.back().userId + 1;
	users.push_back(data);
	saveNewUser(data);
}
void loadContactsFromFile(vector <contactStorage>& contacts, int currentUserId) {
	fstream file;
	file.open("adresaci.txt", ios::in);
	string line;
	contactStorage data;
	while (getline(file, line, '|')) {
		data.id = atoi(line.c_str());
		getline(file, line, '|');
		data.userId = atoi(line.c_str());
		getline(file, data.name, '|');
		getline(file, data.surname, '|');
		getline(file, data.phoneNumber, '|');
		getline(file, data.email, '|');
		getline(file, data.address, '|');
		if (currentUserId == data.userId)
			contacts.push_back(contactStorage(data));

	}
	file.close();
}

string mergeContactLine(contactStorage data) {
	string line = "";
	line += to_string(data.id) + '|';
	line += to_string(data.userId) + '|';
	line += data.name + '|';
	line += data.surname + '|';
	line += data.phoneNumber + '|';
	line += data.email + '|';
	line += data.address + '|';
	return line;
}
void saveNewContact(contactStorage newContact) {
	fstream file;
	file.open("adresaci.txt", ios::out | ios::app);
	file << mergeContactLine(newContact) << endl;
	file.close();
}
void insertNewContact(vector <contactStorage>& contacts, int userId) {
	contactStorage data;

	data = contactDataGathering();
	data.id = readLastContactId();
	data.userId = userId;
	contacts.push_back(data);
	saveNewContact(data);
}
void displayContactByName(vector <contactStorage> contacts) {
	if (checkIfEmptyContacts(contacts))
		return;
	string searchingName;
	cout << "Podaj Imie ktore chcesz wyszukac: ";
	cin >> searchingName;
	system("cls");

	for (vector <contactStorage>::iterator i = contacts.begin(); i < contacts.end(); i++) {
		if (i->name == searchingName)
			displayRecord(i);
	}
	displayHoldMesage();
}
void displayContactBySurname(vector <contactStorage> contacts) {
	if (checkIfEmptyContacts(contacts))
		return;
	string searchingSurname;
	cout << "Podaj Nazwisko ktore chcesz wyszukac: ";
	cin >> searchingSurname;
	system("cls");

	for (vector <contactStorage>::iterator i = contacts.begin(); i < contacts.end(); i++) {
		if (i->surname == searchingSurname)
			displayRecord(i);
	}
	displayHoldMesage();
}
void displayAllContact(vector <contactStorage> contacts) {
	if (checkIfEmptyContacts(contacts))
		return;
	system("cls");

	for (vector <contactStorage>::iterator i = contacts.begin(); i < contacts.end(); i++) {
		displayRecord(i);
	}
	displayHoldMesage();
}
contactStorage extractingData(string line) {
	stringstream ss(line);
	string temp;
	contactStorage data;
	getline(ss, temp, '|');
	data.id = atoi(temp.c_str());
	getline(ss, temp, '|');
	data.userId = atoi(temp.c_str());
	getline(ss, data.name, '|');
	getline(ss, data.surname, '|');
	getline(ss, data.phoneNumber, '|');
	getline(ss, data.email, '|');
	getline(ss, data.address, '|');
	return data;
}
void saveOneRow(contactStorage data) {
	fstream file;
	file.open("adresaci_temp.txt", ios::out | ios::app);
	file << mergeContactLine(data) << endl;
	file.close();
}
void saveInToFile(vector <contactStorage> contacts, int currentUserId) {
	fstream input, output;
	input.open("adresaci.txt", ios::in);
	output.open("adresaci_temp.txt", ios::out | ios::trunc);
	output.close();
	string line;
	contactStorage dataFromExistingLibrary;
	int i = 0;
	while (getline(input, line)) {
		dataFromExistingLibrary = extractingData(line);

		if (currentUserId == dataFromExistingLibrary.userId && dataFromExistingLibrary.id == contacts[i].id) {
			saveOneRow(contacts[i]);
			i++;
		}

		else if (currentUserId != dataFromExistingLibrary.userId)
			saveOneRow(dataFromExistingLibrary);
	}
	input.close();
	remove("adresaci.txt");
	bool temp = rename("adresaci_temp.txt", "adresaci.txt");

}


void saveInToFile1(vector <contactStorage> contacts) {
	fstream file;
	file.open("adresaci_temp.txt", ios::out | ios::trunc);
	for (auto i = contacts.begin(); i < contacts.end(); i++) {
		file << i->id << '|';
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
void removeContactSequence(vector <contactStorage>& contacts) {
	if (checkIfEmptyContacts(contacts))
		return;
	displayAllContact(contacts);
	cout << endl;
	cout << "Podaj ID kontaktu ktory chcesz usunac: ";
	int idToDelete = getId();
	system("cls");
	vector <contactStorage>::iterator contactToRemove;
	contactToRemove = find_if(contacts.begin(), contacts.end(), [idToDelete](const contactStorage& vi) //you want to compare an item
		{return vi.id == idToDelete; });
	if (contactToRemove == contacts.end()) {
		cout << "Nie znaleziono takiego ID ";
		displayHoldMesage();
		return;
	}

	displayRecord(contactToRemove);
	cout << endl;
	cout << "Jesli chcesz usunac powyzszy kontakt wcisnij 't' " << endl;
	if (getOneChar() == 't') {
		contacts.erase(contactToRemove);
		cout << "Kontakt został usuniety " << endl;
		displayHoldMesage();
	}

}
void editRecord(vector <contactStorage>& contacts, vector <contactStorage>::iterator contactToEdit) {
	char editChoice;
	while (1) {
		system("cls");
		displayRecord(contactToEdit);
		displayEditMenu();
		editChoice = getOneChar();
		switch (editChoice) {
		case '1':
			cout << "Edytuj imie: " << endl;
			contactToEdit->name = getHoleLine();
			break;
		case '2':
			cout << "Edytuj nazwisko: " << endl;
			contactToEdit->surname = getHoleLine();
			break;
		case '3':
			cout << "Edytuj nr. tel: " << endl;
			contactToEdit->phoneNumber = getHoleLine();
			break;
		case '4':
			cout << "Edytuj email: " << endl;
			contactToEdit->email = getHoleLine();
			break;
		case '5':
			cout << "Edytuj adres: " << endl;
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
void editContactSequence(vector <contactStorage>& contacts) {
	if (checkIfEmptyContacts(contacts))
		return;
	displayAllContact(contacts);
	cout << endl;
	cout << "Podaj ID kontaktu ktory chcesz edytowac: ";
	int idToEdit = getId();
	system("cls");
	vector <contactStorage>::iterator contactToEdit;
	contactToEdit = find_if(contacts.begin(), contacts.end(), [idToEdit](const contactStorage& vi) {return vi.id == idToEdit; });
	if (contactToEdit == contacts.end()) {
		cout << "Nie znaleziono takiego ID ";
		displayHoldMesage();
		return;
	}
	editRecord(contacts, contactToEdit);
}

void internalMenu(vector <userStorage>& users, int userId) {
	vector <contactStorage> contacts;
	char menuChoice;
	if (userId == 0)
		return;
	loadContactsFromFile(contacts, userId);
	while (1) {
		system("cls");
		displayInternalMenu();
		menuChoice = getOneChar();
		switch (menuChoice) {
		case '1':
			insertNewContact(contacts, userId);
			break;
		case '2':
			displayContactByName(contacts);
			break;
		case '3':
			displayContactBySurname(contacts);
			break;
		case '4':
			displayAllContact(contacts);
			break;
		case '5':
			removeContactSequence(contacts);
			saveInToFile(contacts, userId);
			break;
		case '6':
			editContactSequence(contacts);
			saveInToFile(contacts, userId);
			break;
		case '7':
			changePassword(users, userId);
			break;
		case '9':
			return;
		default:
			break;
		}
	}
}
int main() {
	vector <userStorage> users;
	char menuChoice;
	loadUsersFromFile(users);
	while (1) {
		system("cls");
		displayMainlMenu();
		menuChoice = getOneChar();
		switch (menuChoice) {
		case '1':
			internalMenu(users, checkPaswordAndReturnUserId(users));
			break;
		case '2':
			insertNewUser(users);
			break;
		case '9':
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
