#pragma once

int findQuizIndexByName(string quizName, const vector<Quiz*>& quizzes) {
	for (size_t i = 0; i < quizzes.size(); i++) {
		if (quizzes[i]->GetQuizname() == quizName) {
			return static_cast<int>(i);
		}
	}
	return -1;
}

void writeQuizNamesToFile(const vector<Quiz*>& quizzes) {
	ofstream file("Quiz_names.txt", ios::app);

	if (file.is_open()) {
		for (const Quiz* quiz : quizzes) {
			file << quiz->GetQuizname() << endl;
		}

		file.close();
	}
	else {
		cout << "\n\t\t\t\tError: Unable to write to file." << endl;
	}
}

vector<string> readQuizNamesFromFile() {
	vector<string> quizNames;
	ifstream file("quiz_names.txt", ios::in);

	if (file.is_open()) {
		string quizName;
		while (getline(file, quizName)) {
			quizNames.push_back(quizName);
		}

		file.close();
	}
	else {
		cout << "\n\t\t\t\tError: Unable to read file." << endl;
	}

	return quizNames;
}

class Admin :public User {
private:
	string _securitycode;

public:
	Admin(string name, string surname, int age, string email, string username, string password, string securitycode)
		: User(name, surname, age, email, username, password)
	{
		SetSecuritycode(securitycode);
	}

	string GetSecuritycode() {
		return this->_securitycode;
	}

	void SetSecuritycode(string securitycode) {
		if (securitycode.length() == 3) {
			bool isDigit = true;

			for (char c : securitycode) {
				if (!isdigit(c)) {
					isDigit = false;
					break;
				}
			}

			if (isDigit) {
				this->_securitycode = securitycode;
				return;
			}
		}
		throw invalid_argument("\n\t\t\t\t\t Invalid Security Code!");
	}

	static void WriteAdminsToFile(const vector<Admin>& admins) {
		ofstream file("admins.txt", ios::out);

		if (file.is_open()) {
			for (Admin admin : admins) {
				file << admin.GetName() << ","
					<< admin.GetSurname() << ","
					<< admin.GetAge() << ","
					<< admin.GetEmail() << ","
					<< admin.GetUsername() << ","
					<< admin.GetPassword() << ","
					<< admin.GetSecuritycode() << endl;
			}

			file.close();
		}
		else {
			cout << "\n\t\t\t\t\t Error: Unable to write to file." << endl;
		}
	}

	static void SignUpAdmin(vector<Admin>& admins) {
		string name, surname, email, username, password, securityCode;
		int age;
		cout << "\n\t\t\t\t\t    Enter your Name: ";
		cin >> name;

		cout << "\n\t\t\t\t\t    Enter your Surname: ";
		cin >> surname;

		cout << "\n\t\t\t\t\t    Enter your Age: ";
		cin >> age;
		cin.ignore();
		cin.clear();

		cout << "\n\t\t\t\t\t    Enter your Email: ";
		cin >> email;

		cout << "\n\t\t\t\t\t    Enter your username: ";
		cin >> username;

		cout << "\n\t\t\t\t\t    Enter your password: ";
		cin >> password;

		cout << "\n\t\t\t\t\t    Enter your security code: ";
		cin >> securityCode;

		Admin newAdmin(name, surname, age, email, username, password, securityCode);
		admins.push_back(newAdmin);

		WriteAdminsToFile(admins);

		cout << "\n\t\t\t\t\t   Admin Sign Up Successful!" << endl;
		cout << "\n\t\t\t\t\t   Welcome, " << username << "!" << endl;
	}

	static Admin SignInAdmin(const vector<Admin>& admins) {
		string username, password, securityCode;

		cout << "\n\t\t\t\t\t   Enter Admin username: ";
		cin >> username;

		cout << "\n\t\t\t\t\t   Enter Admin password: ";
		cin >> password;

		cout << "\n\t\t\t\t\t   Enter Admin security code: ";
		cin >> securityCode;

		for (Admin admin : admins) {
			if (admin.GetUsername() == username && admin.GetPassword() == password && admin.GetSecuritycode() == securityCode) {
				return admin;
			}
		}

		throw exception(" Incorrect username, password, or security code.");
	}

	void  Design() {
		SetColor(7, 7);
		system("cls");

		for (int i = 0; i < 35; i++)
			cout << " ";

		SetColor(4, 7);
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "\t\t\t\t\t  ADMIN:  " << this->GetUsername() << "   " << endl;

		SetColor(7, 7);
		for (int i = 0; i < 35; i++)
			cout << " ";

		SetColor(4, 7);
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl << endl;
		delay(1000);
	}

