#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
using namespace std;
string guesses[100010],answers[100010];
int lasts[128];
int guesscnt,answercnt;
struct Player{
	int win,lost,streak[6];
	Player(){this->win=this->lost=0;for (int i=0;i<6;i++) this->streak[i]=0;}
	Player(const Player& p){this->win=p.win;this->lost=p.lost;for (int i=0;i<6;i++) this->streak[i]=p.streak[i];}
	Player(int win,int lost,int s1,int s2,int s3,int s4,int s5,int s6){this->win=win;this->lost=lost;this->streak[0]=s1;this->streak[1]=s2;this->streak[2]=s3;this->streak[3]=s4;this->streak[4]=s5;this->streak[5]=s6;}
	Player(int win,int lost,int s[6]){this->win=win;this->lost=lost;for (int i=0;i<6;i++) this->streak[i]=s[i];}
	~Player(){}
};
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
bool verifyData(string path="save.wr"){
	ifstream ifs(path);
	string str;
	getline(ifs,str);
	ifs.close();
	stringstream s(str);
	int temp,sum;
	s>>sum;if (!s.good()) return false;
	s>>temp;if (!s.good()) return false;
	for (int i=0;i<6;i++){
		s>>temp;sum-=temp;
		if (!s.good()) return false;
	}
	if (sum!=0) return false; 
	return true;
}
Player readData(string path="save.wr"){
	Player p;
	ifstream ifs(path);
	if (!ifs.good()) return p;
	ifs.close();
	if (!verifyData()) return p;
	ifstream ifs2(path);
	ifs2>>p.win>>p.lost>>p.streak[0]>>p.streak[1]>>p.streak[2]>>p.streak[3]>>p.streak[4]>>p.streak[5];
	ifs2.close();
	return p;
}
void saveData(Player player,string path="save.wr"){
	ofstream ofs(path);
	ofs<<player.win<<" "<<player.lost<<" ";
	for (int i=0;i<6;i++){
		ofs<<player.streak[i]<<" ";
	}
	ofs.close();
}
int main(){
	setFontColor(15,0);
	Player player(readData());
	system("mode con lines=15 cols=33");
	system("title Wordle by GHJ");
	for (int i=0;i<128;i++){
		lasts[i]=0;
	}
	cout<<"输入种子 (0 为自动): ";
	int t=read();
	if (t==0) srand(int(time(0)));
	else srand(t);
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
	for (int i=1;i<=5;i++){
		cout<<"#";
	}
	cout<<"\n";
	bool flag=true;
	int i;
	for (i=1;i<=6;i++){
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
		for (int j=0;j<5;j++){
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
		player.lost++;
		gotoxy(9,0);
		cout<<"The answer is ";
		setFontColor(10,0);
		cout<<ans<<"\n                                             ";
		setFontColor(15,0);
	}
	else{
		player.win++;
		player.streak[i-1]++;
	}
	saveData(player);
	system("pause>nul");
	system("mode con lines=20 cols=33");
	system("cls");
	gotoxy(0,0);
	cout<<"截至目前您的 Wordle 战绩:\n";
	cout<<"已胜/负局数:";
	setFontColor(10,0);
	cout<<player.win;
	setFontColor(15,0);
	cout<<"/";
	setFontColor(12,0);
	cout<<player.lost;
	setFontColor(15,0);
	cout<<"\n当前胜率:";
	setFontColor(10,0);
	cout<<round(player.win*1000.0/(player.win+player.lost))/10<<"%";
	for (int i=0;i<6;i++){
		setFontColor(15,0);
		cout<<"\n猜测 "<<i+1<<" 次的局数:";
		setFontColor(10,0);
		cout<<player.streak[i];
	}
	int cntTot=0;
	for (int i=0;i<6;i++) cntTot+=player.streak[i]*(i+1);
	setFontColor(15,0);
	cout<<"\n总平均(保留2位):";
	setFontColor(14,0);
	cout<<round(cntTot*100.0/player.win)/100<<"\n";
	setFontColor(15,0);
	for (int i=1;i<=33;i++) cout<<"-";
	for (int i=1;i<=12;i++) cout<<" ";
	cout<<"\n战绩图表:\n";
	for (int i=0;i<6;i++){
		cout<<" "<<i+1<<" | ";
		for (int j=0;j<int(player.streak[i]*20.0/player.win);j++){
			setFontColor(10,0);
			cout<<"#";
		}
		for (int j=player.streak[i]*20.0/player.win;j<20;j++){
			setFontColor(15,0);
			cout<<" ";
		}
		cout<<"| "<<round(player.streak[i]*1000.0/player.win)/10<<"%\n";
	} 
	system("pause>nul");
	return 0;
}
