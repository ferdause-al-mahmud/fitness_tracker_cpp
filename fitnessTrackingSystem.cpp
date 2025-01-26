#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <map>
#include <limits>
using namespace std;

class User
{
private:
    int userId;
    string userName;
    double totalCaloriesBurned;
    double totalCaloriesConsumed;

public:
    User(int id, string name) : userId(id), userName(name), totalCaloriesBurned(0), totalCaloriesConsumed(0) {}

    int getUserId() const { return userId; }
    string getUserName() const { return userName; }
    double getTotalCaloriesBurned() const { return totalCaloriesBurned; }
    double getTotalCaloriesConsumed() const { return totalCaloriesConsumed; }

    void logWorkout(const string &exerciseType, double duration, double caloriesBurned)
    {
        totalCaloriesBurned += caloriesBurned;
        cout << "Workout Logged: " << exerciseType << ", Duration: " << duration << " mins, Calories Burned: " << caloriesBurned << endl;
    }

    void logMeal(const string &meal, double calories)
    {
        totalCaloriesConsumed += calories;
        cout << "Meal Logged: " << meal << ", Calories: " << calories << endl;
    }

    void displayProgress() const
    {
        cout << fixed << setprecision(2);
        cout << "\nUser: " << userName << endl;
        cout << "Total Calories Burned: " << totalCaloriesBurned << endl;
        cout << "Total Calories Consumed: " << totalCaloriesConsumed << endl;

        if (totalCaloriesBurned > totalCaloriesConsumed)
        {
            cout << "Calories Deficit: " << totalCaloriesBurned - totalCaloriesConsumed << endl;
        }
        else if (totalCaloriesBurned < totalCaloriesConsumed)
        {
            cout << "Calories Surplus: " << totalCaloriesConsumed - totalCaloriesBurned << endl;
        }
        else
        {
            cout << "Calories Consumed = Calories Burned" << endl;
        }

        cout << endl;
    }

    void saveToFile(ofstream &outFile) const
    {
        outFile << userId << "," << userName << "," << totalCaloriesBurned << "," << totalCaloriesConsumed << endl;
    }

    void loadFromFile(const string &line)
    {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);

        userId = stoi(line.substr(0, pos1));
        userName = line.substr(pos1 + 1, pos2 - pos1 - 1);
        totalCaloriesBurned = stod(line.substr(pos2 + 1, pos3 - pos2 - 1));
        totalCaloriesConsumed = stod(line.substr(pos3 + 1));
    }
};

class FitnessTracker
{
private:
    vector<User> users;
    const string filename = "fitness_data.txt";

    void saveToFile()
    {
        ofstream outFile(filename);
        if (outFile.is_open())
        {
            for (const auto &user : users)
                user.saveToFile(outFile);
            outFile.close();
        }
        else
        {
            cout << "Error opening file for saving." << endl;
        }
    }

    void loadFromFile()
    {
        ifstream inFile(filename);
        if (inFile.is_open())
        {
            users.clear();
            string line;
            while (getline(inFile, line))
            {
                User user(0, "");
                user.loadFromFile(line);
                users.push_back(user);
            }
            inFile.close();
        }
        else
        {
            cout << "No existing data file found. Starting fresh." << endl;
        }
    }

    bool isUserIdUnique(int userId) const
    {
        for (const auto &user : users)
        {
            if (user.getUserId() == userId)
            {
                return false;
            }
        }
        return true;
    }

public:
    FitnessTracker()
    {
        loadFromFile();
    }

    ~FitnessTracker()
    {
        saveToFile();
    }

    void createUser()
    {
        int userId;
        string userName;

        while (true)
        {
            cout << "Enter User ID: ";
            cin >> userId;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid numeric User ID." << endl;
                continue;
            }
            if (!isUserIdUnique(userId))
            {
                cout << "User ID already exists. Please enter a unique User ID." << endl;
                continue;
            }
            break;
        }

        cin.ignore();
        cout << "Enter User Name: ";
        getline(cin, userName);

        users.emplace_back(userId, userName);
        cout << "User created successfully!\n";
    }

    void logWorkout()
    {
        int userId;
        string exerciseType;
        double duration, caloriesBurned;

        while (true)
        {
            cout << "Enter User ID: ";
            cin >> userId;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid numeric User ID." << endl;
                continue;
            }
            break;
        }

        cin.ignore();

        for (auto &user : users)
        {
            if (user.getUserId() == userId)
            {
                cout << "Enter Exercise Type: ";
                getline(cin, exerciseType);

                while (true)
                {
                    cout << "Enter Duration (in minutes): ";
                    cin >> duration;
                    if (cin.fail() || duration <= 0)
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter a positive numeric value." << endl;
                        continue;
                    }
                    break;
                }

                while (true)
                {
                    cout << "Enter Calories Burned: ";
                    cin >> caloriesBurned;
                    if (cin.fail() || caloriesBurned <= 0)
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter a positive numeric value." << endl;
                        continue;
                    }
                    break;
                }

                user.logWorkout(exerciseType, duration, caloriesBurned);
                return;
            }
        }
        cout << "User not found!\n";
    }

    void logMeal()
    {
        int userId;
        string meal;
        double calories;

        while (true)
        {
            cout << "Enter User ID: ";
            cin >> userId;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid numeric User ID." << endl;
                continue;
            }
            break;
        }

        cin.ignore();

        for (auto &user : users)
        {
            if (user.getUserId() == userId)
            {
                cout << "Enter Meal Name: ";
                getline(cin, meal);

                while (true)
                {
                    cout << "Enter Calories: ";
                    cin >> calories;
                    if (cin.fail() || calories <= 0)
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter a positive numeric value." << endl;
                        continue;
                    }
                    break;
                }

                user.logMeal(meal, calories);
                return;
            }
        }
        cout << "User not found!\n";
    }

    void displayUserProgress()
    {
        int userId;

        while (true)
        {
            cout << "Enter User ID: ";
            cin >> userId;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid numeric User ID." << endl;
                continue;
            }
            break;
        }

        for (const auto &user : users)
        {
            if (user.getUserId() == userId)
            {
                user.displayProgress();
                return;
            }
        }
        cout << "User not found!\n";
    }

    void listAllUsers()
    {
        if (users.empty())
        {
            cout << "No users found." << endl;
            return;
        }

        cout << "\nAll Users:\n";
        for (const auto &user : users)
        {
            cout << "User ID: " << user.getUserId() << ", Name: " << user.getUserName() << endl;
        }
    }
};

int main()
{
    FitnessTracker tracker;
    int choice;

    do
    {
        cout << "\nFitness Tracker System\n";
        cout << "1. Create User\n";
        cout << "2. Log Workout\n";
        cout << "3. Log Meal\n";
        cout << "4. Display User Progress\n";
        cout << "5. List All Users\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            tracker.createUser();
            break;
        case 2:
            tracker.logWorkout();
            break;
        case 3:
            tracker.logMeal();
            break;
        case 4:
            tracker.displayUserProgress();
            break;
        case 5:
            tracker.listAllUsers();
            break;
        case 6:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
