// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 终极版.cpp : 定义控制台应用程序的入口点。
#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include<cstring>
using namespace std;
#define N 1000
using namespace std;

static int sum = 0;
int foodnum = 0;

void ShowFoodScore();           /*提前声明管理员查看学生意见反馈函数*/
void WriteScore();              /*学生意见反馈函数*/

typedef struct score            /*定义全局变量和数组*/
{
    char FoodId[20];
    char FoodName[20];
    int socre;
    int socernum;
} foodsocre;

foodsocre FoodMssage[20];

typedef struct node
{
    foodsocre data;
    struct node* next;
} NodeTp;
#define CreateNode(p) p = (NodeTp *)malloc(sizeof(NodeTp));//建立节点的宏
#define DeleteNode(p) free((void *)p);//删除节点的宏

class User                      /*用户类*/
{
private:
    char usename[20] = "";
    char password[20] = "";
public:
    void set();
    void load();
    void Adm_Account();
    void searchfood(int h);
    void searchfood_number(int h);
    void searchfood_name(int h);
    void searchfood(char h);
    void searchfood_number(char h);
    void searchfood_name(char h);
    virtual ~User() {};
};


User u;




struct S_inf                    /*学生资料结构体*/
{
    char number[40];
    char name[40];
    int money;
} members[N];

struct foods                    /*菜品信息结构体*/
{
    int number=0;
    string name;
} foods[N];                     /*结构体对象*/


class manager_use : public User  /*由用户类派生的管理员操作类*/
{
private:
    char ID[20]=" ";
public:
    void Adm_Windows();
    void addfood();
    void deletefood();
    void deletefood_number();
    void deletefood_name();
    void changefood();
    void changefood_number();
    void changefood_name();
    void changefood_price_number();
    void changefood_price_name();
    void setstu();
};
manager_use manager1;           /*管理员操作对象*/


class student_use : public User  /*由用户类派生的学生操作类*/
{
public:
    void save_money(int n);
    void stu_account(int n);
    void readnumber();
    void buy(int n);
};
student_use student1;           /*学生类操作对象*/

/*提前创建信息保存文本*/
void InitialFile()
{
    FILE* fp;
    errno_t err;
    if ((err = fopen_s(&fp,"admin.txt", "a")) == NULL)
    {
        printf("can't open the file use.txt\n");
        exit(0);
    }
    if (fp != NULL)
    {
        fclose(fp);
        fp = NULL;
    }
    
    if ((err = fopen_s(&fp,"menu.txt", "a")) == NULL)
    {
        printf("can't open the file use.txt\n");
        exit(0);
    }
    if (fp != NULL)
    {
        fclose(fp);
        fp = NULL;
    }

    if ((err = fopen_s(&fp,"stu_info.txt", "a")) == NULL)
    {
        printf("can't open the file use.txt\n");
        exit(0);
    }
    if (fp != NULL)
    {
        fclose(fp);
        fp = NULL;
    }

}

/*主菜单*/
void mainmenu()
{
    system("cls");
    int nselete;
    char sTemp[20];
    char errget;
    cout << endl << endl << endl << endl;
    cout << "\t\t\t╭—————【主菜单】——————╮" << endl;
    cout << "\t\t\t*—————************——————* " << endl;
    cout << "\t\t\t*         1 管理者综合系统         * " << endl;
    cout << "\t\t\t*         2 学生综合系  统         * " << endl;
    cout << "\t\t\t*         0 退  出  系  统         * " << endl;
    cout << "\t\t\t*—————************——————* " << endl;
    cout << "\t\t\t╰————————————————╯" << endl;
    cout << endl << endl;
    cout << endl << "\t\t\t请选择数字：";
    cin >> sTemp;
    if (strcmp(sTemp, "1") == 0)
    {
        nselete = 1;
    }
    else if (strcmp(sTemp, "2") == 0)
    {
        nselete = 2;
    }
    else if (strcmp(sTemp, "0") == 0)
    {
        nselete = 0;
    }
    else
    {
        nselete = 88;
    }

    switch (nselete)
    {
    case 1:
        u.Adm_Account();
        break;
    case 2:
        student1.readnumber();
        break;
    case 0:
        exit(0);
        break;
    default:
        cout << "\t\t\t输入错误!请选择0、1、2三个功能键...";
        errget = _getch();
        mainmenu();
        break;
    }
}

/*读取用户名字*/
void readname(char* usename)
{
    cin >> usename;
}

/*读取用户密码*/
void readpassword(char* password)
{
    int k = 0;
    char ch;
    while ((ch = _getch()) != 13)
    {
        if ((ch == '\b'))
        {
            cout << '\b';
            cout << ' ';
            cout << '\b';
            k--;
            continue;
        }
        password[k++] = ch;
        cout << "*";
    }
    password[k] = '\0';
    cout << endl;
}

/*注册新管理员账号*/
void User::set()
{
    int j;
    char errget;
    cout << "\t\t\t请输入注册码:";
    cin >> j;
    if (j == 123)
    {
        cout << "\t\t\t设置用户名：";
        readname(usename);
        cout << "\t\t\t设置密码:";
        readpassword(password);
        ofstream ofile("admin.txt", ios_base::app);
        ofile << usename << endl << password << endl;
        ofile.close();
        cout << "\n\t\t\t设置成功...";
        errget = _getch();
    }
    else
    {
        cout << "\t\t\t注册码错误，无法注册新账号！";
        errget = _getch();
    }
}

/*管理员账户登录*/
void User::load()
{
    char user[20];
    char word[20];
    char errget;
    User uu;
    cout << "\t\t\t请输入用户名:";
    readname(uu.usename);
    cout << "\t\t\t请输入密码:";
    readpassword(uu.password);
    ifstream ifile;
    ifile.open("admin.txt", ios_base::in);
    while (ifile.good())
    {
        ifile.getline(user, 100);
        ifile.getline(word, 100);
        if (strcmp(uu.usename, user) == 0 && strcmp(uu.password, word) == 0)
        {
            cout << "\t\t\t登陆成功(任意键继续)...";
            manager1.Adm_Windows();
            ifile.close();
            errget = _getch();
            return;
        }
    }
    cout << "\t\t\t您的账号或密码错误(任意键继续)...";
    errget = _getch();
    u.Adm_Account();
    ifile.close();
    errget = _getch();
}

/*管理员账户主界面函数*/
void User::Adm_Account()
{
    system("cls");
    int nselete;
    char errget;
    cout << endl << endl << endl << endl;
    cout << "\t\t\t╭————【管理员帐户】—————╮" << endl;
    cout << "\t\t\t*—————************——————*" << endl;
    cout << "\t\t\t*          1.管理员注册            *" << endl;
    cout << "\t\t\t*          2.管理员登陆            *" << endl;
    cout << "\t\t\t*          3.返回主菜单            *" << endl;
    cout << "\t\t\t*          0.退出系  统            *" << endl;
    cout << "\t\t\t*—————************——————* " << endl;
    cout << "\t\t\t╰————————————————╯" << endl;
    do
    {
        fflush(stdin);
        cin.clear();
        cout << "\n\t\t\t输入您要执行操作的序号:";
        cin >> nselete;
    } while (cin.fail());
    cout << endl;
    switch (nselete)
    {
    case 1:
        u.set();
        u.Adm_Account();;
        break;
    case 2:
        u.load();
        break;
    case 3:
        mainmenu();
    case 0:
        cout << "\t\t\t";
        exit(1);
        break;
    default:
        cout << "\t\t\t请选择0、1、2、3四个功能键...";
        errget = _getch();
        u.Adm_Account();
    }

}

