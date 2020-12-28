//
// Created by zimni on 12/24/2020.
//

#include "AuthorMenu.h"

int AuthorStorage::idToUse = 0;
int AuthorStorage::counter = 0;

void AuthorMenu::run() {
    isRunning = true;

    while (isRunning) {
        printOptions();
        chooseOperation();
    }
}

void AuthorMenu::printOptions() {
    Output::print("1. Show all");
    Output::print("2. Add");
    Output::print("3. Remove");
    Output::print("4. Find");
    Output::print("5. Back");
}

void AuthorMenu::chooseOperation() {
    int answer = Input::askInt();

    switch (answer) {
        case 1:
            AuthorMenu::showAll();
            break;
        case 2:
            AuthorMenu::add();
            break;
        case 3:
            AuthorMenu::remove();
            break;
        case 4:
            AuthorMenu::find();
            break;
        case 5:
            exit();
            break;
        default:
            break;
    }
}

void AuthorMenu::exit() {
    isRunning = false;
}

void AuthorMenu::showAll() {
    auto authors = AuthorStorage::loadAll();
    auto authorQty = authors.size();

    std::cout << "Found " << authorQty << " Record";

    if (authorQty == 0 || authorQty > 1) {
        std::cout << "s\n\n";
    } else {
        std::cout << "\n\n";
    }

    for (auto& author : authors) {
        author.printOut();
        std::cout << "\n\n";
    }
}

void AuthorMenu::add() {
    auto name = Input::askString("Enter author's name");
    auto surname = Input::askString("Enter author's surname");
    auto placeOfBirth = Input::askString("Enter author's place of birth");
    auto yearOfBirth = Input::askInt("Enter author's year of birth");
    Author author{};

    for (int i = 0; i < sizeof(author.name); ++i) {
        author.name[i] = name[i];
        author.surname[i] = surname[i];
        author.placeOfBirth[i] = placeOfBirth[i];
    }

    author.yearOfBirth = yearOfBirth;
    AuthorStorage::add(author);
}

void AuthorMenu::remove() {
    AuthorStorage::remove(Input::askInt("Enter ID of author you want to delete"));
}

void AuthorMenu::find() {
    bool isFindRunning = true;

    while (isFindRunning) {
        Output::print(
                "Choose by which attribute you want to find record(s)\n"
                "1. ID\n"
                "2. Name\n"
                "3. Surname\n"
                "4. Year of Birth\n"
                "5. Place of Birth\n"
                "6. Go Back"
        );

        int answer = Input::askInt();

        switch (answer) {
            case 1:
                findById();
                break;
            case 2:
                findByName();
                break;
            case 3:
                findBySurname();
                break;
            case 4:
                findByYearOfBirth();
                break;
            case 5:
                findByPlaceOfBirth();
                break;
            case 6:
                isFindRunning = false;
                break;
            default:
                break;
        }
    }
}

void AuthorMenu::findById() {
    AuthorStorage::findById(Input::askInt("Enter ID"));
}

void AuthorMenu::findByName() {
    AuthorStorage::findByName(Input::askString("Enter name"));
}

void AuthorMenu::findBySurname() {
    AuthorStorage::findBySurname(Input::askString("Enter surname"));
}

void AuthorMenu::findByYearOfBirth() {
    bool run = true;

    while (run) {
        int answer = Input::askInt(
                "Do you want to find authors born\n"
                "1. Exactly during provided year\n"
                "2. After provided year\n"
                "3. Before provided year\n"
                "4. Go back"
                );

        switch (answer) {
            case 1:
                AuthorStorage::findByYoBExactly(Input::askInt("Enter year of birth"));
                break;
            case 2:
                AuthorStorage::findByYoBAfter(Input::askInt("Enter year of birth"));
                break;
            case 3:
                AuthorStorage::findByYoBBefore(Input::askInt("Enter year of birth"));
                break;
            case 4:
                run = false;
                break;
            default:
                break;
        }
    }
}

void AuthorMenu::findByPlaceOfBirth() {
    AuthorStorage::findByPlaceOfBirth(Input::askString("Enter place of birth"));
}
