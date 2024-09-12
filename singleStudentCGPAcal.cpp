//CGPA calculator based on Course information.

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

//Structure for course attributes.
struct MyCoursesAttributes{
    string courseName;
    double creditHours;
    double gradePoints;
};

//My course class with only one method to calculate cgpa.
class MyCourses{
public:

    //A method to calculate cgpa.
    double calculateCGPA(const vector<MyCoursesAttributes>& courses){
        double totalCreditHours = 0.0;
        double totalGradePoints =  0.0;

        //a range based for loop to iterate over vector of type MyCourseAttributes.
        for (const MyCoursesAttributes& course : courses){
            totalCreditHours += course.creditHours;
            totalGradePoints += course.gradePoints * course.creditHours;
        }

        //return the value of cgpa.
        return totalGradePoints / totalCreditHours;
    }
    
};

int main(){
    //To store num of courses enter by the user.
    int numCourses;

    //Prompting the user to enter num of courses.
    cout <<"Enter number of courses : " << endl;
    cin >> numCourses;

    //A vector of courses to passed as an argument when calling the function.
    vector<MyCoursesAttributes> courses(numCourses);

    //Using a for loop to assign values given by user to vector elements.
    for (int i = 0; i < numCourses; i++){
        cout << "Course no. : " << i + 1 << endl;
        cout << "Enter Course Name : " << endl;
        cin >> courses[i].courseName;
        cout << "Enter Credit Hours : " << endl;
        cin >> courses[i].creditHours;
        cout << "Enter Grade Points Obtained : " << endl;
        cin >> courses[i].gradePoints;
    }

    //Obj of class to access method.
    MyCourses MyCoursesObj;

    //calling method and storing its value in a variable.
    double cgpa;
    cgpa = MyCoursesObj.calculateCGPA(courses);

    //Display cgpa.
    cout << "\nYou obtained a CGPA of : " << fixed << setprecision(2) << cgpa << endl;

    return 0;
}


