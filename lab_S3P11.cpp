#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
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
    cout << left << setw(5) << "Id" << "|"
         << setw(25) << "Title" << "|"
         << setw(15) << "Country" << "|"
         << setw(15) << "Type" << "|"
         << setw(10) << "Height" << "|"
         << setw(15) << "Area" << "|"
         << setw(20) << "Population"
         << endl;

    for (int i = 0; i < count; ++i)
    {
        cout << setw(101) << "-----------------------------------------------------------------------------------------------------" << endl;
        cout << left << setw(5) << data[i].id << "|"
             << setw(25) << data[i].name << "|"
             << setw(15) << data[i].country << "|"
             << setw(15) << data[i].type << "|"
             << setw(10) << data[i].height << "|"
             << setw(15) << data[i].area << "|"
             << setw(20) << data[i].population
             << endl;
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
            string input_height;
            cout << "Введите новую высоту: ";
            cin >> input_height;
            try
            {
                data[i].height = stoi(input_height);
            }
            catch (invalid_argument&)
            {
                cout << endl;
                cout << "Ошибка: высота должна быть числом. Изменения не внесены.\n";
                return;
            }
            string input_area;
            cout << "Введите новую площадь: ";
            cin >> input_area;
            try
            {
                data[i].area = stod(input_area);
            }
            catch (invalid_argument&)
            {
                cout << endl;
                cout << "Ошибка: площадь должна быть числом. Изменения не внесены.\n";
                return;
            }
            string input_population;
            cout << "Введите новое население: ";
            cin >> input_population;
            try
            {
                data[i].population = stoi(input_population);
            }
            catch (invalid_argument&)
            {
                cout << endl;
                cout << "Ошибка: население должно быть числом. Изменения не внесены.\n";
                return;
            }
            cout << endl;
            cout << "Данные обновлены.\n";
            return;
        }
    }
    cout << endl;
    cout << "Объект с таким Id не найден. Возврат в главное меню.\n";
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

int main()
{
    Geography* data = nullptr;
    int count = 0;
    string filename = "geography_data.txt";

    data = loadData(filename, count);

    string choice;

    while (true)
    {
        cout << "\nМеню:\n";
        cout << "1. Просмотреть данные\n";
        cout << "2. Редактировать данные\n";
        cout << "3. Вычислить общую площадь\n";
        cout << "4. Сохранить данные\n";
        cout << "0. Выход\n";
        cout << endl;
        cout << "Ваш выбор: ";
        cin >> choice;

        if (choice == "1")
        {
            cout << endl;
            viewData(data, count);
            continue;
        }

        if (choice == "2")
        {
            string input_id;
            cout << endl;
            cout << "Введите Id для редактирования: ";
            cin >> input_id;
            try
            {
                int id = stoi(input_id);
                editData(data, count, id);
            }
            catch (invalid_argument&)
            {
                cout << endl;
                cout << "Ошибка: Id должен быть числом. Возврат в главное меню.\n";
            }
            continue;           
        }

        if (choice == "3")
        {
            double totalArea = calculateTotalArea(data, count);
            cout << endl;
            cout << "Общая площадь всех объектов: " << totalArea << " км²\n";
            continue;
        }

        if (choice == "4")
        {
            cout << endl;
            cout << "Введите имя файла для сохранения данных: ";
            cin >> filename;
            saveData(data, count, filename);
            continue;
        }

        if (choice == "0")
        {
            cout << endl;
            cout << "Выход из программы.\n";
            exit (0);
        }

        else 
        {
            cout << endl;
            cout << "Неверный выбор. Возврат в главное меню.!\n";
            continue;
        }
    }

    return 0;
    delete[] data;
}