/*管理员录入学生函数*/
void manager_use::setstu()
{
    char ch[] = "000";
    system("cls");
    int i = 0;
    cout << endl << endl << endl << endl << endl;
    cout << "\t\t\t╭—————【录入学生信息】—————╮" << endl << endl << endl;
    for (;;)
    {
        cout << "\t\t\t请输学号:";
        cin >> members[i].number;
        if (!strcmp(members[i].number, ch))
        {
            Adm_Windows();
            break;
        }
        cout << endl << "\t\t\t请输入姓名：";
        cin >> members[i].name;
        ofstream ofile("stu_info.txt", ios_base::app);
        ofile << members[i].number << " " << members[i].name << " " << members[i].money << endl;
        ofile.close();
        cout << "\n\t\t\t设置成功...请以'000'结束,如想继续设置请输入学号" << endl;
        members[i].money = 0;
        i++;
    }
    sum = i;
}

/*管理员操作主界面函数*/
void manager_use::Adm_Windows()
{
    system("cls");
    char errget;
    cout << endl << endl << endl << endl;
    cout << "\t\t\t╭—————【管理员窗口】————╮" << endl;
    cout << "\t\t\t*——————************—————*" << endl;
    cout << "\t\t\t*            1 菜 单 查  询        * " << endl;
    cout << "\t\t\t*            2 菜 品 增  加        * " << endl;
    cout << "\t\t\t*            3 菜 品 删  除        * " << endl;
    cout << "\t\t\t*            4 菜 品 修  改        * " << endl;
    cout << "\t\t\t*            5 学生信息录入        * " << endl;
    cout << "\t\t\t*            6 查 看 评  价        * " << endl;
    cout << "\t\t\t*            7 返回 上 一层        * " << endl;
    cout << "\t\t\t*            8 返回 主 菜单        * " << endl;
    cout << "\t\t\t*            0 退 出 系  统        * " << endl;
    cout << "\t\t\t*——————************—————*" << endl;
    cout << "\t\t\t╰————————————————╯" << endl;
    cout << endl << endl;
    cout << "\t\t\t请输入您要选择的数字：";
    int a;
    cin >> a;
    switch (a)
    {
    case 1:
        manager1.searchfood(0);
    case 2:
        manager1.addfood();
    case 3:
        manager1.deletefood();
    case 4:
        manager1.changefood();
    case 5:
        manager1.setstu();
    case 6:
        ShowFoodScore();
    case 7:
        u.Adm_Account();
    case 8:
        mainmenu();
    case 0:
        cout << "\t\t\t";
        exit(1);
    default:
        cout << "\t\t\t请选择0、1、2、3、4、5、6、7、8九个功能键...";
        errget = _getch();
        manager1.Adm_Windows();
        break;
    }
}

/*管理员菜单信息查询子函数（通过菜品编号查询）*/
void User::searchfood_number(int h)
{
    system("cls");
    ifstream f("menu.txt", ios::binary);
    string a;
    int n = 0;
    char errget;
    cout << endl << endl << endl << endl;
    cout << "\t\t\t╭—————【菜单查询】——————╮" << endl;
    cout << "\t\t\t*—————************———————*" << endl;
    cout << "\t\t\t*         **************             *" << endl;
    cout << "\t\t\t*      欢迎来到菜品编号查询系统      *" << endl;
    cout << "\t\t\t*         **************             *" << endl;
    cout << "\t\t\t*—————************———————*" << endl;
    cout << "\t\t\t╰—————————————————╯" << endl;
    cout << endl << endl;
    cout << "\t\t\t请输入你所查询的菜品编号：";
    cin >> a;
    string information[20][3];
    for (int i = 0; i < 20; i++)
    {
        f >> information[i][0] >> information[i][1] >> information[i][2];
        if (a == information[i][0])
        {
            cout << endl << endl << "\t编号" << "\t名称" << "\t价格" << endl;
            cout << "\t" << information[i][0] << "\t" << information[i][1] << "\t" << information[i][2];
            n = 1;
            cout << endl << endl << "\t\t\t查询完成！" << "\n\t\t\t1 返回；   2 继续查询  ";
            int a;
            cin >> a;
            switch (a)
            {
            case 1:
                manager1.searchfood(0);
            case 2:
                manager1.searchfood_number(0);
            default:
                cout << "\t\t\t请选择1、2两个功能键...";
                errget = _getch();
                manager1.searchfood_number(0);
                break;
            }
        }
    }
    if (n == 0)
    {
        cout << "\t\t\t您所查询的菜品不存在！" << "\n\t\t\t1 返回；   2 继续查询        " << endl;
        int a;
        cin >> a;
        switch (a)
        {
        case 1:
            manager1.searchfood(0);
        case 2:
            manager1.searchfood_number(0);
        default:
            cout << "\t\t\t请选择1、2两个功能键...";
            errget = _getch();
            manager1.searchfood_number(0);
            break;
        }
    }
}

/*管理员菜品信息查询子函数（通过菜品名字查询）*/
void User::searchfood_name(int h)
{
    system("cls");
    ifstream f("menu.txt", ios::binary);
    string a;
    int n = 0;
    char errget;
    cout << endl << endl << endl << endl;
    cout << "\t\t\t╭—————【菜单查询】——————╮" << endl;
    cout << "\t\t\t*—————************———————*" << endl;
    cout << "\t\t\t*         **************             *" << endl;
    cout << "\t\t\t*      欢迎来到菜品名称查询系统      *" << endl;
    cout << "\t\t\t*         **************             *" << endl;
    cout << "\t\t\t*—————************———————*" << endl;
    cout << "\t\t\t╰—————————————————╯" << endl;
    cout << endl << endl;
    cout << "\t\t\t请输入你所查询的菜品名称：";
    cin >> a;
    string information[20][3];
    for (int i = 0; i < 20; i++)
    {
        f >> information[i][0] >> information[i][1] >> information[i][2];
        if (a == information[i][1])
        {
            cout << endl << endl << "\t编号" << "\t名称" << "\t价格" << endl;
            cout << "\t" << information[i][0] << "\t" << information[i][1] << "\t" << information[i][2];
            n = 1;
            cout << endl << endl << "\t\t\t查询完成！" << endl << endl << "\n\t\t\t1 返回；   2 继续查询  " << endl;
            int a;
            cin >> a;
            switch (a)
            {
            case 1:
                manager1.searchfood(0);
            case 2:
                manager1.searchfood_name(0);
            default:
                cout << "\t\t\t请选择1、2两个功能键...";
                errget = _getch();
                manager1.searchfood_name(0);
                break;
            }
        }
    }
    if (n == 0)
    {
        cout << "\n\t\t\t您所查询的菜品不存在！" << endl << "\n\t\t\t1 返回；   2 继续查询        " << endl << "\t\t\t";
        int a;
        cin >> a;
        switch (a)
        {
        case 1:
            manager1.searchfood(0);
        case 2:
            manager1.searchfood_name(0);
        default:
            cout << "\t\t\t请选择1、2两个功能键...";
            errget = _getch();
            manager1.searchfood_name(0);
            break;
        }
    }
}

