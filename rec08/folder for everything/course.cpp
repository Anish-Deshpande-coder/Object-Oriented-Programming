// course.cpp
#include "course.h"
#include "student.h"

namespace BrooklynPoly {
    Course::Course(const std::string& courseName) : name(courseName) {}

    const std::string& Course::getName() const { return name; }

    bool Course::addStudent(Student* student) {
        for (Student* s : students) {
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

    std::ostream& operator<<(std::ostream& os, const Course& rhs) {
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
}