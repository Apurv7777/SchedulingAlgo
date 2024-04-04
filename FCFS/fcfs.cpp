#include<iostream>
#include<vector>
#include<iomanip>
#include<ios>
#include <algorithm>
#include<map>
#include <set>
#include<climits>

using namespace std;

class Process{
    public:
    int at;
    int bt;
    int ft;
    Process(int at, int bt){
        this->at = at;
        this->bt = bt;
        this->ft=0;
    }
    Process(int bt){
        this->at = 0;
        this->bt = bt;
    }
};

int n;

void printTable(vector<Process> P){
    cout<<"+-----------+---------------+---------------+---------------+"<<endl;
    cout<<"|                      All time(s) are in ms.               |"<<endl;
    cout<<"+-----------+---------------+---------------+---------------+"<<endl;
    cout<<"|  Process  | Arrival Time  |   Burst Time  |   Final Time  |"<<endl;
    cout<<"+-----------+---------------+---------------+---------------+"<<endl;
    for(int i=0;i<n;i++){
        cout <<"|"<<right<<setfill(' ')<<setw(6)<< "P"<<i+1<<right<<setfill(' ')<<setw(5);
        cout <<"|"<<right<<setfill(' ')<<setw(9)<< P[i].at<<right<<setfill(' ')<<setw(7);
        cout <<"|"<<right<<setfill(' ')<<setw(9)<< P[i].bt<<right<<setfill(' ')<<setw(7);
        cout <<"|"<<right<<setfill(' ')<<setw(9)<<P[i].ft<<right<<setfill(' ')<<setw(7)<<"|"<<endl;
        cout<<"+-----------+---------------+---------------+---------------+"<<endl;
    }
}