/*管理员菜品信息查询主函数*/
void User::searchfood(int h)
{
    system("cls");
    char errget;
    cout << endl << endl << endl << endl;
    cout << "\t\t\t╭—————【菜单查询】——————╮" << endl;
    cout << "\t\t\t*——————************——————*" << endl;
    cout << "\t\t\t*            1 查询所有菜品          *" << endl;
    cout << "\t\t\t*            2 按 编号 查询          *" << endl;
    cout << "\t\t\t*            3 按 菜名 查询          *" << endl;
    cout << "\t\t\t*            4 返回 上 一层          *" << endl;
    cout << "\t\t\t*            5 返回 主 菜单          *" << endl;
    cout << "\t\t\t*            0 退 出 系  统          *" << endl;
    cout << "\t\t\t*——————************——————*" << endl;
    cout << "\t\t\t╰—————————————————╯" << endl;
    cout << endl << endl;
    cout << "\t\t\t请输入您要选择的数字：";
    int a;
    cin >> a;
    switch (a)
    {
    case 1:
    {
        system("cls");
        ifstream f("menu.txt");
        while (!f.eof())
        {
            char a;
            a = f.get();
            cout << a;
        }
        cout << "\t\t\t查询完成，按任意键返回";
        errget = _getch();
        manager1.searchfood(0);
    }
    case 2:
        manager1.searchfood_number(0);
    case 3:
        manager1.searchfood_name(0);
    case 4:
        manager1.Adm_Windows();
    case 5:
        mainmenu();
    case 0:
        cout << "\t\t\t";
        exit(1);
    default:
        cout << "\t\t\t请选择0、1、2、3、4、5六个功能键...";
        errget = _getch();
        manager1.searchfood(0);
        break;
    }
}

/*菜品信息添加主函数*/
void manager_use::addfood()
{
    system("cls");
    string a, b, c;
    char errget;
    ofstream f("menu.txt", ios::app);
    cout << endl << endl << endl << endl;
    cout << "\t\t\t╭—————【菜品增加】——————╮" << endl;
    cout << "\t\t\t*—————************———————*" << endl;
    cout << "\t\t\t*          **************            *" << endl;
    cout << "\t\t\t*        欢迎来到菜品增加系统        *" << endl;
    cout << "\t\t\t*          **************            *" << endl;
    cout << "\t\t\t*—————************———————*" << endl;
    cout << "\t\t\t╰—————————————————╯" << endl;
    cout << endl << endl;
    cout << "\t\t\t请输入所添加的菜品编号：";
    cin >> a;
    f << endl << a << "        ";
    cout << "\n\t\t\t请输入所添加的菜品名称：";
    cin >> b;
    f << b << "           ";
    cout << "\n\t\t\t请输入所添加的菜品价格：";
    cin >> c;
    f << c << endl;
    cout << "\n\t\t\t添加完成！任意键返回...";
    errget = _getch();
    manager1.Adm_Windows();
}

/*菜品信息删除子函数（通过菜品编号删除）*/
void manager_use::deletefood_number()
{
    system("cls");
    ifstream f("menu.txt", ios::binary);
    string a;
    int n = 0;
    char errget;
    cout << endl << endl << endl << endl;
    cout << "\t\t\t╭—————【菜品删除】——————╮" << endl;
    cout << "\t\t\t*—————************———————*" << endl;
    cout << "\t\t\t*          **************            *" << endl;
    cout << "\t\t\t*      欢迎来到菜品编号删除系统      *" << endl;
    cout << "\t\t\t*          **************            *" << endl;
    cout << "\t\t\t*—————************———————*" << endl;
    cout << "\t\t\t╰—————————————————╯" << endl;
    cout << endl << endl;
    cout << "\t\t\t请输入你所要删除的菜品编号：";
    cin >> a;
    cout << endl << endl << endl << endl;
    cout << "\t\t\t╭————************—————╮                " << endl;
    cout << "\t\t\t*———— ************————— *                 " << endl;
    cout << "\t\t\t*           1 确定               *                " << endl;
    cout << "\t\t\t*           2 取消               *                " << endl;
    cout << "\t\t\t*—————************—————*                " << endl;
    cout << "\t\t\t╰————************—————╯                 " << endl;
    cout << "\t\t\t请选择：";
    int d;
    cin >> d;
    switch (d)
    {
    case 1:
    {
        int m = 0;
        string information[20][3];
        int i;
        for (i = 0; i < 20; i++)
        {
            f >> information[i][0] >> information[i][1] >> information[i][2];
            m++;
            if (a == information[i][0])
            {
                n = 1;
                information[i][0] = "0";
            }
            if (information[i][0] == "") break;
        }
        f.close();
        ofstream g("menu.txt", ios::binary);
        for (i = 0; i < m; i++)
        {
            if (information[i][0] != "0")
            {
                g << information[i][0] << "\t" << information[i][1] << "\t" << information[i][2] << endl;
            }
        }
        g.close();
        if (n == 0)
        {
            cout << "\t\t\t您所要删除的菜品不存在！" << endl << "\t\t\t1 返回；   2 继续删除        ";
            int a;
            cin >> a;
            switch (a)
            {
            case 1:
                manager1.deletefood();
            case 2:
                manager1.deletefood_number();
            default:
                cout << "\t\t\t请选择1、2两个功能键...";
                errget = _getch();
                manager1.deletefood_number();
                break;
            }
        }
        if (n == 1)
        {
            cout << "\t\t\t已删除！任意键返回...";
            errget = _getch();
            manager1.deletefood();
        }
    }
    case 2:
        manager1.deletefood();
    }
}

