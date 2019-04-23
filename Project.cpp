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
int gettime(){
    int y;
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    string certime = asctime(timeinfo);
    certime = certime.substr(certime.size()-5,4).c_str();
    y = atoi(certime.c_str()) + 543;
    return y;
}

void ShowBarGraph();//ฟิวเขียน
void ShowLineGraph();//แบมเขียน
void ShowprofitGraph(vector<int>);//ต้าเขียน
void InputData(string textline);//เต๋าเขียน//complete
void SearchData(int,string);//complete
void ProfitAnalysis(int);//ยังไม่มีคนเขียน
void StrToUpper(string &);//complete
void AddToFile(int,string);//complete
string DelSpacebar(int,int,string);//complete
long double AppraiseofCompany(totalprofit);

struct yeardata{
    int year;
    vector<string> company;
    vector<double> money;
};

struct companydata{
    string company;
    vector<int> year;
    vector<double> money;
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

vector<yeardata> ydata;
companydata comdata;
int const cerrentyear = gettime();

//main function//
int main(){
    ifstream source("Detail.txt");
    ofstream dest;
    string textline, command;
    int Oder=0;
    cout<< "Welcome \n";
    do{
        if(Oder == 0) while(getline(source,textline)) cout << textline << endl;
        source.close();
        cout <<"Your Command :";
        getline(cin,textline);
        textline = DelSpacebar(0,textline.size(),textline);
        int end = textline.find_first_of(" ");
        command = textline.substr(0,end);
        StrToUpper(command);
        if(command == "ADD"){
            InputData(textline.substr(3,textline.size()-3));
        }else if(command == "INVESTMENT"){
            SearchData(0,textline.substr(10,textline.size()-10));
        }else if(command == "PARTNER"){
            SearchData(1,textline.substr(7,textline.size()-7));
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
    textline = DelSpacebar(0,textline.size(),textline);
    int end = textline.find_first_of(" ");
    type = textline.substr(0,end);
    StrToUpper(type);
    year = textline.substr(end+1,(textline.size()-end-1));
    if(atoi(year.c_str()) <= 2500 || atoi(year.c_str()) > cerrentyear ) 
    {
        cout << ">INCORRECT YEAR\n";
    }
    else{
        if(type == "INVESTMENT") AddToFile(1 , year);
        else if(type == "PARTNER") AddToFile(2 ,year);
        else cout << "INCORRECT DATA\n";
    }
}

string DelSpacebar(int start,int end,string data){
    int starttmp = start,endtmp = end - 1;
    string datatmp;
    while(data[starttmp] == ' ') starttmp++;
    while(data[endtmp] == ' ') endtmp--;
    if(endtmp != end)endtmp++;
	datatmp = data.substr(0,start) + data.substr(starttmp,endtmp - starttmp) + data.substr(end,data.size() - end - 1);
	return datatmp;

}

void SearchData(int loc,string type){
    string textline;
    int yearst = -1,yearend = -1,chk = 0;
    ydata.clear();
    comdata.year.clear();
    comdata.money.clear();
    type = DelSpacebar(0,type.size(),type);
    for(int i=0;i<type.size();i++){
        if((type[i] < '0' || type[i] > '9' )&&(type[i] != '-')&&(type[i] != ' ')){
            chk = 1;
            break;
        }
    }
    if(chk == 0){
        if(type.find_first_of("-") == -1){
            yearst = atoi(type.c_str());
        }else{
            yearst = atoi(type.substr(0,type.find_first_of("-")).c_str());
            yearend = atoi(type.substr(type.find_first_of("-") + 1,type.size() - type.find_first_of("-")).c_str());
        }
        yeardata yd;
        if(yearst > 2500 && yearst <= cerrentyear && yearend == -1){
            yd.year = yearst;
            ydata.push_back(yd);
        }else if(yearst > 2500 && yearst <= cerrentyear && yearend >= yearst && yearend <= cerrentyear){
            for(int i = yearst ; i <= yearend ; i++){
                yd.year = i;
                ydata.push_back(yd);
            }
        }else{
            cout << ">INCORRECT YEAR\n";
            chk = -1;
        } 
    }
    ifstream source;
    if(loc == 0)source.open("InvestmentSystemData.txt");
    else source.open("PartnerSystemData.txt");
    while(getline(source,textline)){
        if(chk == -1) break;
        int start = textline.find_first_of(",");
        int end = textline.find_last_of(",");
        int years = atoi(textline.substr(0 , start).c_str());
        string names = textline.substr(start + 1,end - start -1);
        double moneys = atof(textline.substr(end + 1, textline.size() - end).c_str());
        if(chk == 0 ){
            if((years >= yearst && years <= yearend ) || (years == yearst && yearend == -1)){
                ydata[years - yearst].company.push_back(names);
                ydata[years - yearst].money.push_back(moneys);
            }
        }else{
            StrToUpper(type);
            if(names == type){
                comdata.company = names;
                comdata.year.push_back(years);
                comdata.money.push_back(moneys);
            }
        }
    }
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
        data = DelSpacebar(0,data.size(),data);
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
                
                data = DelSpacebar(0,data.find_last_of("="),data);
                data = DelSpacebar(data.find_last_of("=") + 1,data.size(),data);
                data[data.find_first_of("=")] = ',';
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
    //ใช้ include LineGraph.h เพื่อสร้างกราฟ ตอนนี้อัพ ไฟล์ LineGraph.h ลง github แล้วแต่ยังเขียนไม่เสร็จ ใช้ Dev C++ ทำ.

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
