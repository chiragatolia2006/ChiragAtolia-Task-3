#include <iostream>
#include <vector>
#include <string>
#include <limits> // for numeric_limits

using namespace std;

class Task {
    string name;
    string description;
    string dueDate;
    bool completed;
public:
    Task(const string& n, const string& d, const string& dd)
        : name(n), description(d), dueDate(dd), completed(false) {}
    string getName() const { return name; }
    string getDescription() const { return description; }
    string getDueDate() const { return dueDate; }
    bool isCompleted() const { return completed; }
    void setName(const string& n) { name = n; }
    void setDescription(const string& d) { description = d; }
    void setDueDate(const string& dd) { dueDate = dd; }
    void markCompleted() { completed = true; }
    void display() const {
        cout << "Task: " << name << " (" << (completed ? "Completed" : "Pending") << ")" << endl;
        cout << " Due: " << dueDate << endl;
        cout << " Description: " << description << endl;
    }
};

class ToDoList {
    vector<Task> tasks;
public:
    void displayMenu() {
        cout << "\n----- To-Do List Menu -----\n";
        cout << "1. Add Task\n";
        cout << "2. Delete Task\n";
        cout << "3. Display Tasks\n";
        cout << "4. Mark Task as Completed\n";
        cout << "5. Edit Task\n";
        cout << "6. Exit\n";
        cout << "---------------------------\n";
    }

    void addTask() {
        string name, description, dueDate;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush leftover newline

        cout << "Enter task name: ";
        getline(cin, name);
        cout << "Enter task description: ";
        getline(cin, description);
        cout << "Enter task due date (YYYY-MM-DD): ";
        getline(cin, dueDate);

        tasks.emplace_back(name, description, dueDate);
        cout << "Task added.\n";
    }

    void deleteTask() {
        if (tasks.empty()) {
            cout << "No tasks to delete.\n";
            return;
        }
        displayTasks();
        int n;
        cout << "Enter task number to delete: ";
        cin >> n;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input!\n";
            return;
        }

        if (n < 1 || n > (int)tasks.size()) {
            cout << "Invalid task number!\n";
            return;
        }
        tasks.erase(tasks.begin() + (n - 1));
        cout << "Task deleted.\n";
    }

    void displayTasks() {
        if (tasks.empty()) {
            cout << "No tasks in the list.\n";
            return;
        }
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << "\nTask #" << (i + 1) << ":\n";
            tasks[i].display();
        }
    }

    void markCompleted() {
        if (tasks.empty()) {
            cout << "No tasks to mark as completed.\n";
            return;
        }
        displayTasks();
        int n;
        cout << "Enter task number to mark as completed: ";
        cin >> n;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input!\n";
            return;
        }

        if (n < 1 || n > (int)tasks.size()) {
            cout << "Invalid task number!\n";
            return;
        }
        tasks[n - 1].markCompleted();
        cout << "Marked as completed.\n";
    }

    void editTask() {
        if (tasks.empty()) {
            cout << "No tasks to edit.\n";
            return;
        }
        displayTasks();
        int n;
        cout << "Enter task number to edit: ";
        cin >> n;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input!\n";
            return;
        }

        if (n < 1 || n > (int)tasks.size()) {
            cout << "Invalid task number!\n";
            return;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush newline

        string name, description, dueDate;
        cout << "Enter new task name (leave blank to keep current): ";
        getline(cin, name);
        cout << "Enter new description (leave blank to keep current): ";
        getline(cin, description);
        cout << "Enter new due date (leave blank to keep current): ";
        getline(cin, dueDate);

        if (!name.empty()) tasks[n - 1].setName(name);
        if (!description.empty()) tasks[n - 1].setDescription(description);
        if (!dueDate.empty()) tasks[n - 1].setDueDate(dueDate);

        cout << "Task updated.\n";
    }

    void run() {
        int choice;
        do {
            displayMenu();
            cout << "Enter your choice: ";
            cin >> choice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a number.\n";
                continue;
            }

            switch (choice) {
                case 1: addTask(); break;
                case 2: deleteTask(); break;
                case 3: displayTasks(); break;
                case 4: markCompleted(); break;
                case 5: editTask(); break;
                case 6: cout << "Exiting.\n"; break;
                default: cout << "Invalid choice.\n";
            }
        } while (choice != 6);
    }
};

int main() {
    ToDoList todo;
    todo.run();
    return 0;
}
