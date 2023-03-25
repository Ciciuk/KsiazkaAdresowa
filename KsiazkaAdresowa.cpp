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

struct ContactStorage {
	int id = 0;
	int userId = 0;
	string phoneNumber, name, surname, address, email;
};

struct UserStorage {
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

void displayRecord(vector <ContactStorage>::iterator placeInStructureToDisplay) {
	cout << left << setw(20) << "ID:" << placeInStructureToDisplay->id << endl;
	cout << left << setw(20) << "Imie:" << placeInStructureToDisplay->name << endl;
	cout << left << setw(20) << "Nazwisko:" << placeInStructureToDisplay->surname << endl;
	cout << left << setw(20) << "Nr.tel:" << placeInStructureToDisplay->phoneNumber << endl;
	cout << left << setw(20) << "Adres e-mail:" << placeInStructureToDisplay->email << endl;
	cout << left << setw(20) << "Adres:" << placeInStructureToDisplay->address << endl;
	cout << endl;
}

string getWholeLine() {
	string line;

	cin.sync();
	getline(cin, line);

	return line;
}

bool checkIfEmptyUsers(vector <UserStorage> users) {
	if (users.empty()) {
		cout << "Brak zarejestrowanych uzytkownikow ";
		system("pause");;
		return true;
	}

	return false;
}

bool checkPassword(vector <UserStorage>::iterator i) {
	string password;

	for (int j = 3; j > 0; j--) {
		cout << "Pozostalo Ci: " << j << " prob" << endl;
		cout << "Podaj haslo: " << endl;
		password = getWholeLine();
		if (password == i->userPassword) {
			cout << "Gratuluje, poprawne haslo" << endl;
			system("pause");;
			return true;
		}
		else {
			cout << "Nieprawidlowe haslo" << endl;
			cout << endl;
			system("pause");;
		}
	}

	cout << "Wykorzystano wszystkie proby, nastapi przekierowanie na ekran glowny" << endl;
	system("pause");;

	return false;
}

int checkLastId(int a, int b) {
	return (a > b) ? a : b;
}

void changePassword(vector <UserStorage>& users, int actualUser) {
	vector <UserStorage>::iterator i = find_if(users.begin(), users.end(), [actualUser](const UserStorage& vi) {return vi.userId == actualUser; });//wyrazenie lambda
	fstream file;

	cout << "Podaj nowe haslo: ";
	i->userPassword = getWholeLine();

	file.open("uzytkownicy.txt", ios::out | ios::trunc);

	for (auto i = users.begin(); i < users.end(); i++) {
		file << i->userId << '|';
		file << i->userName << '|';
		file << i->userPassword << '|';
		file << endl;
	}
	cout << "Haslo zostalo zmienione: ";

	file.close();
}

int checkPaswordAndReturnUserId(vector <UserStorage> users) {
	UserStorage data;

	system("cls");

	if (checkIfEmptyUsers(users))
		return 0;
	cout << "Podaj login:  " << endl;

	data.userName = getWholeLine();

	for (vector <UserStorage>::iterator i = users.begin(); i < users.end(); i++) {
		if (data.userName == i->userName) {
			if (checkPassword(i))
				return i->userId;
			else
				break;
		}
	}

	cout << "Brak loginu w bazie danych:  ";
	system("pause");;

	return 0;
}

bool checkIfEmptyContacts(vector <ContactStorage> contacts) {
	if (contacts.empty()) {
		cout << "Brak kontaktow ";
		system("pause");;
		return true;
	}

	return false;
}

ContactStorage contactDataGathering() {
	ContactStorage data;

	cout << "Podaj imie: ";
	data.name = getWholeLine();
	cout << "Podaj nazwisko: ";
	data.surname = getWholeLine();
	cout << "Podaj nr. tel ";
	data.phoneNumber = getWholeLine();
	cout << "Podaj e-mail: ";
	data.email = getWholeLine();
	cout << "Podaj adres: ";
	data.address = getWholeLine();
	cout << endl;

	return data;
}

UserStorage userDataGathering() {
	UserStorage data;

	cout << "Podaj login: ";
	data.userName = getWholeLine();
	cout << "Podaj haslo: ";
	data.userPassword = getWholeLine();
	cout << endl;

	return data;
}

void loadUsersFromFile(vector <UserStorage>& users) {
	fstream file;
	string line;
	UserStorage data;

	file.open("uzytkownicy.txt", ios::in);

	while (getline(file, line, '|')) {
		if (line == "\n")
			break;
		data.userId = atoi(line.c_str());
		getline(file, data.userName, '|');
		getline(file, data.userPassword, '|');
		users.push_back(UserStorage(data));
	}

	file.close();
}

string mergeUserLine(UserStorage data) {
	string line = "";

	line += to_string(data.userId) + '|';
	line += data.userName + '|';
	line += data.userPassword + '|';

	return line;
}

void saveNewUser(UserStorage newUser) {
	fstream file;

	file.open("uzytkownicy.txt", ios::out | ios::app);
	file << mergeUserLine(newUser) << endl;

	file.close();
}

void insertNewUser(vector <UserStorage>& users) {
	UserStorage data;

	data = userDataGathering();

	if (users.empty())
		data.userId = 1;
	else
		data.userId = users.back().userId + 1;

	users.push_back(data);
	saveNewUser(data);
}

int loadContactsFromFile(vector <ContactStorage>& contacts, int currentUserId) {
	fstream file;
	string line;
	ContactStorage data;
	int lastIdFromNotLoadedContact = 0;

	file.open("adresaci.txt", ios::in);

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
		if (currentUserId == data.userId)
			contacts.push_back(ContactStorage(data));
		else
			lastIdFromNotLoadedContact = data.id;
	}

