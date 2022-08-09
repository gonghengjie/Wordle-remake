#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
using namespace std;
const int length=5;
const int cishu=6;
string guesses[100010],answers[100010];
int lasts[128];
int guesscnt,answercnt;
inline int read(){
	int x=0;bool flag=1;char c=getchar();
	while (c<'0'||c>'9'){if (c=='-') flag=0;c=getchar();}
	while (c>='0' && c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return (flag? x:~(x-1));
}
void gotoxy(short x,short y){
    COORD coord={y,x};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void setFontColor(int ForgC,int BackC){
	WORD wColor=((BackC&0x0F)<<4)+(ForgC&0x0F);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),wColor);
}
bool check(string str){
	for (int i=1;i<=guesscnt;i++){
		if (str==guesses[i]) return true;
	}
	return false;
}
int main(){
	system("mode con lines=15 cols=32");
	system("title Wordle by Gong.H.J.");
	for (int i=0;i<128;i++){
		lasts[i]=0;
	}
	cout<<"输入种子 (0 为自动): ";
	int t=read();
	if (t==0) srand(int(time(0)));
	else srand(t);
	setFontColor(15,0);
	ifstream ifs1("Wordlist\\solutions.txt");
	while (getline(ifs1,answers[++answercnt]));
	ifs1.close();
	ifstream ifs2("Wordlist\\guesses.txt");
	while (getline(ifs2,guesses[++guesscnt]));
	ifs2.close();
	gotoxy(0,0);
	cout<<"词库: "<<guesscnt<<" 词, 答案库: "<<answercnt<<" 词.\n";
	string ans=answers[rand()%answercnt+1];
	gotoxy(1,0);
	for (int i=1;i<=length;i++){
		cout<<"#";
	}
	cout<<"\n";
	bool flag=true;
	for (int i=1;i<=cishu;i++){
		for (int k=1;k<=2;k++){
			for (int j=1;j<=13;j++){
				gotoxy(i+k+2,2*j-2);
				if (lasts[(int)'a'+(k-1)*13+(j-1)]==1){
					setFontColor(14,0);
					cout<<char((int)'a'+(k-1)*13+(j-1));
					setFontColor(15,0);
				}
				else if (lasts[(int)'a'+(k-1)*13+(j-1)]==2){
					setFontColor(10,0);
					cout<<char((int)'a'+(k-1)*13+(j-1));
					setFontColor(15,0);
				}
				else if (lasts[(int)'a'+(k-1)*13+(j-1)]==-1){
					setFontColor(12,0);
					cout<<char((int)'a'+(k-1)*13+(j-1));
					setFontColor(15,0);
				}
				else cout<<char((int)'a'+(k-1)*13+(j-1));
			}
		}
		gotoxy(i+1,0);
		string str;
		getline(cin,str);
		gotoxy(i+1,0);
		if (str=="answer"){
			MessageBox(NULL,ans.c_str(),"Hint",MB_OK);
		}
		if (!check(str)){
			cout<<"                                    ";
			i--;continue;
		}
		if (str==ans){
			flag=false;
			setFontColor(10,0);
			cout<<str;
			setFontColor(15,0);
			break;
		}
		for (int j=0;j<length;j++){
			if (str[j]==ans[j]){
				setFontColor(10,0);
				lasts[int(str[j])]=2;
				cout<<str[j];
				setFontColor(15,0);
			}
			else if (ans.find(str[j])==string::npos){
				setFontColor(12,0);
				lasts[int(str[j])]=-1;
				cout<<str[j];
				setFontColor(15,0);
			}
			else{
				setFontColor(14,0);
				lasts[int(str[j])]=1;
				cout<<str[j];
				setFontColor(15,0);
			}
		}
		gotoxy(i+3,0);
		cout<<"                              \n";
		cout<<"                              \n";
	}
	if (flag){
		gotoxy(cishu+3,0);
		cout<<"The answer is ";
		setFontColor(10,0);
		cout<<ans<<"\n                                             ";
		setFontColor(15,0);
	}
	system("pause>nul");
	return 0;
}
