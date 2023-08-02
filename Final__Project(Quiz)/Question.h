#pragma once

class Answer {
private:
    vector<string> _answerVariants;

public:
    Answer(string answer1, string answer2, string answer3, string answer4) {
        this->_answerVariants.push_back(answer1);
        this->_answerVariants.push_back(answer2);
        this->_answerVariants.push_back(answer3);
        this->_answerVariants.push_back(answer4);
    }

    int GetAnswerCount() const {
        return this->_answerVariants.size();
    }

    string GetAnswerVariant(int index) {
        if (index >= 0 && index < 4) {
            return this->_answerVariants[index];
        }
        throw out_of_range("Invalid index: must be between 0 and 3");
    }

    string GetAnswerText(int index) const {
        if (index >= 0 && index < 4) {
            return this->_answerVariants[index];
        }
        throw out_of_range("Invalid index: must be between 0 and 3");
    }

    void SetAnswerVariant(int index, string answer) {
        if (index >= 0 && index < 4) {
            this->_answerVariants[index] = answer;
            return;
        }
        throw out_of_range("Invalid index: must be between 0 and 3");
    }

    void ShuffleAnswerVariants(int correctAnswerIndex) {
        string correctAnswer = _answerVariants[correctAnswerIndex];

        vector<string> incorrectAnswers;
        for (int i = 0; i < _answerVariants.size(); i++) {
            if (i != correctAnswerIndex) {
                incorrectAnswers.push_back(_answerVariants[i]);
            }
        }
        random_shuffle(incorrectAnswers.begin(), incorrectAnswers.end());

        int incorrectIndex = 0;
        for (int i = 0; i < _answerVariants.size(); i++) {
            if (i != correctAnswerIndex) {
                _answerVariants[i] = incorrectAnswers[incorrectIndex++];
            }
        }
    }

    void SetAnswerText(int index, const string& text) {
        if (index >= 0 && index < 4) {
            this->_answerVariants[index] = text;
            return;
        }
        throw out_of_range("Invalid index: must be between 0 and 3");
    }

};

class Question {
private:
    string _questionText;
    vector<Answer*> _answers;
    int _correctAnswerIndex;

public:

    Question(const string& questionText, const vector<Answer*>& answers, int correctAnswerIndex)
        : _questionText(questionText), _answers(answers), _correctAnswerIndex(correctAnswerIndex) {}

    vector<Answer*> GetAnswers() const {
        return _answers;
    }

    int GetCorrectAnswerIndex() const {
        return _correctAnswerIndex;
    }

    string GetQuestionText() const {
        return this->_questionText;
    }

    void AddAnswer(string answer1, string answer2, string answer3, string answer4) {
        this->_answers.push_back(new Answer(answer1, answer2, answer3, answer4));
    }

    void ShuffleAnswers() {
        for (Answer* answer : _answers) {
            answer->ShuffleAnswerVariants(_correctAnswerIndex);
        }
    }

    bool CheckAnswer(int userChoice) const {
        if (userChoice == _correctAnswerIndex) {
            return true;
        }
        return false;
    }

    void SetCorrectAnswerIndex(int index) {
        if (index >= 0 && index < 4) {
            this->_correctAnswerIndex = index;
            return;
        }
        throw out_of_range("Invalid index: must be between 0 and 3");
    }

    void SetQuestionText(string text) {
        this->_questionText = text;
    }

    int GetAnswerCount() const {
        return static_cast<int>(_answers.size());
    }

    ~Question() {
        for (Answer* answer : _answers) {
            delete answer;
        }
    }

};

class Quiz {
private:
    string _quizName;
    vector<Question*> _questions;

public:
    Quiz(string name) : _quizName(name) {}

    string GetQuizname() const {
        return _quizName;
    }

    int GetQuestionCount() const {
        return static_cast<int>(_questions.size());
    }

    Question* GetQuestionByIndex(int index) {
        if (index >= 0 && index < _questions.size()) {
            return _questions[index];
        }
        else {
            throw out_of_range("Invalid index");
        }
    }

    void AddQuestion(string questionText, string answer1, string answer2, string answer3, string answer4, int correctIndex) {
        vector<Answer*> answers;
        answers.push_back(new Answer(answer1, answer2, answer3, answer4));

        Question* question = new Question(questionText, answers, correctIndex - 1);
        _questions.push_back(question);
    }

    void ClearQuestions() {
        for (Question* question : _questions) {
            delete question;
        }
        _questions.clear();
    }

