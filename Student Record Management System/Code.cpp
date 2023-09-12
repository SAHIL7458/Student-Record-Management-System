#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Student {
private:
    string name, roll_no, course, address, email_id, contact_no;

public:
    void menu();
    void insert();
    void display();
    void modify();
    void search();
    void remove();
};

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Student::menu() {
    while (true) {
        clearScreen();

        cout << "-----------------------------" << endl;
        cout << "| STUDENT MANAGEMENT SYSTEM |" << endl;
        cout << "-----------------------------" << endl;
        cout << "1. Enter New Record" << endl;
        cout << "2. Display Record" << endl;
        cout << "3. Modify Record" << endl;
        cout << "4. Search Record" << endl;
        cout << "5. Delete Record" << endl;
        cout << "6. Exit" << endl;

        cout << "Choose Option [1/2/3/4/5/6]: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                insert();
                break;
            case 2:
                display();
                break;
            case 3:
                modify();
                break;
            case 4:
                search();
                break;
            case 5:
                remove();
                break;
            case 6:
                exit(0);
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
}

void Student::insert() {
    clearScreen();

    cout << "Add Student Details" << endl;
    cout << "Enter Name: ";
    cin.ignore(); // Clear the newline character left in the buffer
    getline(cin, name);
    cout << "Enter Roll No.: ";
    cin >> roll_no;
    cout << "Enter Course: ";
    cin.ignore(); // Clear the newline character left in the buffer
    getline(cin, course);
    cout << "Enter Email Id: ";
    cin >> email_id;
    cout << "Enter Contact No: ";
    cin >> contact_no;
    cout << "Enter Address: ";
    cin.ignore(); // Clear the newline character left in the buffer
    getline(cin, address);

    ofstream file("studentRecord.txt", ios::app);
    if (!file.is_open()) {
        cerr << "Error: Unable to open the file." << endl;
        return;
    }
    
    file << name << "|" << roll_no << "|" << course << "|" << email_id << "|" << contact_no << "|" << address << endl;
    file.close();
    cout << "Student record added successfully." << endl;
}

void Student::display() {
    clearScreen();

    ifstream file("studentRecord.txt");
    if (!file.is_open()) {
        cerr << "No data is present." << endl;
        return;
    }

    string line;
    int total = 1;
    cout << "Student Record Table" << endl;
    while (getline(file, line)) {
        vector<string> fields;
        size_t pos = 0;
        while ((pos = line.find("|")) != string::npos) {
            fields.push_back(line.substr(0, pos));
            line.erase(0, pos + 1);
        }
        fields.push_back(line);

        cout << "\nStudent No.: " << total++ << endl;
        cout << "Student Name: " << fields[0] << endl;
        cout << "Student Roll No.: " << fields[1] << endl;
        cout << "Student Course: " << fields[2] << endl;
        cout << "Student Email Id.: " << fields[3] << endl;
        cout << "Student Contact No.: " << fields[4] << endl;
        cout << "Student Address: " << fields[5] << endl;
    }

    file.close();
    if (total == 1) {
        cout << "No data is present." << endl;
    }
}

void Student::modify() {
    clearScreen();

    string rollno;
    cout << "Modify Student Details" << endl;
    cout << "Enter Roll No. of Student you want to Modify: ";
    cin >> rollno;

    ifstream file("studentRecord.txt");
    if (!file.is_open()) {
        cerr << "No data is present." << endl;
        return;
    }

    vector<string> lines;
    string line;
    bool found = false;
    
    while (getline(file, line)) {
        vector<string> fields;
        size_t pos = 0;
        while ((pos = line.find("|")) != string::npos) {
            fields.push_back(line.substr(0, pos));
            line.erase(0, pos + 1);
        }
        fields.push_back(line);

        if (fields[1] == rollno) {
            found = true;
            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, fields[0]);
            cout << "Enter Roll No.: ";
            cin >> fields[1];
            cout << "Enter Course: ";
            cin.ignore();
            getline(cin, fields[2]);
            cout << "Enter Email Id: ";
            cin >> fields[3];
            cout << "Enter Contact No.: ";
            cin >> fields[4];
            cout << "Enter Address: ";
            cin.ignore();
            getline(cin, fields[5]);
        }

        lines.push_back(fields[0] + "|" + fields[1] + "|" + fields[2] + "|" + fields[3] + "|" + fields[4] + "|" + fields[5]);
    }

    file.close();

    if (!found) {
        cout << "Student with Roll No. " << rollno << " not found." << endl;
        return;
    }

    ofstream outFile("studentRecord.txt");
    if (!outFile.is_open()) {
        cerr << "Error: Unable to open the file." << endl;
        return;
    }

    for (const string& updatedLine : lines) {
        outFile << updatedLine << endl;
    }
    outFile.close();
    cout << "Student record modified successfully." << endl;
}

void Student::search() {
    clearScreen();

    string rollno;
    cout << "Search Student Data" << endl;
    cout << "Enter Roll No. of Student you want to Search: ";
    cin >> rollno;

    ifstream file("studentRecord.txt");
    if (!file.is_open()) {
        cerr << "No data is present." << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(file, line)) {
        vector<string> fields;
        size_t pos = 0;
        while ((pos = line.find("|")) != string::npos) {
            fields.push_back(line.substr(0, pos));
            line.erase(0, pos + 1);
        }
        fields.push_back(line);

        if (fields[1] == rollno) {
            found = true;
            cout << "Student Name: " << fields[0] << endl;
            cout << "Student Roll No.: " << fields[1] << endl;
            cout << "Student Course: " << fields[2] << endl;
            cout << "Student Email Id.: " << fields[3] << endl;
            cout << "Student Address: " << fields[5] << endl;
        }
    }

    file.close();

    if (!found) {
        cout << "Student with Roll No. " << rollno << " not found." << endl;
    }
}

void Student::remove() {
    clearScreen();

    string rollno;
    cout << "Delete Student Details" << endl;
    cout << "Enter Roll No. of Student you want to Delete: ";
    cin >> rollno;

    ifstream file("studentRecord.txt");
    if (!file.is_open()) {
        cerr << "No data is present." << endl;
        return;
    }

    vector<string> lines;
    string line;
    bool found = false;
    
    while (getline(file, line)) {
        vector<string> fields;
        size_t pos = 0;
        while ((pos = line.find("|")) != string::npos) {
            fields.push_back(line.substr(0, pos));
            line.erase(0, pos + 1);
        }
        fields.push_back(line);

        if (fields[1] == rollno) {
            found = true;
        } else {
            lines.push_back(fields[0] + "|" + fields[1] + "|" + fields[2] + "|" + fields[3] + "|" + fields[4] + "|" + fields[5]);
        }
    }

    file.close();

    if (!found) {
        cout << "Student with Roll No. " << rollno << " not found." << endl;
        return;
    }

    ofstream outFile("studentRecord.txt");
    if (!outFile.is_open()) {
        cerr << "Error: Unable to open the file." << endl;
        return;
    }

    for (const string& updatedLine : lines) {
        outFile << updatedLine << endl;
    }
    outFile.close();
    cout << "Student record deleted successfully." << endl;
}

int main() {
    Student project;
    project.menu();
    return 0;
}
