
#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

// Базовий клас користувача
class User {
public:
    string name;
    string email;
    string password;

    User(string n, string e, string p) {
        name = n;
        email = e;
        password = p;
    }

    void show() {
        cout << name << " (" << email << ")" << endl;
    }
};

// Клас студента
class Student : public User {
public:
    vector<int> courseIds;

    Student(string n, string e, string p)
        : User(n, e, p) {}

    void enrollCourse(int courseId) {
        for (int id : courseIds) {
            if (id == courseId) {
                return;
            }
        }

        courseIds.push_back(courseId);
    }

    void show() {
        cout << "Студент: " << name
             << ", Email: " << email << endl;
    }
};

// Клас викладача
class Teacher : public User {
public:
    vector<int> courseIds;

    Teacher(string n, string e, string p)
        : User(n, e, p) {}

    void show() {
        cout << "Викладач: " << name
             << ", Email: " << email << endl;
    }
};

// Клас уроку
class Lesson {
public:
    int id;
    string title;
    string content;

    Lesson(int i, string t, string c) {
        id = i;
        title = t;
        content = c;
    }

    void show() {
        cout << "Урок №" << id << ": "
             << title << " - " << content << endl;
    }
};

// Клас завдання
class Assignment {
public:
    int id;
    string title;
    int maxScore;

    Assignment(int i, string t, int score) {
        id = i;
        title = t;
        maxScore = score;
    }

    void show() {
        cout << "Завдання №" << id
             << ": " << title
             << ", максимальний бал: "
             << maxScore << endl;
    }

    void submit(Student student, int score) {
        if (score < 0 || score > maxScore) {
            cout << "Неправильний бал!" << endl;
            return;
        }

        cout << student.name << " отримав "
             << score << " із " << maxScore
             << " балів." << endl;
    }
};

// Клас курсу
class Course {
public:
    int id;
    string title;
    int teacherIndex;

    vector<Lesson> lessons;
    vector<Assignment> assignments;

    Course(int i, string t, int teacher) {
        id = i;
        title = t;
        teacherIndex = teacher;
    }

    void addLesson(string title, string content) {
        Lesson lesson(lessons.size() + 1, title, content);
        lessons.push_back(lesson);
    }

    void addAssignment(string title, int score) {
        Assignment assignment(assignments.size() + 1,
                              title, score);
        assignments.push_back(assignment);
    }

    void show(vector<Teacher>& teachers) {
        cout << "Курс №" << id
             << ": " << title;

        cout << ", викладач: "
             << teachers[teacherIndex].name;

        cout << ", уроків: " << lessons.size();
        cout << ", завдань: " << assignments.size()
             << endl;
    }
};

// Клас запису на курс
class Enrollment {
public:
    int studentIndex;
    int courseIndex;
    int progress;

    Enrollment(int student, int course) {
        studentIndex = student;
        courseIndex = course;
        progress = 0;
    }

    void show(vector<Student>& students,
              vector<Course>& courses) {

        cout << students[studentIndex].name
             << " - "
             << courses[courseIndex].title
             << ", прогрес: "
             << progress << "%" << endl;
    }
};

// Основна програма
vector<Student> students;
vector<Teacher> teachers;
vector<Course> courses;
vector<Enrollment> enrollments;

int nextCourseId = 1;

// Додавання студента
void addStudent() {
    string name, email, password;

    cout << "Ім'я студента: ";
    getline(cin, name);

    cout << "Email: ";
    getline(cin, email);

    cout << "Пароль: ";
    getline(cin, password);

    students.push_back(Student(name, email, password));

    cout << "Студента додано!" << endl;
}

// Додавання викладача
void addTeacher() {
    string name, email, password;

    cout << "Ім'я викладача: ";
    getline(cin, name);

    cout << "Email: ";
    getline(cin, email);

    cout << "Пароль: ";
    getline(cin, password);

    teachers.push_back(Teacher(name, email, password));

    cout << "Викладача додано!" << endl;
}

// Створення курсу
void addCourse() {
    if (teachers.empty()) {
        cout << "Спочатку додайте викладача!" << endl;
        return;
    }

    string title;

    cout << "Назва курсу: ";
    getline(cin, title);

    cout << "\nСписок викладачів:\n";

    for (int i = 0; i < teachers.size(); i++) {
        cout << i + 1 << ". "
             << teachers[i].name << endl;
    }

    int index;

    cout << "Виберіть викладача: ";
    cin >> index;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (index < 1 || index > teachers.size()) {
        cout << "Неправильний номер!" << endl;
        return;
    }

    courses.push_back(
        Course(nextCourseId++, title, index - 1)
    );

    teachers[index - 1].courseIds.push_back(nextCourseId - 1);

    cout << "Курс створено!" << endl;
}

