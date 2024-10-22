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

void viewData(Geography* data, int count)
{
    for (int i = 0; i < count; ++i)
    {
        cout << endl;
        cout << "Id: " << data[i].id << "\n"
             << "Название: " << data[i].name << "\n"
             << "Страна: " << data[i].country << "\n"
             << "Тип: " << data[i].type << "\n"
             << "Высота: " << data[i].height << " м\n"
             << "Площадь: " << data[i].area << " км²\n"
             << "Население: " << data[i].population << endl;
        cout << endl;
    }
}

void editData(Geography* data, int count, int id)
{
    for (int i = 0; i < count; ++i)
    {
        if (data[i].id == id)
        {
            cout << endl;
            cout << "Введите новое название: ";
            cin >> data[i].name;
            cout << "Введите новую страну: ";
            cin >> data[i].country;
            cout << "Введите новый тип объекта: ";
            cin >> data[i].type;
            cout << "Введите новую высоту: ";
            cin >> data[i].height;
            cout << "Введите новую площадь: ";
            cin >> data[i].area;
            cout << "Введите новое население: ";
            cin >> data[i].population;
            cout << endl;
            cout << "Данные обновлены.\n";
            return;
        }
    }
    cout << "Объект с таким ID не найден.\n";
}

double calculateTotalArea(Geography* data, int count)
{
    double totalArea = 0;
    for (int i = 0; i < count; ++i)
    {
        totalArea += data[i].area;
    }
    return totalArea;
}

void saveData(Geography* data, int count, const string& filename)
{
    ofstream file(filename);
    
    for (int i = 0; i < count; ++i)
    {
        file << data[i].id << " "
             << data[i].name << " "
             << data[i].country << " "
             << data[i].type << " "
             << data[i].height << " "
             << data[i].area << " "
             << data[i].population << endl;
    }

    file.close();
    cout << endl;
    cout << "Данные успешно сохранены в файл: " << filename << endl;
}
