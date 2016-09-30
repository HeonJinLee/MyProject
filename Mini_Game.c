#include <iostream> // 화면크기 100x25    폰트 래스터 12x27
#include <string>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <CONIO.H>

#pragma warning(disable : 4996)

using namespace std;
int life = 3, win = 0;   // life - 전체 판수   win - 전체 이긴 횟수
char name[100];          // name - 사용자 이름

void Loading()   // 로딩화면
{
	system("cls");

	for (int i = 0; i < 8; i++) {
		cout << "\n\n\t";
		cout << "※로딩중에 키를 입력할 경우 게임이 종료될 수 있습니다.※\n\n\t";
		cout << "※플레이어의 부주의로 인해 게임이 종료될 경우에는\n\n";
		cout << "\t보상을 해드릴 수 없습니다.※\n\n\t";
		cout << "로딩중 입니다....\n\n\t";
		for (int j = 0; j <= i; j++) cout << "■";
		for (int k = 7; k >= i; k--) cout << "□";
		Sleep(300);
		system("cls");
	}
}

void Loading2() // 강화시 로딩화면
{
	system("cls");

	for(int i=0; i<6; i++) {
		cout << "\n\n\t";
		cout << "※강화중에 키를 입력할 경우 게임이 종료될 수 있습니다.※\n\n\t";
		cout << "※플레이어의 부주의로 인해 게임이 종료될 경우에는\n\n";
		cout << "\t보상을 해드릴 수 없습니다.※\n\n\n\t";
		cout << "강화중 입니다....\n\n\t";
		for(int j=0; j<=i; j++) cout << "■";
		for(int k=4; k>=i; k--) cout << "□";
		Sleep(700);
		system("cls");
	}
	system("cls");
}

void Loading3() // 홀짝 결과 출력시 로딩화면
{
	system("cls");

	for(int i=0; i<6; i++) {
		cout << "\n\n\n\t";
		cout << "※로딩중에 키를 입력할 경우 게임이 종료될 수 있습니다.※\n\n\t";
		cout << "※플레이어의 부주의로 인해 게임이 종료될 경우에는\n\n";
		cout << "\t보상을 해드릴 수 없습니다.※\n\n\n\t";
		cout << "결과를 출력하고 있습니다....\n\n\t";
		for(int j=0; j<=i; j++) cout << "■";
		for(int k=4; k>=i; k--) cout << "□";
		Sleep(700);
		system("cls");
	}
	system("cls");
}

void Start()   // 시작 시 사용자 등록
{
	cout << "\n\n\n\t사이버보안학과 학술제에 온 것을 환영합니다";
	getchar();
	getchar();
	system("cls");
	while (1)
	{
		system("cls");
		cout << "\n\n\n\t아 .. 근데 자네 이름이 뭔가 ... ?\n";
		cout << "\t이름 >>";
		cin.getline(name, 100);
		
		if ( !(name[0] == '\0' || name[0] == ' ') )
		{
			break;
		}
	}
	cout << "\n\t이름이 참 이쁘구만... 핡핡";
	getchar(); getchar();
	system("cls");
	cout << "\n\n\n\t" << name << " 혹시 ... 게임 좋아하나...?\n";
	getchar();
	cout << "\n\n\t대답이 어느쪽이든 상관없엉 이미 게임은 시작되었거든ㅋ\n";
	getchar();
	cout << "\n\n\t어서와 ~ 요딴건 처음이지 ?\n\n";
	getchar();
	system("cls");
}

void setting()    // 맨처음 주의사항
{
	cout << "\n\n\t간단히 설명해 주겠네. \n";
	cout << "\n\t이 설명은 한번 밖에 나오지 않으니 잘 읽고 게임을 해주시게나..\n";
	getchar();
	cout << "\n\t 1. 게임은 1000원에 3판임. \n";
	cout << "\n\t 2. 0번 승리하면 !  000원 드림 ! (1000 잃음)\n";
	cout << "\n\t 3. 1판 승리하면 !  500원 드림 ! ( 500 잃음)\n";
	cout << "\n\t 4. 2판 승리하면 ! 1500원 드림 ! ( 500 얻음)\n";
	cout << "\n\t 5. 3판 승리하면 ! 2000원 드림 ! (1000 얻음)\n";
	cout << "\n\t 6. 게임이 모두 끝났을 시 뒤에 ★임원★ 을 불러 확인을 해야됨. \n";
	cout << "\n\t 7. 잘못 입력해서 프로그램에 이상이 생길 경우 보상 해드릴수 없음. \n";
	cout << "\n\t 8. 구라치다 걸리면 중간고사 폭풍설사. ^^* \n\n";

	cout << "\n\t ※ 주의 ! 확인이 되지 않으면 게임은 패배처리가 됩니다. ※\n";
	cout << "\n\t ※ 주의 ! 확인이 되지 않으면 게임은 패배처리가 됩니다. ※\n";
	cout << "\n\t ※ 주의 ! 확인이 되지 않으면 게임은 패배처리가 됩니다. ※\n";

	getchar(); getchar();
	system("cls");
}