// Запис студента на курс
void enrollStudent() {
    if (students.empty() || courses.empty()) {
        cout << "Спочатку додайте студента та курс!" << endl;
        return;
    }

    cout << "\nСтуденти:\n";

    for (int i = 0; i < students.size(); i++) {
        cout << i + 1 << ". "
             << students[i].name << endl;
    }

    int studentIndex;

    cout << "Виберіть студента: ";
    cin >> studentIndex;

    if (studentIndex < 1 || studentIndex > students.size()) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Неправильний номер!" << endl;
        return;
    }

    cout << "\nКурси:\n";

    for (int i = 0; i < courses.size(); i++) {
        cout << i + 1 << ". "
             << courses[i].title << endl;
    }

    int courseIndex;

    cout << "Виберіть курс: ";
    cin >> courseIndex;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (courseIndex < 1 || courseIndex > courses.size()) {
        cout << "Неправильний номер!" << endl;
        return;
    }

    studentIndex--;
    courseIndex--;

    for (Enrollment e : enrollments) {
        if (e.studentIndex == studentIndex &&
            e.courseIndex == courseIndex) {

            cout << "Студент вже записаний на цей курс!"
                 << endl;
            return;
        }
    }

    students[studentIndex].enrollCourse(
        courses[courseIndex].id
    );

    enrollments.push_back(
        Enrollment(studentIndex, courseIndex)
    );

    cout << "Студента записано на курс!" << endl;
}

// Показати студентів
void showStudents() {
    if (students.empty()) {
        cout << "Список порожній!" << endl;
        return;
    }

    for (int i = 0; i < students.size(); i++) {
        cout << i + 1 << ". ";
        students[i].show();
    }
}

// Показати викладачів
void showTeachers() {
    if (teachers.empty()) {
        cout << "Список порожній!" << endl;
        return;
    }

    for (int i = 0; i < teachers.size(); i++) {
        cout << i + 1 << ". ";
        teachers[i].show();
    }
}

// Показати курси
void showCourses() {
    if (courses.empty()) {
        cout << "Список порожній!" << endl;
        return;
    }

    for (int i = 0; i < courses.size(); i++) {
        courses[i].show(teachers);
    }
}

// Показати записи на курси
void showEnrollments() {
    if (enrollments.empty()) {
        cout << "Записів поки немає!" << endl;
        return;
    }

    for (int i = 0; i < enrollments.size(); i++) {
        cout << i + 1 << ". ";
        enrollments[i].show(students, courses);
    }
}

// Додавання уроку
void addLesson() {
    if (courses.empty()) {
        cout << "Спочатку створіть курс!" << endl;
        return;
    }

    showCourses();

    int index;

    cout << "Виберіть курс: ";
    cin >> index;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (index < 1 || index > courses.size()) {
        cout << "Неправильний номер!" << endl;
        return;
    }

    string title, content;

    cout << "Назва уроку: ";
    getline(cin, title);

    cout << "Зміст уроку: ";
    getline(cin, content);

    courses[index - 1].addLesson(title, content);

    cout << "Урок додано!" << endl;
}

// Додавання завдання
void addAssignment() {
    if (courses.empty()) {
        cout << "Спочатку створіть курс!" << endl;
        return;
    }

    showCourses();

    int index;

    cout << "Виберіть курс: ";
    cin >> index;

    if (index < 1 || index > courses.size()) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Неправильний номер!" << endl;
        return;
    }

    string title;
    int score;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Назва завдання: ";
    getline(cin, title);

    cout << "Максимальний бал: ";
    cin >> score;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (score < 1) {
        cout << "Бал повинен бути більшим за 0!" << endl;
        return;
    }

    courses[index - 1].addAssignment(title, score);

    cout << "Завдання додано!" << endl;
}

// Оновлення прогресу
void updateProgress() {
    if (enrollments.empty()) {
        cout << "Записів на курси немає!" << endl;
        return;
    }

    showEnrollments();

    int index;

    cout << "Виберіть запис: ";
    cin >> index;

    if (index < 1 || index > enrollments.size()) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Неправильний номер!" << endl;
        return;
    }

    int progress;

    cout << "Новий прогрес (0-100): ";
    cin >> progress;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (progress < 0 || progress > 100) {
        cout << "Неправильне значення прогресу!" << endl;
        return;
    }

    enrollments[index - 1].progress = progress;

    cout << "Прогрес оновлено!" << endl;
}

// Головна функція
int main() {
    int choice;

    do {
        cout << "\n===== НАВЧАЛЬНА ПЛАТФОРМА =====\n";

        cout << "1. Додати студента\n";
        cout << "2. Додати викладача\n";
        cout << "3. Створити курс\n";
        cout << "4. Записати студента на курс\n";
        cout << "5. Показати студентів\n";
        cout << "6. Показати викладачів\n";
        cout << "7. Показати курси\n";
        cout << "8. Показати записи на курси\n";
        cout << "9. Додати урок до курсу\n";
        cout << "10. Додати завдання до курсу\n";
        cout << "11. Оновити прогрес студента\n";
        cout << "0. Вихід\n";

        cout << "Ваш вибір: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                addStudent();
                break;

            case 2:
                addTeacher();
                break;

            case 3:
                addCourse();
                break;

            case 4:
                enrollStudent();
                break;

            case 5:
                showStudents();
                break;

            case 6:
                showTeachers();
                break;

            case 7:
                showCourses();
                break;

            case 8:
                showEnrollments();
                break;

            case 9:
                addLesson();
                break;

            case 10:
                addAssignment();
                break;

            case 11:
                updateProgress();
                break;

            case 0:
                cout << "Програму завершено!" << endl;
                break;

            default:
                cout << "Невірний пункт меню!" << endl;
        }

    } while (choice != 0);

    return 0;
}
