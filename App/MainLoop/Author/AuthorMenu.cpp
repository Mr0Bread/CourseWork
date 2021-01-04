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
    Output::print("5. Edit");
    Output::print("6. Back");
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
            AuthorMenu::edit();
            break;
        case 6:
            exit();
            break;
        default:
            Output::print("Invalid command");
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
    auto name = Input::askString(50, "Enter author's name");
    auto surname = Input::askString(50, "Enter author's surname");
    auto placeOfBirth = Input::askString(50, "Enter author's place of birth");
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

void AuthorMenu::edit() {
    int idToEdit = getIdOfAuthorToEdit();

    if (idToEdit == -1) {
        Output::print(
                "There is no author in storage\n"
                "Add at least one to be able to edit information"
        );
        return;
    }

    Author authorToEdit = AuthorStorage::loadById(idToEdit);
    bool run = true;

    while (run) {
        int answer = Input::askInt(
                "Enter what attribute you want to edit\n"
                "1. Name\n"
                "2. Surname\n"
                "3. Year of birth\n"
                "4. Place of birth\n"
                "5. Save changes\n"
                "6. Back"
        );

        switch (answer) {
            case 1:
                editName(&authorToEdit);
                break;
            case 2:
                editSurname(&authorToEdit);
                break;
            case 3:
                editYearOfBirth(&authorToEdit);
                break;
            case 4:
                editPlaceOfBirth(&authorToEdit);
                break;
            case 5:
                saveChanges(&authorToEdit);
                break;
            case 6:
                run = false;
                break;
            default:
                Output::print("Invalid command");
                break;
        }
    }
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

int AuthorMenu::getIdOfAuthorToEdit() {
    auto authors = AuthorStorage::loadAll();
    auto authorQty = authors.size();

    if (authorQty == 0) {
        return -1;
    }

    auto ids = new int[authorQty];
    bool run = true;
    int idToReturn;

    Output::print(
            "Enter ID of Author you want to edit\n"
            "Here is list of available IDs"
    );

    for (int i = 0; i < authorQty; ++i) {
        ids[i] = authors[i].id;
        Output::print(ids[i]);
    }

    int answer = Input::askInt();

    while (run) {
        for (int i = 0; i < authorQty; ++i) {
            if (ids[i] == answer) {
                idToReturn = ids[i];
                run = false;
                break;
            }
        }

        if (run) {
            answer = Input::askInt(
                    "Invalid ID is provided\n Enter one of the existing ones"
            );
        }
    }

    delete[] ids;
    return idToReturn;
}

void AuthorMenu::editName(Author* pAuthor) {
    auto newName = Input::askString(50, "Enter new name of Author");

    for (int i = 0; i < sizeof(pAuthor->name); ++i) {
        pAuthor->name[i] = newName[i];
    }

    Output::print("New name successfully saved");
}

void AuthorMenu::editSurname(Author* pAuthor) {
    auto newSurname = Input::askString(50, "Enter new surname of Author");

    for (int i = 0; i < sizeof(pAuthor->surname); ++i) {
        pAuthor->surname[i] = newSurname[i];
    }

    Output::print("New surname successfully saved");
}

void AuthorMenu::editYearOfBirth(Author* pAuthor) {
    auto newYearOfBirth = Input::askInt("Enter new year of birth");
    pAuthor->yearOfBirth = newYearOfBirth;
    Output::print("New Year Of Birth successfully saved");
}

void AuthorMenu::editPlaceOfBirth(Author* pAuthor) {
    auto newPlaceOfBirth = Input::askString(50, "Enter Author's new place of birth");

    for (int i = 0; i < sizeof(pAuthor->placeOfBirth); ++i) {
        pAuthor->placeOfBirth[i] = newPlaceOfBirth[i];
    }

    Output::print("New place of birth successfully saved");
}

void AuthorMenu::saveChanges(Author* pAuthor) {
    int answer = Input::askInt(
            "Are you sure you want to save changes?\n"
            "1. Yes\n"
            "2. No\n"
            "3. Back"
    );

    bool run = true;

    while (run) {
        switch (answer) {
            case 1:
                AuthorStorage::save(*pAuthor);
                run = false;
                break;
            case 2:
                run = false;
                break;
            case 3:
                run = false;
                break;
            default:
                answer = Input::askInt("Invalid command. Try again");
                break;
        }
    }
}
