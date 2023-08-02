#pragma once

class User {
private:
	string _name;
	string _surname;
	int _age;
	string _email;
	string _username;
	string _password;

public:
	User() = delete;
	User(string username) {
		SetUsername(username);
	}

	User(string name, string surname, int age, string email, string username, string password) {
		SetName(name);
		SetSurname(surname);
		SetAge(age);
		SetEmail(email);
		SetUsername(username);
		SetPassword(password);
	}

	string GetName() {
		return this->_name;
	}

	string GetSurname() {
		return this->_surname;
	}

	int GetAge() {
		return this->_age;
	}

	string GetEmail() {
		return this->_email;
	}

	string GetUsername() {
		return this->_username;
	}

	string GetPassword() {
		return this->_password;
	}

	void SetName(string name) {
		if (name.length() > 3 && isupper(name[0])) {
			bool is_Letters = true;
			for (char ch : name) {
				if (!isalpha(ch)) {
					is_Letters = false;
					break;
				}
			}

			if (is_Letters)
				this->_name = name;
			else
				throw invalid_argument("Name must contain only letters!");
		}
		else
			throw invalid_argument("Name's length must be greater than 3 and start with an uppercase letter!");
	}

	void SetSurname(string surname) {
		if (surname.length() > 3 && isupper(surname[0])) {
			bool is_Letters = true;
			for (char ch : surname) {
				if (!isalpha(ch)) {
					is_Letters = false;
					break;
				}
			}

			if (is_Letters)
				this->_surname = surname;
			else
				throw invalid_argument("Surname must contain only letters!");
		}
		else
			throw invalid_argument("Surname's length must be greater than 3 and start with an uppercase letter!");
	}

	void SetAge(int age) {
		if (age >= 6) {
			this->_age = age;
			return;
		}
		throw invalid_argument("Age must be greater than or equal to 6!");
	}

	void SetEmail(string email) {
		bool symbol = false;
		bool dotcom = false;

		for (char c : email) {
			if (c == '@')
				symbol = true;
			if (c == '.' && email.substr(email.size() - 4) == ".com")
				dotcom = true;
		}

		if (!email.empty() && symbol && dotcom) {
			this->_email = email;
			return;
		}

		throw invalid_argument("Invalid email: must contain the '@' symbol and end with '.com'");
	}

	void SetUsername(string username) {
		if (username.length() >= 10) {
			this->_username = username;
			return;
		}
		throw invalid_argument("Invalid username:  [1]->length must be greater than 10");
	}

	void SetPassword(string password) {
		bool hasSymbol = false;

		for (char c : password) {
			if (c == '_' || c == '.')
				hasSymbol = true;
		}

		if (password.length() >= 8 && isupper(password[0]) && hasSymbol) {
			this->_password = password;
			return;
		}
		throw invalid_argument("Invalid password: must be at least 8 characters, start with an uppercase letter, and contain '_' or '.' symbols");
	}

	virtual void openPage() = 0;

};