void Game()    // 게임 고르는 창
{
	cout << "\n\n\t" << name << " 자네는 지금 " << 3 - life << "판을 하였고 \n";
	cout << "\n\n\t" << name << " 자네는 지금 " << life << "판이 남았고 \n";
	cout << "\n\n\t" << name << " 자네는 지금 " << win << " 판을 이겼구만 \n";
	cout << "\n\n\t" << name << " 잘 왔네 게임중 하나를 골라 보시게나 \n\n";
	cout << "\t┌───────────────────────────┐\n";
	cout << "\t│\t1.  개 쉬워요 홀짝 게임\t\t\t\t│\n";
	cout << "\t│\t2.  인생 역전 인생 강화\t\t\t\t│\n";
	cout << "\t│\t3.  인생 한방 복권 게임\t\t\t\t│\n";
	cout << "\t│\t4.  찍신 강림 주사위 게임\t\t\t│\n";
	cout << "\t│\t5.  한국인의 묵찌빠 맞추기\t\t\t│\n";
	cout << "\t└───────────────────────────┘\n";
}

void ghfWkr()    // 홀짝 게임
{
	int num, count = 0, mwin = 0, mlose = 0; // int - 홀/짝 변수   count - 홀짝게임 판수   mwin - 미니게임 승수     mlose - 미니게임 패수   
	char i;
	srand(time(NULL));

	system("cls");
	cout << "\n\n\t개 쉬워요 홀짝 게임에 온 걸 환영하네 " << name << "\n";
	cout << "\n\t게임의 룰을 설명하지 .. \n\n\n";
	cout << "\n\t★ 게임은 총 3판\n";
	cout << "\n\t★ 홀 / 짝을 선택한다.\n";
	cout << "\n\t★ 맞춘다.\n";
	cout << "\n\t★ 2 번만 맞추면 당신의 승리.\n";
	cout << "\n\t★ 게임을 파.괘.한.다.\n";
	cout << "\n\t★    R U READY?";
	getchar(); getchar();
	system("cls");

	while (count != 3)
	{
		cout << "\n\n\t 1. 당연히 홀이지 멍청한 녀석\n";
		cout << "\n\t 2. 뭔솔? 당연히 짝이지  \n\n";
		cout << "\n\t당신의 선택은 ?? ";
		cin >> i;
		if (i == '1' || i == '2')
		{
			Loading3();

			if (i == '1') num = 1;
			else if (i == '2') num = 0;

			if (rand() % 2 == num)
			{
				cout << "\n\n\n\t정답\n";
				cout << "\n\n\n\t화면을 넘기시려면 Enter키를 눌러주세요.";
				getchar(); getchar();
				system("cls");
				count++;
				mwin++;
			}
			else {
				cout << "\n\n\tㅋㅋㅋㅋㅋㅋㅋㅋ아닌데? 틀렸는데? 아닌뎈ㅋㅋㅋㅋㅋㅋ아닌데? 틀렸는데? 아닌뎈ㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋ";
				cout << "ㅋㅋㅋㅋ아닌데? 틀렸는데? 아닌뎈ㅋㅋㅋㅋㅋㅋㅋㅋ아닌데? 틀렸는데? 아닌뎈ㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋ";
				cout << "ㅋㅋㅋㅋㅋㅋㅋㅋ아닌데? 틀렸는데? 아닌뎈ㅋㅋㅋㅋㅋㅋㅋㅋ아닌데? 틀렸는데? 아닌뎈ㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋ";
				cout << "ㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋ아닌데? 틀렸는데? 아닌뎈ㅋㅋㅋㅋㅋㅋ아닌데? 틀렸는데? 아닌뎈ㅋㅋㅋㅋㅋㅋㅋㅋㅋ";
				cout << "ㅋㅋㅋㅋㅋㅋㅋㅋ아닌데? 틀렸는데? 아닌뎈ㅋㅋㅋㅋㅋㅋㅋㅋ아닌데? 틀렸는데? 아닌뎈ㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋ";
				cout << "ㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋ아닌데? 틀렸는데? 아닌뎈ㅋㅋㅋㅋㅋㅋ아닌데? 틀렸는데? 아닌뎈ㅋㅋㅋㅋㅋㅋㅋㅋㅋ";
				cout << "ㅋㅋㅋㅋ아닌데? 틀렸는데? 아닌뎈ㅋㅋㅋㅋㅋㅋㅋㅋ아닌데? 틀렸는데? 아닌뎈ㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋ";
				cout << "ㅋㅋㅋㅋㅋㅋㅋㅋ아닌데? 틀렸는데? 아닌뎈ㅋㅋㅋㅋㅋㅋㅋㅋ아닌데? 틀렸는데? 아닌뎈ㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋ";
				cout << "\n\n\n\t화면을 넘기시려면 Enter키를 눌러주세요.";
				getchar(); getchar();
				system("cls");
				count++;
			}
		}
		else {
			cout << "\t그걸 치라고 만든 키보드가 아닐텐데 -_-^??";
			getchar(); getchar();
			system("cls");
		}
	}
	if (mwin >= 2) {
		cout << "\n\n\t총 " << mwin << "번이나 이겼군... 너의 승리다 닝겐..\n\n";
		cout << "\n\t화면을 넘기시려면 Enter키를 눌러주세요.";
		getchar();
		getchar();
		system("cls");
		win++;
	}
	else{
		cout << "\n\n\t총 " << mwin << "번 이겼군... 어리석은 닝겐이여.. 이번 게임은 너의 패.배. 후훗\n\n";
		cout << "\n\t화면을 넘기시려면 Enter키를 눌러주세요.";
		getchar();
		getchar();
		system("cls");
		mlose++;
	}
}

