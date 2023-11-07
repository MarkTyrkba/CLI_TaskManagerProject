#include <iostream>//      for I/O operations
#include <string>//        std::string
#include <vector>//        dynamic array
#include <unordered_map>// hashmap
#include <fstream>//       std::ifstream
#include <sstream>//       std::istringstream
#include <functional> //   std::function

//code by Mark Tyrkba
//https://github.com/MarkTyrkba

class Task
{
public:
    Task() : t_title(""), t_description("") {}

    Task(std::string title, std::string description) : t_title(title), t_description(description) {}

    void update(const std::string& title, const std::string& description)
    {
        if (!title.empty())
            t_title = title;

        if (!description.empty())
            t_description = description;
   }

private:
    std::string t_title, t_description;

    friend class Tasks;
};

class Tasks
{
public:
    void addTask()
    {
        std::string title, description;
        bool titleUpdated, descriptionUpdated;

        std::system("cls");
        std::cout << "Now enter the title of task\nenter 10 to return\n";
        do
        {
            std::getline(std::cin, title);

            if (title == "10")
                return;

            titleUpdated = !title.empty() && title.find_first_not_of(' ') != std::string::npos;

            if (!titleUpdated)
                std::cout << "Title cannot be empty or contain only spaces. Please enter a valid title.\n";
        } while (!titleUpdated);


        std::cout << "Now enter the description of task\n";
        do
        {
            std::getline(std::cin, description);

            descriptionUpdated = !description.empty() && description.find_first_not_of(' ') != std::string::npos;

            if (!descriptionUpdated)
                std::cout << "Description cannot be empty or contain only spaces. Please enter a valid description.\n";
        } while (!descriptionUpdated);

        if (title == "cs poigrat'" || description == "cs poigrat'")
        {
            system("start \"\" \"Y:\\SteamLibrary\\steamapps\\common\\Counter-Strike Global Offensive\\game\\bin\\win64\\cs2.exe\"");
            std::cout << "ok! go v cs\n";
            return;
        }

        m_tasks[m_index++] = Task(title, description);

        std::system("cls");
        std::cout << "Task has been created successfully\n\n";
   }


    void viewTasks()
    {
        std::system("cls");
        if (m_tasks.empty())
        {
            std::cout << "Currently you does not created any tasks , create task then you can use this function\n" << std::endl;
            return;
        }

        std::cout << "All tasks:\n";
        for (const auto& [index, task] : m_tasks)
        {
            std::cout << "Task " << index << ":\n";
            std::cout << "Title: " << task.t_title << "\nDescription: " << task.t_description << std::endl << std::endl;
        }
    }

    void updateTask()
    {
        std::size_t index;
        std::string title, description;
        bool indexUpdated, titleUpdated, descriptionUpdated;

        std::system("cls");
        std::cout << "Enter:\n (1) Index of task\n (2) New title\n (3) New description\n";
        do
        {
            std::cout << "Now enter the index of the chosen task: \nenter 10 to return\n";
            std::cin >> index;
            indexUpdated = !std::cin.fail();

            if (index == 10)
                return;

            if (!indexUpdated || index >= m_index || index <= 0)
            {
                std::cout << "Index must be valid. Please enter a valid index.\n";
                std::cin.clear();
            }
        } while (!indexUpdated);

        std::system("cls");
        do
        {
            std::cin.ignore(); // Clear the newline character left in the input buffer
            std::cout << "Now enter the new title: ";
            std::getline(std::cin, title);
            titleUpdated = !title.empty() && title.find_first_not_of(' ') != std::string::npos;

            if (!titleUpdated)
                std::cout << "Title cannot be empty or contain only spaces. Please enter a valid title.\n";
        } while (!titleUpdated);

        do
        {
            std::cout << "Now enter the new description: ";
            std::getline(std::cin, description);
            descriptionUpdated = !description.empty() && description.find_first_not_of(' ') != std::string::npos;

            if (!descriptionUpdated)
                std::cout << "Description cannot be empty or contain only spaces. Please enter a valid description.\n";
        } while (!descriptionUpdated);

        std::cout << "Updated Task index: " << index << std::endl;
        std::cout << "Updated Title: " << title << std::endl;
        std::cout << "Updated Description: " << description << std::endl;

        m_tasks[index].update(title, description);
        std::system("cls");
    }

    bool checkIfDeleteAllOf()
    {
        bool updated = false;
        int checker;

        do
        {
            if (doNotAskMeAnymore)
            {
                std::system("cls");
                std::cout << "Ok\n";
                return false;
            }

            std::cout << "If you suddendly want to delete all of your tasks , just enter 1 , if you does not hit 0\nDo not ask my anymore! -> enter 10" << std::endl;
            std::cin >> checker;

            if (checker == 10)
                doNotAskMeAnymore = true;

            if (!doNotAskMeAnymore && checker != 0 && checker != 1)
                std::cout << "Please enter only 0 or 1\n";

            else if (checker == 1 || checker == 0)
                updated = true;
        } while (!updated);

        if (checker == 0)
            return false;

        else
            return true;

        std::system("cls");

        return false;
    }

