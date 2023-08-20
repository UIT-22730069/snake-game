#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
using namespace std;
void gotoxy( int column, int line );
struct Point{
    int x,y;
};
class CONRAN{
public:
    struct Point A[100];
    int DoDai;
    int HuongHienTai=0;
    CONRAN(){
        DoDai = 3;
        A[0].x = 12; A[0].y = 10;
        A[1].x = 11; A[1].y = 10;
        A[2].x = 10; A[2].y = 10;
    }
    void Ve(){
        for (int i = 0; i < DoDai; i++){
            gotoxy(A[i].x,A[i].y);
            if (i==0) {
                cout<<"0";
            } else {
                cout<<"X";
            }

        }
    }
    void DiChuyen(int Huong){
        // 0 Di qua phai
        // 1 Di len
        // 2 Di qua trai
        // 3 Di xuong
        if ((Huong==0 && HuongHienTai==2)||(Huong==1 && HuongHienTai==3)||(Huong==2 && HuongHienTai==0)||(Huong==3 && HuongHienTai==1)) {
            HuongHienTai = HuongHienTai;
        } else {
            HuongHienTai = Huong;
        }
        for (int i = DoDai-1; i>0;i--)
            A[i] = A[i-1];
        if (HuongHienTai==0) A[0].x = A[0].x + 1;
        if (HuongHienTai==1) A[0].y = A[0].y + 1;
        if (HuongHienTai==2) A[0].x = A[0].x - 1;
        if (HuongHienTai==3) A[0].y = A[0].y - 1;
    }
};
void VeKhung(){
    for(int i = MINX;i<=MAXX;i++)
    {
        for(int j = MINX;j<MAXY;j++)
        {
            if((i==MINX)|| i==MAXX||j==MINY||j=MAXY)
            gotoxy(i,j);
            printf("+");
        }
    }
}
int main()
{
    // ve khung 
    system("cls");
    VeKhung();
    r.Ve();
    r.DiChuyen(Huong);
    Sleep(300);

    CONRAN r;
    int Huong = 0;
    float TocDo = 300;
    char t;

    while (1){
        if (kbhit()){
            t = getch();
            if (t=='a') Huong = 2;
            if (t=='w') Huong = 3;
            if (t=='d') Huong = 0;
            if (t=='s') Huong = 1;
        }
        system("cls");
        r.Ve();
        r.DiChuyen(Huong);
        Sleep(TocDo);
    }

    return 0;
}


void gotoxy( int column, int line )
  {
  COORD coord;
  coord.X = column;
  coord.Y = line;
  SetConsoleCursorPosition(
    GetStdHandle( STD_OUTPUT_HANDLE ),
    coord
    );
  }
