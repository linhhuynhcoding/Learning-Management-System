#include <conio.h> 
#include <iomanip>
#include <windows.h>
#include <iostream>
#include "DBConnection.h"
#include "UI.h"
#include "LoginService.h"
#include "AdminService.h"
#include "GiangvienService.h"
#include "SinhVienService.h"
#include <vector> 


using namespace std;


const vector <string> Roles = { "Admin", "Giảng viên", "Sinh viên" };



void initMenu() {

}


int main() {
    SetConsoleOutputCP(CP_UTF8);  // Enable Unicode output in console
    //_setmode(_fileno(stdout), _O_U16TEXT);
 /*   _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_WTEXT);*/

    DBConnection* db = new DBConnection();
    UI* myui = new UI();
    LoginService* login = new LoginService(db);
    AdminService* adsv = new AdminService(db);
    GiangvienService* gvsv = new GiangvienService(db);
    SinhVienService* svsv = new SinhVienService(db);
    

    //system("cls");
    while (true) {
        myui->Header();
        myui->Title("ĐĂNG NHẬP TÀI KHOẢN");

        int roleSelection = myui->MenuSelectorbyIndex("Bạn là ....?", Roles, "");
        while (!(roleSelection >= 1 && roleSelection <= 3)) {
            myui->Clear("ĐĂNG NHẬP TÀI KHOẢN");

            roleSelection = myui->MenuSelectorbyIndex("Bạn là ....?", Roles, "");
        }
        pair <string, string> tk = myui->LoginForm(roleSelection);
        if (!login->checkpass(tk.first, tk.second, roleSelection)) {
            system("pause");
            system("cls");
            continue;
        }
        else {
            cout << "\n\tĐĂNG NHẬP THÀNH CÔNG!\t";
            system("pause");
        }

        const string MSSV = tk.first;
        const string MSGV = tk.first;
    home:
        myui->Clear("XIN CHÀO!!!");
        system("pause");
        int code = myui->MenuSelectorbyRoles(roleSelection, 10, 0, 0);
        // Role Admin
        if (roleSelection == 1) { 
            if (code == 300) {
                pair <string, string> tk = myui->RegisterForm();
                adsv->Taotk(tk.first, tk.second);
                system("pause");
                goto home;
            }
            else if (code == 0) {
                string mssv, manganh, ten, dob;
                int khoa;
                myui->Clear("THÊM SINH VIÊN!!!");
                adsv->ManganhTable();
                myui->TaoSVForm(mssv, ten, dob, manganh, khoa);
                adsv->ThemSv(mssv, ten, dob, khoa, manganh);
                system("pause");
                goto home;
            }
            else if (code == 10) {
                string mssv;
                myui->Clear("XÓA SINH VIÊN!!!");
                adsv->SvTable();
                cout << "\tNhập MSSV muốn xóa : ";
                cin >> mssv;
                if (mssv == "quit")
                    goto home;
                adsv->XoaSv(mssv);
                system("pause");
                goto home;
            }
            else if (code == 100) {
                string msgv, trinhdo, ten, dob;
                myui->Clear("THÊM GIẢNG VIÊN!!!");
                adsv->ManganhTable();
                myui->TaoGVForm(msgv, ten, dob, trinhdo);
                adsv->ThemGv(msgv, ten, dob, trinhdo);
                system("pause");
                goto home;
            }
            else if (code == 110) {
                string msgv;
                myui->Clear("XÓA GIẢNG VIÊN!!!");
                adsv->GvTable();
                cout << "\tNhập MSSV muốn xóa : ";
                cin >> msgv;
                if (msgv == "quit")
                    goto home;
                adsv->XoaGv(msgv);
                system("pause");
                goto home;
            }
            else if (code == 200) {
                string malh, mamh, mapg, magv, ngaystart;
                int ca, ngay;
                myui->Clear("MỞ LỚP HỌC!!!");
                adsv->GvMhTable();
                adsv->MamhTable();
                adsv->MaPgTable();
                adsv->LophocTable(0);
                cout << setw(25) << left << "\tMã lớp học : "; cin >> malh;
                if (malh == "quit") goto home;
                cout << setw(25) << left << "\tMã môn học : "; cin >> mamh;
                cout << setw(25) << left << "\tMã phòng : "; cin >> mapg;
                cout << setw(25) << left << "\tMã GV : "; cin >> magv;
                cout << setw(25) << left << "\tCa : "; cin >> ca;
                cout << setw(25) << left << "\tThứ : "; cin >> ngay;
                cout << setw(25) << left << "\tNgày bắt đầu : "; cin >> ngaystart;
                adsv->ThemLophoc(malh, mamh, mapg, magv, ngaystart, ca, ngay);
                system("pause");
                goto home;
            }
            else if (code == 220) {
                string malh;
                myui->Clear("KHÓA LỚP!!");
                adsv->LophocTable(0);
                cout << setw(25) << left << "\tMã lớp học : "; cin >> malh;
                if (malh == "quit") goto home;

                adsv->KhoaLop(malh);
                system("pause");
                goto home;
            }

        }
        // Role GiangVien
        else if (roleSelection == 2) {
            if (code == 0) {
                string mamh, magv;
                int ca, ngay;
                myui->Clear("THÊM MÔN GIẢNG DẠY!!");
                adsv->GvMhTable();
                adsv->MamhTable();

                cout << setw(25) << left << "\tMã môn học : "; cin >> mamh;
                cout << setw(25) << left << "\tMã GV : "; cin >> magv;
                gvsv->ThemMon(mamh, magv);
                system("pause");
                goto home;
            }
            else if (code == 10) {
                string mamh, magv;
                int ca, ngay;
                myui->Clear("XÓA MÔN GIẢNG DẠY!!");
                adsv->GvMhTable();
                adsv->MamhTable();

                cout << setw(25) << left << "\tMã môn học : "; cin >> mamh;
                cout << setw(25) << left << "\tMã GV : "; cin >> magv;
                gvsv->XoaMon(mamh, magv);
                system("pause");
                goto home;
            }
            else if (code == 100) {
                string malh;
                code100:
                myui->Clear("XEM DANH SÁCH LỚP!!");
                gvsv->LopGV(MSGV);
                cout << setw(30) << left << "\tXuất danh sách theo MALOP : "; cin >> malh;
                cout << "\n";
                gvsv->XuatDSL(malh);
                char opt;
                cout << setw(30) << left << "Xuất danh sách lớp khác (Y/N) : "; 
                cin >> opt;
                if (opt == 'Y')
                    goto code100;
                else 
                    goto home;
                system("pause");
            }
        }
        // Role SinhVien
        else if (roleSelection == 3) {
            if (code == 0) {
                myui->Clear("ĐĂNG KÝ LỚP!!!");
                svsv->DSLSVTable(MSSV);
                adsv->MamhTable();
                adsv->LophocTable(0);
                string malh;
                cout << setw(25) << left << "\tMã lớp học : "; cin >> malh;
                if (malh == "quit")
                    goto home;

                svsv->DKL(malh, MSSV);
                system("pause");
                goto home;

            }else if (code == 10) {
                myui->Clear("HỦY LỚP!!!");
                svsv->DSLSVTable(MSSV);
                adsv->MamhTable();
                adsv->LophocTable(0);
                string malh;
                cout << setw(25) << left << "\tMã lớp học : "; cin >> malh;
                if (malh == "quit")
                    goto home;
                svsv->HuyLop(malh, MSSV);
                system("pause");
                goto home;

            }
            else if (code == 100) {
                myui->Clear("KẾT QUẢ HỌC TẬP!!!");
                adsv->MamhTable();
                svsv->KQHT(MSSV);
                system("pause");
                goto home;
            }
        }
        system("cls");
    }


    system("pause");
    return 0;
}
