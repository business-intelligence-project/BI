#include<iostream>
#include<cmath>
#include<fstream>
#include<ctime>
#include<stdlib.h>
#include<string>
#include<algorithm>
#include<stdio.h>
#include<vector>
#include<time.h>
using namespace std;
 
time_t rawtime;
struct tm * timeinfo;

//Write definition of function prototype here
void ShowBarGraph();//ฟิวเขียน
void ShowLineGraph();//แบมเขียน
void ShowprofitGraph(vector<int>);//ยังไม่มีคนเขียน
void InputData(string textline);//เต๋าเขียน//complete
void SearchData(string);//ยังไม่มีคนเขียน
void ProfitAnalysis(int);//ยังไม่มีคนเขียน
void StrToUpper(string &);//complete
void AddToFile(int,string);//complete
long double AppraiseofCompany(totalprofit);

struct yeardata{
    int year;
    public:
    vector<string> company;
    vector<int> money;
};

struct companydata{
    string company;
    public:
    vector<int> year;
    vector<int> money();
};

struct profitfromselling{
    double profit;
    public:
    vector<double> profitvec();
};

struct  totalprofit
{
    profitfromselling *receive1;
    companydata *receive2;
    public:
    vector<double> profit;
    vector<double> profitforecast;
    vector<double> totalprofitvec(profitfromselling *, companydata *);
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
        StrToUpper(command);
        if(command == "ADD"){
            InputData(textline);
        }else{cout <<">UNKNOWN COMMAND\n";}
        
        
        
        
        
        if(textline == "EXIT")break;
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
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    string certime = asctime(timeinfo);
    certime = certime.substr(certime.size()-5,4).c_str();
    if(atoi(year.c_str()) <= 2500 || atoi(year.c_str()) > atoi(certime.c_str()) + 543 ) 
    {
        cout << ">INCORRECT YEAR\n";
    }
    else{
        if(type == "INVESTMENT") AddToFile(1 , year);
        else if("PARTNER") AddToFile(2 ,year);
        else cout << "INCORRECT DATA\n";
    }
}

void SearchData(string type){
    //ค้นหาแบบเป็นปีเก็บค่าไว้ใน struct yeardata
    //ค้นหาแบบเป็นชื่อบริษัทเก็บค่าไว้ใน struct companydata
}

void AddToFile(int loc,string year){
    string data;
    int end;
    ofstream dest;
    if (loc == 1) dest.open("InvestmentSystemData.txt");
    else dest.open("PartnerSystemData.txt");
    while(true){
        cout << "Input :";
        getline(cin,data);
        end = data.find_first_of("=");
        StrToUpper(data);
        if(data == "END") {
            cout <<">>INPUT CLOSED !\n";
            dest.close();
            break;
        }
        if(end > 0 ){
            string smoney = data.substr(end + 1,data.size()-end);
            smoney[data.size()-end]='\0';
            double money = atoi(smoney.c_str());
            if(money > 0){
                data[end] = ',';
                dest << year <<"," << data << "\n" ,ios::app;
                cout << ">>COMPLETE\n";
            } 
            else cout << " >>MONEY MUST BE NUMBER\n";
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

vector<double> totalprofit::totalprofitvec(profitfromselling *input1,companydata *input2){
    vector<double> data1,data2;
    data1 = input1 -> profitvec;
    data2 = input2 -> money;
    int Numberyears = sizeof(companydata::year);
    for (int i = 0; i < Numberyears; i++)
    {
        profit.push_back(data1[i]+data2[i]);
    }
    double sum=0;
    for (int i = 0; i < 5; i++)
    {
        sum=0;
        for (int j = 0+i; j < Numberyears+i; j++)
        { 
            sum +=profit[j];
        }
        profitforecast.push_back(sum/Numberyears);
    }   
}

long double AppraiseofCompany(totalprofit asset){
    long double value;
    double sum=0;
    int Numberyears = sizeof(companydata::year);
    for (int i = 0; i < 5; i++)
    {
        sum+=asset.profitforecast[i];
    } 
    double SumUnitMillion;
    SumUnitMillion=sum/1000000; //ปรับเป็นหน่วย ล้านบาท
    value = (pow(SumUnitMillion,Numberyears))*1000000; //ใช้สูตรก่อนแล้วค่อยกลับให้กลายเป็นหน่วยเดิม
    return value;
}