void Ending()    // 게임종료후 안내
{
	int won[4] = { 0, 500, 1500, 2000 };                        //승리당 배팅 금액
	cout << "\n\n\t모든 게임이 종료되었습니다.\n";
	cout << "\n\t  +++++++++++ 최종 결과 +++++++++++ \n";
	cout << "\n\t\t     3전 " << win << "승 " << 3 - win << "패\n";
	cout << "\n\t\t   " << won[win] << " 받아가세영ㅋ\n";
	cout << "\n\t  +++++++++++++++++++++++++++++++++\n";
	cout << "\n\t게임에 참여해 주셔서 감사합니다.... \n";
	cout << "\n\t억울하시다구요 ? 게임이 이상하다구요 ? \n"; getchar();
	cout << "\n\t그럼 한판 더 하세요 ... ㅋ \n\n";
	cout << "\n\t임원진을 불러 확인 후 돈을 받아가세요 !!\n";
	cout << "\n\t확인이 불가능 할 경우 돈을 돌려드리지 않습니다 !!\n";
	getchar(); getchar(); getchar(); getchar();
}

void Secret(char str[])    // 비밀번호 암호화
{
	int ch, i = 0; // ch - 한글자씩 읽음  i - 자리수 포인터
	cout << "\n\n\n\t비밀번호 : ";
	do
	{
		ch = getch();
		if (ch == 8)
		{
			if (i != 0)
			{
				printf("\b");
				fputs(" ", stdout);
				printf("\b");

				if (i > 0)
					i--;
			}
		}
		else {
			if (ch != '\n' && ch != (char)13) {
				str[i++] = ch;
				printf("*");
			}
		}
	} while ((ch != '\n' && ch != (char)13) && i < 99);
	str[i] = '\0';
}

