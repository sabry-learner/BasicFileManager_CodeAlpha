#include <iostream>
#include <Windows.h>
#include <string>
#include <codecvt>
#include <locale>
#include <fstream> // For file operations
using namespace std;

class FileManager {
private:
    wstring currentDirectory;

    void listDirectoryContents(const wstring& path) {
        WIN32_FIND_DATAW findFileData;
        HANDLE hFind = FindFirstFileW((path + L"\\*").c_str(), &findFileData);
        if (hFind != INVALID_HANDLE_VALUE) {
            do {
                wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
                string fileName = converter.to_bytes(findFileData.cFileName);
                cout << fileName << endl;
            } while (FindNextFileW(hFind, &findFileData) != 0);
            FindClose(hFind);
        }
    }

    bool createDirectory(const wstring& path) {
        return CreateDirectoryW(path.c_str(), NULL) != 0;
    }

    bool copyFile(const wstring& source, const wstring& destination) {
        return CopyFileW(source.c_str(), destination.c_str(), FALSE) != 0;
    }

    bool moveFile(const wstring& source, const wstring& destination) {
        return MoveFileW(source.c_str(), destination.c_str()) != 0;
    }

    bool touchFile(const wstring& filePath) {
        wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
        string utf8FilePath = converter.to_bytes(filePath);
        ofstream file(utf8FilePath);
    return file.good();
}


public:
    FileManager() : currentDirectory(L".") {}

    void run() {
        string command;

        while (true) {
            cout << "\n\t\t========================" << endl;
            cout << "\t\t|  Basic File Manager   |\n";
            cout << "\t\t========================" << endl;
            wcout << "\tCurrent Directory: " << currentDirectory << endl;
            cout << "\tAvailable commands:" << endl;
            cout << "\t1. List directory contents (ls)" << endl;
            cout << "\t2. Create directory (mkdir)" << endl;
            cout << "\t3. Copy file (cp)" << endl;
            cout << "\t4. Move file (mv)" << endl;
            cout << "\t5. Change directory (cd)" << endl;
            cout << "\t6. Create empty file (touch)" << endl;
            cout << "\t7. Exit" << endl;
            cout << "  =>Enter command number or its abbreviation: ";
            cin >> command;

            if (command == "ls" || command == "1") {
                listDirectoryContents(currentDirectory);
            }
            else if (command == "mkdir" || command == "2") {
                string newDirName;
                cout << "\tEnter directory name: ";
                cin >> newDirName;
                if (createDirectory(currentDirectory + L"\\" + wstring(newDirName.begin(), newDirName.end())))
                    cout << "\tDirectory created successfully: " << newDirName << endl;
                else
                    cout << "\tFailed to create directory: " << newDirName << endl;
            }
            else if (command == "cp" || command == "3") {
                string source, destination;
                cout << "\tEnter source file path: ";
                cin >> source;
                cout << "\tEnter destination file path: ";
                cin >> destination;
                if (copyFile(wstring(source.begin(), source.end()), wstring(destination.begin(), destination.end())))
                    cout << "\tFile copied successfully." << endl;
                else
                    cout << "\tFailed to copy file." << endl;
            }
            else if (command == "mv" || command == "4") {
                string source, destination;
                cout << "\tEnter source file path: ";
                cin >> source;
                cout << "\tEnter destination file path: ";
                cin >> destination;
                if (moveFile(wstring(source.begin(), source.end()), wstring(destination.begin(), destination.end())))
                    cout << "\tFile moved successfully." << endl;
                else
                    cout << "\tFailed to move file." << endl;
            }
            else if (command == "cd" || command == "5") {
                string newDir;
                cout << "\tEnter directory path: ";
                cin >> newDir;
                currentDirectory = wstring(newDir.begin(), newDir.end());
            }
            else if (command == "touch" || command == "6") {
                string fileName;
                cout << "\tEnter file name: ";
                cin >> fileName;
                wstring filePath = currentDirectory + L"\\" + wstring(fileName.begin(), fileName.end());
                if (touchFile(filePath))
                    cout << "\tFile created successfully: " << fileName << endl;
                else
                    cout << "\tFailed to create file: " << fileName << endl;
            }
            else if (command == "exit" || command == "7") {
                cout << "\t\t==========================\n";
                cout << "\t\t Thanks for using My App :)\n";
                cout << "\t\t==========================\n\n";
                break;
            }
            else {
                cout << "\tInvalid command, Please try again!" << endl;
            }

            // Clear the screen after each command and wait for 2 seconds
            Sleep(2000); // 2000 milliseconds (2 seconds)
            system("cls"); // Clear the screen
        }
    }
};

int main() {
    FileManager fileManager;
    fileManager.run();

    return 0;
}
