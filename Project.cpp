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
#include<graphics.h>
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
void ShowprofitGraph(vector<int>);//ยังไม่มีคนเขียน
void InputData(string textline);//เต๋าเขียน//complete
void SearchData(int,string);//complete
void ProfitAnalysis(int);//ยังไม่มีคนเขียน
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

struct profitfromselling{
    double profit;
    vector<double> profitvec();
};

struct  totalprofit
{ 
    profitfromselling *receive1;
    companydata *receive2;
    vector<double> profit;
    vector<double> profitforecast;
    vector<double> totalprofitvec(profitfromselling *, companydata *);
};

vector<yeardata> ydata_investment;//เก็บข้อมูลจากการ Search คำว่า profit พศ ของ InvestmentSystemData.txt//
vector<yeardata> ydata_partner;//เก็บข้อมูลจากการ Search คำว่า profit พศ ของ PartnerSystemDatatxt//
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
		}else if(command == "CLOSE" || command == "EXIT" || command == "END") {
            cout << "Thank you for use this Program.";
            break;
        }
        
        
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
        else if(type == "SELLING") AddToFile(3 ,year);
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
        }else if(yearst > 2500 && yearst <= cerrentyear && yearend >= yearst && yearend <= cerrentyear){
            for(int i = yearst ; i <= yearend ; i++){
                yd.year = i;
                ydata.push_back(yd);
                ydata_investment.push_back(yd);
                ydata_partner.push_back(yd);
                ydata_selling.push_back(yd);
            }
        }else{
            cout << ">INCORRECT YEAR\n";
            chk = -1;
        } 
    }
    ifstream source;
    if(loc == 0)source.open("InvestmentSystemData.txt");
    else if(loc == 1 ||loc == 2) source.open("PartnerSystemData.txt");
    
    if(loc != 2){
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
    else{
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
                chk=-1;
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
                chk=-1;
                break;
            }
        }
        source.close();
        source.open("SellingSystemData.txt");
        while(getline(source,textline)){
            if(chk == -1) break;
            int start = textline.find_first_of(",");
            int years = atoi(textline.substr(0 , start).c_str());
            string names = "";
            double moneys = atof(textline.substr(start + 1, textline.size() - start).c_str());
            if(chk == 0 ){
                if((years >= yearst && years <= yearend ) || (years == yearst && yearend == -1)){
                    ydata_selling[years - yearst].company.push_back(names);
                    ydata_selling[years - yearst].money.push_back(moneys);
                }
            }else{
                cout << "INCORRECT DATA\n";
                chk=-1;
                break;
            }
        }
            
    }
    if(chk == 0){
    	ShowBarGraph();
	}
    else if(chk == 1){
    	ShowLineGraph();
	}
}

void AddToFile(int loc,string year){
    string data;
    int end;
    ofstream dest;
    if (loc == 1) dest.open("InvestmentSystemData.txt",ios::app);
    else if(loc == 2)dest.open("PartnerSystemData.txt",ios::app);
    else if(loc == 3)dest.open("SellingSystemData.txt",ios::app);
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
        if(loc == 1 ||loc == 2){
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
        }else{
            if(atof(data.c_str()) > 0){
                data = DelSpacebar(0,data.size(),data);
                dest << year <<","<< data << "\n" ,ios::app;
                cout << ">>COMPLETE\n";
            } 
            else cout << " >>MONEY MUST BE NUMBER\n";
        }
    }
    
}

void ProfitAnalysis(int year){
    //คำนวนกำไรแต่ละปีเก็บไว้ใน vector แล้วเรียก function ShowprofitGraph
    vector<int> profit;

    
}

