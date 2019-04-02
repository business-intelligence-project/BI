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

time_t t =time(NULL);
//tm* timePrt=localtime(&t);

//Write definition of function prototype here
void ShowBarGraph();//ฟิวเขียน
void ShowLineGraph();//แบมเขียน
void ShowprofitGraph(vector<int>);//ยังไม่มีคนเขียน
void InputData(string textline);//เต๋าเขียน
void SearchData(string);//ยังไม่มีคนเขียน
void ProfitAnalysis(int);//ยังไม่มีคนเขียน
void StrToUpper(string &);//complete
void AddToFile(string,string);//complete

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
        StrToUpper(command);        ofstream d("InvestmentSystemData.txt");d<<"He",ios::app;d.close();
        if(command == "ADD"){
            InputData(textline);
        }else{cout <<"UNKNOWN COMMAND\n";}
        break;//ยังไม่ได้เขียนวิธีจบ loop
    }while(true);

}

//Write definition of function here
void StrToUpper(string &text){
    for(int i=0;i<text.size();i++){
        text[i]=toupper(text[i]);
    }
}

void InputData(string textline){
    string type, year;
    int end = textline.find_first_of(" ",5);
    type = textline.substr(4,end-4);
    StrToUpper(type);
    year = textline.substr(end+1,(textline.size()-end-1));
    if(atoi(year.c_str()) <=2500 || atoi(year.c_str()) > 2562 /*timePrt->tm_year*/) 
    {
        cout << "Incorrect data\n";
    }
    else{
        if(type == "INVESTMENT") AddToFile("InvestmentSystemData.txt",year);
        else if("Partner") AddToFile("PartnerSystemData.txt",year);
        else cout << "Incorrect data\n";
    }
}

void SearchData(string type){
    //ค้นหาแบบเป็นปีเก็บค่าไว้ใน struct yeardata
    //ค้นหาแบบเป็นชื่อบริษัทเก็บค่าไว้ใน struct companydata
}

void AddToFile(string loc,string year){
    string data;
    int end;
    ofstream dest(loc.c_str());
    while(true){
        cout << "INPUT :";
        getline(cin,data);
        end = data.find_first_of("=");
        data[end]=',';
        StrToUpper(data);
        if(data == "END") {
            dest.close();
            break;
        }
        if(end > 0 ){ 
            //string smoney = data.substr(end,data.size()-end);smoney[end,data.size()-end]='\0';
            //double money = atof(smoney.c_str());cout <<smoney<<","<<money;
            /*if(money > 0)*/ dest << year <<"," << data << "\n" , ios::app;
            //else cout << " >>Money must be number\n";
            cout << ">>COMPLETE\n";
        }else cout << " >>CANNOT INPUT DATA\n";
    }
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