void Kanghwa() // 강화게임
{
	int i, s, h; // i - 강화한 숫자   s - 강화 입력   h - 확률
	char sarm[16][20]={"시궁창 노숙자", "서울역 노숙자", "우울한 실업자", "그저그런 백수", "평범한 인간", "평범한 회사원", "중산층 젊은이", "로또2등 당첨", "성공한 인생", "강남빌딩 주인", "중소기업 CEO", "대기업 회장님", "대통령", "빌 게이츠", "억수르", "우주정복"};

	i=0;
	srand(time(NULL));

	system("cls");
	cout << "\n\n\t인생 역전 인생 강화 게임에 온 걸 환영하네 " << name << "\n";
	cout << "\n\t게임의 룰을 설명하지 .. \n\n\n";
	cout << "\n\t★ 강화 / 울트라 슈퍼 강화를 한다.\n";
	cout << "\n\t★ 울트라 슈퍼 강화는 +2만큼 강화한다.\n";
	cout << "\n\t★ 성공 / 실패 한다.\n";
	cout << "\n\t★ +8강을 한다면 당신의 승리.\n";
	cout << "\n\t★ 게임을 파.괘.한.다.\n";
	cout << "\n\t★    R U READY?";
	getchar();
	getchar();
	system("cls");

	i=0;
	while(i!=16) {
		cout << "\n\n\t┌─────────────────────────────┐\n";
		cout << "\t│  +" << i << " " << sarm[i] << "-> +" << i+1 << " " << sarm[i+1] << "			    │\n";
		cout << "\t│  강화하시겠습니까? (성공확률 : " << 100-i*5 << "%)			    │\n";
		cout << "\t│  1: 강화  2: 울트라 슈퍼 강화(성공확률 : " << (100-i*5)-20 << "%)	    │\n";
		cout << "\t└─────────────────────────────┘\n";
		cout << "\n\t  입력 >> ";
		cin >> s;

		if(s==1) {
			Loading2();
			h=rand()%100+1;
			if(0<=h && h<=100-i*5) 
			{ 
				cout << "\n\n\t★★강화 성공!!★★\n"; 
				Sleep(1000); 
				system("cls"); 
				i++; 
			}
			else
			{ 
				cout << "\n\n\t☆☆강화 실패!!☆☆\n\n"; 
				if(i>=8) { cout << "\t" << sarm[i] << "에 성공하다니.... 너의 승리다 닝겐..\n\n"; win++; }
				else cout <<"\t" << sarm[i] << "?? 풉.. 어리석은 닝겐이여.. 이번 게임은 너의 패.배. 후훗\n\n";
				cout << "\n\t화면을 넘기시려면 Enter키를 눌러주세요.";
				getchar(); 
				getchar();
				system("cls"); 
				return ; 
			}
		}
		else if(s==2)
		{
			Loading2();
			h=rand()%100+1;
			if(0<=h && h<=(100-i*5)-20) 
			{ 
				cout << "\n\n\t★★강화 성공!!★★\n"; 
				Sleep(1000); 
				system("cls"); 
				i+=2; 
			}
			else
			{ 
				cout << "\n\n\t☆☆강화 실패!!☆☆\n\n"; 
				if(i>=8) { cout << "\t" << sarm[i] << "에 성공하다니.... 너의 승리다 닝겐..\n\n"; win++; }
				else cout <<"\t" << sarm[i] << "?? 풉.. 어리석은 닝겐이여.. 이번 게임은 너의 패.배. 후훗\n\n";
				cout << "\n\t화면을 넘기시려면 Enter키를 눌러주세요.";
				getchar(); 
				getchar();
				system("cls"); 
				return ; 
			}
		}
		else {
			cout << "\t그걸 치라고 만든 키보드가 아닐텐데 -_-^?? \n";	
			getchar();
			getchar();
			system("cls");
		}
		if(i==17) {
			cout << "\t" << sarm[i] << "을 성공하다니.... 너의 승리다 닝겐..\n\n";
			cout << "\t화면을 넘기시려면 Enter키를 눌러주세요.";
			win++;
			getchar();
			getchar();
			system("cls"); 
			return ; 
		}
	}
}

