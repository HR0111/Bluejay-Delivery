#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

// Employee structure to store relevant information
struct Employee
{
    std::string name;
    std::string position;
    int daysWorked;
    int hoursBetweenShifts;
    int hoursInSingleShift;
};

// Function to parse a line of data and populate the Employee structure
Employee parseLine(const std::string &line)
{
    Employee emp;
    std::istringstream iss(line);
    iss >> emp.name >> emp.position >> emp.daysWorked >> emp.hoursBetweenShifts >> emp.hoursInSingleShift;
    return emp;
}

int main()
{
    // File path (Assumption: The file is in the same directory as the executable)
    std::string filePath = "Assignment_Timecard.xlsx";

    // Open the file using the specified path
    std::ifstream inputFile(filePath);

    // Check if the file is successfully opened
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening the file: " << filePath << std::endl;
        perror("File open error");
        return 1;
    }

    std::vector<Employee> employees; // Vector to store employee data

    // Read data from the file and populate the employees vector
    std::string line;
    while (std::getline(inputFile, line))
    {
        employees.push_back(parseLine(line));
    }

    // Criteria 1: Employees who have worked for 7 consecutive days
    std::cout << "Employees who have worked for 7 consecutive days:" << std::endl;
    for (const auto &emp : employees)
    {
        if (emp.daysWorked == 7)
        {
            std::cout << emp.name << " (Position: " << emp.position << ")" << std::endl;
        }
    }
    std::cout << std::endl;

    // Criteria 2: Employees with less than 10 hours between shifts but greater than 1 hour
    std::cout << "Employees with less than 10 hours between shifts but greater than 1 hour:" << std::endl;
    for (const auto &emp : employees)
    {
        if (emp.hoursBetweenShifts > 1 && emp.hoursBetweenShifts < 10)
        {
            std::cout << emp.name << " (Position: " << emp.position << ")" << std::endl;
        }
    }
    std::cout << std::endl;

    // Criteria 3: Employees who have worked for more than 14 hours in a single shift
    std::cout << "Employees who have worked for more than 14 hours in a single shift:" << std::endl;
    for (const auto &emp : employees)
    {
        if (emp.hoursInSingleShift > 14)
        {
            std::cout << emp.name << " (Position: " << emp.position << ")" << std::endl;
        }
    }

    // Close the file
    inputFile.close();

 return 0;
}
