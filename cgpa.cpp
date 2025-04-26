#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>
using namespace std;

struct Course {
    string name;
    float marks;
    int creditHours;
    string grade;
    float gradePoint;
};

struct Student {
    string name;
    string rollNo;
    vector<Course> courses;
    float GPA = 0.0;
};

// Converts marks to grade and grade points
pair<string, float> getGradeAndPoint(float marks) {
    if (marks >= 90) {
		return {"A+", 4.00};
	}
	else if (marks >= 86) {
		return {"A", 4.00};
	}
	else if (marks >= 82) {
		return {"A-", 3.67};
	}
	else if (marks >= 78) {
		return {"B+", 3.33};
	}
	else if (marks >= 74) {
		return {"B", 3.00};
	}
	else if (marks >= 70) {
		return {"B-", 2.67};
	}
	else if (marks >= 66) {
		return {"C+", 2.33};
	}
	else if (marks >= 62) {
		return {"C", 2.00};
	}
	else if (marks >= 58) {
		return {"C-", 1.67};
	}
	else if (marks >= 54) {
		return {"D+", 1.33};
	}
	else if (marks >= 50) {
		return {"D", 1.00};
	}
	else {
		return {"F", 0.00};
	}
}

// Calculates GPA from the list of courses
float calculateGPA(vector<Course>& courses) {
    float totalPoints = 0, totalCredits = 0;
    for (auto& course : courses) {
        auto [grade, point] = getGradeAndPoint(course.marks);
        course.grade = grade;
        course.gradePoint = point;
        totalPoints += point * course.creditHours;
        totalCredits += course.creditHours;
    }
    return (totalCredits > 0) ? totalPoints / totalCredits : 0.0;
}

// Input a single course
void inputCourse(vector<Course>& courses) {
    Course course;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\nEnter Course Name: ";
    getline(cin, course.name);
    cout << "Enter Credit Hours (1-4): ";
    cin >> course.creditHours;
    cout << "Enter Marks Obtained (0-100): ";
    cin >> course.marks;
    courses.push_back(course);
    cout << "Course Added Successfully!\n";
}

// Update existing course
void updateCourse(vector<Course>& courses) {
    if (courses.empty()) {
        cout << "\nNo courses to update.\n";
        return;
    }

    cout << "\n Available Courses:\n";
    for (int i = 0; i < courses.size(); ++i)
        cout << i + 1 << ". " << courses[i].name << endl;

    int choice;
    cout << "\nEnter course number to update: ";
    cin >> choice;

    if (choice >= 1 && choice <= courses.size()) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter New Course Name: ";
        getline(cin, courses[choice - 1].name);
        cout << "Enter New Credit Hours: ";
        cin >> courses[choice - 1].creditHours;
        cout << "Enter New Marks: ";
        cin >> courses[choice - 1].marks;
        cout << "Course Updated Successfully!\n";
    } 
    else {
        cout << "Invalid selection.\n";
    }
}

// Delete a course
void deleteCourse(vector<Course>& courses) {
    if (courses.empty()) {
        cout << "\nNo courses to delete.\n";
        return;
    }

    cout << "\nAvailable Courses:\n";
    for (int i = 0; i < courses.size(); ++i)
        cout << i + 1 << ". " << courses[i].name << endl;

    int choice;
    cout << "\nEnter course number to delete: ";
    cin >> choice;

    if (choice >= 1 && choice <= courses.size()) {
        courses.erase(courses.begin() + choice - 1);
        cout << "? Course Deleted Successfully!\n";
    } 
    else {
        cout << "Invalid selection.\n";
    }
}

// Display GPA Report
void showGPA(Student& student) {
    student.GPA = calculateGPA(student.courses);

    cout << "\n=============== GPA REPORT ===============\n";
    cout << "Name      : " << student.name << endl;
    cout << "Roll No   : " << student.rollNo << endl;

    cout << "\n" << left
         << setw(25) << "Course Name"
         << setw(10) << "Marks"
         << setw(8)  << "Grade"
         << setw(15) << "Credit Hours"
         << setw(15) << "Grade Points" << endl;

    cout << string(70, '-') << endl;

    float totalCredits = 0, totalPoints = 0;
    for (const auto& c : student.courses) {
        float gPoints = c.gradePoint * c.creditHours;
        cout << left << setw(25) << c.name << setw(10) << c.marks << setw(8)  << c.grade << setw(15) << c.creditHours << setw(15) << fixed << setprecision(2) << gPoints << endl;

        totalCredits += c.creditHours;
        totalPoints += gPoints;
    }

    cout << "\n" << string(40, '-') << endl;
    cout << "Total Credits     : " << totalCredits << endl;
    cout << "Total Grade Points: " << totalPoints << endl;
    cout << "GPA             : " << fixed << setprecision(2) << student.GPA << endl;
    cout << "==========================================\n";
}

// Student dashboard
void studentPortal(Student& student) {
    int option;
    do {
        cout << "\n====== Student Portal ======\n";
        cout << "1. Add Course\n";
        cout << "2. Update Course\n";
        cout << "3. Delete Course\n";
        cout << "4. Show GPA Report\n";
        cout << "5. Exit\n";
        cout << "Choose an option: ";
        cin >> option;

        switch (option) {
            case 1: inputCourse(student.courses); break;
            case 2: updateCourse(student.courses); break;
            case 3: deleteCourse(student.courses); break;
            case 4: showGPA(student); break;
            case 5: cout << "===========================================\nExiting... Thank you!\nDeveloped By Muzammil Zaidi\n"; break;
            default: cout << "Invalid option.\n";
        }
    } 
    while (option != 5);
}

// Main entry point
int main() {
    Student student;
    cout << "\n========== Welcome to GPA Calculator ==========\n";
    cout << "Enter Your Name    : ";
    getline(cin, student.name);
    cout << "Enter Your Roll No : ";
    getline(cin, student.rollNo);

    studentPortal(student);
    return 0;
}