	file.close();

	return lastIdFromNotLoadedContact;
}

string mergeContactDataInToLine(ContactStorage data) {
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

void saveNewContactToFile(ContactStorage newContact) {
	fstream dataBase;

	dataBase.open("adresaci.txt", ios::out | ios::app);
	dataBase << mergeContactDataInToLine(newContact) << endl;

	dataBase.close();
}

void insertNewContact(vector <ContactStorage>& contacts, int userId, int lastUnloadContactId) {
	ContactStorage data;

	data = contactDataGathering();
	data.id = checkLastId(lastUnloadContactId, contacts.back().id) + 1;
	data.userId = userId;
	contacts.push_back(data);
	saveNewContactToFile(data);

	cout << "Nowy kontakt dodany." << endl;
	system("pause");

	return;
}

void displayContactByName(vector <ContactStorage> contacts) {
	string searchingName;

	if (checkIfEmptyContacts(contacts))
		return;

	cout << "Podaj Imie ktore chcesz wyszukac: ";
	searchingName = getWholeLine();
	system("cls");

	for (vector <ContactStorage>::iterator i = contacts.begin(); i < contacts.end(); i++) {
		if (i->name == searchingName)
			displayRecord(i);
	}

	system("pause");
}

void displayContactBySurname(vector <ContactStorage> contacts) {
	string searchingSurname;

	if (checkIfEmptyContacts(contacts))
		return;

	cout << "Podaj Nazwisko ktore chcesz wyszukac: ";
	searchingSurname = getWholeLine();
	system("cls");

	for (vector <ContactStorage>::iterator i = contacts.begin(); i < contacts.end(); i++) {
		if (i->surname == searchingSurname)
			displayRecord(i);
	}

	system("pause");;
}

void displayAllContacts(vector <ContactStorage> contacts) {
	if (checkIfEmptyContacts(contacts))
		return;

	system("cls");

	for (vector <ContactStorage>::iterator i = contacts.begin(); i < contacts.end(); i++) {
		displayRecord(i);
	}

	system("pause");;
}

ContactStorage extractingData(string line) {
	stringstream ss(line);
	string temp;
	ContactStorage data;

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

void saveToFileAfterContactRemove(int contactToDeleteId) {
	fstream dataBase, tempDataBase;
	string line;

	dataBase.open("adresaci.txt", ios::in);
	tempDataBase.open("adresaci_temp.txt", ios::out | ios::trunc);

	while (getline(dataBase, line)) {
		if (stoi((line.substr(0, line.find('|')))) != contactToDeleteId)
			tempDataBase << line << endl;
	}

	dataBase.close();
	tempDataBase.close();

	remove("adresaci.txt");
	rename("adresaci_temp.txt", "adresaci.txt");
}

void saveToFileAfterContactEdit(vector <ContactStorage>::iterator contactToEdit) {
	fstream dataBase, tempDataBase;
	string line;
	ContactStorage dataFromExistingLibrary;

	dataBase.open("adresaci.txt", ios::in);
	tempDataBase.open("adresaci_temp.txt", ios::out | ios::trunc);

	while (getline(dataBase, line)) {
		dataFromExistingLibrary = extractingData(line);
		if (stoi((line.substr(0, line.find('|')))) != contactToEdit->id)
			tempDataBase << line << endl;
		else if (stoi((line.substr(0, line.find('|')))) == contactToEdit->id)
			tempDataBase << mergeContactDataInToLine(*contactToEdit) << endl;
	}

	dataBase.close();
	tempDataBase.close();

	remove("adresaci.txt");
	rename("adresaci_temp.txt", "adresaci.txt");
}

char getOneChar() {
	string input = "";
	char sign = { 0 };

	while (true) {
		cin.sync();
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
	string line;
	int number = 0;

	while (true) {
		cin.sync();
		getline(cin, line);
		stringstream input(line);
		if (input >> number)
			break;
		cout << "Niepoprawne ID wpisz ponownie" << endl;
	}

	return number;
}

void removeContactSequence(vector <ContactStorage>& contacts) {
	int idToDelete;
	vector <ContactStorage>::iterator contactToRemove;

	if (checkIfEmptyContacts(contacts))
		return;

	displayAllContacts(contacts);
	cout << endl;
	cout << "Podaj ID kontaktu ktory chcesz usunac: ";
	idToDelete = getId();

	system("cls");
	contactToRemove = find_if(contacts.begin(), contacts.end(), [idToDelete](const ContactStorage& vi) {return vi.id == idToDelete; });
	if (contactToRemove == contacts.end()) {
		cout << "Nie znaleziono takiego ID ";
		system("pause");;
		return;
	}

	displayRecord(contactToRemove);
	cout << endl;
	cout << "Jesli chcesz usunac powyzszy kontakt wcisnij 't' " << endl;

	if (getOneChar() == 't') {
		saveToFileAfterContactRemove(contactToRemove->id);
		contacts.erase(contactToRemove);
		cout << "Kontakt został usuniety " << endl;
		system("pause");;
	}

	return;
}

void editRecordMenu(vector <ContactStorage>::iterator& contactToEdit) {
	char editChoice;

	while (1) {
		system("cls");
		displayRecord(contactToEdit);
		displayEditMenu();
		editChoice = getOneChar();
		switch (editChoice) {
		case '1':
			cout << "Edytuj imie: " << endl;
			contactToEdit->name = getWholeLine();
			break;
		case '2':
			cout << "Edytuj nazwisko: " << endl;
			contactToEdit->surname = getWholeLine();
			break;
		case '3':
			cout << "Edytuj nr. tel: " << endl;
			contactToEdit->phoneNumber = getWholeLine();
			break;
		case '4':
			cout << "Edytuj email: " << endl;
			contactToEdit->email = getWholeLine();
			break;
		case '5':
			cout << "Edytuj adres: " << endl;
			contactToEdit->address = getWholeLine();
			break;
		case '6':
			return;
			break;
		default:
			break;
		}
	}
}

void editContactSequence(vector <ContactStorage>& contacts) {
	int idToEdit;
	vector <ContactStorage>::iterator contactToEdit;

	if (checkIfEmptyContacts(contacts))
		return;

	displayAllContacts(contacts);
	cout << endl;
	cout << "Podaj ID kontaktu ktory chcesz edytowac: ";
	idToEdit = getId();
	system("cls");

	contactToEdit = find_if(contacts.begin(), contacts.end(), [idToEdit](const ContactStorage& vi) {return vi.id == idToEdit; });//wyrazenie lambda

	if (contactToEdit == contacts.end()) {
		cout << "Nie znaleziono takiego ID ";
		system("pause");;
		return;
	}

	editRecordMenu(contactToEdit);
	saveToFileAfterContactEdit(contactToEdit);
}

void internalMenu(vector <UserStorage>& users, int userId) {
	vector <ContactStorage> contacts;
	char menuChoice;
	int lastUnloadedContactId = 0;

	if (userId == 0)
		return;

	lastUnloadedContactId = loadContactsFromFile(contacts, userId);

	while (1) {
		system("cls");
		displayInternalMenu();
		menuChoice = getOneChar();
		switch (menuChoice) {
		case '1':
			insertNewContact(contacts, userId, lastUnloadedContactId);
			break;
		case '2':
			displayContactByName(contacts);
			break;
		case '3':
			displayContactBySurname(contacts);
			break;
		case '4':
			displayAllContacts(contacts);
			break;
		case '5':
			removeContactSequence(contacts);
			break;
		case '6':
			editContactSequence(contacts);
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
	vector <UserStorage> users;
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
