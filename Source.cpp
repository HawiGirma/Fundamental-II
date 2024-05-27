#include <mysql.h>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int qstatus;
int carid;
string payment, carclass;
// Function prototypes
void insertData(MYSQL* connect);
void insertDataagain(MYSQL* connect);
void deletedata(MYSQL* connect);
void deleterows(MYSQL* connect);
void displaysedans(MYSQL* connect);
void displaysuvs(MYSQL* connect);
void displaypickuptrucks(MYSQL* connect);
void displayvans(MYSQL* connect);
void displaypayment(MYSQL* connect);
void displayuserdata(MYSQL* connect);
void displayalldata(MYSQL* connect);
void showMenu(const string& role, MYSQL* connect);
int main()
{
    MYSQL* connect;
    connect = mysql_init(0);
    if (connect == nullptr)
    {
        cout << "Error: mysql_init() failed" << endl;
        return 1;
    }

    connect = mysql_real_connect(connect, "localhost", "root", "group 12024#", "CRS", 3306, NULL, 0);

    if (connect)
    {
        system("cls");
        int choice;
        string role, username;
        char x;

        cout << "\n\t\t\t ----------------------------------------------\n";
        cout << "\t\t\t|                WELCOME BACK:)                  |\n";
        cout << "\t\t\t ----------------------------------------------\n";

        cout << " \n\t\t\tAre you a user or an admin\?";
        cout << "\n\t\t\t User \n\t\t\t Admin \t\t\t>_____";
        cin >> role;
        showMenu(role, connect);
    }
    else
    {
        cout << "connectection to database has failed: " << mysql_error(connect) << endl;
    }
    return 0;
}

void showMenu(const string& role, MYSQL* connect)
{
    system("cls");
    int choice;
    char x;
    while (role == "admin" || role == "user")
    {
        if (role == "admin")
        {
            cout << "\n\t\t\t ----------------------------------------------\n";
            cout << "\t\t\t|                 ADMIN PAGE                      |\n";
            cout << "\t\t\t ------------------------------------------------\n";

            cout << "\n\t\t\t1. Drop every Customer Data" << endl;
            cout << "\n\t\t\t2. Display all Customer's Data" << endl;
            cout << "\n\t\t\t3. Exit" << endl;
            cin >> choice;

            switch (choice)
            {
            case 1:
                deleterows(connect);
                break;
            case 2:
                displayalldata(connect);
                break;
            case 3:
                cout << "\t\t\tExiting the program." << endl;
                exit(0);
                break;
            default:
                cout << "\t\t\tInvalid choice. Please try again." << endl;
            }
        }
        else if (role == "user")
        {
            cout << "\n\t\t\t ----------------------------------------------\n";
            cout << "\t\t\t|                  USER PAGE                     |\n";
            cout << "\t\t\t ----------------------------------------------\n";
            cout << "\t\t\t Do you have account \?:(y/n)";
            cin >> x;
            if (x == 'Y' || x == 'y')
            {
                cout << "\n\t\t\t1. Display Own Data" << endl;
                cout << "\n\t\t\t2. Modify Own record" << endl;
                cout << "\n\t\t\t3. Delete Own record" << endl;
                cout << "\n\t\t\t4. Exit" << endl;
                cin >> choice;
                switch (choice)
                {
                case 1:
                    displayuserdata(connect);
                    break;
                case 2:
                    insertDataagain(connect);
                    break;
                case 3:
                    deletedata(connect);
                    break;
                case 4:
                    cout << "\t\t\tExiting the program." << endl;
                    exit(0);
                    break;
                default:
                    cout << "\t\t\tInvalid choice. Please try again." << endl;
                }
            }
            else if (x == 'n' || x == 'N')
            {
                cout << "\n\t\t\t ----------------------------------------------\n";
                cout << "\t\t\t|                CREATE ACCOUNT                  |\n";
                cout << "\t\t\t ----------------------------------------------\n";
                cout << "\n\t\t\t1. Insert Data" << endl;
                cout << "\n\t\t\t2. Exit" << endl;
                cin >> choice;

                switch (choice)
                {
                case 1:
                {
                    
                    insertData(connect);
                    break;
                }
                case 2:
                {
                    cout << "\t\t\tExiting the program." << endl;
                    exit(0);
                    break;
                }
                default:
                    cout << "\t\t\tInvalid choice. Please try again." << endl;
                }
            }
        }
        else
            cout << "\n\t\t\tInvalid role. Exiting." << endl;
    }
    return;
}

