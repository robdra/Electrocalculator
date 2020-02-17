#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <iomanip>

#include "calc.h"

long double eChange(long double result, std::string &color);
int Amount();
void SerialRes();
void ParalellRes();
void colorCode(int cnt, std::string &color, std::string val);
double vals[24] = {1.0, 1.1, 1.2, 1.3, 1.5, 1.6, 1.8, 2.0, 2.2, 2.4, 2.7, 3.0, 3.3, 3.6, 3.9, 4.3, 4.7, 5.1, 5.6, 6.2, 6.8, 7.5, 8.2, 9.1};



int main(int argc, char const *argv[])
{
    std::string choice= "";
    std::cout << "Are your resistors serial or parallel?" << std::endl;
    std::cin >> choice;

    if(choice == "Serial" || choice == "serial")
    {
        SerialRes();
    }
    else if(choice == "Parallel" || choice == "parallel")
    {
        ParalellRes();
    }
    else
    {
        std::cout << "Wrong input" << std::endl;
    }
    return 0;
}

void SerialRes()
{
    //int howMany = Amount();

    int howMany;
    std::vector<Resistor> RV; // Vector of Resistor class RV
    std::string Res; // RESISTANCE FROM USERS
    double tolerance;
    std::string color;

    
    std::cout << "How many resistors do you want to use? " << std::endl;
    std::cin >> howMany;

    // GET DATA
    for (int i = 1; i <= howMany; i++)
    {
        
        Resistor R;
        std::cout << "Enter resistance of resistor " << i << std::endl;
        std::cin >> Res; // Resistance
        std::cout << "Enter tolerance of resistor " << i << ". Only use full numbers" << std::endl;
        std::cin >> tolerance;
        tolerance = tolerance / pow(10, 2);

        R.resistance = Res;
        R.ID = i;
        R.tolerance = tolerance;
        
        RV.push_back(R);
    }
    
    int vectorCounter = 0;
    std::string value;
    double tol;
    long double rMin = 0;
    long double rMax = 0;
    long double minVal = 0;
    long double maxVal = 0;
    long double result = 0;
    long double intVal = 0;
    
    //PRINT DATA
    for (int i = 0; i < howMany; i++)
    {   
        value = RV[vectorCounter].resistance;
        tol = RV[vectorCounter].tolerance;
        char c = value.back();
        if(c == 'k' || c == 'K')
        {
            value.erase(value.size() -1);
            intVal = std::stod(value) * pow(10, 3);
        }
        else if(c == 'm' || c == 'M')
        {
            value.erase(value.size() -1);
            intVal = std::stod(value) * pow(10, 6);
        }
        else if(c == 'g' || c == 'G')
        {
            value.erase(value.size() -1);
            intVal = std::stod(value) * pow(10, 9);
        }
        else
        {
            intVal = std::stod(value);
        }
        rMin = intVal * (1 - tol);
        rMax = intVal * (1 + tol);
        minVal += rMin;
        maxVal += rMax;
        result += intVal;
        vectorCounter++;
        //std::cout << intVal << std::endl;
    }
    long double e24Val = eChange(result, color);

    if(result > 999999999)
    {
        result = result / pow(10, 9);
        e24Val = e24Val / pow(10, 9);
        minVal = minVal / pow(10, 9);
        maxVal = maxVal / pow(10, 9);
        std::cout << "Total resistance of your resistors: " << std::setprecision(9) << result << "G Ohm" << std::endl;
        std::cout << "Best value in E24 series: " << e24Val << "G Ohm" << std::endl;
        std::cout << "Interval is between [" << std::setprecision(9) << minVal << "G, " << std::setprecision(9) << maxVal << "G]" << std::endl;
    }
    else if(result > 999999)
    {
        result = result / pow(10, 6);
        e24Val = e24Val / pow(10, 6);
        minVal = minVal / pow(10, 6);
        maxVal = maxVal / pow(10, 6);
        std::cout << "Total resistance of your resistors: " << std::setprecision(6) << result << "M Ohm" << std::endl;
        std::cout << "Best value in E24 series: " << e24Val << "M Ohm" << std::endl;
        std::cout << "Interval is between [" << std::setprecision(6) << minVal << "M, " << std::setprecision(6) << maxVal << "M]" << std::endl;
    }
    else if(result > 999)
    {
        result = result / pow(10, 3);
        e24Val = e24Val / pow(10, 3);
        minVal = minVal / pow(10, 3);
        maxVal = maxVal / pow(10, 3);
        std::cout << "Total resistance of your resistors: " << std::setprecision(3) << result << "K Ohm" << std::endl;
        std::cout << "Best value in E24 series: " << e24Val << "K Ohm" << std::endl;
        std::cout << "Interval is between [" << std::setprecision(3) << minVal << "K, " << std::setprecision(3) << maxVal << "K]" << std::endl;
    }
    else
    {
        std::cout << "Total resistance of your resistors: " << result << " Ohm" << std::endl;
        std::cout << "Best value in E24 series: " << e24Val << " Ohm" << std::endl;
        std::cout << "Interval is between [" << minVal << ", " << maxVal << "]" << std::endl;
        
    }
    std::cout << "Colorcode is" << color << std::endl;

}

