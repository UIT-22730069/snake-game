#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <ctime>

#define MINX 10
#define MAXX 50
#define MINY 2
#define MAXY 25

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
        A[0].x = 16; A[0].y = 7;
        A[1].x = 15; A[1].y = 7;
        A[2].x = 14; A[2].y = 7;
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

    bool KiemnTraTongTuong() {
        if (A[0].x == MINX || A[0].x == MAXX || A[0].y == MINY || A[0].y == MAXY) {
            return true;
        } else {
            return false;
        }
    }
    bool KiemTraDaAnMoi(Point moi)
    {
        return A[0].x == moi.x && A[0].y == moi.y;
    }
    void LonLen () {
        if (A[DoDai-2].x < A[DoDai-1].x) {
            A[DoDai].x = A[DoDai-1].x + 1;
            A[DoDai].y = A[DoDai-1].y;
        } else if (A[DoDai-2].x > A[DoDai-1].x){
            A[DoDai].x = A[DoDai-1].x - 1;
            A[DoDai].y = A[DoDai-1].y;
        } else {
            if (A[DoDai-2].y < A[DoDai-1].y) {
                A[DoDai].x = A[DoDai-1].x;
                A[DoDai].y = A[DoDai-1].y + 1;
            } else {
                A[DoDai].x = A[DoDai-1].x;
                A[DoDai].y = A[DoDai-1].y - 1;
            }
        }
        DoDai++;
    }
};
class MOI{
public:
    struct Point ViTri;
    bool DaBiAn = false;
    Point XuatViTRi () {
        return ViTri;
    }
    MOI() {
        ViTri = {
            rand() % (MAXX - MINX - 1) + MINX,
            rand() % (MAXY - MINY - 1) + MINY
        };
    }
    void XuatHien()
    {
        srand(time(0));
        int x, y ;
        if (DaBiAn) {
            x = rand() % (MAXX - MINX -1) + MINX;
            y = rand() % (MAXY - MINY -1) + MINY;
            ViTri = {
                x,
                y,
            };
            DaBiAn= false;
        } else {
            x = ViTri.x;
            y = ViTri.y;
        };

        // Sau khi có tọa độ quả táo thì vẽ lên màn hình
        gotoxy(x, y);
        cout << "M";
    }
};

void VeKhung(){
    for(int i = MINX;i <= MAXX;i++)
    {
        for(int j = MINY; j<= MAXY;j++)
        {
            if(i==MINX || i==MAXX || j==MINY ||j ==MAXY)
            {
                gotoxy(i,j);
                cout<<"+";
            }
        }
    }
}
int main()
{
    CONRAN r;
    MOI moi;
    int Huong = 0;
    float TocDo = 300;
    char t;
    bool DaTongTuong = false;
    bool DaAnMoi = false;

    while (1){
        if (kbhit()){
            t = getch();
            if (t=='a') Huong = 2;
            if (t=='w') Huong = 3;
            if (t=='d') Huong = 0;
            if (t=='s') Huong = 1;
        }
        system("cls");
        VeKhung();
        moi.XuatHien();
        r.Ve();
        r.DiChuyen(Huong);
        Sleep(TocDo);
        DaTongTuong = r.KiemnTraTongTuong();
        DaAnMoi = r.KiemTraDaAnMoi(moi.ViTri);

        if (DaAnMoi) {
            moi.DaBiAn = true;
            r.LonLen();
        }

        if (DaTongTuong) {
            system("cls");
            gotoxy(0,0);
            printf("Game over!");
            break;
        }
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
