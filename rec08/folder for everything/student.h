// student.h
#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include <vector>
namespace BrooklynPoly {
    class Course;

    class Student {
        friend std::ostream& operator<<(std::ostream& os, const Student& rhs);
    public:
        Student(const std::string& name);

        const std::string& getName() const;
        bool addCourse(Course* course);
        void removedFromCourse(Course* course);

    private:
        std::string name;
        std::vector<Course*> courses;
    };
}
#endif // STUDENT_H
