#pragma once

class Player :public User {
private:
	double _score;
	int _correctAnswers;
	int _incorrectAnswers;
	int _pass;

public:
	Player(string username, int correctAnswers, int incorrectAnswers, int passAnswers, double score)
		: User(username), _correctAnswers(correctAnswers), _incorrectAnswers(incorrectAnswers), _pass(passAnswers), _score(score) {}

	Player(string name, string surname, int age, string email, string username, string password)
		: User(name, surname, age, email, username, password), _score(0.0), _correctAnswers(0), _incorrectAnswers(0), _pass(0) {}


	double GetScore() const {
		return this->_score;
	}

	int GetCorrectAnswers() const {
		return this->_correctAnswers;
	}

	int GetIncorrectAnswers() const {
		return this->_incorrectAnswers;
	}

	int GetPassAnswers() const {
		return this->_pass;
	}

	void IncrementCorrectAnswers() {
		this->_correctAnswers++;
	}

	void IncrementIncorrectAnswers() {
		this->_incorrectAnswers++;
	}

	void IncrementPassAnswers() {
		this->_pass++;
	}

	void SetScore(double score) {
		if (score >= 0 && score <= 100) {
			this->_score = score;
			return;
		}
		throw invalid_argument("Invalid score!");
	}

	static void WritePlayersToFile(const vector<Player>& players) {
		ofstream file("players.txt", ios::out);

		if (file.is_open()) {
			for (Player player : players) {
				file << player.GetName() << ","
					<< player.GetSurname() << ","
					<< player.GetAge() << ","
					<< player.GetEmail() << ","
					<< player.GetUsername() << ","
					<< player.GetPassword() << endl;
			}

			file.close();
		}
		else {
			cout << "\n\t\t\t\t\tError: Unable to write to file." << endl;
		}
	}

	static void SignUpPlayer(vector<Player>& players) {
		string name, surname, email, username, password;
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

		Player newPlayer(name, surname, age, email, username, password);
		players.push_back(newPlayer);

		WritePlayersToFile(players);

		cout << "\n\t\t\t\t\t   Sign Up Successful!" << endl;
		cout << "\n\t\t\t\t\t   Welcome, " << username << "!" << endl;
	}

	static Player SignInPlayer(vector<Player> players) {
		string username, password;

		cout << "\n\t\t\t\t\t   Enter Player username: ";
		cin >> username;

		cout << "\n\t\t\t\t\t   Enter Player password: ";
		cin >> password;

		for (Player player : players) {
			if (player.GetUsername() == username && player.GetPassword() == password) {
				return player;
			}
		}

		throw exception("Incorrect username or password.");
	}

	void displayQuizNames(const vector<Quiz>& quizzes) const {
		cout << "\n\t\t\tAvailable Quizzes:" << endl;
		for (const Quiz& quiz : quizzes) {
			cout << "\t\t\t- " << quiz.GetQuizname() << endl;
		}
	}

	void Design() {
		SetColor(7, 7);
		system("cls");

		SetColor(4, 7);
		cout << "\n\t\t\t\t\t     WELCOME TO THE GAME   " << endl << endl;
		SetColor(7, 7);
		for (int i = 0; i < 35; i++)
			cout << " ";

		SetColor(4, 7);
		cout << "   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "\t\t\t\t\t    PLAYER:  " << this->GetUsername() << "   " << endl;

		SetColor(7, 7);
		for (int i = 0; i < 35; i++)
			cout << " ";

		SetColor(4, 7);
		cout << "   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl << endl;
		delay(1000);
	}

	static void SavePlayerResultsToFile(const vector<Player>& players) {
		ofstream file("Players_Results.txt", ios::app);

		if (file.is_open()) {
			for (Player player : players) {
				file << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
				file << " Player Username:\t" << player.GetUsername() << endl
					<< " Correct Answers:\t" << player.GetCorrectAnswers() << endl
					<< " Incorrect Answers:\t" << player.GetIncorrectAnswers() << endl
					<< " Passed Answers:\t" << player.GetPassAnswers() << endl
					<< " PLayer Score:\t\t" << player.GetScore() << "%" << endl;
				file << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
			}
			file.close();
		}
		else {
			cout << "\n\t\t\t\t\tError: Unable to write player results to file." << endl;
		}
	}

	void ReadPlayerResultsFromFile() {
		ifstream inFile("Players_Results.txt", ios::in);

		if (!inFile.is_open()) {
			cout << "Error: Unable to open the file 'Players_Results.txt' for reading." << endl;
			return;
		}

		string line;
		while (getline(inFile, line)) {
			cout << line << endl;
		}

		inFile.close();
	}

	void ReadPlayersFromFile(vector<Player>& players) {
		ifstream playerFile("Players_Results.txt");
		if (!playerFile) {
			cout << "Error: Unable to open the file 'Players_Results.txt' for reading." << endl;
			return;
		}
		players.clear();

		string line;
		while (getline(playerFile, line)) {
			if (line == "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~") {
				string username;
				double score;

				while (getline(playerFile, line) && line != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~") {
					if (line.find("Player Username:\t") != -1) {
						username = line.substr(line.find(":") + 1);
					}
					else if (line.find("PLayer Score:\t") != -1) {
						score = stod(line.substr(line.find(":") + 1));
					}
				}

				Player player(username, 0, 0, 0, score);
				players.push_back(player);
			}
		}

		playerFile.close();
	}


