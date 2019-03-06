#include "person.cpp"
#include <fstream>
#include <vector>
#include <iostream>
#include <iomanip>

void readData(vector<Person> &employees);
void getCompanies(vector<Person> &employees, vector<string> &companyNames);
void printHighestPaid(vector<Person> &employees);
void seperateAndSave(vector<Person> &employees, vector<string> &companyNames);

int main()
{
  vector<Person> employees;
  vector<string> companyNames;

  readData(employees);
  getCompanies(employees, companyNames);
  printHighestPaid(employees);
  seperateAndSave(employees, companyNames);

  return 0;
}

void readData(vector<Person> &employees)
{
  ifstream inFile;
  Person temp;
  string fName, lName, compName, restOfLine;
  float hoursWorked, payRate;
  int empID;
  inFile.open("input.txt");

  while(!inFile.eof())
  {
    inFile >> fName >> lName;
    inFile >> empID;
    inFile >> compName;
    inFile >> hoursWorked >> payRate;
    getline(inFile, restOfLine);
    temp.setFirstName(fName);
    temp.setLastName(lName);
    temp.setEmployeeId(empID);
    temp.setCompanyName(compName);
    temp.setHoursWorked(hoursWorked);
    temp.setPayRate(payRate);
    employees.push_back(temp);
  }
  employees.pop_back();

  inFile.close();
}

void getCompanies(vector<Person> &employees, vector<string> &companyNames)
{
  string name;

  for (int i = 0; i < employees.size(); i++)
  {
    int k = 0;
    name = employees.at(i).getCompanyName();

    if (companyNames.empty())
      companyNames.push_back(name);

    for (int j = 0; j < companyNames.size(); j++)
    {
      if (name == companyNames.at(j))
        k++;
    }

    if (k == 0)
      companyNames.push_back(name);
  }
}

void printHighestPaid(vector<Person> &employees)
{
  int num;
  float temp;

  for (int i = 0; i < employees.size(); i++)
  {
    if (temp < employees.at(i).totalPay())
    {
      temp = employees.at(i).totalPay();
      num = i;
    }
  }

  cout << "Highest Paid:\t" << employees.at(num).fullName() << endl
  << "Employee ID:\t" << employees.at(num).getEmployeeId() << endl
  << "Employer:\t" << employees.at(num).getCompanyName() << endl
  << "Total Pay:\t$" << fixed << setprecision(2)
  << employees.at(num).totalPay() << endl;
}

void seperateAndSave(vector<Person> &employees, vector<string> &companyNames)
{
  ofstream outFile;
  string cName;
  vector<Person> temp;

  for(int i = 0; i < companyNames.size(); i++)
  {
    float total = 0;
    cName = companyNames.at(i) + ".txt";
    outFile.open(cName);

    for (int j = 0; j < employees.size(); j++)
    {
      if (companyNames.at(i) == employees.at(j).getCompanyName())
      {
        outFile << setw(10) << left << employees.at(j).getFirstName()
        << setw(10) << left  << employees.at(j).getLastName()
        << setw(4) << left << employees.at(j).getEmployeeId()
        << setw(13) << left << employees.at(j).getCompanyName()
        << "$" << setw(9) << left << fixed << setprecision(2)
        << employees.at(j).totalPay() << endl;
        total = total + employees.at(j).totalPay();
      }
    }
    outFile << "Total:\t$" << fixed << setprecision(2) << total;
    outFile.close();
  }
}
