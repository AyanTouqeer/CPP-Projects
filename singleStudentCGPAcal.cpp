#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

struct MyCoursesAttributes{
    string courseName;
    double creditHours;
    double gradePoints;
};


class MyCourse{
public:
    double calculateCGPA(const vector<MyCoursesAttributes>& courses){ //taking a parameter of a vector.
        double totalCreditHours = 0.0;
        double totalGradePoints = 0.0;

        //using a range based for loop.
        for(const MyCoursesAttributes& course : courses){ // for loop will iterate over every element in the vector.
            totalCreditHours += course.creditHours; // credit hours of current course will be added.
            totalGradePoints += course.creditHours * course.gradePoints;
        }

        //values are incremented in the variables. Therefore, now return there division.
        return totalGradePoints / totalCreditHours;
    }

};


int main(){
    int numCourses;
    cout << "Enter number of courses : " << endl;
    cin >> numCourses;
    //create a class obj.
    MyCourse MyCourseObj;
    //defining a vector.
    vector<MyCoursesAttributes> courses(numCourses); // courses vector has been created.

    //for loop to assign value to attributes of elements in a vector.
    for (int i = 0; i < numCourses ; ++i){
        cout << "Course no. " << i + 1 << endl;
        cout << "Enter course name : " << endl;
        cin >> courses[i].courseName;
        cout << "Enter credit hours : " << endl;
        cin >> courses[i].creditHours;
        cout << "Enter grade points : " << endl;
        cin >> courses[i].gradePoints;
    }

    double cgpa = MyCourseObj.calculateCGPA(courses); // This line is highlighted by a red line.

    cout << "\nYour CGPA is : " << fixed << setprecision(2) << cgpa << endl;
}


