#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class shopping
{
private:
    int pcode;
    float price;
    float dis;
    string pname;

public:
    void menu();
    void administrator();
    void buyer();
    void add();
    void edit();
    void rem();
    void list();
    void receipt();
};

void shopping::menu()
{
    int choice;
    string email;
    string password;
    bool exitMenu = false;

    while (!exitMenu)
    {
        cout << "\n\t\t\t\t Supermarket Main Menu\n";
        cout << "\t\t\t_______________________________________\n";
        cout << "\t\t\t| 1) Administrator   |\n";
        cout << "\t\t\t| 2) Buyer           |\n";
        cout << "\t\t\t| 3) Exit            |\n";
        cout << "\t\t\t Please select: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "\t\t\t Please Login\n";
            cout << "\t\t\t Enter Email: ";
            cin >> email;
            cout << "\t\t\t Password: ";
            cin >> password;

            if (email == "Carlos@gmail.com" && password == "Carlos123")
            {
                administrator();
            }
            else
            {
                cout << "Invalid email/password\n";
            }
            break;

        case 2:
            buyer();
            break;

        case 3:
            exitMenu = true;
            break;

        default:
            cout << "Please select a valid option!\n";
        }
    }
}

void shopping::administrator()
{
    int choice;
    bool exitAdmin = false;

    while (!exitAdmin)
    {
        cout << "\n\n\t\t Administrator Menu\n";
        cout << "\t\t 1) Add Product\n";
        cout << "\t\t 2) Modify Product\n";
        cout << "\t\t 3) Delete Product\n";
        cout << "\t\t 4) Back to Main Menu\n";
        cout << "\n\t Please enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            add();
            break;

        case 2:
            edit();
            break;

        case 3:
            rem();
            break;

        case 4:
            exitAdmin = true;
            break;

        default:
            cout << "Invalid choice!\n";
        }
    }
}

void shopping::buyer()
{
    int choice;
    bool exitBuyer = false;

    while (!exitBuyer)
    {
        cout << "\t\t\t Buyer Menu\n";
        cout << "\t\t\t 1) Buy product\n";
        cout << "\t\t\t 2) Back to Main Menu\n";
        cout << "\t\t\t Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            receipt();
            break;

        case 2:
            exitBuyer = true;
            break;

        default:
            cout << "Invalid choice!\n";
        }
    }
}

void shopping::add()
{
    fstream data;
    int code;
    bool productExists = false;

    cout << "\n\n\t Add New Product\n";
    cout << "\t Product Code: ";
    cin >> pcode;
    cout << "\t Product Name: ";
    cin >> pname;
    cout << "\t Product Price: ";
    cin >> price;
    cout << "\t Product Discount: ";
    cin >> dis;

    // Verificar si el producto ya existe
    data.open("database.txt", ios::in);
    if (data)
    {
        while (data >> code)
        {
            if (code == pcode)
            {
                productExists = true;
                break;
            }
        }
        data.close();
    }

    if (productExists)
    {
        cout << "\n\n\tProduct already exists!\n";
    }
    else
    {
        data.open("database.txt", ios::app);
        data << pcode << " " << pname << " " << price << " " << dis << "\n";
        data.close();
        cout << "\n\n\tProduct added successfully!\n";
    }
}

void shopping::edit()
{
    fstream data, temp;
    int code;
    bool found = false;

    cout << "\n\n\t Modify Product\n";
    cout << "\t Enter Product Code: ";
    cin >> pcode;

    data.open("database.txt", ios::in);
    if (!data)
    {
        cout << "\n\nFile doesn't exist!\n";
        return;
    }

    temp.open("temp.txt", ios::out);
    while (data >> code >> pname >> price >> dis)
    {
        if (code == pcode)
        {
            cout << "\n\tNew Product Code: ";
            cin >> code;
            cout << "\tNew Product Name: ";
            cin >> pname;
            cout << "\tNew Product Price: ";
            cin >> price;
            cout << "\tNew Product Discount: ";
            cin >> dis;
            temp << code << " " << pname << " " << price << " " << dis << "\n";
            found = true;
        }
        else
        {
            temp << code << " " << pname << " " << price << " " << dis << "\n";
        }
    }
    data.close();
    temp.close();
    remove("database.txt");
    rename("temp.txt", "database.txt");

    if (found)
    {
        cout << "\n\n\tRecord edited successfully!\n";
    }
    else
    {
        cout << "\n\nRecord not found!\n";
    }
}

void shopping::rem()
{
    fstream data, temp;
    int code;
    bool found = false;

    cout << "\n\n\t Delete Product\n";
    cout << "\t Enter Product Code: ";
    cin >> pcode;

    data.open("database.txt", ios::in);
    if (!data)
    {
        cout << "\n\nFile doesn't exist!\n";
        return;
    }

    temp.open("temp.txt", ios::out);
    while (data >> code >> pname >> price >> dis)
    {
        if (code == pcode)
        {
            found = true;
            cout << "\n\n\tProduct deleted successfully!\n";
        }
        else
        {
            temp << code << " " << pname << " " << price << " " << dis << "\n";
        }
    }
    data.close();
    temp.close();
    remove("database.txt");
    rename("temp.txt", "database.txt");

    if (!found)
    {
        cout << "\n\nRecord not found!\n";
    }
}

void shopping::list()
{
    fstream data;
    data.open("database.txt", ios::in);
    if (!data)
    {
        cout << "\n\n No products available\n";
        return;
    }

    cout << "\n\n| Product Code | Product Name | Price | Discount |\n";
    cout << "-------------------------------------------------\n";
    while (data >> pcode >> pname >> price >> dis)
    {
        cout << pcode << "          " << pname << "        " << price << "      " << dis << "%\n";
    }
    data.close();
}

void shopping::receipt()
{
    fstream data;
    int codes[100], quantities[100];
    int c = 0;
    float total = 0.0;

    cout << "\n\n\tReceipt\n";
    data.open("database.txt", ios::in);
    if (!data)
    {
        cout << "\n\n Empty database\n";
        return;
    }

    list();
    data.close();

    char choice;
    do
    {
        cout << "\n\nEnter Product Code: ";
        cin >> codes[c];
        cout << "Enter Quantity: ";
        cin >> quantities[c];
        c++;

        cout << "\nDo you want to buy another product? (y/n): ";
        cin >> choice;
    } while (choice == 'y');

    cout << "\n\n| Product Code | Product Name | Quantity | Price | Amount | Discounted Amount |\n";
    cout << "----------------------------------------------------------------------\n";

    for (int i = 0; i < c; i++)
    {
        data.open("database.txt", ios::in);
        while (data >> pcode >> pname >> price >> dis)
        {
            if (pcode == codes[i])
            {
                float amount = price * quantities[i];
                float discountedAmount = amount - (amount * dis / 100);
                total += discountedAmount;

                cout << pcode << "          " << pname << "        " << quantities[i] << "       " << price << "      " << amount << "          " << discountedAmount << "\n";
            }
        }
        data.close();
    }

    cout << "\nTotal Amount: " << total << "\n";
}

int main()
{
    shopping s;
    s.menu();
    return 0;
}