int getSmallest(int *arr, map<int,bool> &m){
    int min = arr[0];
    int minIndex=0;
    for(int i=1;i<n;i++){
        if(arr[i] < min && m[arr[i]]!=true){
            min = arr[i];
            minIndex = i;
        } 
        if(m[arr[i]]==true && arr[i]!=INT_MAX){
            min = arr[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void getWidth(int w[][3],int elem[],int arr[]){
    for(int i=0;i<n;i++){
        int element = elem[arr[i]];
        if(element >= 10 && element < 17)
            element /= 2;
        else if(element >= 17 && element < 300)
            element /= 3;
        else if (element >= 300 && element <=500)
            element /= 6;
        else if(element > 500 && element < 9000)
            element /= 100;
        else if (element >= 9000 && element <= 90000)
            element /= 1000;
        else if (element > 90000){
            cout<<"Your System may get's hang !!"<<endl;
            exit(0);
        }
        int w1,w2,w3;
        if(element==0){
            w1 = 3;
            w2 = 2; 
            w3 = 1; 
        }else if(element>0 && element <= 10){
            w1=(3*element);
            w2=(2*element);
            w3=(1*element);
        }else{
            w1=4*(element/3);
            w2=2*(element/3);
            w3=2*(element/3);
        }
        w[i][0] = w1;
        w[i][1] = w2;
        w[i][2] = w3;
    }
}    

void printLine1(int w[][3],int &i, int &manip,vector<bool> delta,bool &flag,bool *newLine){
    if(i==manip){
        return;
    }
    if(delta[i]){
        cout<<setfill('-')<<setw(3)<<'+';
        flag=true;
    }else{
        if(flag){
            i--;
            manip--;
            flag=false;
        }
        if(newLine[i]){
            return;
        } else {
        cout<<setfill('-')<<setw(w[i][0])<<'+';
        }
    }
    i++;
    printLine1(w,i,manip,delta,flag,newLine);
}

void printLine2(int w[][3],string pname[],int &i,int &manip,vector<bool> delta,bool &flag,bool *newLine){
    if(i==manip){
        return;
    }
    if(delta[i]){
        cout<<right<<setfill(' ')<<setw(3)<<"\u0394"<<right<<setfill(' ')<<setw(1)<<"|";
        flag=true;
        manip++;
    } else {
        if(flag){
            i--;
            manip--;
            flag=false;
        }
        if(newLine[i]){ 
            return;
        }else{ 
            cout<<right<<setfill(' ')<<setw(w[i][1])<< pname[i] <<right<<setfill(' ')<<setw(w[i][2])<<"|";
        }
    }
    i++;
    printLine2(w,pname,i,manip,delta,flag,newLine);
}

void printLine3(int w[][3], int &i, int &manip,vector<bool> delta,bool &flag,bool *newLine){
    if(i==manip){
        return;
    }
    if(delta[i]){
        cout<<setfill('-')<<setw(3)<<'+';
        flag=true;
        manip++;
    }else{
        if(flag){
            i--;
            manip--;
            flag=false;
        }
        if(newLine[i]){
            return;
        }else {
        cout<<setfill('-')<<setw(w[i][0])<<'+';
        }
    }
    i+=1;
    printLine3(w,i,manip,delta,flag,newLine);
}

void printLine4(int w[][3], vector<int> gchart,int &i,int &manip,vector<bool> delta,bool &flag,bool *newLine){
    if(i==manip){
        return;
    }
    if(delta[i]){
        cout<<setfill(' ')<<setw(3)<<gchart[i+1];
        flag = true;
        manip++;
    } else {
            if(newLine[i]){
                return;
            } else {
        if(flag){
            cout<<setfill(' ')<<setw(w[i-1][0])<<gchart[i+1];
        } else {
            cout<<setfill(' ')<<setw(w[i][0])<<gchart[i+1];
        }
        }
    }
    i+=1;
    printLine4(w,gchart,i,manip,delta,flag,newLine);
}

void printLines(int w[][3], vector<int> gchart, string pname[],int &k, int manip,vector<bool> delta,bool *newLine){
    bool flag=false;
    cout<<'+';
    bool changed = false;
    if(newLine[k]){
        changed = true;
        newLine[k]=false;
    }
    if(newLine[k]){
        k=0;
    }
    int beforeK = k;
    printLine1(w,k,manip,delta,flag,newLine);
    cout<<endl;
    if(!newLine[k-1] && changed){
        k=beforeK;
    } else {
        k=0;
    }
    cout<<'|';
    flag=false;
    printLine2(w,pname,k,manip,delta,flag,newLine);
    
    if(!newLine[k-1] && changed){
        k=beforeK;
    } else {
        k=0;
    }
    cout<<endl;
    cout<<'+';
    flag=false;
    printLine3(w,k,manip,delta,flag,newLine);
    if(!newLine[k-1] && changed){
        k=beforeK;
    } else {
        k=0;
    }
    cout<<endl;
    cout<<gchart[k];
    flag=false;
    printLine4(w,gchart,k,manip,delta,flag,newLine);
    cout<<endl;
}

void printGanttChart(int arr[],int elem[],int bt[], string pname[], vector<int> gchart,int manip,vector<bool> delta){
    int w[n][3];
    getWidth(w,bt,arr);
    bool newLine[gchart.size()] = {false};
    int k=0;
    int sum=0;
    for(int i=0;i<manip;i++){
        sum+=w[i][0];
        if(sum>=50){
            newLine[i+1]=true;
            sum=0;
        }
    }
    cout<<"GANTT CHART :"<<endl;
    while(k!=manip){
        printLines(w,gchart,pname,k,manip,delta,newLine); 
    }
}

void getCalc(vector<Process> P){
    float n = P.size();
    float avgtat=0.0,avgwt=0.0;
    for(int i=0;i<n;i++){
        avgtat += P[i].ft - P[i].at;
        avgwt += P[i].ft - P[i].bt - P[i].at;
    }
    avgtat /= n;
    avgwt /= n;
    cout<<"Average Turn Around Time : "<<avgtat<<" ms."<<endl;
    cout<<"Average Waiting Time : "<<avgwt<<" ms."<<endl;
}

int main() {
    cout<<"+----------------------------+"<<endl;
    cout<<"  Enter no. of process(s) : ";
    cin>>n;
    cout<<"+----------------------------+"<<endl;
    if(n<=0){
        cout<<"Please enter positive integer !!";
        exit(0);
    }
    vector<Process> P;
    int at[n];
    int bt[n];
    for(int i=0;i<n;i++){
        cout<<"  Enter arrival time of P"<<i+1<<" : ";
        cin>>at[i];
        if(at[i]<0){
            cout<<"Please enter positive arrival time !!";
            exit(0);
        }
        cout<<"  Enter burst time of P"<<i+1<<" : ";
        cin>>bt[i];
        if(bt[i]<0){
            cout<<"Please enter positive burst time !!";
            exit(0);
        }
        cout<<"+----------------------------+"<<endl;
        Process p(at[i],bt[i]);
        P.push_back(p);
    }
    int zero[n] = {0};
    map<int,bool> m;
    string pname[n];
    int arr[n];
    int elem[n];
    set<int> s;
    for(int i=0;i<n;i++){
        s.insert(at[i]);
    }
    bool flag;
    if(s.size()==1){
        flag = true;
    }
    for(int i=0;i<n;i++){
        int index;
        if(flag){
            index = i;
        } else {
            index = getSmallest(at,m);
        }
        arr[i] = index;
        elem[i] = at[index];
        m[elem[i]] = true;
        pname[i] = "P" + to_string(index+1);
        if(m[at[index]]==true){
            at[index]=INT_MAX;
        }
    }
    vector<int> gchart;

    if(elem[0]!=0)
        gchart.push_back(elem[0]);
    else
        gchart.push_back(0);
    
    int k = 0;
    vector<bool> delta;

    for(int i=1;i<=n;i++){
        gchart.push_back(0);
        gchart[gchart.size()-1] = gchart[gchart.size()-2];
        if(gchart[gchart.size()-1]!=0 && gchart[gchart.size()-1]<elem[k]){
            int j = elem[k]-gchart[gchart.size()-1];
            while(j>0){
                gchart[gchart.size()-1] ++;
                j--;
            }
            gchart.push_back(gchart[gchart.size()-1]);
            delta.push_back(true);
        } 
        
        gchart[gchart.size()-1] += bt[arr[k++]];
        delta.push_back(false);
        P[arr[k-1]].ft = gchart[gchart.size()-1];
        printTable(P);
        printGanttChart(arr,elem,bt,pname,gchart,gchart.size()-1,delta);
    }
    getCalc(P);
    return 0;
}