void insertData(MYSQL* connect)
{
    int id;
    string name, phone, email;
    string choice;
    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter username: ";
    cin.ignore();                        // Ignore newline character from previous input
    getline(cin, name);
    cout << "Enter your Email: ";
    getline(cin, email);
    cout << "Enter your telephone No.: ";
    getline(cin, phone);

loop:
    system("cls");
    cout << "\t\t\n<<<<<<<<<<< Now We need you to choose Car classes You would like to rent >>>>>>>>>>>\n";
    cout << "\n\t\t Sedans\n";
    cout << "\t\t SUVS\n";
    cout << "\t\t Pickup Trucks\n";
    cout << "\t\t Minivans and Vans\n";
    cout << "\nChoice___";
    cin >> carclass;

    if (carclass == "Sedans" || "sedans")
    {

        displaysedans(connect);
        cout << "\n\t\t========= Choose based on designated Vehicle ID:__";
        cin >> carid;
    }
    else if (carclass == "SUVS" || "suvs" || "suv")
    {

        displaysuvs(connect);
        cout << "\t\t========= Choose based on designated Vehicle ID:__";
        cin >> carid;
    }
    else if (carclass == "Pickup Trucks" || "Pickup" || "pickups" || "pickup")
    {

        displaypickuptrucks(connect);
        cout << "\t\t========= Choose based on designated Vehicle ID:__";
        cin >> carid;
    }
    else if (carclass == "Minivans" || "minivans" || "Vans" || "vans")
    {

        displayvans(connect);
        cout << "\t\t========= Choose based on designated Vehicle ID:__";
        cin >> carid;
    }
    else
    {
        cout << "Invalid Car class choice, Try again";
        goto loop;
    }
    system("cls");
    cout << "\t\t\n>>>>>>>>>>>> Next to the payment section....\n";
    cout << "\t\t\t\n===============================================" << endl;
    cout << "\t\t\t\n============== Payment Information ============" << endl;
    cout << "\t\t\t\n===============================================" << endl;
    displaypayment(connect);
    cout << "\t\t\n========= Choose from payment Options:_____";
    cin >> payment;

    // INSERT INTO Customers(CusID, name, Email, Phone) VALUES(1,'Eyuel', 'ey.mazi233@gmail.com', '0922697578')"
    string insertQuery = "INSERT INTO Customers (CusID, name, Email, Phone,  VehicleClass,  VehicleID, Payment) VALUES (" + to_string(id) + ", '" + name + "', '" + email + "','" + phone + "', '" + carclass + "', " + to_string(carid) + ", '" + payment + "' )";
    const char* insertQ = insertQuery.c_str();
    qstatus = mysql_query(connect, insertQ);
    if (!qstatus)
    {
        cout << "Data inserted successfully!" << endl;
    }
    else
    {
        cout << "Failed to insert data: " << mysql_error(connect) << endl;
    }
}