void qhrrnjs() // 복권 게임
{
	int i; // i - 확률

	srand(time(NULL));

	system("cls");
	cout << "\n\n\t인생 한방 복권 게임에 온 걸 환영하네 " << name << "\n";
	cout << "\n\t게임의 룰을 설명하지 .. \n\n\n";
	cout << "\n\t★ 이 게임은 한판에 모든걸 걸지\n";
	cout << "\n\t★ 자신의 운을 믿는다.\n";
	cout << "\n\t★ 끗 ! \n";
	cout << "\n\t★ 당첨된다면 당신의 승리.\n";
	cout << "\n\t★ 게임을 파.괘.한.다.\n";
	cout << "\n\t★    R U READY?";
	getchar();
	getchar();
	system("cls");

	cout<<"\n\n\n\t ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n";
	cout<<"\t ■                                                                      ■\n";
	cout<<"\t ■                                                                      ■\n";
	cout<<"\t ■          □              □            □□□□□□□    □          ■\n";
	cout<<"\t ■          □              □                        □    □          ■\n";
	cout<<"\t ■          □□□□□□□□□                        □    □          ■\n";
	cout<<"\t ■          □              □                              □          ■\n";
	cout<<"\t ■          □□□□□□□□□           □□□□□□□□   □          ■\n";
	cout<<"\t ■                  □                          □          □          ■\n";
	cout<<"\t ■          □□□□□□□□□                  □    □□□□          ■\n";
	cout<<"\t ■                                        □                □          ■\n";
	cout<<"\t ■          □□□□□□□□□            □                □          ■\n";
	cout<<"\t ■                          □            □                            ■\n";
	cout<<"\t ■                         □             □□□□□□□□□□          ■\n";
	cout<<"\t ■                                                                      ■\n";
	cout<<"\t ■                                                                      ■\n";
	cout<<"\t ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n";

	cout<<"긁겟습니까 ....?\n";
	getchar();
	getchar();

	system("cls");
	cout<<"\n\n\t 엔터 연타시 결과창이 보이지 않습니다 ... \n";
	cout<<"\n\n\n\t ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n"; Sleep(300);
	cout<<"\t ■                                                                      ■\n"; Sleep(300);
	cout<<"\t ■    □□□□□□□□        □                    □□□□□□□□    ■\n"; Sleep(300);
	cout<<"\t ■                  □        □                         □  □         ■\n"; Sleep(300);
	cout<<"\t ■                  □        □                        □    □        ■\n"; Sleep(300);
	cout<<"\t ■                  □        □□□□□□□□         □      □       ■\n"; Sleep(300);
	cout<<"\t ■                                                                      ■\n"; Sleep(300);
	cout<<"\t ■  □□□□□□□□□□    □□□□□□□□□□  □□□□□□□□□□  ■\n"; Sleep(300);
	cout<<"\t ■                                                         □           ■\n"; Sleep(300);
	cout<<"\t ■    □□□□ □□□□       □                      □□□□□□      ■\n"; Sleep(300);
	cout<<"\t ■          □       □       □                     □          □     ■\n"; Sleep(300);
	cout<<"\t ■    □□□□       □       □                    □            □    ■\n"; Sleep(300);
	cout<<"\t ■    □             □       □                     □          □     ■\n"; Sleep(300);
	cout<<"\t ■    □□□□       □       □□□□□□□□        □□□□□□      ■\n"; Sleep(300);
	cout<<"\t ■                                                                      ■\n"; Sleep(300);
	cout<<"\t ■                                                                      ■\n"; Sleep(300);
	cout<<"\t ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n";

	system("cls");

	i = rand()%100;
	if( i >= 0 && i < 55 )
	{
		system("cls");

		cout<<"\n\n\n\t ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n";
		cout<<"\t ■                                                                      ■\n";
		cout<<"\t ■                                □                                    ■\n";
		cout<<"\t ■          □□□□□□□□□    □                                    ■\n";
		cout<<"\t ■                □        □    □          □□□□□□□□          ■\n";
		cout<<"\t ■                □        □    □                        □          ■\n";
		cout<<"\t ■                □   □   □    □□□                    □          ■\n";
		cout<<"\t ■                     □         □          □□□□□□□□          ■\n";
		cout<<"\t ■         □□□□□□□□□□□ □                        □          ■\n";
		cout<<"\t ■                                □                       □           ■\n";
		cout<<"\t ■               □□□□□□□□                         □            ■\n";
		cout<<"\t ■              □              □                      □              ■\n";
		cout<<"\t ■             □                □                                     ■\n";
		cout<<"\t ■              □              □                                      ■\n";
		cout<<"\t ■               □□□□□□□□                                       ■\n";
		cout<<"\t ■                                                                      ■\n";
		cout<<"\t ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n";

		cout<<"\n\n\t한방에 지셧수 ㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋ\n";
		getchar(); getchar();
		system("cls");
	}
	else {
		system("cls");

		cout<<"\n\n\n\t ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n";
		cout<<"\t ■                                                                      ■\n";
		cout<<"\t ■                           □             □□□        □            ■\n";
		cout<<"\t ■          □□□□□□□   □                           □            ■\n";
		cout<<"\t ■          □               □         □□□□□□□    □            ■\n";
		cout<<"\t ■          □               □□□           □          □            ■\n";
		cout<<"\t ■          □               □             □  □    □□□            ■\n";
		cout<<"\t ■          □□□□□□□   □           □      □      □            ■\n";
		cout<<"\t ■                           □         □          □    □            ■\n";
		cout<<"\t ■                                                                      ■\n";
		cout<<"\t ■             □□□□□□□□         □□□□□□□□□□            ■\n";
		cout<<"\t ■            □              □        □                □            ■\n";
		cout<<"\t ■           □                □       □                □            ■\n";
		cout<<"\t ■            □              □        □                □            ■\n";
		cout<<"\t ■             □□□□□□□□         □□□□□□□□□□            ■\n";
		cout<<"\t ■                                                                      ■\n";
		cout<<"\t ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n";
		
		cout<<"\n\n\n\t올ㅋ 당첨잼 ㅇㅇ.... ㅊㅊ \n";

		getchar(); getchar();
		system("cls");

		win ++;
	}
}
void pic(int a)
{
	switch(a) {
		case 1: cout << "\t┌─────┐\n";
				cout << "\t│          │\n";
				cout << "\t│          │\n";
				cout << "\t│    ●    │\n";
				cout << "\t│          │\n";
				cout << "\t│          │\n";
				cout << "\t└─────┘\n";
				break;
		case 2: cout << "\t┌─────┐\n";
				cout << "\t│        ●│\n";
				cout << "\t│          │\n";
				cout << "\t│          │\n";
				cout << "\t│          │\n";
				cout << "\t│●        │\n";
				cout << "\t└─────┘\n";
				break;
		case 3: cout << "\t┌─────┐\n";
				cout << "\t│        ●│\n";
				cout << "\t│          │\n";
				cout << "\t│    ●    │\n";
				cout << "\t│          │\n";
				cout << "\t│●        │\n";
				cout << "\t└─────┘\n";
				break;
		case 4: cout << "\t┌─────┐\n";
				cout << "\t│●      ●│\n";
				cout << "\t│          │\n";
				cout << "\t│          │\n";
				cout << "\t│          │\n";
				cout << "\t│●      ●│\n";
				cout << "\t└─────┘\n";
				break;
		case 5: cout << "\t┌─────┐\n";
				cout << "\t│●      ●│\n";
				cout << "\t│          │\n";
				cout << "\t│    ●    │\n";
				cout << "\t│          │\n";
				cout << "\t│●      ●│\n";
				cout << "\t└─────┘\n";
				break;
		case 6: cout << "\t┌─────┐\n";
				cout << "\t│●      ●│\n";
				cout << "\t│          │\n";
				cout << "\t│●      ●│\n";
				cout << "\t│          │\n";
				cout << "\t│●      ●│\n";
				cout << "\t└─────┘\n";
				break;
	}
}
void wntkdnl()  // 주사위 게임
{
	int i,r1,r2,re; // i - 사용자가 선택값   r1 - 첫번째 주사위   r2 - 두번째 주사위   re - 결과 

	srand(time(NULL));

	system("cls");
	cout << "\n\n\t찍신 강림 주사위 게임에 온 걸 환영하네 " << name << "\n";
	cout << "\n\t게임의 룰을 설명하지 .. \n\n\n";
	cout << "\n\t★ 첫번째 주사에 비하여 두번째 주사위의 수가 어떠한지 맞추는 게임.\n";
	cout << "\n\t★ 이 게임은 한판에 모든걸 걸지\n";
	cout << "\n\t★ 1. 두번째 주사위가 크다 \n";
	cout << "\n\t★ 2. 두번째 주사위와 같다 \n";
	cout << "\n\t★ 3. 두번째 주사위가 작다 \n";
	cout << "\n\t★ 자신의 운을 믿는다.\n";
	cout << "\n\t★ 끗 ! \n";
	cout << "\n\t★ 한판만 승리해도 당신의 승리.\n";
	cout << "\n\t★ 게임을 파.괘.한.다.\n";
	cout << "\n\t★    R U READY?";
	getchar();
	getchar();

	do {
		system("cls");
		cout << "\n\n\t★ 1. 첫번째 주사위에 비하여 두번째 주사위가 크다 \n";
		cout << "\n\t★ 2. 첫번째 주사위에 비하여 두번째 주사위와 같다 \n";
		cout << "\n\t★ 3. 첫번째 주사위에 비하여 두번째 주사위가 작다 \n\n";
		cout << "\n\n\t번호 >> ";
		cin>>i;
	}while(i!=1 && i!=2 && i!=3);

	Loading3();

	r1 = (rand()%6+1);
	r2 = (rand()%6+1);

	if(r1 > r2) { re = 3; }
	else if(r1 == r2) { re = 2; }
	else { re = 1; }

	cout << "\n\n\t 첫번째 주사위\n";
	pic(r1);
	Sleep(1500);
	cout << "\n\n\t두번째 주사위\n";
	pic(r2);

	if( re == i ) { win++; cout << "\n\n\t정답입니다. 핥핥 그대는 찍신 !! 빠밤\n"; }
	else { cout << "\n\n\t 풉 ... 찍신은 무슨 ... ㅋㅋㅋㅋㅋ \n"; }

	getchar(); getchar(); getchar();
	system("cls");
}

