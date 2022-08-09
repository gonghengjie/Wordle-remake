#include<bits/stdc++.h>
using namespace std;
string answers[100010],answers2[100010],str1,str2;
int answercnt,answercnt2;
int main(){
	answercnt=answercnt2=0;
	cout<<" __    __              _ _          ___               _             \n/ / /\\ \\ \\___  _ __ __| | | ___    / __\\ __ __ _  ___| | _____ _ __ \n\\ \\/  \\/ / _ \\| '__/ _` | |/ _ \\  / / | '__/ _` |/ __| |/ / _ \\ '__|\n \\  /\\  / (_) | | | (_| | |  __/ / /__| | | (_| | (__|   <  __/ |   \n  \\/  \\/ \\___/|_|  \\__,_|_|\\___| \\____/_|  \\__,_|\\___|_|\\_\\___|_|   \n";
	cout<<"\n每次请输入你猜的字符串和结果(红为0,黄为1,绿为2):\n";
	ifstream ifs("..\\..\\Wordlist\\solutions.txt");
	while (getline(ifs,answers[++answercnt]));
	ifs.close();
	cout<<answercnt<<" word(s) were found.\n";
	while (true){
		cin>>str1;
		if (str1=="restart"){
			system("cls");
			main();
			return 0;
		}
		cin>>str2;
		answercnt2=0;
		for (int i=1;i<=answercnt;i++){
			for (int j=0;j<5;j++){
				if (str2[j]=='0'){
					if (answers[i].find(str1[j])!=string::npos){
						answers[i]="";
						break;
					}
				}
				else if (str2[j]=='1'){
					if (answers[i].find(str1[j])==string::npos || answers[i][j]==str1[j]){
						answers[i]="";
						break;
					}
				}
				else if (str2[j]=='2'){
					if (answers[i].find(str1[j])==string::npos || answers[i][j]!=str1[j]){
						answers[i]="";
						break;
					}
				}
			}
		}
		for (int i=1;i<=answercnt;i++){
			if (answers[i]!="") answers2[++answercnt2]=answers[i];
		}
		answercnt=answercnt2;
		for (int i=1;i<=answercnt;i++){
			answers[i]=answers2[i];
		}
		ofstream ofs("result.txt");
		for (int i=1;i<=answercnt;i++){
			ofs<<answers[i]<<"\n";
		}
		ofs.close();
		cout<<answercnt<<" word(s) were found.\n";
	}
	return 0;
}
