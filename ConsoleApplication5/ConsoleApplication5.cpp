#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <Windows.h>
using namespace std;

class Student {
private:
    string groupName;
    vector<string> subjects;
    int sdanixRabor;
    int neSdanixRabot;
public:
    Student(string group) : groupName(group), sdanixRabor(0), neSdanixRabot(0) {}

    vector<string> getSubjects() const {
        return subjects;
    }

    void addSubject(string subject) {
        if (subjects.end() == find(subjects.begin(), subjects.end(), subject))
            subjects.push_back(subject);
        else
            cout << "Дисциплина \"" << subject << "\" уже есть у студента" << endl;
    }

    void addSdanixRabor() {
        sdanixRabor++;
    }

    void addNesdanixRabot() {
        neSdanixRabot++;
    }

    void yaProshauTeba() {
        if (neSdanixRabot > 0) {
            neSdanixRabot--;
        }
        else {
            neSdanixRabot = neSdanixRabot;
        }
    }

    void getSdanixRabor() {
        if (sdanixRabor > 0) {
            sdanixRabor--;
        }
        else {
            sdanixRabor = sdanixRabor;
        }
    }

    int getNeSdanixRabot() const {
        return neSdanixRabot;
    }

    string getGroupName() const {
        return groupName;
    }

    int getCompletedAssignments() const {
        return sdanixRabor;
    }
};

class Teacher {
private:
    string subject;
    vector<string> groups;
public:
    Teacher(const string& subject) : subject(subject) {}

    void addGroup(const string& group) {
        groups.push_back(group);
    }

    vector<string> getGroups() const {
        return groups;
    }

    string getSubject() const {
        return subject;
    }
};

class Group {
private:
    string name;
    vector<Student> students;
    vector<Teacher> teachers;
public:
    Group(const string name) : name(name) {}

    vector<Student> getStudents() {
        return students;
    }

    void addStudent(const Student& student) {
        students.push_back(student);
    }

    void addTeacher(const Teacher& teacher) {
        teachers.push_back(teacher);
    }

    string getName() const {
        return name;
    }
};

class MPT {
private:
    vector<Teacher> teachers;
public:
    vector<Group> groups;

    void addGroup(const Group group) {
        groups.push_back(group);
    }

    void addTeacher(const Teacher teacher) {
        teachers.push_back(teacher);
    }

    void addWork(Student student) {
        student.addSdanixRabor();
    }

    void addDolg(Student student) {
        student.addNesdanixRabot();
    }

    void showStudentInGroup(Group& group) {
        cout << "Количество студентов в группе " << group.getName() << ": " << group.getStudents().size() << endl;
    }

    void showStudentInfo(const Student student) {
        cout << "Информация о студенте:" << endl;
        cout << "Название группы: " << student.getGroupName() << endl;
        cout << "Дисциплины: ";
        for (const auto& subject : student.getSubjects()) {
            cout << subject << ", ";
        }
        cout << endl;
        cout << "Количество выполненных работ: " << student.getCompletedAssignments() << endl;
        cout << "Количество долгов: " << student.getNeSdanixRabot() << endl;
    }

    void showAllStudentsInfo() {
        for (auto& group : groups) {
            for (auto& student : group.getStudents()) {
                showStudentInfo(student);
                cout << endl;
            }
        }
    }

    void showAllGroups() const {
        cout << "Все группы:" << endl;
        for (const auto& group : groups) {
            cout << group.getName() << endl;
        }
    }

    bool groupExists(const string& group_name) const {
        for (const auto& group : groups) {
            if (group.getName() == group_name) {
                return true;
            }
        }
        return false;
    }

    bool subjectExists(const string& subject) {
        for (auto& group : groups) {
            for (auto& student : group.getStudents()) {
                if (find(student.getSubjects().begin(), student.getSubjects().end(), subject) != student.getSubjects().end())
                    return true;
            }
        }
        return false;
    }
};

int main() {
    setlocale(LC_ALL, "RUS");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(0, "");
    MPT MPT;

    string group_name;
    cout << "\nВведите название группы: ";
    cin >> group_name;

    Group group(group_name);

    Student student1(group_name);

    string subject;
    cout << "Введите дисциплину для группы: ";
    cin >> subject;
    student1.addSubject(subject);

    Teacher teacher1(subject);

    string groupOfTeacher;

    do {
        cout << "Введите название группы для преподователя: ";

        cin >> groupOfTeacher;

        if (groupOfTeacher != group_name) {
            cout << "Группы с таким названием не существует! Пожайлуста, попробуйте ещё раз! \n";
        }
    } while (groupOfTeacher != group_name);

    teacher1.addGroup(groupOfTeacher);
    group.addStudent(student1);
    group.addTeacher(teacher1);
    MPT.addGroup(group);
    MPT.addTeacher(teacher1);
    char choice;

    do {
        cout << " \n1 - Добавить работу группе\n 2 - Добавить долг группе\n 3 - Посмотреть количество студентов в группе\n 4 - Показать информацию о группе\n 5 - Добавить студента в группу\n 6 - Добавить новую группу\n 7 - Показать все группы\n 8 - Добавить новую дисциплину\n 9 - Удалить долги группе\n 10 - Отметить практическую работу выполненной\n 11 - Завершить\n";
        cin >> choice;

        switch (choice) {
        case '1':
            cout << "\nГруппе был добвален практос\n";
            MPT.addWork(student1);
            break;
        case '2':
            cout << "\nГруппе был добавлен долг\n";
            MPT.addDolg(student1);
            break;
        case '3':
            MPT.showStudentInGroup(group);
            break;
        case '4':
            MPT.showStudentInfo(student1);
            break;
        case '5':
        {
            string newStudentGroup;
            cout << "\nВведите название группы для  студента";
            cin >> newStudentGroup;

            if (!MPT.groupExists(newStudentGroup)) {
                cout << "\nГруппы с таким названием нет\n" << endl;
            }
            else {
                Student newStudent(newStudentGroup);
                group.addStudent(newStudent);
            }
            break;
        }
        case '6':
        {
            string newGroup;
            cout << "\nВведите название новой группы: ";
            cin >> newGroup;

            if (MPT.groupExists(newGroup)) {
                cout << "\nГруппа с таким названием уже существует\n" << endl;
            }
            else {
                Group new_Group(newGroup);
                MPT.addGroup(new_Group);
            }
            break;
        }
        case '7':
            MPT.showAllGroups();
            break;
        case '8':
        {
            string newSubject;
            cout << "\nВведите название новой дисциплины: ";
            cin >> newSubject;

            student1.addSubject(newSubject);

            for (Student& student : group.getStudents()) {
                student.addSubject(newSubject);
            }

            cout << "Дисциплина добавлена\n" << endl;

            break;
        }
        case '9':
            cout << "\nE группы был удалён один долг";
            student1.yaProshauTeba();
            break;
        case 's':
            student1.getSdanixRabor();
            cout << "\nСтуденты выполнили практическую работу\n";
            break;
        case 'q':
            cout << "Вы вышли из программы!";
            break;
        default:
            cout << "\nТакого в меню нет!\n" << endl;
            break;
        }

    } while (choice != 'q');

    return 0;
}