/*菜品信息删除子函数（通过菜品名称删除）*/
void manager_use::deletefood_name()
{
    system("cls");
    ifstream f("menu.txt", ios::binary);
    string a;
    int n = 0;
    char errget;
    cout << endl << endl << endl << endl;
    cout << "\t\t\t╭—————【菜品删除】——————╮" << endl;
    cout << "\t\t\t*—————************———————*" << endl;
    cout << "\t\t\t*          **************            *" << endl;
    cout << "\t\t\t*      欢迎来到菜品名称删除系统      *" << endl;
    cout << "\t\t\t*          **************            *" << endl;
    cout << "\t\t\t*—————************———————*" << endl;
    cout << "\t\t\t╰—————————————————╯" << endl;
    cout << endl << endl;
    cout << "\t\t\t请输入你所要删除的菜品名称：";
    cin >> a;
    cout << endl << endl;
    cout << "\t\t\t╭————************—————╮                " << endl;
    cout << "\t\t\t*———— ************————— *                 " << endl;
    cout << "\t\t\t*           1 确定               *                " << endl;
    cout << "\t\t\t*           2 取消               *                " << endl;
    cout << "\t\t\t*—————************—————*                " << endl;
    cout << "\t\t\t╰————************—————╯                 " << endl;
    cout << "\n\t\t\t请选择：";
    int d;
    cin >> d;
    switch (d)
    {
    case 1:
    {
        int m = 0;
        string information[20][3];
        int i;
        for (i = 0; i < 20; i++)
        {
            f >> information[i][0] >> information[i][1] >> information[i][2];
            m++;
            if (a == information[i][1])
            {
                n = 1;
                information[i][1] = "0";
            }
            if (information[i][0] == "") break;
        }
        f.close();
        ofstream g("menu.txt", ios::binary);
        for (i = 0; i < m; i++)
        {
            if (information[i][1] != "0") g << information[i][0] << "\t" << information[i][1] << "\t" << information[i][2] << endl;
        }
        f.close();
        if (n == 0)
        {
            cout << "\t\t\t您所要删除的菜品不存在！" << endl << "\t\t\t1 返回；   2 继续删除        ";
            int a;
            cin >> a;
            switch (a)
            {
            case 1:
                manager1.deletefood();
            case 2:
                manager1.deletefood_name();
            }
        }
        if (n == 1)
        {
            cout << "\n\t\t\t已删除！任意键返回...";
            errget = _getch();
            manager1.deletefood();
        }
    }
    case 2:
        manager1.deletefood();
    default:
        cout << "\t\t\t请选择1、2三个功能键...";
        errget = _getch();
        break;
    }
}

/*菜品信息删除主函数*/
void manager_use::deletefood()
{
    system("cls");
    char errget;
    cout << endl << endl << endl << endl << endl;
    cout << endl << endl << endl << endl;
    cout << "\t\t\t╭—————【菜品删除】——————╮" << endl;
    cout << "\t\t\t*—————************———————*" << endl;
    cout << "\t\t\t*         ***************            *" << endl;
    cout << "\t\t\t*        欢迎来到菜品删除系统        *" << endl;
    cout << "\t\t\t*         ***************            *" << endl;
    cout << "\t\t\t*           1.按编号删除             *" << endl;
    cout << "\t\t\t*           2.按菜名删除             *" << endl;
    cout << "\t\t\t*           3.返回上一层             *" << endl;
    cout << "\t\t\t*           4.返回主菜单             *" << endl;
    cout << "\t\t\t*           0.退出系  统             *" << endl;
    cout << "\t\t\t*—————************———————*" << endl;
    cout << "\t\t\t╰—————————————————╯" << endl;
    cout << endl << endl;
    int a;
    cin >> a;
    switch (a)
    {
    case 1:
        manager1.deletefood_number();
    case 2:
        manager1.deletefood_name();
    case 3:
        manager1.Adm_Windows();
    case 4:
        mainmenu();
    case 0:
        cout << "\t\t\t";
        exit(1);
    default:
        cout << "\t\t\t请选择0、1、2、3、4五个功能键...";
        errget = _getch();
        break;
    }
}

/*菜品信息修改子函数（通过菜品编号修改）*/
void manager_use::changefood_number()
{
    system("cls");
    string a, b;
    int n = 0;
    char errget;
    cout << endl << endl << endl << endl;
    cout << "\t\t\t╭—————【菜品编号修改】—————╮" << endl;
    cout << "\t\t\t*——————************———————*" << endl;
    cout << "\t\t\t*          *******************         *" << endl;
    cout << "\t\t\t*        欢迎来到菜品编号修改系统      *" << endl;
    cout << "\t\t\t*          *******************         *" << endl;
    cout << "\t\t\t*——————************———————*" << endl;
    cout << "\t\t\t╰——————————————————╯" << endl;
    cout << endl << endl;
    cout << endl << endl << "\t\t\t请输入你所要修改的菜品编号：";
    cin >> a;
    cout << endl << "\t\t\t请输入您要将编号修改为：";
    cin >> b;
    cout << endl << endl;
    cout << "\t\t\t╭————************—————╮                " << endl;
    cout << "\t\t\t*———— ************————— *                 " << endl;
    cout << "\t\t\t*           1 确定               *                " << endl;
    cout << "\t\t\t*           2 取消               *                " << endl;
    cout << "\t\t\t*—————************—————*                " << endl;
    cout << "\t\t\t╰————************—————╯                 " << endl;
    cout << "\n\t\t\t请选择：";
    int d;
    cin >> d;
    switch (d)
    {
    case 1:
    {
        int m = 0;
        ifstream f("menu.txt", ios::binary);
        string information[20][3];
        int i;
        for (i = 0; i < 20; i++)
        {
            f >> information[i][0] >> information[i][1] >> information[i][2];
            m++;
            if (information[i][0] == "") break;
        }
        f.close();
        for (i = 0; i < m; i++)
        {
            if (a == information[i][0])
            {
                information[i][0] = b;
                n = 1;
            }
        }
        ofstream g("menu.txt", ios::binary);
        for (i = 0; i < m; i++)
        {
            g << information[i][0] << "\t" << information[i][1] << "\t" << information[i][2] << endl;
        }
        if (n == 0)
        {
            cout << "\t\t\t您所要修改的菜品不存在！" << endl << "\t\t\t1 返回；   2 继续修改        ";
            int a;
            cin >> a;
            switch (a)
            {
            case 1:
                manager1.changefood();
            case 2:
                manager1.changefood_number();
            default:
                cout << "\t\t\t请选择1、2三个功能键...";
                errget = _getch();
                break;
            }
        }
        else if (n == 1)
        {
            cout << "\t\t\t已修改！任意键返回...";
            errget = _getch();
            manager1.changefood();
        }
    }
    case 2:
        manager1.changefood();
    default:
        cout << "\t\t\t请选择1、2两个功能键...";
        errget = _getch();
        break;
    }
}

