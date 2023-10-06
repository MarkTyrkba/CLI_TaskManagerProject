#include <iostream>//      for I/O operations
#include <string>//        std::string
#include <vector>//        dynamic array
#include <unordered_map>// hashmap
#include <fstream>//       std::ifstream
#include <sstream>//       std::istringstream

//code by Mark Tyrkba
//https://github.com/MarkTyrkba

class Task
{
public:
    Task() : t_title(""), t_description("") {}

    Task(std::string title, std::string description) : t_title(title), t_description(description) {}

    const void update(const std::string& title, const std::string& description)
    {
        if (!title.empty())
            t_title = title;

        if (!description.empty())
            t_description = description;

        return;
    }

private:
    std::string t_title, t_description;

    friend class Tasks;
};

class Tasks
{
public:
    const void addTask()
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
        return;
    }


    const void viewTasks()
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

        return;
    }

    const void updateTask()
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
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
        return;
    }

    const bool checkIfDeleteAllOf()
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

    const void deleteTask()
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
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        } while (!indexUpdated);

        m_tasks.erase(index);

        std::cout << "Deleted succesfully\n";
        return;
    }

    const void saveData() const
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
        return;
    }

    const void loadData()
    {
        std::ifstream inFile("output.txt");
        if (!inFile)
        {
            std::cerr << "Failed to open the file for reading." << std::endl;
            return;
        }

        if (!m_tasks.empty())
        {
            bool concr = false, changed = false;
            std::cout << "Clear all past data in your talk list?\n0 -> No\n1 -> Yes\n" << std::endl;

            do
            {
                std::cin >> concr;
                if (concr != 0 && concr != 1)
                    std::cout << "Input can be only 1 or 2\n";

                else
                    changed = true;
            } while (!changed);

            if (concr)
            {
                m_tasks.clear();
                std::system("cls");
                std::cout << "Data cleared successfully\n";
            }
        }

        std::string line;
        while (std::getline(inFile, line))
        {
            int index;
            std::string title, description;

            std::istringstream iss(line);
            if (iss >> index >> title >> description)
            {
                m_tasks[index].t_title = title;
                m_tasks[index].t_description = description;
            }
        }

        std::system("cls");
        std::cout << "Data has been loaded from the file successfully.\n";
        return;
    }

private:
    std::size_t m_index = 1;
    std::unordered_map<std::size_t, Task> m_tasks;
    bool doNotAskMeAnymore = false;
};


const void printMenu()
{
    std::cout << "Task Manager Menu:\n"
        << "1. Add Task\n"
        << "2. View Tasks\n"
        << "3. Update Task\n"
        << "4. Delete Task\n"
        << "5. Save Data\n"
        << "6. Load Data\n"
        << "7. Exit\n"
        << "Enter your choice (1-7): ";
    return;
}

int main()
{
    std::cout << "Choose number of action (1 - 7)\n";
    printMenu();
    Tasks task;
    for (;;)
    {
        short action;
        std::cin >> action;
        std::cin.ignore();

        switch (action)
        {
        case 1:
            task.addTask();
            break;
        case 2:
            task.viewTasks();
            break;
        case 3:
            task.updateTask();
            break;
        case 4:
            task.deleteTask();
            break;
        case 5:
            task.saveData();
            break;
        case 6:
            task.loadData();
            break;
        case 7:
            std::cout << "Exit succeeded" << std::endl;
            return 0;
        default:
            std::cout << "Invalid option. Please select a valid action." << std::endl;
            break;
        }

        printMenu();
    }

    return 0;
}
