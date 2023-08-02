#pragma once

void FirstPage() {
    delay(200);
    for (int i = 0; i < 7; i++)
        cout << endl;

    SetColor(2, 0);
    delay(300);
    cout << "\t\t\t  ______________                             ____     ___________" << endl;
    delay(120);
    cout << "\t\t\t /  __________  \\\\     =====      =====     |___||   |  ______  ||" << endl;
    delay(120);
    cout << "\t\t\t/  //         \\  \\\\    |   ||     |   ||     ___     |_/    /   ||" << endl;
    delay(120);
    cout << "\t\t\t|  ||         |  ||    |   ||     |   ||    |   \\\\         /   //" << endl;
    delay(120);
    cout << "\t\t\t|  ||         |  ||    |   ||     |   ||    |   ||        /   //" << endl;
    delay(120);
    cout << "\t\t\t|  ||         |  ||    |   ||     |   ||    |   ||       /   //" << endl;
    delay(120);
    cout << "\t\t\t|  ||    __   |  ||    |   ||     |   ||    |   ||      /   //" << endl;
    delay(120);
    cout << "\t\t\t|  ||    \\ \\\\ |  ||    |    \\\\___/    ||    |   ||     /   //     __" << endl;
    delay(120);
    cout << "\t\t\t\\  \\\\________/  //     \\              //    |   ||    |    \\\\___//||" << endl;
    delay(120);
    cout << "\t\t\t \\_____________//       \\____________//     |___//    |___________||" << endl;
    delay(120);
    cout << "\t\t\t            \\_\\\\         " << endl;

    delay(3000);
    system("cls");
}