/*菜品信息修改子函数（通过菜品名称修改）*/
void manager_use::changefood_name()
{
    system("cls");
    string a, b;
    int n = 0;
    char errget;
    cout << endl << endl << endl << endl;
    cout << "\t\t\t╭—————【菜品名称修改】—————╮" << endl;
    cout << "\t\t\t*——————************———————*" << endl;
    cout << "\t\t\t*          *******************         *" << endl;
    cout << "\t\t\t*       欢迎来到菜品名称修改系统       *" << endl;
    cout << "\t\t\t*          *******************         *" << endl;
    cout << "\t\t\t*——————************———————*" << endl;
    cout << "\t\t\t╰——————————————————╯" << endl;
    cout << endl << endl;
    cout << "\t\t\t请输入你所要修改的菜品名称：";
    cin >> a;
    cout << endl << "\t\t\t请输入您要将名称修改为：";
    cin >> b;
    cout << endl << endl;
    cout << "\t\t\t╭————************—————╮                " << endl;
    cout << "\t\t\t*———— ************————— *                 " << endl;
    cout << "\t\t\t*           1 确定               *                " << endl;
    cout << "\t\t\t*           2 取消               *                " << endl;
    cout << "\t\t\t*—————************—————*                " << endl;
    cout << "\t\t\t╰————************—————╯                 " << endl;
    cout << "\n\t\t\t请选择：";
    int d;
    cin >> d;
    switch (d)
    {
    case 1:
    {
        int m = 0;
        ifstream f("menu.txt", ios::binary);
        string information[20][3];
        int i;
        for (i = 0; i < 20; i++)
        {
            f >> information[i][0] >> information[i][1] >> information[i][2];
            m++;
            if (information[i][0] == "") break;
        }
        f.close();
        for (i = 0; i < m; i++)
        {
            if (a == information[i][1])
            {
                information[i][1] = b;
                n = 1;
            }
        }
        ofstream g("menu.txt", ios::binary);
        for (i = 0; i < m; i++)
        {
            g << information[i][0] << "\t" << information[i][1] << "\t" << information[i][2] << endl;
        }
        if (n == 0)
        {
            cout << "\n\t\t\t您所要修改的菜品不存在！" << endl << "\t\t\t1 返回；   2 继续修改        ";
            int a;
            cin >> a;
            switch (a)
            {
            case 1:
                manager1.changefood();
            case 2:
                manager1.changefood_name();
            }
        }
        else if (n == 1)
        {
            cout << "\n\t\t\t已修改！任意键返回...";
            errget = _getch();
            manager1.changefood();
        }
    }
    case 2:
        manager1.changefood();
    default:
        cout << "\t\t\t请选择1、2两个功能键...";
        errget = _getch();
        break;
    }
}

/*菜品价格修改函数（通过菜品编号修改）*/
void manager_use::changefood_price_number()
{
    system("cls");
    string a, b;
    int n = 0;
    char errget;
    cout << endl << endl << endl << endl;
    cout << "\t\t\t╭—————【菜品价格修改】—————╮" << endl;
    cout << "\t\t\t*——————************———————*" << endl;
    cout << "\t\t\t*          *******************         *" << endl;
    cout << "\t\t\t*      欢迎来到按菜品编号修改价格系统  *" << endl;
    cout << "\t\t\t*          *******************         *" << endl;
    cout << "\t\t\t*——————************———————*" << endl;
    cout << "\t\t\t╰——————————————————╯" << endl;
    cout << endl << endl;
    cout << "\t\t\t请输入你所要修改的菜品编号：";
    cin >> a;
    cout << endl << "\t\t\t请输入您要将价格修改为：";
    cin >> b;
    cout << endl << endl;
    cout << "\t\t\t╭————************—————╮                " << endl;
    cout << "\t\t\t*———— ************————— *                 " << endl;
    cout << "\t\t\t*           1 确定               *                " << endl;
    cout << "\t\t\t*           2 取消               *                " << endl;
    cout << "\t\t\t*—————************—————*                " << endl;
    cout << "\t\t\t╰————************—————╯                 " << endl;
    cout << "\n\t\t\t请选择：";
    int e;
    cin >> e;
    switch (e)
    {
    case 1:
    {
        int m = 0;
        ifstream f("menu.txt", ios::binary);
        string information[20][3];
        int i;
        for (i = 0; i < 20; i++)
        {
            f >> information[i][0] >> information[i][1] >> information[i][2];
            m++;
            if (information[i][0] == "") break;
        }
        f.close();
        for (i = 0; i < m; i++)
        {
            if (a == information[i][0])
            {
                information[i][2] = b;
                n = 1;
            }
        }
        ofstream g("menu.txt", ios::binary);
        for (i = 0; i < m; i++)
        {
            g << information[i][0] << "\t" << information[i][1] << "\t" << information[i][2] << endl;
        }
        if (n == 0)
        {
            cout << "\n\t\t\t您所要修改的菜品不存在！" << endl << "\t\t\t1 返回；   2 继续修改        ";
            int a;
            cin >> a;
            switch (a)
            {
            case 1:
                manager1.changefood();
            case 2:
                manager1.changefood_price_number();
            }
        }
        else if (n == 1)
        {
            cout << "\n\t\t\t已修改！任意键返回...";
            errget = _getch();
            manager1.changefood();
        }
    }
    case 2:
        manager1.changefood();
    default:
        cout << "\t\t\t请选择1、2两个功能键...";
        errget = _getch();
        break;
    }
}

/*菜品价格修改函数（通过菜品名称修改）*/
void manager_use::changefood_price_name()
{
    system("cls");
    string a, b;
    int n = 0;
    char errget;
    cout << endl << endl << endl << endl;
    cout << "\t\t\t╭—————【菜品价格修改】—————╮" << endl;
    cout << "\t\t\t*——————************———————*" << endl;
    cout << "\t\t\t*          *******************         *" << endl;
    cout << "\t\t\t*      欢迎来到按菜品名称修改价格系统  *" << endl;
    cout << "\t\t\t*          *******************         *" << endl;
    cout << "\t\t\t*——————************———————*" << endl;
    cout << "\t\t\t╰——————————————————╯" << endl;
    cout << endl << endl;
    cout << "\t\t\t请输入你所要修改的菜品名称：";
    cin >> a;
    cout << endl << "\t\t\t请输入您要将价格修改为：";
    cin >> b;
    cout << endl << endl;
    cout << "\t\t\t╭————************—————╮                " << endl;
    cout << "\t\t\t*———— ************————— *                 " << endl;
    cout << "\t\t\t*           1 确定               *                " << endl;
    cout << "\t\t\t*           2 取消               *                " << endl;
    cout << "\t\t\t*—————************—————*                " << endl;
    cout << "\t\t\t╰————************—————╯                 " << endl;
    cout << "\n\t\t\t请选择：";
    int e;
    cin >> e;
    switch (e)
    {
    case 1:
    {
        int m = 0;
        ifstream f("menu.txt", ios::binary);
        string information[20][3];
        int i;
        for (i = 0; i < 20; i++)
        {
            f >> information[i][0] >> information[i][1] >> information[i][2];
            m++;
            if (information[i][0] == "") break;
        }
        f.close();
        for (i = 0; i < m; i++)
        {
            if (a == information[i][1])
            {
                information[i][2] = b;
                n = 1;
            }
        }
        ofstream g("menu.txt", ios::binary);
        for (i = 0; i < m; i++)
        {
            g << information[i][0] << "\t" << information[i][1] << "\t" << information[i][2] << endl;
        }
        if (n == 0)
        {
            cout << "\n\t\t\t您所要修改的菜品不存在！" << endl << "\t\t\t1 返回；   2 继续修改        ";
            int a;
            cin >> a;
            switch (a)
            {
            case 1:
                manager1.changefood();
            case 2:
                manager1.changefood_price_name();
            default:
                cout << "\t\t\t请选择1、2三个功能键...";
                errget = _getch();
                break;
            }
        }
        else if (n == 1)
        {
            cout << "\n\t\t\t已修改！任意键返回...";
            errget = _getch();
            manager1.changefood();
        }
    }
    case 2:
        manager1.changefood();
    default:
        cout << "\t\t\t请选择1、2两个功能键...";
        errget = _getch();
        break;
    }
}