	void openPage() override {
		vector<Quiz*> quizzes;
		while (true) {
			Design();

			cout << "\t\t\t\t\t [1] Create New Quiz          " << endl
				<< "\t\t\t\t\t [2] Add New Question         " << endl
				<< "\t\t\t\t\t [3] Modify Existing Question " << endl
				<< "\t\t\t\t\t [4] Delete Question          " << endl
				<< "\t\t\t\t\t [5] Go Back to Main Menu     " << endl
				<< "\t\t\t\t\t [0] Exit                     " << endl;

			int choice;
			cout << "\n\t\t\t\t\t Enter your choice: ";
			cin >> choice;
			cin.ignore();

			switch (choice) {
			case 1: {
				cout << "\a\a\a";
				Design();

				string quizName;
				cout << "\n\t\t\t\t\tEnter the name of the new quiz: ";
				getline(cin, quizName);

				Quiz* newQuiz = new Quiz(quizName);

				quizzes.push_back(newQuiz);

				while (true) {
					string questionText;
					cout << "\nEnter the question text (or 'exit' to finish adding questions): ";
					getline(cin, questionText);

					if (questionText == "exit") {
						break;
					}

					string answer1, answer2, answer3, answer4;
					cout << "\n\t\t\t\t\tEnter answer option 1: ";
					getline(cin, answer1);
					cout << "\n\t\t\t\t\tEnter answer option 2: ";
					getline(cin, answer2);
					cout << "\n\t\t\t\t\tEnter answer option 3: ";
					getline(cin, answer3);
					cout << "\n\t\t\t\t\tEnter answer option 4: ";
					getline(cin, answer4);

					int correctOption;
					cout << "\n\t\t\t\t\tEnter correct answer option (1 - 4): ";
					cin >> correctOption;
					cin.ignore();

					if (correctOption < 1 || correctOption > 4) {
						cout << "\n\t\t\t\t\tInvalid correct answer option. Please try again..." << endl;
						delay(2000);
						continue;
					}

					newQuiz->AddQuestion(questionText, answer1, answer2, answer3, answer4, correctOption);
				}

				char saveChoice;
				cout << "\n\n\t\t\t\tDo you want to save the quiz to a file? (y(Y)/n(N)): ";
				cin >> saveChoice;
				cin.ignore();

				if (saveChoice == 'y' || saveChoice == 'Y') {
					newQuiz->SaveToFile();
					writeQuizNamesToFile(quizzes);
				}
				else {
					delete newQuiz;
					return;
				}

				break;
			}
			case 2: {
				cout << "\a\a\a";
				vector<string> quizNames = readQuizNamesFromFile();
				Design();
				if (quizNames.empty()) {
					cout << "\n\t\t\t\tNo quiz exists yet. Please create a new quiz first." << endl;
					delay(2000);
					break;
				}

				cout << "\n\t\t\t\t\t   Available Quizzes:   " << endl;
				for (const string& name : quizNames) {
					cout << "\t\t\t\t\t\t" << name << endl;
				}

				string quizName;
				cout << "\n\t\t\tEnter the name of the quiz to which you want to add a new question: ";
				getline(cin, quizName);

				int quizIndex = findQuizIndexByName(quizName, quizzes);
				if (quizIndex == -1) {
					bool existsInList = false;
					for (const string& name : quizNames) {
						if (name == quizName) {
							existsInList = true;
							break;
						}
					}

					if (existsInList) {
						Quiz* newQuiz = new Quiz(quizName);
						quizzes.push_back(newQuiz);
						quizIndex = quizzes.size() - 1;
					}
					else {
						cout << "\n\t\t Quiz with the this name not found in the list. Please try again..." << endl;
						delay(2000);
						break;
					}
				}

				Quiz& chosenQuiz = *quizzes[quizIndex];

				string questionText;
				cout << "\n\t\t\tEnter the question text (or 'exit' to finish adding questions): ";
				getline(cin, questionText);

				while (questionText != "exit") {
					string answer1, answer2, answer3, answer4;
					cout << "\n\t\t\t\t\tEnter answer option 1: ";
					getline(cin, answer1);
					cout << "\n\t\t\t\t\tEnter answer option 2: ";
					getline(cin, answer2);
					cout << "\n\t\t\t\t\tEnter answer option 3: ";
					getline(cin, answer3);
					cout << "\n\t\t\t\t\tEnter answer option 4: ";
					getline(cin, answer4);

					int correctOption;
					cout << "\n\t\t\t\t\tEnter correct answer option (1 - 4): ";
					cin >> correctOption;
					cin.ignore();

					if (correctOption < 1 || correctOption > 4) {
						cout << "\n\t\t\t\t\tInvalid correct answer option. Please try again..." << endl;
						delay(2000);
						continue;
					}

					chosenQuiz.AddQuestion(questionText, answer1, answer2, answer3, answer4, correctOption);

					cout << "\n\t\tEnter the question text (or 'exit' to finish adding questions): ";
					getline(cin, questionText);
				}

				char saveChoice;
				cout << "\n\t\t\t\tDo you want to save the quiz to a file? (y(Y)/n(N)): ";
				cin >> saveChoice;
				cin.ignore();

				if (saveChoice == 'y' || saveChoice == 'Y') {
					chosenQuiz.AppendToFile();
				}
				else {
					delete& chosenQuiz;
					return;
				}

				break;
			}

			case 3: {
				cout << "\a\a\a";
				vector<Quiz*> quizzes;
				vector<string> quizNames = readQuizNamesFromFile();
				Design();

				if (quizNames.empty()) {
					cout << "\n\t\t\tNo quiz exists yet. Please create a new quiz first." << endl;
					delay(1000);
					break;
				}

				cout << "\n\t\t\t\t\t   Available Quizzes:   " << endl;
				for (const string& name : quizNames) {
					cout << "\t\t\t\t\t\t" << name << endl;
				}

				string quizName;
				cout << "\n\t\t\tEnter the name of the quiz containing the question you want to modify: ";
				getline(cin, quizName);

				int quizIndex = findQuizIndexByName(quizName, quizzes);
				if (quizIndex == -1) {
					bool existsInList = false;
					for (const string& name : quizNames) {
						if (name == quizName) {
							existsInList = true;
							break;
						}
					}

					if (existsInList) {
						Quiz* newQuiz = new Quiz(quizName);
						quizzes.push_back(newQuiz);
						quizIndex = quizzes.size() - 1;
					}
					else {
						cout << "\n\t\t\tQuiz with the this name not found in the list. Please try again..." << endl;
						delay(2000);
						break;
					}
				}

				Quiz& chosenQuiz = *quizzes[quizIndex];

				try {
					chosenQuiz.LoadFromFile(chosenQuiz, quizName);
				}
				catch (const exception& e) {
					cout << "Error loading quiz data: " << e.what() << endl;
					break;
				}

				if (chosenQuiz.GetQuestionCount() == 0) {
					cout << "\n\t\t\tNo questions found in the selected quiz. Please add questions first." << endl;
					delay(2000);
					break;
				}

				cout << "\n\t\t\tSelect the question you want to modify (enter the question number):" << endl;
				chosenQuiz.DisplayQuestions();

				int selectedQuestion;
				cout << "\n\t\t\t\tEnter the question number: ";
				cin >> selectedQuestion;
				cin.ignore();

				if (selectedQuestion < 1 || selectedQuestion > chosenQuiz.GetQuestionCount()) {
					cout << "\n\t\t\t\tInvalid question number. Please try again..." << endl;
					delay(2000);
					break;
				}

				Question& chosenQuestion = *chosenQuiz.GetQuestionByIndex(selectedQuestion - 1);

				cout << "Question: " << chosenQuestion.GetQuestionText() << endl;
				vector<Answer*> answers = chosenQuestion.GetAnswers();
				for (Answer* answer : answers) {
					for (int i = 0; i < 4; i++) {
						cout << "\tAnswer " << i + 1 << ": " << answer->GetAnswerVariant(i) << endl;
					}
				}

				string newQuestionText;
				cout << "\n\tEnter the new question text (or 'exit' to keep the current question): ";
				getline(cin, newQuestionText);

				if (newQuestionText != "exit") {
					chosenQuestion.SetQuestionText(newQuestionText);
				}


				vector<Answer*> answers1 = chosenQuestion.GetAnswers();
				for (Answer* answer : answers1) {
					for (int i = 0; i < 4; i++) {
						string newAnswerText;
						cout << "\nEnter the new answer for option " << i + 1 << " (or 'exit' to keep the current answer): ";
						getline(cin, newAnswerText);

						if (newAnswerText != "exit") {
							answer->SetAnswerVariant(i, newAnswerText);
						}
					}
				}

				int newCorrectAnswerIndex;
				cout << "\n\t\t\t\tEnter the new correct answer index (1-4) for the question: ";
				cin >> newCorrectAnswerIndex;
				cin.ignore();

				if (newCorrectAnswerIndex >= 1 && newCorrectAnswerIndex <= 4) {
					chosenQuestion.SetCorrectAnswerIndex(newCorrectAnswerIndex - 1);
				}
				else {
					cout << "\n\t\t\t\tInvalid correct answer index. Please try again..." << endl;
					delay(2000);
					break;
				}

				char saveChoice;
				cout << "\n\t\t\t\tDo you want to save the quiz to a file? (y(Y)/n(N)): ";
				cin >> saveChoice;
				cin.ignore();

				if (saveChoice == 'y' || saveChoice == 'Y') {
					chosenQuiz.SaveToFile();
				}
				else {
					delete& chosenQuiz;
					return;
				}

				break;
			}
			case 4: {
				cout << "\a\a\a";
				vector<Quiz*> quizzes;
				vector<string> quizNames = readQuizNamesFromFile();
				Design();

				if (quizNames.empty()) {
					cout << "\n\t\t\tNo quiz exists yet. Please create a new quiz first." << endl;
					delay(1000);
					break;
				}

				cout << "\n\t\t\t\t\t   Available Quizzes:   " << endl;
				for (const string& name : quizNames) {
					cout << "\t\t\t\t\t\t" << name << endl;
				}

				string quizName;
				cout << "\n\t\t\tEnter the name of the quiz containing the question you want to delete: ";
				getline(cin, quizName);

				int quizIndex = findQuizIndexByName(quizName, quizzes);
				if (quizIndex == -1) {
					bool existsInList = false;
					for (const string& name : quizNames) {
						if (name == quizName) {
							existsInList = true;
							break;
						}
					}

					if (existsInList) {
						Quiz* newQuiz = new Quiz(quizName);
						quizzes.push_back(newQuiz);
						quizIndex = quizzes.size() - 1;
					}
					else {
						cout << "\n\t\t\tQuiz with the provided name not found in the list. Please try again..." << endl;
						delay(2000);
						break;
					}
				}

				Quiz& chosenQuiz = *quizzes[quizIndex];

				try {
					chosenQuiz.LoadFromFile(chosenQuiz, quizName);
				}
				catch (const exception& e) {
					cout << "Error loading quiz data: " << e.what() << endl;
					break;
				}

				if (chosenQuiz.GetQuestionCount() == 0) {
					cout << "\n\t\t\tNo questions found in the selected quiz. Please add questions first." << endl;
					delay(2000);
					break;
				}

				cout << "\n\t\t\tSelect the question you want to delete (enter the question number):" << endl;
				chosenQuiz.DisplayQuestions();

				int selectedQuestion;
				cout << "\n\t\t\t\tEnter the question number: ";
				cin >> selectedQuestion;
				cin.ignore();

				if (selectedQuestion < 1 || selectedQuestion > chosenQuiz.GetQuestionCount()) {
					cout << "\n\t\t\t\tInvalid question number. Please try again..." << endl;
					delay(2000);
					break;
				}

				chosenQuiz.DeleteQuestion(selectedQuestion - 1);
				cout << "\n\t\t\t\t\tQuestion has been deleted." << endl;
				delay(2000);

				char saveChoice;
				cout << "\n\t\t\t\tDo you want to save the quiz to a file? (y(Y)/n(N)): ";
				cin >> saveChoice;
				cin.ignore();

				if (saveChoice == 'y' || saveChoice == 'Y') {
					chosenQuiz.SaveToFile();
				}
				else {
					delete& chosenQuiz;
					return;
				}
				break;
			}
			case 5: {
				cout << "\a\a\a";
				return;
			}
			case 0: {
				cout << "\a\a\a";
				SetColor(15, 0);
				exit(0);
			}
			default: {
				cout << "\a\a\a";
				cout << "\n\t\t\t\t\tInvalid choice. Please enter a valid option." << endl;
				cout << "\n\t\t\t\t\t";
				system("pause");
				break;
			}
			}
		}
	}
};

void ReadAdminsFromFile(vector<Admin>& admins) {
	ifstream adminFile("admins.txt", ios::in);
	if (!adminFile) {
		cout << "\n\t\t\t\t\tError: Unable to open the file for reading." << endl;
		return;
	}

	string line;
	while (getline(adminFile, line)) {
		string name, surname, email, username, password, securityCode;
		int age;

		size_t pos = 0;
		pos = line.find(',');
		name = line.substr(0, pos);
		line.erase(0, pos + 1);

		pos = line.find(',');
		surname = line.substr(0, pos);
		line.erase(0, pos + 1);

		pos = line.find(',');
		age = stoi(line.substr(0, pos));
		line.erase(0, pos + 1);

		pos = line.find(',');
		email = line.substr(0, pos);
		line.erase(0, pos + 1);

		pos = line.find(',');
		username = line.substr(0, pos);
		line.erase(0, pos + 1);

		pos = line.find(',');
		password = line.substr(0, pos);
		line.erase(0, pos + 1);

		securityCode = line;

		Admin admin(name, surname, age, email, username, password, securityCode);
		admins.push_back(admin);
	}

	adminFile.close();
}
