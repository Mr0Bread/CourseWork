//
// Created by zimni on 12/24/2020.
//

#include <algorithm>
#include "BookMenu.h"

int BookStorage::counter = 0;
int BookStorage::idToUse = 0;

void BookMenu::run() {
    isRunning = true;

    while (isRunning) {
        printOptions();
        chooseOperation();
    }
}

void BookMenu::printOptions() {
    Output::print("1. Show all");
    Output::print("2. Add");
    Output::print("3. Remove");
    Output::print("4. Find");
    Output::print("5. Edit");
    Output::print("6. Back");
}

void BookMenu::chooseOperation() {
    int answer = Input::askInt();

    switch (answer) {
        case 1:
            BookMenu::showAll();
            break;
        case 2:
            BookMenu::add();
            break;
        case 3:
            BookMenu::remove();
            break;
        case 4:
            BookMenu::find();
            break;
        case 5:
            BookMenu::edit();
            break;
        case 6:
            exit();
            break;
        default:
            break;
    }
}

void BookMenu::exit() {
    isRunning = false;
}

void BookMenu::showAll() {
    auto books = BookStorage::loadAll();
    auto booksQty = books.size();

    std::cout << "Found " << booksQty << " Record";

    if (booksQty == 0 || booksQty > 1) {
        std::cout << "s\n\n";
    } else {
        std::cout << "\n\n";
    }

    for (auto& book : books) {
        book.printOut();
        std::cout << "\n\n";
    }
}

void BookMenu::add() {
    auto title = Input::askString(50, "Enter book's title");
    auto yearOfRelease = Input::askInt("Enter year of release");
    auto language = Input::askString(50, "Enter language book has been written in");
    auto pageQty = Input::askInt("Enter quantity of page");
    auto authorID = getAuthorId();

    Book book{};

    for (int i = 0; i < sizeof(book.language); ++i) {
        book.language[i] = language[i];
        book.title[i] = title[i];
    }

    book.yearOfRelease = yearOfRelease;
    book.pageQty = pageQty;
    book.authorId = authorID;
    BookStorage::add(book);
}

void BookMenu::remove() {
    BookStorage::remove(Input::askInt("Enter ID of book you want to delete"));
}

void BookMenu::find() {
    bool isFindRunning = true;

    while (isFindRunning) {
        Output::print("Choose by which attribute you want to find record(s)?");
        Output::print("1. ID");
        Output::print("2. Title");
        Output::print("3. AuthorID");
        Output::print("4. Year of Release");
        Output::print("5. Language");
        Output::print("6. Page quantity");
        Output::print("7. Go Back");

        int answer = Input::askInt();

        switch (answer) {
            case 1:
                findById();
                break;
            case 2:
                findByTitle();
                break;
            case 3:
                findByAuthorId();
                break;
            case 4:
                findByYearOfRelease();
                break;
            case 5:
                findByLanguage();
                break;
            case 6:
                findByPageQuantity();
                break;
            case 7:
                isFindRunning = false;
                break;
            default:
                Output::print("Invalid command");
                break;
        }
    }
}

void BookMenu::findById() {
    BookStorage::findById(
            Input::askInt("Enter ID"),
            [](Book book, int id) {
                return book.id == id;
            }
    );
}

void BookMenu::findByTitle() {
    BookStorage::findByTitle(Input::askString("Enter Title"));
}

void BookMenu::findByAuthorId() {
    BookStorage::findByAuthorId(Input::askInt("Enter Author ID"));
}

void BookMenu::findByYearOfRelease() {
    bool run = true;

    while (run) {
        int answer = Input::askInt(
                "Do you want to\n"
                "1. Find books released exactly in provided year\n"
                "2. After provided year\n"
                "3. Before provided year\n"
                "4. Go Back\n"
        );

        switch (answer) {
            case 1:
                BookStorage::findReleasedExactly(Input::askInt("Enter Year of Release"));
                break;
            case 2:
                BookStorage::findReleasedAfter(Input::askInt("Enter year of Release"));
                break;
            case 3:
                BookStorage::findReleasedBefore(Input::askInt("Enter year of Release"));
                break;
            case 4:
                run = false;
                break;
            default:
                Output::print("Invalid command");
                break;
        }
    }
}

void BookMenu::findByLanguage() {
    BookStorage::findByLanguage(Input::askString("Enter language"));
}

void BookMenu::findByPageQuantity() {
    bool run = true;

    while (run) {
        int answer = Input::askInt(
                "Do you want to:\n"
                "1. Find books with exactly provided page quantity\n"
                "2. More than provided\n"
                "3. Less than provided\n"
                "4. Go Back\n"
        );

        switch (answer) {
            case 1:
                BookStorage::findByPagesExactly(Input::askInt("Enter page quantity"));
                break;
            case 2:
                BookStorage::findByPagesMoreThan(Input::askInt("Enter page quantity"));
                break;
            case 3:
                BookStorage::findByPagesLessThan(Input::askInt("Enter page quantity"));
                break;
            case 4:
                run = false;
                break;
            default:
                Output::print("Invalid command");
                break;
        }
    }
}