/*修改菜品信息主函数*/
void manager_use::changefood()
{
    system("cls");
    char errget;
    cout << endl << endl << endl << endl << endl;
    cout << "\t\t\t╭—————【菜品修改】——————╮" << endl;
    cout << "\t\t\t*——————************——————*" << endl;
    cout << "\t\t\t*            1 修改编  号            *" << endl;
    cout << "\t\t\t*            2 修改菜  名            *" << endl;
    cout << "\t\t\t*            3 修改价  格            *" << endl;
    cout << "\t\t\t*            4 返回上一层            *" << endl;
    cout << "\t\t\t*            5 返回主菜单            *" << endl;
    cout << "\t\t\t*            0 退出系  统            *" << endl;
    cout << "\t\t\t*——————************——————*" << endl;
    cout << "\t\t\t╰—————————————————╯" << endl;
    cout << endl << endl << "\t\t\t请选择：";
    int a;
    cin >> a;
    switch (a)
    {
    case 1:
        manager1.changefood_number();
    case 2:
        manager1.changefood_name();
    case 3:
    {
        system("cls");
        string a, b;
        int n = 0;
        cout << endl << endl << endl << endl;
        cout << "\t\t\t╭—————【菜品价格修改】——————╮" << endl;
        cout << "\t\t\t*——————************————————*" << endl;
        cout << "\t\t\t*          *****************             *" << endl;
        cout << "\t\t\t*        欢迎来到菜品价格修改系统        *" << endl;
        cout << "\t\t\t*          ******************            *" << endl;
        cout << "\t\t\t*           1.按编号修改价格             *" << endl;
        cout << "\t\t\t*           2.按菜名修改价格             *" << endl;
        cout << "\t\t\t*           3.返回上  一  层             *" << endl;
        cout << "\t\t\t*           4.返回主  菜  单             *" << endl;
        cout << "\t\t\t*           0.退出  系    统             *" << endl;
        cout << "\t\t\t*——————************————————*" << endl;
        cout << "\t\t\t╰———————————————————╯" << endl;
        cout << endl << endl;
        cout << "\t\t\t请选择：";
        int d;
        cin >> d;
        switch (d)
        {
        case 1:
            manager1.changefood_price_number();
        case 2:
            manager1.changefood_price_name();
        case 3:
            manager1.changefood();
        case 4:
            mainmenu();
        case 0:
            cout << "\t\t\t";
            exit(1);
        }
    }
    case 4:
        manager1.Adm_Windows();
    case 5:
        mainmenu();
    case 0:
        cout << "\t\t\t";
        exit(1);
    default:
        cout << "\t\t\t请选择1、2两个功能键...";
        errget = _getch();
        break;
    }
}

/*读取学生ID函数*/
void readID(char* ID)
{
    cin >> ID;
}

/*学生账户主函数*/
void student_use::stu_account(int n)
{
    system("cls");
    char errget;
    cout << endl << endl << endl << endl;
    cout << "\t\t\t╭—————【 学生账户 】————╮" << endl;
    cout << "\t\t\t*——————************—————*" << endl;
    cout << "\t\t\t*            1 菜 单 查  询        * " << endl;
    cout << "\t\t\t*            2 余 额 查  询        * " << endl;
    cout << "\t\t\t*            3 充        值        * " << endl;
    cout << "\t\t\t*            4 购 买 菜  品        * " << endl;
    cout << "\t\t\t*            5 菜 品 评  价        * " << endl;
    cout << "\t\t\t*            6 返回 上 一层        * " << endl;
    cout << "\t\t\t*            7 返回 主 菜单        * " << endl;
    cout << "\t\t\t*            0 退 出 系  统        * " << endl;
    cout << "\t\t\t*——————************—————*" << endl;
    cout << "\t\t\t╰————————————————╯" << endl;
    cout << endl << endl;
    cout << "\t\t\t请输入要选择的数字：";
    int k;
    cin >> k;
    switch (k)
    {
    case 1:
        student1.searchfood('h');
    case 2:
        cout << "\t\t\t你的余额为：   " << members[n].money << endl;
        system("pause");
        break;
    case 3:
        save_money(n);
        break;
    case 4:
        buy(n);
    case 5:
        WriteScore();
        break;
    case 6:
        student1.readnumber();
    case 7:
        mainmenu();
    case 0:
        cout << "\t\t\t";
        exit(1);
    default:
        cout << "\t\t\t请选择0、1、2、3、4、5、6、7八个功能键...";
        errget = _getch();
        manager1.Adm_Windows();
        break;
    }
    stu_account(n);
}

/*学生点餐系统函数*/
void student_use::buy(int n)
{
    char num[40];
    cout << endl << endl << endl << "\t\t\t请输入购买的菜品编号:";
    cin >> num;
    string information[20][3];
    ifstream f("menu.txt", ios::binary);
    for (int i = 0; i < 20; i++)
    {
        f >> information[i][0] >> information[i][1] >> information[i][2];
        if (num == information[i][0])
        {
            cout << endl << endl << "\t编号" << "\t名称" << "\t价格" << endl;
            cout << "\t" << information[i][0] << "\t" << information[i][1] << "\t" << information[i][2];
            char buf[10];
            strcpy_s(buf, information[i][2].c_str());
            sscanf_s(buf, "%d", &i);
            if (members[n].money - i > 0)
            {
                members[n].money -= i;
                cout << endl << endl << "\t\t\t购买完成！余额为：" << members[n].money << endl << "\t\t\t1 返回；   2 继续购买  ";
                ofstream g("stu_info.txt", ios::binary);
                for (i = 0; i < sum; i++)
                {
                    g << members[i].number << "\t" << members[i].name << "\t" << members[i].money << endl;
                }
            }
            else
            {
                cout << endl << endl << "\t\t\t购买失败，余额不足！" << endl << endl << "                          1 返回；   2 继续购买  ";
            }
            int a;
            cin >> a;
            switch (a)
            {

            case 1:
                stu_account(n);
            case 2:
                buy(n);
            }
        }
    }
    if (n == 0)
    {
        cout << "\t\t\t您所购买的菜品不存在！" << endl << "\t\t\t1 返回；   2 继续购买        " << endl;
        int a;
        cin >> a;
        switch (a)
        {
        case 1:
            stu_account(n);
        case 2:
            buy(n);
        }
    }
}

/*学生充值函数*/
void student_use::save_money(int n)
{
    int i;
    cout << endl << endl << endl << "\t\t\t请输入充值的金额:";
    int money;
    cin >> money;
    members[n].money += money;
    ofstream g("stu_info.txt", ios::binary);
    for (i = 0; i < sum; i++)
        g << members[i].number << "\t" << members[i].name << "\t" << members[i].money << endl;
    cout << endl << "\t\t\t充值成功！！余额为：" << members[n].money << endl << endl << "\t\t\t1.继续充值	        2.返回" << endl;
    cin >> i;
    switch (i)
    {

    case 1:
        save_money(n);
    case 2:
        stu_account(n);
    }
}

