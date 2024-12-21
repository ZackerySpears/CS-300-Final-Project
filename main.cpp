//Zackery Spears

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//Course structure to hold course details
struct Course {
    string courseNumber;
    string courseName;
    vector<string> prerequisites;

    Course(string number, string name) : courseNumber(number), courseName(name) {}
};

// Function to load course data from a CSV file
vector<Course> loadCourseData(const string& fileName) {
    //Use the file name directly
    vector<Course> courses;
    ifstream file(fileName);  
    //Check if the file opens successfully
    if (!file.is_open()) {  
        cout << "Unable to open file: " << fileName << endl;
        return courses;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string courseNumber, courseName, prereq;

        getline(ss, courseNumber, ',');
        getline(ss, courseName, ',');

        Course course(courseNumber, courseName);
        while (getline(ss, prereq, ',')) {
            course.prerequisites.push_back(prereq);
        }

        courses.push_back(course);
    }
    // Close the file after reading
    file.close(); 
    return courses;
}

//Function to print the course list in alphanumeric order
void printCourseList(const vector<Course>& courses) {
    vector<Course> sortedCourses = courses;

    sort(sortedCourses.begin(), sortedCourses.end(), [](Course a, Course b) {
        return a.courseNumber < b.courseNumber;
        });

    cout << "\nHere is a sample schedule:" << endl;
    cout << endl;
    for (const auto& course : sortedCourses) {
        cout << course.courseNumber << ", " << course.courseName << endl;
    }
}

//Function to print details of a specific course
void printCourse(const vector<Course>& courses, string courseNumber) {
    for (const auto& course : courses) {
        if (course.courseNumber == courseNumber) {
            cout << course.courseNumber << ", " << course.courseName << endl;
            cout << "Prerequisites: ";
            for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                cout << course.prerequisites[i];
                if (i < course.prerequisites.size() - 1) {
                    cout << ", ";
                }
            }
            cout << endl;
            return;
        }
    }
    cout << "Course not found." << endl;
}


int main() {
    bool menuLoop = true;
    int userInput;
    vector<Course> courses;
    cout << "Welcome to the course planner." << endl;
    cout << endl;

    while (menuLoop == true) {
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "" << endl;
        cout << "What would you like to do?" << endl;

        cin >> userInput;
        switch (userInput) {
        case 1:
            courses = loadCourseData("CS 300 ABCU_Advising_Program_Input.csv");
            if (!courses.empty()) {
                cout << "Data loaded successfully." << endl;
            }
            else {
                cout << "Unable to load data." << endl;
            }
            break;
        case 2:
            if (!courses.empty()) {
                printCourseList(courses);
            }
            else {
                cout << "Please load data first." << endl;
            }
            break;

        case 3:
            if (!courses.empty()) {
                    cout << "What course do you want to know about? ";
                    string courseNumber;
                    cin >> courseNumber;
                    printCourse(courses, courseNumber);
                }
                else {
                    cout << "Please load data first." << endl;
                } 
                break;
        
        case 9: 
            cout << "Thank you for using the course planner" << endl;
            menuLoop = false;
            break;
        default:
            cout << userInput << " is not a valid option." << endl;
            break;
        }
    } 
}