void m() // 묵
{
	system("cls");
	cout << "\n\n\t□□□□□□□□□□□□□□□□□□□\n\t□                                  □\n\t□                                  □\n\t□                                  □\n\t□      ■■■■■■■              □\n\t□      ■    ■    ■■■■        □\n\t□      ■    ■    ■    ■        □\n\t□      ■    ■    ■    ■■■■  □\n\t□      ■    ■    ■    ■    ■  □\n\t□      ■■■■■■■    ■    ■  □\n\t□  ■■■          ■    ■    ■  □\n\t□  ■              ■    ■    ■  □\n\t□  ■      ■■■■■■■■    ■  □\n\t□  ■        ■■■        ■■■  □\n\t□  ■          ■■            ■  □\n\t□  ■            ■            ■  □\n\t□  ■■                        ■  □\n\t□    ■■                      ■  □\n\t□      ■■                  ■■  □\n\t□        ■■■■■■■■■■■    □\n\t□                                  □\n\t□□□□□□□□□□□□□□□□□□□\n\n";
	Sleep(50);
}
void J() // 찌
{
	system("cls");
	cout << "\n\n\t□□□□□□□□□□□□□□□□□□□\n\t□      ■■■■     ■■■         □\n\t□      ■    ■    ■    ■        □\n\t□      ■    ■   ■    ■         □\n\t□      ■    ■  ■    ■          □\n\t□      ■    ■ ■    ■           □\n\t□      ■    ■■    ■            □\n\t□      ■    ■    ■■■■        □\n\t□      ■    ■    ■    ■■■■  □\n\t□      ■    ■    ■    ■    ■  □\n\t□      ■■■■■■■    ■    ■  □\n\t□  ■■■          ■    ■    ■  □\n\t□  ■              ■    ■    ■  □\n\t□  ■      ■■■■■■■■    ■  □\n\t□  ■        ■■■        ■■■  □\n\t□  ■          ■■            ■  □\n\t□  ■            ■            ■  □\n\t□  ■■                        ■  □\n\t□    ■■                      ■  □\n\t□      ■■                  ■■  □\n\t□        ■■■■■■■■■■■    □\n\t□□□□□□□□□□□□□□□□□□□\n\n";
	Sleep(50);
}
void b() // 빠
{
	system("cls");
	cout << "\n\n\t□□□□□□□□□□□□□□□□□□□\n\t□            ■■■■■■■        □\n\t□            ■    ■    ■        □\n\t□      ■■■■    ■    ■■■■  □\n\t□      ■    ■    ■    ■    ■  □\n\t□      ■    ■    ■    ■    ■  □\n\t□      ■    ■    ■    ■    ■  □\n\t□      ■    ■    ■    ■    ■  □\n\t□      ■    ■    ■    ■    ■  □\n\t□■■■■                      ■  □\n\t□■    ■                      ■  □\n\t□■    ■    ■■■■■■■    ■  □\n\t□■    ■                      ■  □\n\t□■    ■                      ■  □\n\t□■    ■■                    ■  □\n\t□■      ■■                  ■  □\n\t□■■       ■■               ■  □\n\t□  ■■                        ■  □\n\t□    ■■                    ■■  □\n\t□      ■■                ■■    □\n\t□        ■■■■■■■■■■      □\n\t□□□□□□□□□□□□□□□□□□□\n\n";
	Sleep(50);
}

