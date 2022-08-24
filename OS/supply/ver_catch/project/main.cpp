#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <experimental/filesystem>
using namespace std;

int main(int argc, char* argv[])
{



    // Вывод аргументов командной строки
    // argv[0] - Путь к программе
    // argv[1] - Путь к фалу с новой версией
    // argv[2] - Путь к выходного файлу исходного кода
    // argv[3] - Тип изменяемой версии ОС или алгоритм
    //    for (int i=0; i<argc; i++) {
    //        cout << argv[i]<< endl;
    //    }

    if (argc < 4) {
         cout << "usage ver.catch.exe <version_file> <source_file> <type (alg or os)>"  << endl;
         cin.ignore();
         return -1;
    }

    std::string versionFileName = argv[1];
    std::string sourceFileName = argv[2];
    std::string type = argv[3];
    std::string searchString;

    if (type == "alg") {
        searchString = "#define LIBS_UALG_VERSION";
        cout << "ver_catch run for alg" << endl;
    }
    else {
        searchString = "#define OS_VERSION_PART_2";
        cout << "ver_catch run for os" << endl;
    }

    //считываем версию из файла
    ifstream file_with_version;
    file_with_version.open(argv[1]);

    if (!file_with_version.is_open()) {
        cout << "error when opening file with new version" << endl;
        return 1;
    }

    std::string version;
    getline(file_with_version, version);
    file_with_version.close();


    //====================================================
    //Считывание информации из файла исходного кода
    ifstream file_source_code;
    ofstream new_file_source_code;
    file_source_code.open(argv[2]);

    if (!file_source_code.is_open()) {
        cout << "error when opening file with source code" << endl;
        return 2;
    }

    new_file_source_code.open(sourceFileName + "new");

    if (!new_file_source_code.is_open()) {
        cout << "error when opening file with source code" << endl;
        return 2;
    }


    std::string line;

    while (getline(file_source_code, line)) {
        size_t pos = line.find(searchString, 0);

        if (pos != string::npos) {
            line = searchString + " ";
            line += "\"" + version + "\"";
        }

        new_file_source_code << line << std::endl;
    }

    file_source_code.close();
    new_file_source_code.close();

    std::experimental::filesystem::remove(sourceFileName);
    std::experimental::filesystem::copy(sourceFileName + "new", sourceFileName);
    std::experimental::filesystem::remove(sourceFileName + "new");

    cout << "prebild completed" << endl;

    return 0;
}
