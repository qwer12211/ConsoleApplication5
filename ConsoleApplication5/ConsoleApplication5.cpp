#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <string>
#include <vector>
using namespace std;

class Student {
public:
    string name;
    string group;
    vector<string> disciplines;
    int completed_works;
    int debts;

    Student(string name, string group) : name(name), group(group), completed_works(0), debts(0) {}

    void addDiscipline(string discipline) {
        disciplines.push_back(discipline);
    }
};

class Teacher {
public:
    string name;
    vector<string> disciplines;
    vector<string> groups;

    Teacher(string name) : name(name) {}

    void addDiscipline(string discipline) {
        disciplines.push_back(discipline);
    }

    void addGroup(string group) {
        groups.push_back(group);
    }
};

class MPT {
public:
    vector<Student> students;
    vector<Teacher> teachers;

    void addStudentToGroup(Student& student, string group) {
        student.group = group;
        students.push_back(student);
    }

    void incrementCompletedWork(Student& student) {
        student.completed_works++;
    }

    void addDisciplineToTeacher(Teacher& teacher, string discipline) {
        teacher.addDiscipline(discipline);
    }

    void addGroupToTeacher(Teacher& teacher, string group) {
        teacher.addGroup(group);
    }

    void submitWork(Student& student) {
        student.completed_works++;
        student.debts--;
    }

    int countStudentsInClass(string group) {
        int count = 0;
        for (const auto& student : students) {
            if (student.group == group)
                count++;
        }
        return count;
    }
};



int main() {
    setlocale(LC_ALL, "RUS");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(0, "");

    MPT mpt;
    while (true) {
        cout << "Выберите операцию:\n"
            << "1. Добавить студента\n"
            << "2. Добавить преподавателя\n"
            << "3. Добавить дисциплину преподавателю\n"
            << "4. Добавить группу преподавателю\n"
            << "5. Сдать работу\n"
            << "6. Добавить долг\n"
            << "7. Показать студентов\n"
            << "8. Выход\n";
        int choice;
        cin >> choice;
        switch (choice) {
        case 1: {
            cout << "Введите имя студента: ";
            string name;
            cin >> name;
            cout << "Введите группу студента: ";
            string group;
            cin >> group;

            bool studentExists = false;
            for (const auto& student : mpt.students) {
                if (student.name == name) {
                    studentExists = true;
                    break;
                }
            }


            if (studentExists) {
                cout << "Студент с таким именем уже существует." << endl;
            }
            else {
                Student student(name, group);
                mpt.addStudentToGroup(student, group);
            }
            break;
        }

        case 2: {
            cout << "Введите имя преподавателя: ";
            string name;
            cin >> name;
            Teacher teacher(name);
            mpt.teachers.push_back(teacher);
            break;
        }
        case 3: {
            cout << "Введите имя преподавателя: ";
            string teacher_name;
            cin >> teacher_name;
            cout << "Введите дисциплину: ";
            string discipline;
            cin >> discipline;
            for (auto& teacher : mpt.teachers) {
                if (teacher.name == teacher_name) {
                    bool disciplineExists = false;
                    for (const auto& existingDiscipline : teacher.disciplines) {
                        if (existingDiscipline == discipline) {
                            disciplineExists = true;
                            break;
                        }
                    }
                    if (!disciplineExists) {
                        teacher.addDiscipline(discipline);
                    }
                    else {
                        cout << "Дисциплина уже добавлена преподавателю." << endl;
                    }
                    break;
                }
            }
            break;
        }

        case 4: {
            cout << "Введите имя преподавателя: ";
            string teacher_name;
            cin >> teacher_name;
            cout << "Введите группу: ";
            string group;
            cin >> group;
            bool group_exists = false;
            bool teacher_exists = false;
            for (auto& teacher : mpt.teachers) {
                if (teacher.name == teacher_name) {
                    teacher_exists = true;
                    for (const auto& existing_group : teacher.groups) {
                        if (existing_group == group) {
                            group_exists = true;
                            break;
                        }
                    }
                    if (group_exists) {
                        cout << "Группа уже существует у преподавателя." << endl;
                    }
                    else {
                        teacher.addGroup(group);
                        cout << "Группа успешно добавлена." << endl;
                    }
                    break;
                }
            }
            if (!teacher_exists) {
                cout << "Преподаватель не найден." << endl;
            }
            break;
        }


        case 5: {
            cout << "Введите имя студента, который сдает работу: ";
            string student_name;
            cin >> student_name;
            for (auto& student : mpt.students) {
                if (student.name == student_name) {
                    mpt.submitWork(student);
                    break;
                }
            }
            break;
        }
        case 6: {
            cout << "Введите имя студента, которому добавляется долг: ";
            string student_name;
            cin >> student_name;
            for (auto& student : mpt.students) {
                if (student.name == student_name) {
                    student.debts++;
                    break;
                }
            }
            break;
        }
        case 7: {
            for (const auto& student : mpt.students) {
                cout << student.name << " " << student.group << " " << student.completed_works << " " << student.debts << endl;
            }
            break;
        }
        case 8: {
            return 0;
        }
        default: {
            cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
            break;
        }
        }
    }
    return 0;
}
