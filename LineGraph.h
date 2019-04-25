#include<graphics.h>
#include<iostream>
using namespace std;

struct companydata{
    string company;
    vector<int> year;
    vector<double> money;
};

class LineGraphCompany{
	public:
		companydata comdata;
		LineGraphCompany();
		void ShowGraph(int,int);
		
};
LineGraphCompany::LineGraphCompany(){
	double min=comdata.money[0],max=0;
	for(int i=0;i<sizeof(comdata.money)/sizeof(comdata.money[0]);i++){
		if(comdata.money[i]>max)max=comdata.money[i];
		if(comdata.money[i]<min)min=comdata.money[i];
	}
	ShowGraph(min,max);
}

LineGraphCompany::ShowGraph(int min ,int max){
	int const W = 800 ,H = 600;
	initwindow(W,H);
	line (0.05*W,H-(0.1*H),getmaxx(),H-(0.1*H));
	line (0.05*W,H-(0.1*H),0.05*W,-getmaxx());
	
}
