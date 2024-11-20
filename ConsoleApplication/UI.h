#include <iomanip>
#include <windows.h>
#include <iostream>
#include <conio.h> 
#include <vector> 
#include <string> 

using namespace std;
#pragma once
class UI
{

public: 
    string AdminMenu[10][10][10];
    string GiangvienMenu[10][10][10];
    string SinhvienMenu[10][10][10];

    UI() {
        SetConsoleOutputCP(CP_UTF8);  // Enable Unicode output in console
        //--- MENU CẤP 1
        AdminMenu[0][0][0] = "Thêm/ Xóa/ Sửa Sinh viên";
        AdminMenu[1][0][0] = "Thêm/ Xóa/ Sửa Giảng viên";
        AdminMenu[2][0][0] = "Thêm/ Xóa/ Sửa Lớp học";
        AdminMenu[3][0][0] = "Tạo/ Xóa Tài khoản";
        AdminMenu[4][0][0] = "Đổi Mật khẩu";
        AdminMenu[9][0][0] = "Thoát";

        GiangvienMenu[0][0][0] = "Sửa môn học có thể dạy";
        GiangvienMenu[1][0][0] = "Xem danh sách lớp";//100
        GiangvienMenu[2][0][0] = "Cập nhập điểm số";
        GiangvienMenu[3][0][0] = "Đổi Mật khẩu";
        GiangvienMenu[9][0][0] = "Thoát";

        SinhvienMenu[0][0][0] = "Đăng ký/ Hủy Lớp";
        SinhvienMenu[1][0][0] = "Xem kết quả học tập"; // 100
        SinhvienMenu[2][0][0] = "Đổi Mật khẩu";
        SinhvienMenu[9][0][0] = "Thoát";

        //--- MENU CẤP 2
        AdminMenu[0][0][0] = "Thêm Sinh viên"; //0
        AdminMenu[0][1][0] = "Xóa Sinh viên"; //10
        AdminMenu[0][2][0] = "Sửa Sinh viên";
        AdminMenu[0][9][0] = "Quay lại";

        AdminMenu[1][0][0] = "Thêm Giảng viên";//100
        AdminMenu[1][1][0] = "Xóa Giảng viên";//110
        AdminMenu[1][2][0] = "Sửa Giảng viên";
        AdminMenu[1][9][0] = "Quay lại";

        AdminMenu[2][0][0] = "Thêm Lớp học";//200
        AdminMenu[2][1][0] = "Xóa Lớp học";
        AdminMenu[2][2][0] = "Khóa Lớp học";//220
        AdminMenu[2][9][0] = "Quay lại";

        AdminMenu[3][0][0] = "Tạo tài khoản"; //300
        AdminMenu[3][1][0] = "Xóa tài khoản";
        AdminMenu[3][9][0] = "Quay lại";

        GiangvienMenu[0][0][0] = "Thêm môn"; //0
        GiangvienMenu[0][1][0] = "Xóa môn";//10
        GiangvienMenu[0][9][0] = "Quay lại";

        SinhvienMenu[0][0][0] = "Đăng ký Lớp";//0
        SinhvienMenu[0][1][0] = "Hủy lớp";//10
        SinhvienMenu[0][9][0] = "Quay lại";

        //--- MENU CẤP 3
    }

	void Header() {

        for (int i = 0; i < 100; i++) cout << "=";
        string TitleHeader = "HỆ THỐNG QUẢN LÝ SINH VIÊN";
        cout << "\n" << setw(40) << "" << left << TitleHeader << "\n";
        for (int i = 0; i < 100; i++) cout << "=";
        cout << "\n";
        string members[] = { "Huỳnh Vũ Nhật Linh", "Huỳnh Vũ Nhật Linh", "Huỳnh Vũ Nhật Linh", "Huỳnh Vũ Nhật Linh" };
        for (string m : members) {
            cout << setw(100) << right << m;
            cout << endl;
        }
        for (int i = 0; i < 100; i++) cout << "_";
	}

    void Title(string _input) {
        cout << "\n\n" << setw(40) << "" << left << _input << "\n";

    }

    void Clear(string _title) {
        system("cls");
        Header();
        Title(_title);
    }