    void deleteTask()
    {
        std::system("cls");
        if (m_tasks.empty())
        {
            std::cout << "Currently you does not created any tasks , create task then you can use this function\n" << std::endl;
            return;
        }

        if (!doNotAskMeAnymore)
        {
            bool ifDA = checkIfDeleteAllOf();
            if (ifDA)
            {
                m_tasks.clear();
                m_index = 1;
                std::cout << "\nDeleted succesfully!\n" << std::endl;
                return;
            }
            std::system("cls");
        }

        std::size_t index;
        bool indexUpdated;
        do
        {
            std::cout << "Now enter the index of task to delete.\nenter 10 to return\n";
            std::cin >> index;
            indexUpdated = !std::cin.fail();

            if (index == 10)
                return;

            if (!indexUpdated || index >= m_index)
            {
                std::cout << "Index must be valid. Please enter a valid index.\n";
                std::cin.clear();
            }
        } while (!indexUpdated);

        m_tasks.erase(index);

        std::cout << "Deleted succesfully\n";
    }

    void saveData() const
    {
        if (m_tasks.empty())
        {
            std::cout << "Currently you does not created any tasks , create task then you can use this function\n" << std::endl;
            return;
        }

        std::ofstream outFile("output.txt");

        if (!outFile)
        {
            std::cerr << "Can not open file to save data." << std::endl;
            return;
        }

        for (const auto& pair : m_tasks)
            outFile << pair.first << ' ' << pair.second.t_title << ' ' << pair.second.t_description << std::endl;

        outFile.close();

        std::system("cls");
        std::cout << "Data has been saved successfully in project directory\n";
    }

    void readData(std::ifstream& inFile, std::unordered_map<std::size_t, Task>& map)
    {
        std::string line;
        while (std::getline(inFile, line))
        {
            std::size_t index;
            std::string title, description;

            std::istringstream iss(line);
            if (iss >> index >> title >> description)
            {
                map[index].t_title = title;
                map[index].t_description = description;
            }
        }
    }

    void loadData()
    {
        std::ifstream inFile("output.txt");
        if (!inFile)
        {
            std::cerr << "Failed to open the file for reading." << std::endl;
            return;
        }

        readData(inFile, m_tasks);

        std::system("cls");
        std::cout << "Data has been loaded from the file successfully.\n";
    }

    static void printSavedData()
    {
        std::ifstream inFile("output.txt");

        std::system("cls");

        if (!inFile)
        {
            std::cerr << "Failed to open the file for reading." << std::endl;
            return;
        }

        std::cout << "Data from 'output.txt':\n";

        std::string line;
        while (std::getline(inFile, line))
        {
            int index;
            std::string title, description;

            std::istringstream iss(line);
            if (iss >> index >> title >> description)
                std::cout << "Index: " << index << "\nTitle: " << title << "\nDescription: " << description << "\n\n";
        }

        inFile.close();
    }


private:
    std::size_t m_index = 1;
    std::unordered_map<std::size_t, Task> m_tasks;
    bool doNotAskMeAnymore = false;
};


void printMenu()
{
    std::cout
        << "Task Manager Menu:\n"
        << "1. Add Task\n"
        << "2. View Tasks\n"
        << "3. Update Task\n"
        << "4. Delete Task\n"
        << "5. Save Data\n"
        << "6. Load Data\n"
        << "7. Print saved Data\n"
        << "8. Exit\n"
        << "Enter your choice (1-8): ";
}

int main()
{
    std::cout << "Choose number of action (1 - 7)\n";

    printMenu();

    Tasks task;

    std::unordered_map<int, std::function<void()> > actions = {
            {1, [&task]() { task.addTask(); }},
            {2, [&task]() { task.viewTasks(); }},
            {3, [&task]() { task.updateTask(); }},
            {4, [&task]() { task.deleteTask(); }},
            {5, [&task]() { task.saveData(); }},
            {6, [&task]() { task.loadData(); }},
            {7, [&task]() { task.printSavedData(); }},
            {8, []() { std::cout << "Exit succeeded" << std::endl; }},
    };

    for (;;)
    {
        short action;
        std::cin >> action;
        std::cin.ignore();

        if (actions.find(action) != actions.end())
            actions[action]();

        else
            std::cout << "Invalid option. Please select a valid action." << std::endl;

        printMenu();
    }

    return 0;
}
