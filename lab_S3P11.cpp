#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

struct Geography
{
    int id;
    string name;
    string country;
    string type;
    int height;
    double area;
    int population;
};

Geography* loadData(const string& filename, int& count)
{
    ifstream file(filename);
    
    count = 0;
    string line;

    while (getline(file, line))
    {
        ++count;
    }

    file.close();
    file.open(filename);
    
    Geography* data = new Geography[count];

    for (int i = 0; i < count; ++i)
    {
        file >> data[i].id
             >> data[i].name
             >> data[i].country
             >> data[i].type
             >> data[i].height
             >> data[i].area
             >> data[i].population;
    }

    file.close();
    return data;
}
