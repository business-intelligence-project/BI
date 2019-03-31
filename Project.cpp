#include<iostream>
#include<cmath>
#include<fstream>
#include<ctime>
#include<stdlib.h>
#include<string>
#include<algorithm>
#include<stdio.h>
#include<vector>
using namespace std;
//Write definition of function prototype here
void ShowBarGraph();//ฟิวเขียน
void ShowLineGraph();//แบมเขียน
void ShowprofitGraph(vector<int>);//ยังไม่มีคนเขียน
void InputData(string textline);//เต๋าเขียน
void SearchData(string);//ยังไม่มีคนเขียน
void ProfitAnalysis(int);//ยังไม่มีคนเขียน
void StrToUpper(string &);//complete

struct yeardata{
    int year;
    vector<string> company;
    vector<int> money;
};

struct companydata{
    string company;
    vector<int> year;
    vector<int> money;
};

//main function//
int main(){
    ifstream source("Detail.txt");
    ofstream dest;
    string textline, command;
    int Oder=0;
    cout<< "Welcome \n";
    do{
        if(Oder == 0) while(getline(source,textline)) cout << textline << endl;
        cout <<"Your Command :";
        getline(cin,textline);
        int end = textline.find_first_of(" ");
        command = textline.substr(0,end);
        if(command == "ADD"){
            InputData(textline);
        }
        break;
    }while(true);

}

//Write definition of function here
void StrToUpper(string &text){
    for(int i=0;i<text.size();i++){
        text[i]=toupper(text[i]);
    }
}

void InputData(string textline){
    string type;
    int end = textline.find_first_of(" ");
    type = textline.substr(4,end);
    StrToUpper(type);
    string data , year;
    cout<< type<<",";
    year = textline.substr(end+1,(textline.size()));
    time_t t =time(NULL);
    tm* timePrt=localtime(&t);
    if(atoi(year.c_str()) <=2500 && atoi(year.c_str()) > timePrt->tm_year) cout << "Incorrect data\n";
    else{
        if(type == "INVESMENT"){
            while(getline(cin,data)){
                
            }
        }else if("Partner"){
            while(getline(cin,data)){
                
            }
        }else cout << "Incorrect data\n";
        }
    

}

void SearchData(string type){
    //ค้นหาแบบเป็นปีเก็บค่าไว้ใน struct yeardata
    //ค้นหาแบบเป็นชื่อบริษัทเก็บค่าไว้ใน struct companydata
}

void ProfitAnalysis(int year){
    //คำนวนกำไรแต่ละปีเก็บไว้ใน vector แล้วเรียก function ShowprofitGraph
    vector<int> profit;


}

void ShowBarGraph(){
    
}
void ShowLineGraph(){

}

void ShowprofitGraph(vector<int> profit){

}