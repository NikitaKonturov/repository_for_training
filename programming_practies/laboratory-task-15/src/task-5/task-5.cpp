#include"task-5.hpp"


void readFile(std::vector<Student>& vect, std::ifstream& fin) 
{
    std::string name = "";
    std::string surename = "";
    std::string fathername = "";
    size_t cource = 1;
    size_t group = 1;
    while(fin >> name) {
        fin >> surename;
        if(fin.fail()){
            break;
        }
        fin >> fathername;
        if(fin.fail()){
            break;
        }
        fin >> cource;
        if(fin.fail()){
            break;
        }
        fin >> group;
        if(fin.fail()){
            break;
        }
        vect.push_back(Student(name + surename + fathername, cource, group));
    }
}

void writeToFile(const std::vector<Student>& vector, std::ofstream& fout)
{
    for(const Student& student : vector) {
        fout << student.name << " " << student.cource << " " << student.group << std::endl; 
    }
}


void fiveTask(std::string& path)
{
    std::ifstream fin(path);

    std::vector<Student> studentVector;
    checkFile(fin, path);

    readFile(studentVector, fin);
    std::cout << "Файл считан..." << std::endl;

    fin.close();

    std::sort(studentVector.begin(), studentVector.end(), [](const Student& first, const Student& second){
        std::string sFirst = first.name;
        std::string sSecond = second.name;
        for(char& symbol : sFirst) {
            toupper(symbol);
        }
        for(char symbol : sSecond) {
            toupper(symbol);
        }
        return sFirst < sSecond;
        });

    std::filesystem::path dir(path);
    std::string directory = std::filesystem::absolute(dir.parent_path()).string();
    
    std::ofstream fout(directory + "/Fio.txt");
    writeToFile(studentVector, fout);
    std::cout << "Создан файл Fio.txt..." << std::endl;

    fout.close();
    fout.open(directory + "/Groups.txt");

    std::sort(studentVector.begin(), studentVector.end(), [](const Student& first, const Student& second) {
        if (first.cource != second.cource) {
            return first.cource < second.cource;
        }
        if (first.group != second.group) {
            return first.group < second.group;
        }

        std::string sFirst = first.name;
        std::string sSecond = second.name;
        for(char& symbol : sFirst) {
            toupper(symbol);
        }
        for(char symbol : sSecond) {
            toupper(symbol);
        }
        return sFirst < sSecond;
    });

    writeToFile(studentVector, fout);
    std::cout << "Содан файл Groups.txt..." << std::endl;

    fout.close();
}
