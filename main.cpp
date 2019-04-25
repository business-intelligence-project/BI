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
//#include<graphics.h>
//#include "Bargraph.h"
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

void ShowBarGraph(double);//????????
void ShowLineGraph();//????????
void ShowprofitGraph(vector<int>);//???????????????
void InputData(string textline);//?????????//complete
void SearchData(int,string);//complete
void ProfitAnalysis(int);//???????????????
void StrToUpper(string &);//complete
void AddToFile(int,string);//complete
string DelSpacebar(int,int,string);//complete
//long double AppraiseofCompany(totalprofit);
void BarGraphCompany();

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

vector<yeardata> ydata_investment;//???????????????? Search ????? profit ?? ??? InvestmentSystemData.txt//
vector<yeardata> ydata_partner;//???????????????? Search ????? profit ?? ??? PartnerSystemDatatxt//
vector<yeardata> ydata_selling;
vector<yeardata> ydata_totalmoney;
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
        }else if(command == "SELLING"){
        	SearchData(2,textline.substr(7,textline.size()-7));
		}else if(command == "CLOSE") {
            cout << "Thank you for use this Program.";
            break;
        }else
        {cout <<">UNKNOWN COMMAND\n";}

        
        
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
        else if(type == "SELLING") AddToFile(3,year);
        else if(type == "PROFIT") AddToFile(4,year);
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
            ydata_investment.push_back(yd);
            ydata_partner.push_back(yd);
            ydata_selling.push_back(yd);
            ydata_totalmoney.push_back(yd);
        }else if(yearst > 2500 && yearst <= cerrentyear && yearend >= yearst && yearend <= cerrentyear){
            for(int i = yearst ; i <= yearend ; i++){
                yd.year = i;
                ydata.push_back(yd);
                ydata_investment.push_back(yd);
                ydata_partner.push_back(yd);
                ydata_selling.push_back(yd);
                ydata_totalmoney.push_back(yd);
            }
        }else{
            cout << ">INCORRECT YEAR\n";
            chk = -1;
        } 
    }
    ifstream source;
    if(loc == 0)source.open("InvestmentSystemData.txt");
    else if(loc == 1)source.open("PartnerSystemData.txt");
    else if(loc == 2)source.open("SellingSystemData.txt");
    else if(loc == 3)source.open("ProfitSystemData.txt");
    if(loc == 0 || loc==1){
        while(getline(source,textline)){
            if(chk == -1) break;
            if(loc ==0 || loc==1){
            int start = textline.find_first_of(",");
            int end = textline.find_last_of(",");
            int years = atoi(textline.substr(0 , start).c_str());
            string names = textline.substr(start + 1,end - start -1);
            double moneys = atof(textline.substr(end + 1, textline.size() - end).c_str());

            if(loc==3||loc==4){
                int start = textline.find_first_of(",");
                int end = textline.find_last_of(",");
                double moneys = atof(textline.substr(end + 1, textline.size() - end).c_str());  
                }
            
            if(chk == 0 ){
                if((years >= yearst && years <= yearend ) || (years == yearst && yearend == -1)){
                    ydata[years - yearst].company.push_back(names);
                    ydata[years - yearst].money.push_back(moneys);
                }
            }else{
                if(chk==1){
                    if((years >= yearst && years <= yearend ) || (years == yearst && yearend == -1)){
                    ydata[years - yearst].money.push_back(moneys);
                }
                StrToUpper(type);
                if(names == type){
                    comdata.company = names;
                    comdata.year.push_back(years);
                    comdata.money.push_back(moneys);
                }
            }
        }
    }else{
        ydata_investment.clear();
        ydata_partner.clear();
        while(getline(source,textline)){
            if(chk == -1) break;
            int start = textline.find_first_of(",");
            int end = textline.find_last_of(",");
            int years = atoi(textline.substr(0 , start).c_str());
            string names = textline.substr(start + 1,end - start -1);
            double moneys = atof(textline.substr(end + 1, textline.size() - end).c_str());
            if(chk == 0 ){
                if((years >= yearst && years <= yearend ) || (years == yearst && yearend == -1)){
                    ydata_partner[years - yearst].company.push_back(names);
                    ydata_partner[years - yearst].money.push_back(moneys);
                }
            }else{
                cout << "INCORRECT DATA\n";
                break;
            }
        }
        source.close();
        source.open("InvestmentSystemData.txt");
        while(getline(source,textline)){
            if(chk == -1) break;
            int start = textline.find_first_of(",");
            int end = textline.find_last_of(",");
            int years = atoi(textline.substr(0 , start).c_str());
            string names = textline.substr(start + 1,end - start -1);
            double moneys = atof(textline.substr(end + 1, textline.size() - end).c_str());
            if(chk == 0 ){
                if((years >= yearst && years <= yearend ) || (years == yearst && yearend == -1)){
                    ydata_investment[years - yearst].company.push_back(names);
                    ydata_investment[years - yearst].money.push_back(moneys);
                }
            }else{
                cout << "INCORRECT DATA\n";
                break;
            }
        }
    }
}
}
}

void AddToFile(int loc,string year){
    string data;
    double end;
    ofstream dest;
    if (loc == 1) dest.open("InvestmentSystemData.txt");
    else if(loc == 2)dest.open("PartnerSystemData.txt");
    else if(loc == 3)dest.open("SellingSystemData.txt");
    else if(loc == 4)dest.open("ProfitSystemData.txt");
    while(true){
        if(loc==1||loc==2){
        cout << "Input :";
        getline(cin,data);
        end = data.find_first_of("=");
        StrToUpper(data);
        data = DelSpacebar(0,data.size(),data);
        }else{
            if(loc ==3 || loc==4){
                cout<<"Input :";
                getline(cin,data);
                end = atof(data.c_str());
                StrToUpper(data);
            }
        }
        if(data == "END") {
            cout <<">>INPUT CLOSED !\n";
            dest.close();
            break;
        }
        if(end > 0 ){
            if(loc == 3 || loc ==4){
                dest << year <<"," << data << "\n" ,ios::app;
                cout << ">>COMPLETE\n";
            }else{
            string smoney = data.substr(end + 1,data.size()-end);
            smoney[data.size()-end]='\0';
            double money = atoi(smoney.c_str());
            if(money > 0){
                data = DelSpacebar(0,data.find_last_of("="),data);
                data = DelSpacebar(data.find_last_of("=") + 1,data.size(),data);
                data[data.find_first_of("=")] = ',';
                dest << year <<"," << data << "\n" ,ios::app;
                cout << ">>COMPLETE\n";
            }else{ 
                cout << " >>MONEY MUST BE NUMBER\n";
                }
            }

    }else{
        cout << " >>CANNOT INPUT DATA\n";
    }
    }
}

void ProfitAnalysis(int year){
    //????????????????????????? vector ????????? function ShowprofitGraph
    vector<int> profit;

    
}

void ShowBarGraph(){
    
}

void ShowLineGraph(){

}

void ShowprofitGraph(vector<int> profit){

}//???
