// student.cpp
#include "student.h"
#include "course.h"
namespace BrooklynPoly{
Student::Student(const std::string& studentName) : name(studentName) {}

const std::string& Student::getName() const { return name; }

bool Student::addCourse(Course* course) {
    for (Course* c : courses) {
        if (c == course) return false;
    }
    courses.push_back(course);
    return true;
}

void Student::removedFromCourse(Course* course) {
    for (Course*& c : courses) {
        if (c == course) {
            c = nullptr;  // Mark the course as removed
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Student& rhs) {
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
}