void ParalellRes()
{
    int howMany;
    std::vector<Resistor> RV; // Vector of Resistor class RV
    std::string Res; // RESISTANCE FROM USERS
    double tolerance = 0;
    std::string color;
    
    std::cout << "How many resistors do you want to use? " << std::endl;
    std::cin >> howMany;

    // GET DATA
    for (int i = 1; i <= howMany; i++)
    {
        
        Resistor R;
        std::cout << "Enter resistance of resistor " << i << std::endl;
        std::cin >> Res; // Resistance
        std::cout << "Enter tolerance of resistor " << i << ". Only use integers" << std::endl;
        std::cin >> tolerance;
        tolerance = tolerance / pow(10, 2);

        R.resistance = Res;
        R.ID = i;
        R.tolerance = tolerance;
        
        RV.push_back(R);
    }

    double tol;
    long double rMin = 0;
    long double rMax = 0;
    long double minVal = 0;
    long double maxVal = 0;
    long double halfMin = 0;
    long double halfMax = 0;
    int vectorCounter = 0;
    std::string value;
    long double result = 0;
    long double preResult = 0;
    long double intVal = 0;
    long double changed = 0;

    //PRINT DATA
    for (int i = 0; i < howMany; i++)
    {   
        value = RV[vectorCounter].resistance;
        tol = RV[vectorCounter].tolerance;
        char c = value.back();
        if(c == 'k' || c == 'K')
        {
            value.erase(value.size() -1);
            intVal = std::stod(value) * pow(10, 3);
            
        }
        else if(c == 'm' || c == 'M')
        {
            value.erase(value.size() -1);
            intVal = std::stod(value) * pow(10, 6);
        }
        else if(c == 'g' || c == 'G')
        {
            value.erase(value.size() -1);
            intVal = std::stod(value) * pow(10, 9);
        }
        else
        {
            intVal = std::stod(value);
        }
        rMin = intVal * (1 - tol);
        rMax = intVal * (1 + tol);
        halfMin = 1/rMin;
        halfMax = 1/rMax;
        changed = 1/intVal;
        //std::cout << "changed: " << changed << std::endl;
        preResult += changed;
        minVal += halfMin;
        maxVal += halfMax;
        
        vectorCounter++;
        //std::cout << "preResult: " << preResult << std::endl;
    }
    result = 1/preResult;
    minVal = 1/minVal;
    maxVal = 1/maxVal;
    long double e24Val = eChange(result, color);
    if(result > 999999999)
    {
        result = result / pow(10, 9);
        e24Val = e24Val / pow(10, 9);
        minVal = minVal / pow(10, 9);
        maxVal = maxVal / pow(10, 9);
        std::cout << "Total resistance of your resistors: " << std::setprecision(9) << result << "G Ohm" << std::endl;
        std::cout << "Best value in E24 series: " << e24Val << "G Ohm" << std::endl;
        std::cout << "Interval is between [" << std::setprecision(9) << minVal << "G, " << std::setprecision(9) << maxVal << "G]" << std::endl;
    }
    else if(result > 999999)
    {
        result = result / pow(10, 6);
        e24Val = e24Val / pow (10, 6);
        minVal = minVal / pow(10, 6);
        maxVal = maxVal / pow(10, 6);
        std::cout << "Total resistance of your resistors: " << std::setprecision(6) << result << "M Ohm" << std::endl;
        std::cout << "Best value in E24 series: " << e24Val << "M Ohm" << std::endl;
        std::cout << "Interval is between [" << std::setprecision(6) << minVal << "M, " << std::setprecision(6) << maxVal << "M]" << std::endl;
    }
    else if(result > 999)
    {
        result = result / pow(10, 3);
        e24Val = e24Val / pow (10, 3);
        minVal = minVal / pow(10, 3);
        maxVal = maxVal / pow(10, 3);
        std::cout << "Total resistance of your resistors: " << std::setprecision(3) << result << "K Ohm" << std::endl;
        std::cout << "Best value in E24 series: " << e24Val << "K Ohm" << std::endl;
        std::cout << "Interval is between [" << std::setprecision(3) << minVal << "K, " << std::setprecision(3) << maxVal << "K]" << std::endl;
    }
    else
    {
        std::cout << "Total resistance of your resistors " << result << " Ohm" << std::endl;
        std::cout << "Best value in E24 series: " << e24Val << " Ohm" << std::endl;
        std::cout << "Interval is between [" << minVal << ", " << maxVal << "]" << std::endl;
    }
    std::cout << "Colorcode is" << color << std::endl;
}