void rkdnlqkdnlqh()
{
	int i; // i - 사용자가 고른 묵찌빠

	system("cls");
	cout << "\n\n\t한국인의 묵찌빠 게임에 온 걸 환영하네 " << name << "\n";
	cout << "\n\t게임의 룰을 설명하지 .. \n\n\n";
	cout << "\n\t★ 묵찌빠 모르는 한국사람도 있나 !?.\n";
	cout << "\n\t★ 이 게임은 한판에 모든걸 걸지\n";
	cout << "\n\t★ 어떤 것이 나올지 맞추는 게임 ... !! 핥핥 찍으면 다맞음 ㅇㅇ..\n";
	cout << "\n\t★ 1. 남자는 ""묵""이지 -_-+ \n";
	cout << "\n\t★ 2. 대세는 ""가위""임 ㅋㅋ \n";
	cout << "\n\t★ 3. ""빠""는 역시 ""빠""군\n";
	cout << "\n\t★ 끗 ! \n";
	cout << "\n\t★ 한판만 승리해도 당신의 승리.\n";
	cout << "\n\t★ 게임을 파.괘.한.다.\n";
	cout << "\n\t★    R U READY?";
	getchar();
	getchar();
	system("cls");

	cout << "\t▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣\n";
	cout << "\t▣                                                                            ▣\n";
	cout << "\t▣                                                                            ▣\n";
	cout << "\t▣                                                                            ▣\n";
	cout << "\t▣                                                                            ▣\n";
	cout << "\t▣                                                                            ▣\n";
	cout << "\t▣        ■■■■■■■■    ■■■■■■■  ■    ■    ■    ■  ■        ▣\n";
	cout << "\t▣        ■            ■        ■  ■      ■    ■    ■    ■  ■        ▣\n";
	cout << "\t▣        ■            ■        ■  ■      ■    ■    ■    ■  ■        ▣\n";
	cout << "\t▣        ■■■■■■■■        ■  ■      ■    ■    ■    ■  ■        ▣\n";
	cout << "\t▣                              ■  ■  ■    ■    ■■■■■■■  ■■■    ▣\n";
	cout << "\t▣        ■■■■■■■■      ■  ■  ■    ■    ■    ■    ■  ■        ▣\n";
	cout << "\t▣                ■            ■  ■  ■    ■    ■    ■    ■  ■        ▣\n";
	cout << "\t▣        ■■■■■■■■    ■  ■  ■  ■  ■    ■    ■    ■  ■        ▣\n";
	cout << "\t▣                      ■    ■  ■  ■  ■  ■    ■    ■    ■  ■        ▣\n";
	cout << "\t▣                      ■    ■  ■  ■  ■  ■    ■■■■■■■  ■        ▣\n";
	cout << "\t▣                                                                            ▣\n";
	cout << "\t▣                                                                            ▣\n";
	cout << "\t▣                                                                            ▣\n";
	cout << "\t▣                                                                            ▣\n";
	cout << "\t▣                                                                            ▣\n";
	cout << "\t▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣\n";
	cout << "\t                              아무 키나 누르세요.";
	getchar();

	system("cls");

	cout << "\n\t★ 1. 남자는 ""묵""이지 -_-+ \n";
	cout << "\n\t★ 2. 대세는 ""가위""임 ㅋㅋ \n";
	cout << "\n\t★ 3. ""빠""는 역시 ""빠""군..\n";

	cout<<"\t번호 >> ";
	cin>>i;

	srand(time(NULL));

	int r;
	r=rand()%3+1;

	for(int i=0; i<10; i++) {
		for(int j=0; j<3; j++) {
			if( j==0 ) m();
			else if( j==1 ) J();
			else b();
		}
	}

	if( r==1 ) m();
	else if( r==2 ) J();
	else b();

	if(r==i) { cout << "\n\t정답.. Vㅔ리 찍신이잖아 ?";}
	else { cout << "\n\t에휴 ... 찍는 것도 못해 .. "; }

	getchar();
	getchar();
	system("cls");

}