/*学生用户登录函数*/
void student_use::readnumber()
{
    char a[40];
    char errget;
    system("cls");
    cout << endl << endl << endl << endl;
    cout << "\t\t\t╭—————【学生用户登录】——————╮" << endl;
    cout << "\t\t\t*                                        *" << endl;
    cout << "\t\t\t*          *****************             *" << endl;
    cout << "\t\t\t*         欢迎来到学生饭卡系统          *" << endl;
    cout << "\t\t\t*          *****************             *" << endl;
    cout << "\t\t\t╰———————————————————╯" << endl;
    cout << endl << endl << endl << endl;
    cout << endl << endl << "\t\t\t请输入你的学号：";
    cin >> a;
    cout << endl;
    int t = 0, flag = 0;
    for (t = 0; t < sum; t++)
        if (!strcmp(members[t].number, a))
        {
            flag = 1;
            break;
        }
    if (flag)
    {
        cout << "\t\t\t登陆成功(任意键继续)...";
        student1.stu_account(t);
        errget = _getch();
        return;
    }
    else
    {
        cout << "\t\t\t该学生没有注册...";
        errget = _getch();
        mainmenu();
    }
}

/*学生菜单信息查询子函数（通过菜品编号查询）*/
void User::searchfood_number(char h)
{
    system("cls");
    ifstream f("menu.txt", ios::binary);
    string a;
    int n = 0;
    char errget;
    cout << endl << endl << endl << endl;
    cout << "\t\t\t╭—————【菜单查询】——————╮" << endl;
    cout << "\t\t\t*—————************———————*" << endl;
    cout << "\t\t\t*         **************             *" << endl;
    cout << "\t\t\t*      欢迎来到菜品编号查询系统      *" << endl;
    cout << "\t\t\t*         **************             *" << endl;
    cout << "\t\t\t*—————************———————*" << endl;
    cout << "\t\t\t╰—————————————————╯" << endl;
    cout << endl << endl;
    cout << "\t\t\t请输入你所查询的菜品编号：";
    cin >> a;
    string information[20][3];
    for (int i = 0; i < 20; i++)
    {
        f >> information[i][0] >> information[i][1] >> information[i][2];
        if (a == information[i][0])
        {
            cout << endl << endl << "\t编号" << "\t名称" << "\t价格" << endl;
            cout << "\t" << information[i][0] << "\t" << information[i][1] << "\t" << information[i][2];
            n = 1;
            cout << endl << endl << "\t\t\t查询完成！" << "\n\t\t\t1 返回；   2 继续查询  ";
            int a;
            cin >> a;
            switch (a)
            {
            case 1:
                student1.searchfood(h);
            case 2:
                student1.searchfood_number(h);
            default:
                cout << "\t\t\t请选择1、2三个功能键...";
                errget = _getch();
                student1.searchfood_number(h);
                break;
            }
        }
    }
    if (n == 0)
    {
        cout << "\t\t\t您所查询的菜品不存在！" << "\n\t\t\t1 返回；   2 继续查询        " << endl;
        int a;
        cin >> a;
        switch (a)
        {
        case 1:
            student1.searchfood(h);
        case 2:
            student1.searchfood_number(h);
        default:
            cout << "\t\t\t请选择1、2两个功能键...";
            errget = _getch();
            student1.searchfood_number(h);
            break;
        }
    }
}

/*学生菜品信息查询子函数（通过菜品名称查询）*/
void User::searchfood_name(char h)
{
    system("cls");
    ifstream f("menu.txt", ios::binary);
    string a;
    int n = 0;
    char errget;
    cout << endl << endl << endl << endl;
    cout << "\t\t\t╭—————【菜单查询】——————╮" << endl;
    cout << "\t\t\t*—————************———————*" << endl;
    cout << "\t\t\t*         **************             *" << endl;
    cout << "\t\t\t*      欢迎来到菜品名称查询系统      *" << endl;
    cout << "\t\t\t*         **************             *" << endl;
    cout << "\t\t\t*—————************———————*" << endl;
    cout << "\t\t\t╰—————————————————╯" << endl;
    cout << endl << endl;
    cout << "\t\t\t请输入你所查询的菜品名称：";
    cin >> a;
    string information[20][3];
    for (int i = 0; i < 20; i++)
    {
        f >> information[i][0] >> information[i][1] >> information[i][2];
        if (a == information[i][1])
        {
            cout << endl << endl << "\t编号" << "\t名称" << "\t价格" << endl;
            cout << "\t" << information[i][0] << "\t" << information[i][1] << "\t" << information[i][2];
            n = 1;
            cout << endl << endl << "\t\t\t查询完成！" << endl << endl << "\n\t\t\t1 返回；   2 继续查询  " << endl;
            int a;
            cin >> a;
            switch (a)
            {
            case 1:
                student1.searchfood(h);
            case 2:
                student1.searchfood_name(h);
            default:
                cout << "\t\t\t请选择1、2两个功能键...";
                errget = _getch();
                student1.searchfood_name(h);
                break;
            }
        }
    }
    if (n == 0)
    {
        cout << "\n\t\t\t您所查询的菜品不存在！" << endl << "\n\t\t\t1 返回；   2 继续查询        " << endl << "\t\t\t";
        int a;
        cin >> a;
        switch (a)
        {
        case 1:
            student1.searchfood(h);
        case 2:
            student1.searchfood_name(h);
        default:
            cout << "\t\t\t请选择1、2两个功能键...";
            errget = _getch();
            student1.searchfood_name(h);
            break;
        }
    }
}

/*学生菜品信息查询主函数*/
void User::searchfood(char h)
{
    system("cls");
    char errget;
    cout << endl << endl << endl << endl << endl;
    cout << "\t\t\t╭—————【菜单查询】——————╮" << endl;
    cout << "\t\t\t*——————************——————*" << endl;
    cout << "\t\t\t*            1 查询所有菜品          *" << endl;
    cout << "\t\t\t*            2 按编号查询            *" << endl;
    cout << "\t\t\t*            3 按菜名查询            *" << endl;
    cout << "\t\t\t*            4 返回 上 一层          *" << endl;
    cout << "\t\t\t*            5 返回 主 菜单          *" << endl;
    cout << "\t\t\t*            0 退 出 系  统          *" << endl;
    cout << "\t\t\t*——————************——————*" << endl;
    cout << "\t\t\t╰—————————————————╯" << endl;
    cout << endl << endl << endl << endl;
    cout << "\t\t\t请输入您要选择的数字：";
    int p;
    cin >> p;
    switch (p)
    {
    case 1:
    {
        system("cls");
        ifstream f("menu.txt");
        while (!f.eof())
        {
            char a;
            a = f.get();
            cout << a;
        }
        cout << "\t\t\t查询完成，按任意键返回";
        errget = _getch();
        student1.searchfood(h);
    }
    case 2:
        student1.searchfood_number(h);
    case 3:
        student1.searchfood_name(h);
    case 4:
        student1.stu_account(0);
    case 5:
        mainmenu();
    case 0:
        cout << "\t\t\t";
        exit(1);
    default:
        cout << "\t\t\t请选择0、1、2、3、4、5三个功能键...";
        errget = _getch();
        student1.searchfood(h);
        break;

    }
}