int BookMenu::getAuthorId() {
    if (AuthorStorage::loadAll().size() == 0) {
        Output::print(
                "There is no authors in database so you have to create new one.\n"
                "It's ID will be assigned to Book automatically"
        );
        return assignIdOfNewAuthor();
    }

    int answer = Input::askInt(
            "Do you want to\n"
            "1. Assign existing author\n"
            "2. Create new one and assign id of it"
    );
    int id;

    bool run = true;

    while (run) {
        switch (answer) {
            case 1:
                id = assignExistingAuthorId();
                run = false;
                break;
            case 2:
                id = assignIdOfNewAuthor();
                run = false;
                break;
            default:
                answer = Input::askInt("Invalid command");
                break;
        }
    }

    return id;
}

int BookMenu::assignExistingAuthorId() {
    int chosenId;
    auto authors = AuthorStorage::loadAll();
    std::vector<int> ids;
    Output::print("Available IDs: \n");

    for (auto& author : authors) {
        ids.push_back(author.id);
        Output::print(author.id);
    }

    bool run = true;
    int answer = Input::askInt("Enter one of the given ids");

    while (run) {
        for (auto& id : ids) {
            if (id == answer) {
                chosenId = answer;
                run = false;
                break;
            }
        }

        if (run) {
            answer = Input::askInt("Invalid ID has been provided. Enter another one");
        }
    }

    return chosenId;
}

int BookMenu::assignIdOfNewAuthor() {
    AuthorMenu::add();
    return AuthorStorage::getCounter() - 1;
}

void BookMenu::edit() {
    int idToEdit = getIdOfBookToEdit();

    if (idToEdit == -1) {
        Output::print(
                "There is no books in storage\n"
                "Add at least one to be able to edit information"
        );
        return;
    }

    Book bookToEdit = BookStorage::loadById(idToEdit);
    bool run = true;

    while (run) {
        int answer = Input::askInt(
                "Enter what attribute you want to edit\n"
                "1. Title\n"
                "2. Author ID\n"
                "3. Year of release\n"
                "4. Language\n"
                "5. Page Quantity\n"
                "6. Save changes\n"
                "7. Back"
        );

        switch (answer) {
            case 1:
                editTitle(&bookToEdit);
                break;
            case 2:
                editAuthorId(&bookToEdit);
                break;
            case 3:
                editYearOfRelease(&bookToEdit);
                break;
            case 4:
                editLanguage(&bookToEdit);
                break;
            case 5:
                editPageQuantity(&bookToEdit);
                break;
            case 6:
                saveChanges(&bookToEdit);
                break;
            case 7:
                run = false;
                break;
            default:
                Output::print("Invalid command");
                break;
        }
    }
}

int BookMenu::getIdOfBookToEdit() {
    auto books = BookStorage::loadAll();
    auto bookQty = books.size();

    if (bookQty == 0) {
        return -1;
    }

    auto ids = new int[bookQty];
    bool run = true;
    int idToReturn;

    Output::print(
            "Enter ID of Book you want to edit\n"
            "Here is list of available IDs"
    );

    for (int i = 0; i < bookQty; ++i) {
        ids[i] = books[i].id;
        Output::print(ids[i]);
    }

    int answer = Input::askInt();

    while (run) {
        for (int i = 0; i < bookQty; ++i) {
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

void BookMenu::editTitle(Book* pBook) {
    auto newTitle = Input::askString(50, "Enter new title of Book");

    for (int i = 0; i < sizeof(pBook->title); ++i) {
        pBook->title[i] = newTitle[i];
    }

    Output::print("New title successfully saved");
}

void BookMenu::editAuthorId(Book* pBook) {
    auto newAuthorId = getAuthorId();
    pBook->authorId = newAuthorId;
    Output::print("New Author ID successfully saved");
}

void BookMenu::editYearOfRelease(Book* pBook) {
    auto newYearOfRelease = Input::askInt("Enter new year of release");
    pBook->yearOfRelease = newYearOfRelease;
    Output::print("New Year Of Release successfully saved");
}

void BookMenu::editLanguage(Book* pBook) {
    auto newLanguage = Input::askString(50, "Enter new language");

    for (int i = 0; i < sizeof(pBook->language); ++i) {
        pBook->language[i] = newLanguage[i];
    }

    Output::print("New language successfully saved");
}

void BookMenu::editPageQuantity(Book* pBook) {
    auto newPageQty = Input::askInt("Enter new page quantity");
    pBook->pageQty = newPageQty;
    Output::print("New page quantity successfully saved");
}

void BookMenu::saveChanges(Book* pBook) {
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
                BookStorage::save(*pBook);
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
