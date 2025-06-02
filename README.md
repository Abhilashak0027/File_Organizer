# 📁 File Organizer Undo Tool (C++)

This is a simple C++ console application that undoes file organization by moving files from categorized subfolders (like `Images`, `Documents`, etc.) back into the original folder.

---

## 💡 Features

- Restores files to their original folder (e.g., Downloads) after they were organized by file type
- Works entirely in one file: `main.cpp`
- Uses native file system functions (`dirent.h`, `sys/stat.h`, `unistd.h`)

---

## 📂 File

| File       | Description                        |
|------------|------------------------------------|
| `main.cpp` | Contains the full undo logic       |

---

## 🛠 Requirements

- C++ compiler (e.g., g++)
- Works on Windows (tested with MinGW)

---

```markdown
### 1. Update Folder Path

Edit the path in `main.cpp`:
```cpp
string folderPath = "C:/Users/Abhilasha/Downloads";

### 2. Compile
g++ main.cpp -o undo_organizer

### 3. Run
./undo_organizer

Sample Output
Moved back: notes.txt -> Downloads
Moved back: photo.jpg -> Downloads
Undo organization complete.



