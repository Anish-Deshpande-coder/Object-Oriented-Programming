// registrar.cpp
#include "registrar.h"
#include "course.h"
#include "student.h"

namespace BrooklynPoly{
    Registrar::Registrar() {}

    bool Registrar::addCourse(const std::string& courseName) {
        if (findCourse(courseName) != courses.size()) return false;
        courses.push_back(new Course(courseName));
        return true;
    }

    bool Registrar::addStudent(const std::string& studentName) {
        if (findStudent(studentName) != students.size()) return false;
        students.push_back(new Student(studentName));
        return true;
    }

    bool Registrar::enrollStudentInCourse(const std::string& studentName, const std::string& courseName) {
        size_t studentIndex = findStudent(studentName);
        size_t courseIndex = findCourse(courseName);

        if (studentIndex == students.size() || courseIndex == courses.size()) return false;

        Student* student = students[studentIndex];
        Course* course = courses[courseIndex];

        student->addCourse(course);
        course->addStudent(student);
        return true;
    }

    bool Registrar::cancelCourse(const std::string& courseName) {
        size_t courseIndex = findCourse(courseName);
        if (courseIndex == courses.size()) return false;

        Course* course = courses[courseIndex];
        course->removeStudentsFromCourse();
        delete course;
        courses[courseIndex] = nullptr; // Mark the course as removed
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

    size_t Registrar::findStudent(const std::string& name) const {
        for (size_t i = 0; i < students.size(); ++i) {
            if (students[i] && students[i]->getName() == name) return i;
        }
        return students.size();
    }

    size_t Registrar::findCourse(const std::string& name) const {
        for (size_t i = 0; i < courses.size(); ++i) {
            if (courses[i] && courses[i]->getName() == name) return i;
        }
        return courses.size();
    }

    std::ostream& operator<<(std::ostream& os, const Registrar& rhs) {
        os << "Registrar's Report\nCourses:\n";
        for (const Course* course : rhs.courses) {
            if (course) os << *course << std::endl;
        }
        os << "Students:\n";
        for (const Student* student : rhs.students) {
            if (student) os << *student << std::endl;
        }
        return os;
    }
}