	void openPage() override {
		vector<Quiz*> quizzes;
		vector<Player> playerss;

		while (true) {
			Design();

			cout << "\t\t\t\t\t [1] Start Quiz           " << endl
				<< "\t\t\t\t\t [2] Players Result        " << endl
				<< "\t\t\t\t\t [3] Leader Board         " << endl
				<< "\t\t\t\t\t [4] Go Back to Main Menu " << endl
				<< "\t\t\t\t\t [0] Exit                 " << endl;

			int choice;
			cout << "\n\t\t\t\t\t Enter your choice: ";
			cin >> choice;
			cin.ignore();

			switch (choice) {
			case 1: {
				cout << "\a\a\a";
				Design();
				vector<string> quizNames = readQuizNamesFromFile();
				if (quizNames.empty()) {
					cout << "\n\t\t\t\tNo quiz exists yet. Please contact the admin to create a new quiz." << endl;
					delay(2000);
					break;
				}

				cout << "\n\t\t\t\t\t   Available Quizzes:   " << endl;
				for (const string& name : quizNames) {
					cout << "\t\t\t\t\t\t" << name << endl;
				}

				string quizName;
				cout << "\n\t\t\t\tEnter the name of the quiz you want to start: ";
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

				system("cls");
				Design();
				try {
					chosenQuiz.LoadFromFile(chosenQuiz, quizName);
				}
				catch (const exception& e) {
					cout << "\n\t\t\t\tError loading quiz data: " << e.what() << endl;
					break;
				}
				chosenQuiz.ShuffleQuestions();

				cout << "\n\t\t\t\t\tStarting quiz: " << chosenQuiz.GetQuizname() << endl;

				int totalQuestions = chosenQuiz.GetQuestionCount();
				int correctAnswers = 0;

				if (totalQuestions == 0) {
					cout << "\n\t\t\tNo questions found in the selected quiz." << endl;
					delay(2000);
					break;
				}

				string player_UserName = this->GetUsername();
				Player currentPlayer(player_UserName, 0, 0, 0, 0.0);

				for (int i = 0; i < totalQuestions; i++) {
					Question* currentQuestion = chosenQuiz.GetQuestionByIndex(i);

					cout << "\n  Question " << i + 1 << ": " << currentQuestion->GetQuestionText() << endl;
					vector<Answer*> answers = currentQuestion->GetAnswers();
					for (Answer* answer : answers) {
						for (int i = 0; i < 4; i++) {
							cout << "\tAnswer " << i + 1 << ": " << answer->GetAnswerVariant(i) << endl;
						}
					}

					string userInput;
					cout << "\n\t\t\t\tYour Answer (Enter the option number (1 - 4) or 'P' to pass): ";
					cin >> userInput;
					cin.ignore();

					if (userInput == "P" || userInput == "p") {
						cout << "Skipping to the next question..." << endl;
						currentPlayer.IncrementPassAnswers();
					}
					else {
						int userChoice = stoi(userInput);
						if (userChoice >= 1 && userChoice <= 4) {
							bool isCorrect = currentQuestion->CheckAnswer(userChoice - 1);
							if (isCorrect) {
								cout << "\n\t\t\t\t\t\tCorrect answer!" << endl;
								delay(1000);
								correctAnswers++;
								currentPlayer.IncrementCorrectAnswers();
							}
							else {
								cout << "\n\t\t\t\t\t\tIncorrect answer!" << endl;
								delay(1000);
								currentPlayer.IncrementIncorrectAnswers();
							}
						}
						else {
							cout << "Invalid option number. Skipping to the next question..." << endl;
							currentPlayer.IncrementPassAnswers();
						}
					}
					Design();
				}

				double percentage = static_cast<double>(correctAnswers) / totalQuestions * 100;
				cout << "\n\t\t\t  Quiz ended! You answered " << correctAnswers << " out of " << totalQuestions << " questions correctly." << endl;
				cout << "\n\t\t\t\t\t     Your score: " << percentage << "%" << endl;

				currentPlayer.SetScore(percentage);
				playerss.push_back(currentPlayer);

				SavePlayerResultsToFile(playerss);

				delay(5000);

				break;
			}
			case 2: {
				cout << "\a\a\a";
				Design();
				ReadPlayerResultsFromFile();
				cout << "\n\t\t\t\t\tDo you want to leave? (Y/N): ";

				char choice;
				cin >> choice;
				if (choice == 'Y' || choice == 'y') {
					return;
				}
				delay(5000);
				break;
			}
			case 3: {
				cout << "\a\a\a";
				Design();

				vector<Player> players;
				ReadPlayersFromFile(players);

				if (players.empty()) {
					cout << "\n\t\t\t\t\tNo players found in the file." << endl;
					delay(2000);
					break;
				}

				sort(players.begin(), players.end(), [](const Player& a, const Player& b) {
					return a.GetScore() > b.GetScore();
					});

				cout << "\t  Rank\t\t\t\t  Username\t\t\t  Score" << endl;
				cout << "\t========\t\t\t============\t\t\t=========" << endl;
				for (size_t i = 0; i < players.size(); i++) {
					cout << "\t   " << i + 1 << "\t\t\t" << players[i].GetUsername() << "\t\t\t  " << players[i].GetScore() << "%" << endl;
				}

				cout << "\n\n\n\t\t\t\t\tDo you want to leave? (Y/N): ";

				char choice;
				cin >> choice;
				if (choice == 'Y' || choice == 'y') {
					return;
				}
				delay(5000);
				break;
			}
			case 4: {
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


void ReadPlayersFromFile(vector<Player>& players) {
	ifstream playerFile("players.txt");
	if (!playerFile) {
		cout << "\n\t\t\t\t\tError: Unable to open the file for reading." << endl;
		return;
	}

	string line;
	while (getline(playerFile, line)) {
		string name, surname, email, username, password;
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

		password = line;

		Player player(name, surname, age, email, username, password);
		players.push_back(player);
	}

	playerFile.close();
}