int Amount()
{
    int howMany;
    std::vector<Resistor> RV; // Vector of Resistor class RV
    std::string Res; // RESISTANCE FROM USERS
    
    std::cout << "How many resistors do you want to use? " << std::endl;
    std::cin >> howMany;

    // GET DATA
    for (int i = 1; i <= howMany; i++)
    {
        
        Resistor R;
        std::cout << "Enter resistance of resistor " << i << std::endl;
        std::cin >> Res; // Resistance
        R.resistance = Res;
        R.ID = i;
        
        RV.push_back(R);
    }

    return howMany;
}

long double eChange(long double result, std::string &color)
{
    unsigned long long int before = result;
    std::string change = std::to_string(before);
    int cnt = 0;
    for(int i=0; change[i]; i++)
 	    cnt++;
    std::string split = change.substr(0, 3);
    std::string comma = split.insert(1, ".");
    double halfVal = std::stod(comma);
    double eVal = 0.0;
    int counter = 0;
    while (eVal < halfVal)
    {
        eVal = vals[counter];
        counter++;
    }
    
    long double e24Val = eVal * pow(10, cnt-1);
    std::string val = std::to_string(e24Val);
    colorCode(cnt, color, val);
    return e24Val;
}

void colorCode(int cnt, std::string &color, std::string val)
{
    int first = std::stoi(val.substr(0, 1));
    int second = std::stoi(val.substr(1, 1));
    int multiplier = cnt - 2;
    std::string code;

    if(first == 1)
        code.append(" brown");
    else if(first == 2)
        code.append(" red");
    else if(first == 3)
        code.append(" orange");
    else if(first == 4)
        code.append(" yellow");
    else if(first == 5)
        code.append(" green");
    else if(first == 6)
        code.append(" blue");
    else if(first == 7)
        code.append(" purple");
    else if(first == 8)
        code.append(" gray");
    else if(first == 9)
        code.append(" white"); 

    if(second == 1)
        code.append(" brown");
    else if(second == 2)
        code.append(" red");
    else if(second == 3)
        code.append(" orange");
    else if(second == 4)
        code.append(" yellow");
    else if(second == 5)
        code.append(" green");
    else if(second == 6)
        code.append(" blue");
    else if(second == 7)
        code.append(" purple");
    else if(second == 8)
        code.append(" gray");
    else if(second == 9)
        code.append(" white");

    if(multiplier == 0)
        code.append(" black");
    else if(multiplier == 1)
        code.append(" brown");
    else if(multiplier == 2)
        code.append(" red");
    else if(multiplier == 3)
        code.append(" orange");
    else if(multiplier == 4)
        code.append(" yellow");
    else if(multiplier == 5)
        code.append(" green");
    else if(multiplier == 6)
        code.append(" blue");
    
    color = code;
      
}