    void DeleteQuestion(int index) {
        if (index >= 0 && index < _questions.size()) {
            delete _questions[index];
            _questions.erase(_questions.begin() + index);
        }
    }

    void DisplayQuestions() const {
        int questionNumber = 1;
        for (const Question* question : _questions) {
            cout << "Question " << questionNumber << ": " << question->GetQuestionText() << endl;

            vector<Answer*> answers = question->GetAnswers();
            for (Answer* answer : answers) {
                for (int i = 0; i < 4; i++) {
                    cout << "\tAnswer " << i + 1 << ": " << answer->GetAnswerVariant(i) << endl;
                }
            }
            cout << endl;
            questionNumber++;
        }
    }

    void ShuffleQuestions() {
        random_shuffle(_questions.begin(), _questions.end());
        for (Question* question : _questions) {
            question->ShuffleAnswers();
        }
    }

    void SaveToFile() {
        ofstream file(_quizName + ".txt", ios::out);

        if (!file) {
            cout << "Error: Failed to open file while saving quiz." << endl;
            return;
        }

        int questionNumber = 1;
        for (const Question* question : _questions) {
            file << "Question " << questionNumber << ": " << question->GetQuestionText() << endl;

            vector<Answer*> answers = question->GetAnswers();
            for (Answer* answer : answers) {
                for (int i = 0; i < 4; i++) {
                    file << "\tAnswer " << i + 1 << ": " << answer->GetAnswerVariant(i);
                    if (i == question->GetCorrectAnswerIndex()) {
                        file << " (Correct)";
                    }
                    file << endl;
                }
            }
            file << endl;
            questionNumber++;
        }

        file.close();
        cout << "\n\t\t\t\t\tQuiz has been saved to " << _quizName << ".txt" << endl;
        delay(2000);
    }

    void AppendToFile() {
        int lastQuestionNumber = 0;
        string line;
        ifstream file(_quizName + ".txt", ios::in);

        while (getline(file, line)) {
            if (!line.empty() && line.find("Question") == 0) {
                lastQuestionNumber++;
            }
        }

        file.close();

        ofstream outputFile(_quizName + ".txt", ios::app);
        if (!outputFile) {
            cout << "Error: Failed to open file while appending quiz." << endl;
            return;
        }

        int questionNumber = lastQuestionNumber + 1;

        for (const Question* question : _questions) {
            outputFile << "Question " << questionNumber << ": " << question->GetQuestionText() << endl;

            vector<Answer*> answers = question->GetAnswers();
            for (Answer* answer : answers) {
                for (int i = 0; i < 4; i++) {
                    outputFile << "\tAnswer " << i + 1 << ": " << answer->GetAnswerVariant(i);
                    if (i == question->GetCorrectAnswerIndex()) {
                        outputFile << " (Correct)";
                    }
                    outputFile << endl;
                }
            }
            outputFile << endl;
            questionNumber++;
        }

        outputFile.close();
        cout << "\n\t\t\t\t\tQuiz has been appended to " << _quizName << ".txt" << endl;
        delay(2000);
    }

    void LoadFromFile(Quiz& quiz, const string& quizName) {
        if (quizName.empty()) {
            throw invalid_argument("Invalid quiz name: Empty name.");
        }

        string fileName = quizName + ".txt";
        ifstream file(fileName, ios::in);
        if (!file.is_open()) {
            throw runtime_error("Error opening file: " + fileName);
        }

        quiz.ClearQuestions();

        string line;
        while (getline(file, line)) {
            if (line.empty()) {
                continue;
            }

            if (line.find("Question") == 0) {
                string questionText = line.substr(line.find(":") + 2);

                vector<string> answerTexts;
                int correctIndex = -1;

                for (int i = 0; i < 4; i++) {
                    getline(file, line);
                    size_t pos = line.find("(Correct)");
                    if (pos != -1) {
                        correctIndex = i;
                        line.erase(pos, string("(Correct)").length());
                    }

                    answerTexts.push_back(line.substr(line.find(":") + 2));
                }

                quiz.AddQuestion(questionText, answerTexts[0], answerTexts[1], answerTexts[2], answerTexts[3], correctIndex);
                quiz.GetQuestionByIndex(quiz.GetQuestionCount() - 1)->SetCorrectAnswerIndex(correctIndex);
            }
        }

        file.close();
    }

    ~Quiz() {
        ClearQuestions();
    }

};