int main()
{
	while (1)
	{
		char str[100];
		char S[100] = "tkatnsdlajdajd";

		while (1) {
			do{
				Secret(str);
				if (strcmp(S, str) == 0) { system("cls"); break; }
				else system("cls");
			}while(strcmp(S, str) !=0 );
			life = 3;
			win = 0;
			Start();
			setting();

			Loading();
			while (life != 0)
			{
				char number;
				int i = 0;

				do {
					fflush(stdin);
					if (i != 0) {
						cout << "\t그걸 치라고 만든 키보드가 아닐텐데 -_-^?? \n";
						Sleep(1500);
						system("cls");
					}
					Game();
					cout << "\t번호 >> ";
					cin >> number;
					i++;
				} while (number != '1' && number != '2' && number != '3' && number != '4' && number != '5');

				switch (number) {
				case '1' :
					life--;
					ghfWkr(); // 홀짝 게임
					break;
				case '2' :
					life--;
					Kanghwa(); // 강화 게임
					break;
				case '3' :
					life--;
					qhrrnjs(); // 복권 게임
					break;
				case '4' :
					life--;
					wntkdnl(); // 주사위 게임
					break;
				case '5' :
					life--;
					rkdnlqkdnlqh(); // 가위바위보 게임
					break;
				}
			}
			Ending();
			while (true){
				Secret(str);
				if (strcmp(S, str) == 0) { system("cls"); break; }
				else { system("cls"); Ending(); continue; }
			}
		}
	}
}