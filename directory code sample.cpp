#include <iostream>
#include <filesystem>
#include <string>
using namespace std;
namespace fs = std::filesystem;

int main() {
    fs::path currentPath = fs::current_path();

    while (true) {	
        cout << "\nMain Menu:\n";
        cout << "Current Path: " << currentPath.string() << "\n";
        cout << "[1] List Files\n";
        cout << "[2] Create Directory\n";
        cout << "[3] Change Directory\n";
        cout << "[4] Exit\n";
        cout << "Enter your choice: ";

        string choice;
        getline(cin, choice);

        if (choice == "1") listFilesMenu(currentPath);
        else if (choice == "2") createDirectory();
        else if (choice == "3") changeDirectory(currentPath);
        else if (choice == "4") {
            cout << "Exiting program...\n";
            break;
        } else {
            cout << "Invalid choice! Please try again.\n";
        }
    }
    system("cls");
    return 0;
}
void listAllFiles(const fs::path &path) {
    cout << "\nFiles in current directory:\n";
    for (const auto &entry : fs::directory_iterator(path)) {
        cout << " - " << entry.path().filename().string() << endl;
    }
}