void SecondPage() {
    vector<Admin> admins;
    ReadAdminsFromFile(admins);
    vector<Player> players;
    ReadPlayersFromFile(players);

    while (true) {
        SetColor(7, 7);
        system("cls");

        for (int i = 0; i < 6; i++)
            cout << endl;
        SetColor(4, 7);
        cout << "\t\t\t\t\t\tCHOOSE YOUR ROLE:" << endl << endl;

        for (int i = 0; i < 45; i++)
            cout << " ";

        SetColor(4, 7);
        cout << " ---------------------- " << endl;

        for (int i = 0; i < 45; i++)
            cout << " ";

        cout << "|   [1] -> ADMIN       |" << endl;

        for (int i = 0; i < 45; i++)
            cout << " ";

        cout << " ---------------------- " << endl << endl;

        for (int i = 0; i < 45; i++)
            cout << " ";

        SetColor(4, 7);
        cout << " ---------------------- " << endl;

        for (int i = 0; i < 45; i++)
            cout << " ";

        cout << "|   [2] -> PLAYER      |" << endl;

        for (int i = 0; i < 45; i++)
            cout << " ";

        cout << " ---------------------- " << endl;

        char ch = _getch();
        cin.ignore();

        if (ch == '1') {
            cout << "\a\a\a";
            while (true) {
                system("cls");
                system("Color 0F");

                SetColor(14, 4);
                cout << "\n\t\t\t\t ***** WELCOME TO THE ADMINISTRATION MENU *****" << endl;
                for (int i = 0; i < 3; i++)
                    cout << endl;

                int adminChoice;
                cout << "\n\t\t\t\t\t   [1] Sign Up as Admin     " << endl;
                cout << "\t\t\t\t\t   [2] Sign In as Admin     " << endl;
                cout << "\t\t\t\t\t   [3] Hint for Sign Up     " << endl;
                cout << "\t\t\t\t\t   [0] Go Back to Main Menu " << endl << endl;

                cout << "\t\t\t\t\t   Enter your choice: ";
                cin >> adminChoice;
                cin.ignore();

                if (adminChoice == 1) {
                    cout << "\a\a\a";
                    system("cls");
                    system("Color 0F");
                    SetColor(14, 4);
                    cout << "\n\t\t\t\t**** WELCOME TO THE ADMINISTRATION SIGN-UP MENU ****" << endl << endl;
                    for (int i = 0; i < 3; i++)
                        cout << endl;

                    try {
                        Admin::SignUpAdmin(admins);
                        delay(2000);
                    }
                    catch (const exception& ex) {
                        cout << "\n\t\t\t\t\t   Error: " << ex.what() << endl;
                        delay(2000);
                    }
                }

                else if (adminChoice == 2) {
                    cout << "\a\a\a";
                    system("cls");
                    system("Color 0F");
                    SetColor(14, 4);
                    cout << "\n\t\t\t\t**** WELCOME TO THE ADMINISTRATION SIGN-IN MENU ****" << endl << endl;
                    for (int i = 0; i < 3; i++)
                        cout << endl;

                    try {
                        Admin currentAdmin = Admin::SignInAdmin(admins);
                        currentAdmin.openPage();
                        delay(2000);
                        break;
                    }
                    catch (const exception& ex) {
                        cout << "\n\t\t\t\t\t   Error: " << ex.what() << endl;
                        delay(2000);
                    }
                }
                else if (adminChoice == 3) {
                    cout << "\a\a\a";
                    system("cls");
                    system("Color 0F");
                    SetColor(14, 4);
                    cout << "\n\t\t\t\t**** WELCOME TO THE ADMINISTRATION HINT MENU ****" << endl << endl;

                    cout << "\n\t\t\t\t\t    ~~~~~  ADMIN HINT  ~~~~~    " << endl << endl << endl
                        << "\t   Name's and Surname's length must be greater than 3 and start with an uppercase letter!!   " << endl
                        << "\n\t\t\t\t   Age must be greater than or equal to 6!   " << endl
                        << "\n\t\t\t   Email must contain the '@' symbol and end with '.com'   " << endl
                        << "\n\t\t\t\t   Username length must be greater than 10   " << endl
                        << "\n\t   Password must be at least 8 characters, start with an uppercase letter, and contain '_' or '.' symbols   " << endl
                        << "\n\t\t\t\t   Security code's length eqaul to 3 int characters   " << endl;

                    delay(10000);
                    break;
                }
                else if (adminChoice == 0) {
                    cout << "\a\a\a";
                    break;
                }
                else {
                    cout << "\a\a\a";
                    cout << "\n\t\t\t\t\tInvalid choice. Please select a valid option." << endl;
                    cout << "\t\t\t\t\t";
                    system("pause");
                    cout << "\a\a";
                }
            }
        }
        else if (ch == '2') {
            cout << "\a\a\a";
            while (true) {
                system("cls");
                system("Color 0F");

                SetColor(14, 4);
                cout << "\n\t\t\t\t    ***** WELCOME TO THE PLAYER MENU *****    " << endl << endl;
                for (int i = 0; i < 3; i++)
                    cout << endl;

                int playerChoice;
                cout << "\n\t\t\t\t\t   [1] Sign Up as Player     " << endl;
                cout << "\t\t\t\t\t   [2] Sign In as Player     " << endl;
                cout << "\t\t\t\t\t   [3] Hint for Sign Up      " << endl;
                cout << "\t\t\t\t\t   [0] Go Back to Main Menu  " << endl << endl;

                cout << "\t\t\t\t\t   Enter your choice: ";
                cin >> playerChoice;
                cin.ignore();

                if (playerChoice == 1) {
                    cout << "\a\a\a";
                    system("cls");
                    system("Color 0F");
                    SetColor(14, 4);
                    cout << "\n\t\t\t\    t**** WELCOME TO THE PLAYER SIGN-UP MENU ****    " << endl << endl;
                    for (int i = 0; i < 3; i++)
                        cout << endl;

                    try {
                        Player::SignUpPlayer(players);
                        delay(2000);
                    }
                    catch (const exception& ex) {
                        cout << "\n\t\t\t\t\t   Error: " << ex.what() << endl;
                        delay(2000);
                    }
                }
                else if (playerChoice == 2) {
                    cout << "\a\a\a";
                    system("cls");
                    system("Color 0F");
                    SetColor(14, 4);
                    cout << "\n\t\t\t\t    **** WELCOME TO THE PLAYER SIGN-IN MENU ****    " << endl << endl;
                    for (int i = 0; i < 3; i++)
                        cout << endl;
                    try {
                        Player currentPlayer = Player::SignInPlayer(players);
                        currentPlayer.openPage();
                        delay(2000);
                        break;
                    }
                    catch (const exception& ex) {
                        cout << "\n\t\t\t\t\t   Error: " << ex.what() << endl;
                        delay(2000);
                    }
                }
                else if (playerChoice == 3) {
                    cout << "\a\a\a";
                    system("cls");
                    system("Color 0F");
                    SetColor(14, 4);
                    cout << "\n\t\t\t\t   **** WELCOME TO THE PLAYER HINT MENU ****   " << endl << endl;

                    cout << "\n\t\t\t\t\t    ~~~~~  PLAYER HINT  ~~~~~    " << endl << endl << endl
                        << "\t   Name's and Surname's length must be greater than 3 and start with an uppercase letter!!   " << endl
                        << "\n\t\t\t\t   Age must be greater than or equal to 6!   " << endl
                        << "\n\t\t\t   Email must contain the '@' symbol and end with '.com'   " << endl
                        << "\n\t\t\t\t   Username length must be greater than 10   " << endl
                        << "\n\t   Password must be at least 8 characters, start with an uppercase letter, and contain '_' or '.' symbols   " << endl;

                    delay(10000);
                    break;
                }
                else if (playerChoice == 0) {
                    cout << "\a\a\a";
                    break;
                }
                else {
                    cout << "\a\a\a";
                    cout << "\n\t\t\t\t\tInvalid choice. Please select a valid option." << endl;
                    cout << "\t\t\t\t\t";
                    system("pause");
                    cout << "\a\a";
                }
            }
        }
        else {
            cout << "\a\a\a";
            cout << "\n\t\t\t\t Invalid choice. Please select 1 or 2." << endl;
            cout << "\t\t\t\t\t";
            system("pause");
            cout << "\a\a";
        }
    }
}