// Function to delete a column from the 'test' table
void displaysedans(MYSQL* connect)
{
    system("cls");
    cout << "\n\t\t\t\t===============================================" << endl;
    cout << "\t\t\t\t============= Sedans Information ==============" << endl;
    cout << "\t\t\t\t===============================================" << endl;
    MYSQL_RES* res;
    MYSQL_ROW row;

    string selectQuery = "SELECT * FROM sedans";
    const char* selectQ = selectQuery.c_str();
    qstatus = mysql_query(connect, selectQ);
    if (!qstatus)
    {
        res = mysql_store_result(connect);
        cout << endl;
        cout << setw(15) << "VehicleID" << setw(30) << "\tVehicle_Model" << setw(28) << "Vehicle Class" << setw(20) << "Price/day" << setw(20) << "Insurance" << endl;
        while ((row = mysql_fetch_row(res)))
        {
            cout << setw(10) << row[0] << "\t" << setw(30) << row[1] << setw(28) << row[2] << setw(20) << row[3] << setw(25) << row[4] << endl;
        }
        mysql_free_result(res);
    }
    else
    {
        cout << "Query execution failed: " << mysql_error(connect) << endl;
    }
}
void displaysuvs(MYSQL* connect)
{
    system("cls");
    cout << "\n\t\t\t\t=============================================" << endl;
    cout << "\t\t\t\t============== SUV's Information ============" << endl;
    cout << "\t\t\t\t=============================================" << endl;
    MYSQL_RES* res;
    MYSQL_ROW row;

    string selectQuery = "SELECT * FROM suvs";
    const char* selectQ = selectQuery.c_str();
    qstatus = mysql_query(connect, selectQ);
    if (!qstatus)
    {
        res = mysql_store_result(connect);
        cout << endl;
        cout << left;
        cout << setw(15) << "VehicleID" << setw(30) << "Vehicle_Model" << setw(28) << "Vehicle Class" << setw(20) << "Price/day" << setw(20) << "Insurance" << endl;
        while ((row = mysql_fetch_row(res)))
        {
            cout << setw(10) << row[0] << "\t" << setw(30) << row[1] << setw(28) << row[2] << setw(20) << row[3] << setw(25) << row[4] << endl;
        }
        mysql_free_result(res);
    }
    else
    {
        cout << "Query execution failed: " << mysql_error(connect) << endl;
    }
}
void displaypickuptrucks(MYSQL* connect)
{
    system("cls");
    cout << "\n\t\t\t\t=============================================" << endl;
    cout << "\t\t\t\t========= Pickuo Trucks Information =========" << endl;
    cout << "\t\t\t\t=============================================" << endl;
    MYSQL_RES* res;
    MYSQL_ROW row;

    string selectQuery = "SELECT * FROM pickuptrucks";
    const char* selectQ = selectQuery.c_str();
    qstatus = mysql_query(connect, selectQ);
    if (!qstatus)
    {
        res = mysql_store_result(connect);
        cout << endl;
        cout << left;
        cout << setw(15) << "VehicleID" << setw(30) << "Vehicle_Model" << setw(28) << "Vehicle Class" << setw(20) << "Price/day" << setw(20) << "Insurance" << endl;
        while ((row = mysql_fetch_row(res)))
        {
            cout << setw(10) << row[0]<< "\t" << setw(30) << row[1] << setw(28) << row[2] << setw(20) << row[3] << setw(25) << row[4] << endl;
        }
        mysql_free_result(res);
    }
    else
    {
        cout << "Query execution failed: " << mysql_error(connect) << endl;
    }
}
void displayvans(MYSQL* connect)
{
    system("cls");
    cout << "\n\t\t\t\t=============================================" << endl;
    cout << "\t\t\t\t========= Minivans\Vans Information ==========" << endl;
    cout << "\t\t\t\t=============================================" << endl;
    MYSQL_RES* res;
    MYSQL_ROW row;

    string selectQuery = "SELECT * FROM minivansvans";
    const char* selectQ = selectQuery.c_str();
    qstatus = mysql_query(connect, selectQ);
    if (!qstatus)
    {
        res = mysql_store_result(connect);
        cout << endl;
        cout << left;
        cout << setw(15) << "VehicleID" << setw(30) << "Vehicle_Model" << setw(28) << "Vehicle Class" << setw(20) << "Price/day" << setw(20) << "Insurance" << endl;
        while ((row = mysql_fetch_row(res)))
        {
            cout << setw(10) << row[0]<< "\t" << setw(30) << row[1] << setw(28) << row[2] << setw(20) << row[3] << setw(25) << row[4] << endl;
        }
        mysql_free_result(res);
    }
    else
    {
        cout << "Query execution failed: " << mysql_error(connect) << endl;
    }
}