//更新evaluate.txt中的数据
void InitialScore()
{
    FILE* fp;
    errno_t err;
    if ((err = fopen_s(&fp,"evaluate.txt", "a")) == NULL)
    {
        printf("can't open the file evaluate.txt\n");
        exit(0);
    }
    if (fp != NULL)
    {
        fclose(fp);
        fp = NULL;
    }
    //将菜谱中的菜品全部读出来存在FoodMssage数组中
    if ((err = fopen_s(&fp,"menu.txt", "r")) == NULL)
    {
        printf("can't open the file menu.txt\n");
        exit(0);
    }
    int num = 0;
    char foodname[20];
    char foodid[20];
    char foodprice[20];
    fseek(fp, 0, SEEK_SET);     /*读写位置移动到文件开始处*/
    while (!feof(fp))                    /*检查文件是否结束*/
    {
        fscanf_s(fp, "%s %s %s", foodid, _countof(foodid), foodname, _countof(foodname), foodprice, _countof(foodprice));
        strcpy_s(FoodMssage[num].FoodId, foodid);
        strcpy_s(FoodMssage[num].FoodName, foodname);
        FoodMssage[num].socre = 0;
        FoodMssage[num].socernum = 0;
        foodnum = num;
        num++;
    }
    if (fp != NULL)
    {
        fclose(fp);
        fp = NULL;
    }
    //将evaluate.txt中的评价信息全部存入到FoodMssage数组中
    if ((err = fopen_s(&fp,"evaluate.txt", "r")) == NULL)
    {
        printf("can't open the file evaluate.txt\n");
        exit(0);
    }
    num = 0;
    int foodscore = 0;
    int foodscorenum = 0;


    fseek(fp, 0, SEEK_SET);    /*读写位置移动到文件开始处*/

    while (!feof(fp))                    /*检查文件是否结束*/
    {
        fscanf_s(fp, "%s %s %d %d", foodid, _countof(foodid),foodname, _countof(foodname), &foodscore, &foodscorenum);
        for (num = 0; num < 20; num++)
        {
            if ((strcmp(FoodMssage[num].FoodId, foodid) == 0) && (strcmp(FoodMssage[num].FoodName, foodname) == 0))
            {
                FoodMssage[num].socre = foodscore;
                FoodMssage[num].socernum = foodscorenum;
            }
        }
    }
    if (fp != NULL)
    {
        fclose(fp);
        fp = NULL;
    }
    //将FoodMssage数组中更新后的评价信息全部存入到evaluate.txt中
    if ((err = fopen_s(&fp,"evaluate.txt", "w")) == NULL)
    {
        printf("can't open the file evaluate.txt\n");
        exit(0);
    }
    for (num = 0; num < foodnum; num++)
    {
        fprintf(fp, "%s %s %d %d \n", FoodMssage[num].FoodId, FoodMssage[num].FoodName, FoodMssage[num].socre, FoodMssage[num].socernum);
    }
    if (fp != NULL)
    {
        fclose(fp);
        fp = NULL;
    }

}

//从evaluate.txt中输出数据到链表中
NodeTp* GetData()
{
    NodeTp* h, * p, * last;
    CreateNode(h);//建立头结点
    last = h;
    FILE* fp;
    errno_t err;
    if ((err = fopen_s(&fp,"evaluate.txt", "r")) == NULL)
    {
        printf("can't open the file evaluate.txt\n");
        exit(0);
    }

    fseek(fp, 0, SEEK_SET);    //读写位置移动到文件开始处
    while (!feof(fp))                    //检查文件是否结束
    {
        CreateNode(p);//建立一个新的节点
        fscanf_s(fp, "%s %s %d %d", &p->data.FoodId, &p->data.FoodName, &p->data.socre, &p->data.socernum,20);
        last->next = p;
        last = p;
        foodnum--;
        if (!foodnum)
        {
            break;
        }
    }
    last->next = NULL;
    return h;
}

/*管理员查看学生意见反馈函数*/
void ShowFoodScore()
{
    system("cls");
    NodeTp* h, * p;
    h = GetData();
    char errget;
    cout << "\t   菜品编号\t   菜品名称\t   菜品评分\t   评分总人数" << endl;
    p = h->next;//h为头指针
    //输出链表中的信息
    while (p)
    {
        cout << "\t\t" << p->data.FoodId << "\t\t" << p->data.FoodName << "\t\t" << p->data.socre << "\t\t" << p->data.socernum << endl;
        p = p->next;
    }
    errget = _getch();
    manager1.Adm_Windows();
}

/*学生意见反馈函数*/

void WriteScore()
{
    InitialScore();
    int num = 0;
    char foodname[20];
    char foodid[20];
    int foodscore = 0;
    cout << "\t\t\t请输入需评价的菜品编号:";
    cin >> foodid;
    cout << "\t\t\t请输入需评价的菜品名称:";
    cin >> foodname;
    cout << "\t\t\t请输入您的评分:";
    cin >> foodscore;
    for (num = 0; num < 20; num++)
    {
        if ((strcmp(FoodMssage[num].FoodId, foodid) == 0) && (strcmp(FoodMssage[num].FoodName, foodname) == 0)) //验证菜品编号和名称是否正确
        {
            FoodMssage[num].socernum++;
            FoodMssage[num].socre = (FoodMssage[num].socre + foodscore) / FoodMssage[num].socernum;
            break;
        }
    }
    if (20 == num)
    {
        cout << "\t\t\t您输入的菜品编号或者菜品名称有误!";
        return;
    }
    FILE* fp;
    errno_t err;
    if ((err = fopen_s(&fp,"evaluate.txt", "w")) == NULL)
    {
        printf("can't open the file evaluate.txt\n");
        exit(0);
    }
    for (num = 0; num < foodnum; num++)
    {
        fprintf(fp, "%s %s %d %d \n", FoodMssage[num].FoodId, FoodMssage[num].FoodName, FoodMssage[num].socre, FoodMssage[num].socernum); //评价信息保存在文件中
    }
    if (fp != NULL)
    {
        fclose(fp);
        fp = NULL;
    }
}

/************主函数**************/
int main()
{
    InitialFile();
    InitialScore();
    errno_t err;
    FILE* fin;
    err = fopen_s(&fin, "stu_info.txt", "r");
    int i = 0;
    while (fscanf_s(fin, "%s %s %d", members[i].number, _countof(members[i].number),members[i].name, _countof(members[i].number), &members[i].money) != EOF,20)
        i++;
    sum = i;
    mainmenu();
    return 0;
}





// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
