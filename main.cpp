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
        // Chỉ cho rắn rẽ trái/phải hoặc đi thẳng
        if ((Huong==0 && HuongHienTai==2)||(Huong==1 && HuongHienTai==3)||(Huong==2 && HuongHienTai==0)||(Huong==3 && HuongHienTai==1)) {
            HuongHienTai = HuongHienTai;
        } else {
            HuongHienTai = Huong;
        }
        // Di chuyen
        for (int i = DoDai-1; i>0;i--)
            A[i] = A[i-1];
        if (HuongHienTai==0) A[0].x = A[0].x + 1;
        if (HuongHienTai==1) A[0].y = A[0].y + 1;
        if (HuongHienTai==2) A[0].x = A[0].x - 1;
        if (HuongHienTai==3) A[0].y = A[0].y - 1;
    }

    bool KiemnTraTongTuong() {
        // kiểm tra tọa độ của đầu có trùng với tọa độ của tường
        if (A[0].x == MINX || A[0].x == MAXX || A[0].y == MINY || A[0].y == MAXY) {
            return true;
        } else {
            return false;
        }
    }
    bool KiemTraDaAnMoi(Point moi)
    {
        // kiểm tra tọa độ của đầu có trùng với tọa độ của mồi
        return A[0].x == moi.x && A[0].y == moi.y;
    }
    void LonLen () {
        // kiểm tra tọa độ phần từ cuối cùng và phần từ liền kề để biết đuôi rắn đang đi theo hường nào rồi thêm 1 phần tử vào cuối
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
    bool KiemTraDaTongDuoi()
    {
        // kiểm tra tọa độ của đầu có trùng với tọa độ của đuôi
        for (int i=3; i <= DoDai-1; i++) {
            if (A[0].x == A[i].x && A[0].y == A[i].y) {
                return true;
            }
        }
        return false;
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
            rand() % (MAXX - MINX - 2) + MINX + 1,
            rand() % (MAXY - MINY - 2) + MINY + 1
        };
    }
    void XuatHien()
    {
        srand(time(0));
        int x, y ;
        if (DaBiAn) {
            // random tọa độ trong phạm vi chơi
            // đã bị ăn thì lấy tọa độ mới
            x = rand() % (MAXX - MINX -2) + MINX + 1;
            y = rand() % (MAXY - MINY -2) + MINY + 1;
            ViTri = {
                x,
                y,
            };
            DaBiAn= false;
        } else {
            // chưa bị ăn thì lấy tọa độ cũ
            x = ViTri.x;
            y = ViTri.y;
        };

        // Sau khi có tọa độ mồi thì vẽ lên màn hình
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
void HienThiDiem(int Diem){
    gotoxy(25,0);
    cout<<"Score:"<<Diem;
}
int main()
{
    CONRAN r;
    MOI moi;
    int Huong = 0;
    int Diem = 0;
    float TocDo = 300;
    char t;
    bool DaTongTuong = false;
    bool DaAnMoi = false;
    bool DaTongDuoi = false;

    while (1){
        if (kbhit()){
            t = getch();
            if (t=='a') Huong = 2;
            if (t=='w') Huong = 3;
            if (t=='d') Huong = 0;
            if (t=='s') Huong = 1;
        }
        system("cls");
        HienThiDiem(Diem);
        VeKhung();
        moi.XuatHien();
        r.Ve();
        r.DiChuyen(Huong);
        Sleep(TocDo);
        DaTongTuong = r.KiemnTraTongTuong();
        DaAnMoi = r.KiemTraDaAnMoi(moi.ViTri);
        DaTongDuoi = r.KiemTraDaTongDuoi();

        if (DaAnMoi) {
            moi.DaBiAn = true;
            r.LonLen();
            Diem++;
        }

        if (DaTongTuong || DaTongDuoi) {
            system("cls");
            gotoxy(24,0);
            cout<<"Game over!";
            gotoxy(25,1);
            cout<<"Score:"<<Diem;
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