void displaypayment(MYSQL* connect)
{
    system("cls");
    cout << "\n\t\t\t\t=============================================" << endl;
    cout << "\t\t\t\t========= Payment Information ===============" << endl;
    cout << "\t\t\t\t=============================================" << endl;
    MYSQL_RES* res;
    MYSQL_ROW row;

    string selectQuery = "SELECT * FROM payment";
    const char* selectQ = selectQuery.c_str();
    qstatus = mysql_query(connect, selectQ);
    if (!qstatus)
    {
        res = mysql_store_result(connect);
        cout << endl;
        cout << left;
        cout << "\t\t\t" << setw(20) << "PaymentMethod" << setw(30) << "Account" << endl;

        while ((row = mysql_fetch_row(res))) {
            cout << "\t\t\t" << setw(20) << row[0] << setw(30) << row[1] << endl;
        }
        mysql_free_result(res);
    }
    else
    {
        cout << "Query execution failed: " << mysql_error(connect) << endl;
    }
}
// Function to display selected user data using a unique ID
void displayuserdata(MYSQL* connect) {
    int id;
    system("cls");
    cout << "\n\t\t\t\t=============================================" << endl;
    cout << "\t\t\t\t=========== Display your data ===============" << endl;
    cout << "\t\t\t\t=============================================" << endl;
    MYSQL_RES* res;
    MYSQL_ROW row;
    cout << "\n\t\t\t<<<<<< Enter Customer ID: ";
    cin >> id;
    string selectQuery = "SELECT * FROM Customers WHERE CusID = " + to_string(id) + " LIMIT 1";
    const char* selectQ = selectQuery.c_str();
    int qstatus = mysql_query(connect, selectQ);
    if (!qstatus) {
        res = mysql_store_result(connect);
        if (mysql_num_rows(res) == 0) {
            cout << "\n\t\t\tNo data found for Customer ID: " << id << endl;
        }
        else {
            cout << endl;
            cout << left << setw(15) << "Customer ID" << setw(20) << "Name" << setw(30) << "Email Address" << setw(15) << "Phone No." << setw(20) << "Vehicle Class" << setw(15) << "Vehicle ID" << setw(15) << "Payment" << endl;
            while ((row = mysql_fetch_row(res))) {
                cout << setw(15) << row[0] << setw(20) << row[1] << setw(30) << row[2] << setw(15) << row[3] << setw(20) << row[4] << setw(15) << row[5] << setw(15) << row[6] << endl;
            }
        }
        mysql_free_result(res);
    }
    else {
        cout << "Query execution failed: " << mysql_error(connect) << endl;
    }
}
void insertDataagain(MYSQL* connect)
{
    cout << "\n\t\t\t\t=============================================" << endl;
    cout << "\t\t\t\t=========== Modify Your Data ================" << endl;
    cout << "\t\t\t\t=============================================" << endl;
    int id;
    string name, phone, email;
    string choice;
    cout << "\tEnter ID: ";
    cin >> id;
    cout << "Enter username: ";
    cin.ignore();                        // Ignore newline character from previous input
    getline(cin, name);
    cout << "Enter your Email: ";
    getline(cin, email);
    cout << "Enter your telephone No.: ";
    getline(cin, phone);

loop:
    system("cls");
    cout << "\t\t\n<<<<<<<<<<< Now We need you to choose Car classes You would like to rent >>>>>>>>>>>\n";
    cout << "\n\t\t Sedans\n";
    cout << "\t\t SUVS\n";
    cout << "\t\t Pickup Trucks\n";
    cout << "\t\t Minivans and Vans\n";
    cout << "\nChoice___";
    cin >> carclass;

    if (carclass == "Sedans" || "sedans")
    {

        displaysedans(connect);
        cout << "\n\t\t========= Choose based on designated Vehicle ID:__";
        cin >> carid;
    }
    else if (carclass == "SUVS" || "suvs" || "suv")
    {

        displaysuvs(connect);
        cout << "\t\t========= Choose based on designated Vehicle ID:__";
        cin >> carid;
    }
    else if (carclass == "Pickup Trucks" || "Pickup" || "pickups" || "pickup")
    {

        displaypickuptrucks(connect);
        cout << "\t\t========= Choose based on designated Vehicle ID:__";
        cin >> carid;
    }
    else if (carclass == "Minivans" || "minivans" || "Vans" || "vans")
    {

        displayvans(connect);
        cout << "\t\t========= Choose based on designated Vehicle ID:__";
        cin >> carid;
    }
    else
    {
        cout << "Invalid Car class choice, Try again";
        goto loop;
    }
    system("cls");
    cout << "\t\t\n>>>>>>>>>>>> Next to the payment section....\n";
    cout << "\t\t\t\n===============================================" << endl;
    cout << "\t\t\t\n============== Payment Information ============" << endl;
    cout << "\t\t\t\n===============================================" << endl;
    displaypayment(connect);
    cout << "\t\t\n========= Choose from payment Options:_____";
    cin >> payment;

    // INSERT INTO Customers(CusID, name, Email, Phone) VALUES(1,'Eyuel', 'ey.mazi233@gmail.com', '0922697578')"
    string updateQuery = "UPDATE Customers SET name = '" + name + "', Email = '" + email + "', Phone = '" + phone + "', VehicleClass = '" + carclass + "', VehicleID = " + to_string(carid) + ", Payment = '" + payment + "' WHERE CusID = " + to_string(id) + " ";
    const char* updateQ = updateQuery.c_str();
    qstatus = mysql_query(connect, updateQ);
    if (!qstatus) {
        cout << "Record updated successfully." << endl;
    }
    else {
        cout << "Failed to update record: " << mysql_error(connect) << endl;
    }
}
void deletedata(MYSQL* connect)
{
    cout << "\n\t\t\t\t=============================================" << endl;
    cout << "\t\t\t\t=========== Delete your data ================" << endl;
    cout << "\t\t\t\t=============================================" << endl;
    int id;
    cout << "\nEnter ID:__";
    cin >> id;
    string deleteQuery = "DELETE FROM Customers WHERE CusID = " + to_string(id) + " ";
    const char* deleteQ = deleteQuery.c_str();
    qstatus = mysql_query(connect, deleteQ);
    if (!qstatus) {
        cout << "Data deleted successfully." << endl;
    }
    else {
        cout << "Failed to delete row: " << mysql_error(connect) << endl;
    }

}
void deleterows(MYSQL* connect)
{
    string deleteAllQuery = "DELETE FROM Customers";
    const char* deleteAllQ = deleteAllQuery.c_str();
    qstatus = mysql_query(connect, deleteAllQ);
    if (!qstatus) {
        cout << "Every Customer record has been deleted successfully." << endl;
    }
    else {
        cout << "Failed to delete Customers record: " << mysql_error(connect) << endl;
    }

}
void displayalldata(MYSQL* connect) {
    system("cls");
    cout << "\n\t\t\t\t=============================================" << endl;
    cout << "\t\t\t\t=========== Display All data ================" << endl;
    cout << "\t\t\t\t=============================================" << endl;
    MYSQL_RES* res;
    MYSQL_ROW row;
    string selectQuery = "SELECT * FROM Customers ";
    const char* selectQ = selectQuery.c_str();
    int qstatus = mysql_query(connect, selectQ);
    if (!qstatus) {
        res = mysql_store_result(connect);
        if (mysql_num_rows(res) == 0) {
            cout << "\n\t\t\tNo data found " << endl;
        }
        else {
            cout << endl;
            cout << left << setw(15) << "Customer ID" << setw(20) << "Name" << setw(30) << "Email Address" << setw(15) << "Phone No." << setw(20) << "Vehicle Class" << setw(15) << "Vehicle ID" << setw(15) << "Payment" << endl;
            while ((row = mysql_fetch_row(res))) {
                cout << setw(15) << row[0] << setw(20) << row[1] << setw(30) << row[2] << setw(15) << row[3] << setw(20) << row[4] << setw(15) << row[5] << setw(15) << row[6] << endl;
            }
        }
        mysql_free_result(res);
    }
    else {
        cout << "Query execution failed: " << mysql_error(connect) << endl;
    }
}

