//CGPA calculator which stores information of multiple students including their course details and cgpa individually and displays the result.

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

//Structure to store attributes of a student.
struct StudentDetails{
    string studentName;
    double studentAge;
    double studentRollno;
    string studentUniversityName;
    vector<MyCoursesAttributes> courses; //To store courses for each student individually.
    double currentSemester;
    double cgpa;
};

//A Student class with only one method to display student info.
class Student{
public:

    void displayStudentInfo(const vector<StudentDetails>& studentdetails){
        int studentIndex = 0;
        cout << "Enter index of student to access his/her information (Starting from 0): " <<endl;
        cin >> studentIndex;

        cout <<"Student information : " << endl;
        cout << "Student Name : " << studentdetails[studentIndex].studentName << endl;
        cout << "Student Age : " << studentdetails[studentIndex].studentAge << endl;
        cout << "University Name : " << studentdetails[studentIndex].studentUniversityName << endl;
        cout << "Roll no. : " << studentdetails[studentIndex].studentRollno << endl;
        cout << "Currently Studing in semester : " << studentdetails[studentIndex].currentSemester << endl;
        cout << "Course Details : " << endl;
        for (const MyCoursesAttributes& course : studentdetails[studentIndex].courses){
            cout << "Course Name : " << course.courseName << endl;
            cout << "Credit Hours : " << course.creditHours << endl;
            cout << "Grade Points : " << course.gradePoints << endl;
        }
        cout << "CGPA Obtained : " << fixed << setprecision(2) << studentdetails[studentIndex].cgpa << endl;
    }
};


int main(){
    //To store num of students enter by the user.
    int numStudents = 0;
    //To store num of courses enter by the user.
    int numCourses = 0;

    //Prompting the user to enter num of students.
    cout <<"Enter number of students : " << endl;
    cin >> numStudents;

    //A vector of students of size enter by the user.
    vector<StudentDetails> studentdetails(numStudents);

    //A vector of courses of size enter by the user.
    vector<MyCoursesAttributes> courses(numCourses);

    //Assigning values to student details attributes.
    for (int i = 0; i < numStudents; i++){
        cout << "Student no. " << i + 1 << endl;
        cout << "Enter Student Name : " <<endl;
        cin >> studentdetails[i].studentName;
        cout << "Enter Student Age : " << endl;
        cin >> studentdetails[i].studentAge;
        cout << "Enter Student's University Name : " << endl;
        cin >> studentdetails[i].studentUniversityName;
        cout << "Enter Student's roll no. : " << endl;
        cin >> studentdetails[i].studentRollno;
        cout << "Enter Current Semester no. : " << endl;
        cin >> studentdetails[i].currentSemester;

        //Prompting the user to enter num of courses.
        cout <<"Enter number of courses : " << endl;
        cin >> numCourses;

        // Resize the courses vector for the current student
        studentdetails[i].courses.resize(numCourses);

        //Using a for loop to assign values given by user to vector elements.
        for (int j = 0; j < numCourses; j++){
            cout << "Course no. : " << j + 1 << endl;
            cout << "Enter Course Name : " << endl;
            cin >> studentdetails[i].courses[j].courseName;
            cout << "Enter Credit Hours : " << endl;
            cin >> studentdetails[i].courses[j].creditHours;
            cout << "Enter Grade Points Obtained : " << endl;
            cin >> studentdetails[i].courses[j].gradePoints;

            //Obj of class to access method.
            MyCourses MyCoursesObj;
            studentdetails[i].cgpa = MyCoursesObj.calculateCGPA(studentdetails[i].courses);
        }

    }

    Student StudentObj;

    StudentObj.displayStudentInfo(studentdetails);


    return 0;
}