    int MenuSelectorbyIndex(string ques, const vector <string> options, string comment) {
        int opt = -1;
        cout << "\n\t" << ques << "\n";
        for (int i = 0; i < options.size(); i++) {
            cout << "\t\t" << i + 1 << ". " << options[i] << "\n";
        }
        cout << "\n" << "\tĐiền lựa chọn tương ứng ";
        if (comment.length() != 0) {
            cout << "(" << comment << ") ";
        }
        
        cout << " : ";
        cin >> opt;
        
        return opt;
    }

    int MenuSelectorbyRoles(int RoleIndex, int code1, int code2, int code3) {
        Clear("XIN CHÀO!!!");
        int opt = -1;
        for (int i = 0; i < 10; i++) {
            if (RoleIndex == 1) cout << "\t\t" << i + 1 << ". " << AdminMenu[code1 == 10 ? i : code1][code2 == 10 ? i : code2][code3 == 10 ? i : code3] << "\n";
            if (RoleIndex == 2) cout << "\t\t" << i + 1 << ". " << GiangvienMenu[code1 == 10 ? i : code1][code2 == 10 ? i : code2][code3 == 10 ? i : code3] << "\n";
            if (RoleIndex == 3) cout << "\t\t" << i + 1 << ". " << SinhvienMenu[code1 == 10 ? i : code1][code2 == 10 ? i : code2][code3 == 10 ? i : code3] << "\n";
        }
        cout << "\n" << "\tChọn chức năng ";
        cin >> opt; opt--;
        if (opt == 9) {
            if (code1 == 10) return -1;
            if (code2 == 10) return MenuSelectorbyRoles(RoleIndex, 10, 0, 0);
            if (code3 == 10) return MenuSelectorbyRoles(RoleIndex, code1, 10, 0);
        }
        if (code1 == 10) return MenuSelectorbyRoles(RoleIndex, opt, 10, 0);
        return code1 * 100 + opt * 10;
        if (code2 == 10) return MenuSelectorbyRoles(RoleIndex, code1, opt, 0);
        if (code3 == 10) return MenuSelectorbyRoles(RoleIndex, code1, code2, opt);
    }

    pair <string, string> LoginForm(int RoleIndex) {

        Clear("ĐĂNG NHẬP!!!" + (RoleIndex == 1) ? "Admin" : (RoleIndex == 2) ? "Giảng viên" : "Sinh viên");

        string username, password = "";
        char input;
        cout << setw(25) << left << "\tTên đăng nhập : "; cin >> username;
        cout << setw(25) << left << "\tMật khẩu : ";
        
        input = _getch();
        while (input != 13 || password == "") {
            /*if (input == '\b' && password != "") {
                cout << "\b";
                cout << "";                
                password += input;
            }
            else if (input != 8) {
                cout << '*';
            }*/            
            password += input;
            if (input != '\b') cout << "*";
            input = _getch();
        }
        cout << endl;
        //cout << password;

        return { username, password };
    }

    pair <string, string> RegisterForm() {

        Clear("TẠO TÀI KHOẢN!!!");

        string username, password = "";
        char input;
        cout << setw(25) << left << "\tTên đăng nhập : "; cin >> username;
        cout << setw(25) << left << "\tMật khẩu : ";

        input = _getch();
        while (input != 13 || password == "") {
            /*if (input == '\b' && password != "") {
                cout << "\b";
                cout << "";
                password += input;
            }
            else if (input != 8) {
                cout << '*';
            }*/
            password += input;
            if (input != '\b') cout << "*";
            input = _getch();
        }
        cout << endl;
        //cout << password;

        return { username, password };
    }

    void TaoSVForm(string& mssv, string& ten, string& dob, string& manganh, int& khoa ) {
        cout << setw(25) << left << "\tMSSV : "; cin >> mssv;
        cin.ignore();
        cout << setw(25) << left << "\tHọ tên : "; getline(cin, ten);
        cout << setw(25) << left << "\tDOB (yyy/mm/dd): "; cin >> dob;
        cout << setw(25) << left << "\tKhóa : "; cin >> khoa;
        cout << setw(25) << left << "\tMã ngành : "; cin >> manganh;
    }
    void TaoGVForm(string& msgv, string& ten, string& dob, string& trinhdo) {
        cout << setw(25) << left << "\tMSGV : "; cin >> msgv;
        cin.ignore();
        cout << setw(25) << left << "\tHọ tên : "; getline(cin, ten);
        cout << setw(25) << left << "\tDOB (yyy/mm/dd): "; cin >> dob;
        cin.ignore();
        cout << setw(25) << left << "\tTrình độ : "; getline(cin, trinhdo);
    }
};

