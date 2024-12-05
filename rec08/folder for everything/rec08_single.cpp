/*
  rec08_single.cpp
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student;

class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);
public:
    Course(const string& courseName);
    const string& getName() const;
    bool addStudent(Student* student);
    void removeStudentsFromCourse();

private:
    string name;
    vector<Student*> students;
};

class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);
public:
    Student(const string& name);
    const string& getName() const;
    bool addCourse(Course* course);
    void removedFromCourse(Course* course);

private:
    string name;
    vector<Course*> courses;
};

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    Registrar();

    bool addCourse(const string& courseName);
    bool addStudent(const string& studentName);
    bool enrollStudentInCourse(const string& studentName, const string& courseName);
    bool cancelCourse(const string& courseName);
    void purge();

private:
    size_t findStudent(const string& name) const;
    size_t findCourse(const string& name) const;

    vector<Course*> courses;
    vector<Student*> students;
};

// Testing
int main() {
    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;

    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e., do nothing, since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;

    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;

    return 0;
}

// Course Methods
Course::Course(const string& courseName) : name(courseName) {}

const string& Course::getName() const { return name; }

bool Course::addStudent(Student* student) {
    for (const Student* s : students) {
        if (s == student) return false;
    }
    students.push_back(student);
    return true;
}

void Course::removeStudentsFromCourse() {
    for (Student* student : students) {
        if (student) {
            student->removedFromCourse(this);
        }
    }
    students.clear();
}

ostream& operator<<(ostream& os, const Course& rhs) {
    os << rhs.name << ": ";
    bool hasStudents = false;
    for (const Student* student : rhs.students) {
        if (student) {
            os << student->getName() << " ";
            hasStudents = true;
        }
    }
    if (!hasStudents) os << "No Students";
    return os;
}

// Student Methods
Student::Student(const string& studentName) : name(studentName) {}

const string& Student::getName() const { return name; }

bool Student::addCourse(Course* course) {
    for (const Course* c : courses) {
        if (c == course) return false;
    }
    courses.push_back(course);
    return true;
}

void Student::removedFromCourse(Course* course) {
    for (Course*& c : courses) {
        if (c == course) {
            c = courses.back();
            courses.pop_back();
            break;
        }
    }
}

ostream& operator<<(ostream& os, const Student& rhs) {
    os << rhs.name << ": ";
    bool hasCourses = false;
    for (const Course* course : rhs.courses) {
        if (course) {
            os << course->getName() << " ";
            hasCourses = true;
        }
    }
    if (!hasCourses) os << "No Courses";
    return os;
}

// Registrar Methods
Registrar::Registrar() {}

bool Registrar::addCourse(const string& courseName) {
    if (findCourse(courseName) != courses.size()) return false;
    courses.push_back(new Course(courseName));
    return true;
}

bool Registrar::addStudent(const string& studentName) {
    if (findStudent(studentName) != students.size()) return false;
    students.push_back(new Student(studentName));
    return true;
}

bool Registrar::enrollStudentInCourse(const string& studentName, const string& courseName) {
    size_t studentIndex = findStudent(studentName);
    size_t courseIndex = findCourse(courseName);

    if (studentIndex == students.size() || courseIndex == courses.size()) return false;

    Student* student = students[studentIndex];
    Course* course = courses[courseIndex];

    return student->addCourse(course) && course->addStudent(student);
}

bool Registrar::cancelCourse(const string& courseName) {
    size_t courseIndex = findCourse(courseName);
    if (courseIndex == courses.size()) return false;

    Course* course = courses[courseIndex];
    course->removeStudentsFromCourse();
    delete course;
    courses[courseIndex] = courses.back(); // Mark the course as removed by setting it to nullptr
    courses.pop_back();
    return true;
}

void Registrar::purge() {
    for (Course* course : courses) {
        delete course;
    }
    for (Student* student : students) {
        delete student;
    }
    courses.clear();
    students.clear();
}

size_t Registrar::findStudent(const string& name) const {
    for (size_t i = 0; i < students.size(); ++i) {
        if (students[i] && students[i]->getName() == name) return i;
    }
    return students.size();
}

size_t Registrar::findCourse(const string& name) const {
    for (size_t i = 0; i < courses.size(); ++i) {
        if (courses[i] && courses[i]->getName() == name) return i;
    }
    return courses.size();
}

ostream& operator<<(ostream& os, const Registrar& rhs) {
    os << "Registrar's Report\nCourses:\n";
    for (const Course* course : rhs.courses) {
        if (course) os << *course << endl;
    }
    os << "Students:\n";
    for (const Student* student : rhs.students) {
        if (student) os << *student << endl;
    }
    return os;
}

