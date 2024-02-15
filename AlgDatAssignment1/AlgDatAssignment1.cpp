// AlgDatAssignment1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <iomanip>
#include <vector>

#include <windows.h>

using namespace std;
using std::cout;
using std::setw;
struct product{
    string Name;
    string ID;
    float Price;
    string Category;
};
int BubbleSort(vector<product>& products)
{
    for (int i = products.size(); i > 0; i--) {
        for (int j = 0; j < i - 1; j++) {
            if (products[j].Price > products[j + 1].Price) {
                product temp = products[j];
                products[j] = products[j + 1];
                products[j + 1] = temp;
            }
        }
    }
    return 0;
}

vector<product> LoadData() {
    string line;
    string delimiter = ",";
    ifstream file("product_data.txt");
    vector<product> loadedData;
    if (file.is_open()) {
        while (getline(file, line)) {
            //I HATE PARSING
            product tempProd; 
            float tmpPrice;
            int i = 0;
            size_t pos = 0;
            string currSeg;
            while ((pos = line.find(delimiter)) != std::string::npos) {
                currSeg = line.substr(0, pos);

                switch (i)
                {
                case 0:
                    tempProd.ID = currSeg;
                    break;
                case 1:
                    tempProd.Name = currSeg.erase(0,1);
                    break;
                case 2:
                    tempProd.Price = stof(currSeg);
                    break;
                case 3:
                    tempProd.Category = currSeg;
                }
                i++;
                line.erase(0, pos + delimiter.length());
            }
            loadedData.push_back(tempProd);
        }
        file.close();
    }
    return loadedData;
}

product GetProductInfo() {
    product newProduct;
    cout << "Product Name: \n";
    string S1, S2;
    cin >> S1;
    getline(std::cin, S2);
    S1.append(S2);
    newProduct.Name = S1;
    cout << "Product ID: \n";
    cin >> newProduct.ID;
    cout << "Product Price; \n";
    cin >> newProduct.Price;
    cout << "Product Category; \n";
    cin >> newProduct.Category;
    system("CLS");
    return newProduct;
}

void InsertElement(vector<product>& products) {
    system("CLS");
    cout << "Insert Data Here \n";
    products.push_back(GetProductInfo());

    std::cout.width(62); std::cout << std::internal << "Menu " << u8"[↵]" << '\n';
    getchar();
    system("CLS");
}

void UpdateProduct(product& product) {
    char input;
    cout << "Name: " + product.Name + " | " + "ID: " + product.ID + " | " + " Price: " + to_string(product.Price) + " | " + " Category: " + product.Category + "\n";
    cout << "What Field Do You Want To Update? \n";
    cout << "Name (n) | ID (i) | Price (p) | Category (c) \n";
    cin >> input;
    switch (input)
    {
        case 'n':
            cout << "New Name? \n";
            cin >> product.Name;
            break;
        case 'i':
            cout << "New ID? \n";
            cin >> product.ID;
            break;
        case 'p':
            cout << "New Price? \n";
            cin >> product.Price;
            break;
        case 'c':
            cout << "New Category? \n";
            cin >> product.Category;
            break;
        default:
            cout << "Invalid Field \n";
            break;
    }
    cout << "Name: " + product.Name + " | " + "ID: " + product.ID + " | " + " Price: " + to_string(product.Price) + " | " + " Category: " + product.Category + "\n";
    cin.ignore();
    std::cout.width(62); std::cout << std::internal << "Menu " << u8"[↵]" << '\n';
    getchar();
    system("CLS");
}

void OutputProduct(product productToOutput, int index) {
    cout << setw(5) << index;
    cout << "|";
    cout << setw(26) << productToOutput.Name + "    |";
    cout << setw(5) << productToOutput.ID + "|";
    cout << std::fixed << left << "  $" << setw(8) << setprecision(2) << productToOutput.Price << setw(1) << "|";
    cout << setw(12) << right << productToOutput.Category + "\n";
}

void OutputProducts(vector<product> products) {
    cout << setw(37);
    cout << "Products:" << endl;
    cout << setw(5) << "Index";
    cout << "|";
    cout << setw(25) << "Name         ";
    cout << "|";
    cout << setw(5) << "ID";
    cout << "|";
    cout << setw(11) << "Price   ";
    cout << "|";
    cout << setw(12) << "     Category   \n";
    int index = 0;
    for (product productOut : products) {
        OutputProduct(productOut, index);
        index++;
    }
}

int IndexFromName(vector<product> products) {
    string searchTerm;
    string P2;
    cout << "Name To Find: \n";
    cin >> searchTerm;
    getline(std::cin, P2);
    searchTerm.append(P2);
    int i = 0;
    for (auto& a : products) {
        if (a.Name == searchTerm) {
            cout << i << endl;
            return i;
        }
        else {
            i++;
        }
    }
}

int SearchProducts(vector<product>& products) {
    system("CLS");
    cout << "Choose Search Method \n" << "N = Name, I = ID \n";
    char choice;
    int index = 10000;
    cin >> choice;
    switch (choice) {
        case 'n':
            index = IndexFromName(products);
            //cout << index;
            break;
        case 'i':
            //index = IndexFromID(products)
            break;
        default:
            cout << "Invalid Selection \n";
            break;
    }
    return index;
}

void ModifyProduct(int index, vector<product>& products) {
    char choice;
    cout << "Select Action \n" << "D = Delete | U = Update \n";
    cin >> choice;
    switch (choice) {
        case 'd':
            products.erase(products.begin() + index - 1);
            break;
        case 'u':
            UpdateProduct(products[index]);
            break;
        default:
            cout << "Invalid Selection \n";
            break;
    }
}

int main() {

    SetConsoleOutputCP(CP_UTF8);
    bool running = true;
    char option;
    int input = 0;
    vector<product> productList = LoadData();
    OutputProducts(productList);
    std::cout.width(62); std::cout << std::internal << "Menu " << u8"[↵]" << '\n';
    getchar();
    while (running = true) {
        system("CLS");
        BubbleSort(productList);
        cout << "Choose Option: \n";
        cout << "I = Insert | F = Search and Modify Item | O = Output | E = Exit \n";
        cin >> option;
        switch (option)
        {
            case 'i':
                InsertElement(productList);
                break;
            case 'f':
                ModifyProduct(SearchProducts(productList), productList);
                break;
            case 'o':
                OutputProducts(productList);
                break;
            default:
                cout << "Invalid Option\n";
                break;
        }
    }
}