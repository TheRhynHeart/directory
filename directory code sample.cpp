#include <iostream>
#include <filesystem>
#include <string>
using namespace std;
namespace fs = std::filesystem;

int main() {
    fs::path currentPath = fs::current_path();

    while (true) {	
        std::cout << "\nMain Menu:\n";
        std::cout << "[1] List Files\n";
        std::cout << "[2] Create Directory\n";
        std::cout << "[3] Change Directory\n";
        std::cout << "[4] Exit\n";
        std::cout << "Enter your choice: ";

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
void listFilesMenu(const fs::path &path) {
    cout << "\n[1] List All Files\n";
    cout << "[2] List by Extension (e.g., .txt)\n";
    cout << "[3] List by Pattern (e.g., moha *.*)\n";
    cout << "Enter choice: ";
    string choice;
    getline(cin, choice);

    if (choice == "1") listAllFiles(path);
    else if (choice == "2") listByExtension(path);
    else if (choice == "3") listByPattern(path);
    else cout << "Invalid choice!\n";
}
void listByPattern(const fs::path &path) {
    string pattern = getInput("Enter search pattern: ");
    cout << "\nFiles matching pattern '" << pattern << "':\n";
    for (const auto &entry : fs::directory_iterator(path)) {
        string filename = entry.path().filename().string();
        if (filename.find(pattern) != string::npos) {
            cout << " - " << filename << endl;
        }
    }
}
void listAllFiles(const fs::path &path) {
    cout << "\nFiles in current directory:\n";
    for (const auto &entry : fs::directory_iterator(path)) {
        cout << " - " << entry.path().filename().string() << endl;
    }
}
void listByExtension(const fs::path &path) {
    string ext = getInput("Enter extension (e.g., .txt): ");
    cout << "\nFiles with extension " << ext << ":\n";
    for (const auto &entry : fs::directory_iterator(path)) {
        if (entry.path().extension() == ext) {
            cout << " - " << entry.path().filename().string() << endl;
        }
    }
}


void createDirectory() {
    string dirname = getInput("\nEnter directory name: ");
    try {
        if (fs::create_directory(dirname)) {
            cout << "Directory '" << dirname << "' created successfully.\n";
        } else {
            cout << "Directory '" << dirname << "' already exists.\n";
        }
    } catch (const exception &e) {
        cout << "Error: " << e.what() << endl;
    }
}
void changeDirectory(fs::path &currentPath) {
    cout << "\n[1] Move to Parent Directory\n";
    cout << "[2] Move to Root Directory\n";
    cout << "[3] Enter Custom Path (e.g., C:\\Users\\Documents)\n";
    cout << "Enter choice: ";
    string choice;
    getline(cin, choice);

    fs::path newPath;
    
    if (choice == "1") {
        newPath = currentPath.parent_path();
    } 
    else if (choice == "2") {
        newPath = currentPath.root_name().empty() ? "C:\\" : currentPath.root_name().string() + "\\";
        newPath = "/";
    } 
    else if (choice == "3") {
        string customPath = getInput("\nEnter full path: ");
        newPath = customPath;
    } 
    else {
        cout << "Invalid choice!\n";
        return;
    }
    if (fs::exists(newPath) && fs::is_directory(newPath)) {
        currentPath = newPath;
        fs::current_path(newPath);
        cout << "Current directory changed to: " << currentPath.string() << endl;
    } else {
        cout << "Error: Directory \"" << newPath.string() << "\" not found!" << endl;
    }
}


