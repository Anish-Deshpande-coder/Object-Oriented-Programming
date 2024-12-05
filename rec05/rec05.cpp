/*
  rec05-start.cpp

  Remember that the file you are to submit should be named rec05.cpp.
  And YOUR NAME should appear up here in the comment.
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;


#include <iostream>
#include <string>
#include <vector>
#include <iomanip>  // For formatting time output

using namespace std;

class Section {
private:
    class TimeSlot {
        friend ostream& operator<<(ostream& os, const TimeSlot& timeslot) {
            os << "[Day: " << timeslot.day << ", Start time: ";
            unsigned displayHour = timeslot.hour;
            string period = "AM";
            if (timeslot.hour == 0) displayHour = 12;
            else if (timeslot.hour >= 12) {
                period = (timeslot.hour == 12) ? "PM" : "PM";
                if (timeslot.hour > 12) displayHour -= 12;
            }
            os << displayHour << period << "]";
            return os;
        }
    public:
        TimeSlot(const string& day, unsigned hour) : day(day), hour(hour) {}



    private:
        string day;
        unsigned hour;
    };

    class StudentRecord {
        friend ostream& operator<<(ostream& os, const StudentRecord& student) {
            os << "Student: " << student.name << ", Grades: ";
            for (int grade : student.grades) {
                os << grade << " ";
            }
            return os;
        }
    public:
        StudentRecord(const string& name) : name(name), grades(14, -1) {}

        void addGrade(int grade, int week) {
            grades[week - 1] = grade;
        }

        const string& getName() const {
            return name;
        }



    private:
        string name;
        vector<int> grades;
    };

public:
    friend ostream& operator<<(ostream& os, const Section& section) {
        os << "Section: " << section.name << ", Time slot: " << section.timeslot << "\n";
        os << "Students:\n";
        for (const StudentRecord* student : section.students) {
            os << *student << "\n";
        }
        return os;
    }

    Section(const string& name, const string& day, unsigned hour)
        : name(name), timeslot(day, hour) {}

    ~Section() {
        cout << "Section " << name << " is being deleted\n";
        for (StudentRecord* student : students) {
            cout << "Deleting " << student->getName() << "\n";
            delete student;
        }
        students.clear();
    }

    Section(const Section& other) : name(other.name), timeslot(other.timeslot) {
        for (const StudentRecord* student : other.students) {
            students.push_back(new StudentRecord(*student));
        }
    }

    void addStudent(const string& studentName) {
        students.push_back(new StudentRecord(studentName));
    }

    void addGrade(const string& studentName, int grade, int week) {
        for (StudentRecord* student : students) {
            if (student->getName() == studentName) {
                student->addGrade(grade, week);
                return;
            }
        }
    }

private:
    string name;
    TimeSlot timeslot;
    vector<StudentRecord*> students;
};

class LabWorker {
    friend ostream& operator<<(ostream& os, const LabWorker& worker) {
        os << "Lab Worker: " << worker.name << endl;
        if (worker.section) {
            os << *worker.section;
        } else {
            os << "No section assigned yet." << endl;
        }
        return os;
    }
public:
    LabWorker(const string& name) : name(name), section(nullptr) {}
    void addSection(Section& newSection) {
        section = &newSection;
    }
    void addGrade(const string& studentName, int grade, int week) {
        if (section) {
            section->addGrade(studentName, grade, week);
        }
    }
private:
    string name;
    Section* section;
};


void doNothing(const Section& sec) {
    cout << sec << endl;
}

int main() {

    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    cout << secA2 << endl;

    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    cout << secA2 << endl;

    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe( "Moe" );
    cout << moe << endl;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection( secA2 );
    cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
    secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");
    secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection( secB3 );
    cout << jane << endl;

    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);
    moe.addGrade("Paul", 19, 1);
    moe.addGrade("George", 16, 1);
    moe.addGrade("Ringo", 7, 1);
    cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);
    moe.addGrade("Paul", 20, 3);
    moe.addGrade("Ringo", 0, 3);
    moe.addGrade("George", 16, 3);
    cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
         << "those students (or rather their records?)\n";

    cout << "\nTest 9: Copy Constructor: make sure the following calls work:\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n" << secA2 << endl;

} // main


