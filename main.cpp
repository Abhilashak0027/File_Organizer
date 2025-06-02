// #include <iostream>
// #include <unordered_map>
// #include <string>
// #include <dirent.h>
// #include <sys/stat.h>
// #include <cstring>

// using namespace std;

// class FileOrganizer {
// private:
//     string sourcePath;
//     unordered_map<string, string> extensionToFolder;

//     void setupExtensionMap() {
//         extensionToFolder = {
//             {".jpg", "Images"}, {".png", "Images"}, {".jpeg", "Images"},
//             {".pdf", "Documents"}, {".docx", "Documents"}, {".txt", "Documents"},
//             {".mp4", "Videos"}, {".mkv", "Videos"},
//             {".exe", "Executables"}, {".bat", "Executables"},
//             {".cpp", "Code"}, {".py", "Code"}
//         };
//     }

//     string getCategory(const string& extension) {
//         if (extensionToFolder.find(extension) != extensionToFolder.end()) {
//             return extensionToFolder[extension];
//         }
//         return "Others";
//     }

// public:
//     FileOrganizer(const string& path) : sourcePath(path) {
//         setupExtensionMap();
//     }

//     void organize() {
//         DIR* dir = opendir(sourcePath.c_str());
//         if (dir == nullptr) {
//             cerr << "Invalid directory path.\n";
//             return;
//         }

//         struct dirent* entry;
//         while ((entry = readdir(dir)) != nullptr) {
//             string fileName = entry->d_name;
//             if (fileName == "." || fileName == "..") {
//                 continue;
//             }

//             // Check if the file has an extension
//             size_t pos = fileName.find_last_of('.');
//             string extension = (pos == string::npos) ? "" : fileName.substr(pos);

//             string category = getCategory(extension);

//             string targetDir = sourcePath + "/" + category;
//             struct stat st;
//             if (stat(targetDir.c_str(), &st) != 0) {
//                 // Directory does not exist, so create it
//                 int mkdirResult = mkdir(targetDir.c_str());
//                 if (mkdirResult != 0) {
//                     cerr << "Failed to create directory: " << targetDir << endl;
//                     continue;  // Skip to the next file
//                 }
//             }

//             string sourceFilePath = sourcePath + "/" + fileName;
//             string targetFilePath = targetDir + "/" + fileName;

//             if (rename(sourceFilePath.c_str(), targetFilePath.c_str()) == 0) {
//                 cout << "Moved: " << fileName << " -> " << category << "\n";
//             } else {
//                 cerr << "Failed to move: " << fileName << "\n";
//             }
//         }

//         closedir(dir);
//         cout << "Organization complete.\n";
//     }
// };

// int main() {
//     string folderPath;
//     cout << "Enter folder path to organize: ";
//     getline(cin, folderPath);

//     FileOrganizer organizer(folderPath);
//     organizer.organize();

//     return 0;
// }

#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <cstring>
#include <unistd.h>

using namespace std;

void undoOrganize(const string& sourcePath) {
    DIR* dir = opendir(sourcePath.c_str());
    if (dir == nullptr) {
        cerr << "Invalid directory path.\n";
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        string fileName = entry->d_name;
        if (fileName == "." || fileName == "..") {
            continue;
        }

        string sourceFilePath = sourcePath + "/" + fileName;

        // Check if the entry is a directory
        struct stat st;
        if (stat(sourceFilePath.c_str(), &st) == 0 && S_ISDIR(st.st_mode)) {
            // It's a directory, so we skip it and go inside
            string targetDir = sourcePath + "/" + fileName;
            DIR* subdir = opendir(targetDir.c_str());
            if (subdir) {
                struct dirent* subEntry;
                while ((subEntry = readdir(subdir)) != nullptr) {
                    string subFileName = subEntry->d_name;
                    if (subFileName == "." || subFileName == "..") continue;

                    string sourceSubFilePath = targetDir + "/" + subFileName;
                    string targetSubFilePath = sourcePath + "/" + subFileName;

                    // Move the file back to the Downloads folder
                    if (rename(sourceSubFilePath.c_str(), targetSubFilePath.c_str()) == 0) {
                        cout << "Moved back: " << subFileName << " -> Downloads\n";
                    } else {
                        cerr << "Failed to move back: " << subFileName << "\n";
                    }
                }
                closedir(subdir);
            }
        }
    }

    closedir(dir);
    cout << "Undo organization complete.\n";
}

int main() {
    string folderPath = "C:/Users/Abhilasha/Downloads"; // Use forward slashes here
    undoOrganize(folderPath);
    return 0;
}