void ShowBarGraph(){
	double max = 0;
	int count = 0;
	cout<<"\tYear\t\t\tName\t\t\tMoney\n";
	for(int i=0;i<ydata.size();i++){
		yeardata ydatatmp = ydata[i];
		for(int j=0;j<ydatatmp.money.size();j++){
			cout<<"\t"<<ydatatmp.year<<"\t\t\t"<<ydatatmp.company[j]<<"\t\t\t"<<ydatatmp.money[j]<<endl;
			if(ydatatmp.money[j]>max){
				max = ydatatmp.money[j];
			}count++;
		}
	}
	if(count > 1){
		double W = 800 ,H = 600;
		initwindow(W,H);
		line (0.1*W,H-(0.1*H),W*0.9,H-(0.1*H));
		line (0.1*W,H-(0.1*H),0.1*W,(H*0.1));
		setfillstyle(LINE_FILL,RED);
		
		int left = 0.12*W,top,right,bottom,c = 0;
		char ty[100]={};
		for(int i=0;i<ydata.size();i++){
			setfillstyle(LINE_FILL,GREEN);
			yeardata ydatatmp = ydata[i];
			for(int j=0;j<ydatatmp.money.size();j++){
				if(c != 0) left += 0.7*(W/count);
				bottom = H-(0.1*H);
				top = bottom - (ydatatmp.money[j]*H*0.8/max);
				right = left + (0.6*W/count);
				bar(left,top,right,bottom);
				if(j == 0){
					
					sprintf(ty,"%d",ydatatmp.year);
					outtextxy(left,H-(0.08*H),ty);
				}
				sprintf(ty,"%s",ydatatmp.company[j].c_str());
				outtextxy(left,top-20,ty);
				sprintf(ty,"%d",(int)(ydatatmp.money[j]));
				outtextxy(0.02*W,top,ty);
				c++;
			}
			if(ydatatmp.money.size()>0) left += 0.15*W/count;
		}
	}
}

void ShowLineGraph(){
	double max=0;
	int yearmin = gettime(),yearmax = 0;
	for(int i=0;i<comdata.year.size();i++){
		if(comdata.year[i]<yearmin) yearmin=comdata.year[i];
		if(comdata.year[i]>yearmax) yearmax=comdata.year[i];
	}
	int s=yearmax-yearmin +1;
	double mon[s]={};
	for(int i=0;i<comdata.money.size();i++){
		mon[comdata.year[i]-yearmin] +=comdata.money[i];
	}
	for(int i=0;i<s;i++){
		if(mon[i]>max)max=mon[i];
	}
	cout<<"\t\t"<<comdata.company<<endl<<"\tYear\t\tMoney"<<endl;
	for(int i=0;i<s;i++){
		cout<<"\t"<<yearmin+i<<"\t\t"<<mon[i]<<endl;
	}
	if(s>1){
		int const W = 800 ,H = 600;
		initwindow(W,H);
		char mo[100]={},yr[5]={};
		settextstyle(0,0,3);
		sprintf(mo,"%s",comdata.company.c_str());
		outtextxy(0.5*W,10,mo);
		settextstyle(0,0,1);
		line (0.1*W,H-(0.1*H),W*0.9,H-(0.1*H));
		line (0.1*W,H-(0.1*H),0.1*W,(H*0.1));
		int x1=0.15*W,y1=H-(0.1*H)-((0.78*H)*mon[0])/max,x2,y2;
		for(int i=1;i<s;i++){
			sprintf(mo,"%d",(int)mon[i-1]);
			outtextxy(0.02*W,y1-2,mo);
			sprintf(yr,"%d",yearmin+i-1);
			outtextxy(x1 -20,H-(0.07*H),yr);
			x2=(0.15*W)+(i*(0.85*W)/s);
			y2=H-(0.1*H)-((0.78*H)*mon[i])/max;
			line(x1,y1,x2,y2);
			x1=x2;
			y1=y2;
		}
		sprintf(mo,"%d",(int)mon[s-1]);
		outtextxy(0.02*W,y1-2,mo);
		sprintf(yr,"%d",yearmax);
		outtextxy(x1 -20,H-(0.07*H),yr);
	}
    
}

void ShowprofitGraph(vector<int> profit){

}
/*
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
*/



