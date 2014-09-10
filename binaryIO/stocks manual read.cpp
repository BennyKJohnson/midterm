//
//  main.cpp
//  Stocks
//
//  Created by Ben Johnson on 21/05/2014.
//  Copyright (c) 2014 Ben Johnson. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Stock
{
    char ticker[6];
    int price;
    int volumeTradedToday;

};
void sortStocksByPrice(Stock stocks[],int length)
{
    Stock temp;
    
    for (int i =0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            if(stocks[i].price < stocks[j].price)
            {
                temp = stocks[i];
                stocks[i] = stocks[j];
                stocks[j] = temp;
            }
        
        }
    }
    
}
void sortStocksByVolume(Stock stocks[],int length)
{
    Stock temp;
    
    for (int i =0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            if(stocks[i].volumeTradedToday < stocks[j].volumeTradedToday)
            {
                temp = stocks[i];
                stocks[i] = stocks[j];
                stocks[j] = temp;
            }
            
        }
    }
    
}

void writeReport(Stock stocks[],int length, bool isCost = true)
{
    ofstream out;
    if (isCost)
    {
        out.open("report-1.txt",ios::out);
        out << "Corporate Stock Cost - NASDAQ" << endl;
        out << "Stock Tag" << endl;
        out << "Cost"  << endl;
    }
    else
    {
        out.open("report-2.txt",ios::out);
        out << "Corporate Stock Volume Data - NASDAQ" << endl;
        out << "Stock Tag" << endl;
        out << "Volume"  << endl;
    }
    

    for (int i =0; i < length; i++)
    {
        Stock currentStock = stocks[i];
        if (isCost)
            out << currentStock.ticker << "\t" << currentStock.price << endl;
        else
            out << currentStock.ticker << "\t" << currentStock.volumeTradedToday << endl;
    }
    out.close();
    
}
int main(int argc, const char * argv[])
{
    Stock stocks[100];
    
    ifstream infile;
    infile.open("/Users/benjohnson/Desktop/stocks-dataset.txt");
    int i = 0;
    
    while (infile.good()) {
        infile >> stocks[i].ticker;
        infile >> stocks[i].price;
        infile >> stocks[i].volumeTradedToday;
        i++;
        
    }
    infile.close();
    char choice;
    
    cout << "Main Menu:" << endl;
    cout << endl;
    cout << "c: Sort Data by Cost" << endl;
    cout << "v: Sort Data by Trade Volume" << endl;
    cout << "q: quit" << endl;
    cout << "enter choice: ";
    while (true) {
        cin >> choice;
        if (choice == 'c'|| choice == 'C') {
            
            sortStocksByPrice(stocks, i);
            writeReport(stocks, i);
            
            return 0;

        }
        else if (choice == 'v' || choice == 'V')
        {
            sortStocksByVolume(stocks, i);
            writeReport(stocks, i,false);

            return 0;
            
        }
        else if (choice == 'q' || choice == 'Q')
        {
            return 0;
        }
        else
        {
            cout << "Invalid input, please enter valid input" << endl;
            cout << "enter choice: ";
         
            
        }
        
    }

    return 0;
}

