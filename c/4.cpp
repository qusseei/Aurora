// �ռ���.cpp : �������̨Ӧ�ó������ڵ㡣
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

void ShowFoodScore();           /*��ǰ��������Ա�鿴ѧ�������������*/
void WriteScore();              /*ѧ�������������*/

typedef struct score            /*����ȫ�ֱ���������*/
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
    struct node *next;
} NodeTp;
#define CreateNode(p) p = (NodeTp *)malloc(sizeof(NodeTp));//�����ڵ�ĺ�
#define DeleteNode(p) free((void *)p);//ɾ���ڵ�ĺ�

class User                      /*�û���*/
{
private:
    char usename[20];
    char password[20];
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


struct S_inf                    /*ѧ�����Ͻṹ��*/
{
    char number[40];
    char name[40];
    int money;
} members[N];

struct foods                    /*��Ʒ��Ϣ�ṹ��*/
{
    int number;
    string name;
} foods[N];                     /*�ṹ�����*/


class manager_use: public User  /*���û��������Ĺ���Ա������*/
{
private:
    char ID[20];
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
manager_use manager1;           /*����Ա��������*/


class student_use: public User  /*���û���������ѧ��������*/
{
public:
    void save_money(int n);
    void stu_account(int n);
    void readnumber();
    void buy(int n);
};
student_use student1;           /*ѧ�����������*/

/*��ǰ������Ϣ�����ı�*/
void InitialFile()
{
    FILE *fp;
    if((fp = fopen("����Ա�˺�.txt", "a")) == NULL)
    {
        printf("can't open the file use.txt\n");
        exit(0);
    }
    fclose(fp);

    if((fp = fopen("����.txt", "a")) == NULL)
    {
        printf("can't open the file use.txt\n");
        exit(0);
    }
    fclose(fp);

    if((fp = fopen("ѧ����Ϣ.txt", "a")) == NULL)
    {
        printf("can't open the file use.txt\n");
        exit(0);
    }
    fclose(fp);

}

/*���˵�*/
void mainmenu()
{
    system("cls");
    int nselete;
    char sTemp[20];
    cout << endl << endl << endl << endl;
    cout << "\t\t\t�q���������������˵����������������r" << endl;
    cout << "\t\t\t*����������************������������* " << endl;
    cout << "\t\t\t*         1 �������ۺ�ϵͳ         * " << endl;
    cout << "\t\t\t*         2 ѧ���ۺ�ϵ  ͳ         * " << endl;
    cout << "\t\t\t*         0 ��  ��  ϵ  ͳ         * " << endl;
    cout << "\t\t\t*����������************������������* " << endl;
    cout << "\t\t\t�t���������������������������������s" << endl;
    cout << endl << endl;
    cout << endl << "\t\t\t��ѡ�����֣�";
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

    switch(nselete)
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
        cout << "\t\t\t�������!��ѡ��0��1��2�������ܼ�...";
        getch();
        mainmenu();
        break;
    }
}

/*��ȡ�û�����*/
void readname(char *usename)
{
    cin >> usename;
}

/*��ȡ�û�����*/
void readpassword(char *password)
{
    int k = 0;
    char ch;
    while((ch = getch()) != 13)
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

/*ע���¹���Ա�˺�*/
void User::set()
{
    int j;
    cout << "\t\t\t������ע����:";
    cin >> j;
    if(j == 123)
    {
        cout << "\t\t\t�����û�����";
        readname(usename);
        cout << "\t\t\t��������:";
        readpassword(password);
        ofstream ofile("����Ա�˺�.txt", ios_base::app);
        ofile << usename << endl << password << endl;
        ofile.close();
        cout << "\n\t\t\t���óɹ�...";
        getch();
    }
    else
    {
        cout << "\t\t\tע��������޷�ע�����˺ţ�";
        getch();
    }
}

/*����Ա�˻���¼*/
void User::load()
{
    char user[20];
    char word[20];
    User uu;
    cout << "\t\t\t�������û���:";
    readname(uu.usename);
    cout << "\t\t\t����������:";
    readpassword(uu.password);
    ifstream ifile;
    ifile.open("����Ա�˺�.txt", ios_base::in);
    while(ifile.good())
    {
        ifile.getline(user, 100);
        ifile.getline(word, 100);
        if(strcmp(uu.usename, user) == 0 && strcmp(uu.password, word) == 0)
        {
            cout << "\t\t\t��½�ɹ�(���������)...";
            manager1.Adm_Windows();
            ifile.close();
            getch();
            return;
        }
    }
    cout << "\t\t\t�����˺Ż��������(���������)...";
    getch();
    u.Adm_Account();
    ifile.close();
    getch();
}

/*����Ա�˻������溯��*/
void User::Adm_Account()
{
    system("cls");
    int nselete;
    cout << endl << endl << endl << endl;
    cout << "\t\t\t�q��������������Ա�ʻ��������������r" << endl;
    cout << "\t\t\t*����������************������������*" << endl;
    cout << "\t\t\t*          1.����Աע��            *" << endl;
    cout << "\t\t\t*          2.����Ա��½            *" << endl;
    cout << "\t\t\t*          3.�������˵�            *" << endl;
    cout << "\t\t\t*          0.�˳�ϵ  ͳ            *" << endl;
    cout << "\t\t\t*����������************������������* " << endl;
    cout << "\t\t\t�t���������������������������������s" << endl;
    do
    {
        fflush(stdin);
        cin.clear();
        cout << "\n\t\t\t������Ҫִ�в��������:";
        cin >> nselete;
    }
    while(cin.fail());
    cout << endl;
    switch(nselete)
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
        cout << "\t\t\t��ѡ��0��1��2��3�ĸ����ܼ�...";
        getch();
        u.Adm_Account();
    }

}

/*����Ա¼��ѧ������*/
void manager_use::setstu()
{
    char ch[] = "000";
    system("cls");
    int i = 0;
    cout << endl << endl << endl << endl << endl;
    cout << "\t\t\t�q������������¼��ѧ����Ϣ�������������r" << endl << endl << endl;
    for(;;)
    {
        cout << "\t\t\t����ѧ��:";
        cin >> members[i].number;
        if(!strcmp(members[i].number, ch))
        {
            Adm_Windows();
            break;
        }
        cout << endl << "\t\t\t������������";
        cin >> members[i].name;
        ofstream ofile("ѧ����Ϣ.txt", ios_base::app);
        ofile << members[i].number << " " << members[i].name << " " << members[i].money << endl;
        ofile.close();
        cout << "\n\t\t\t���óɹ�...����'000'����,�����������������ѧ��" << endl;
        members[i].money = 0;
        i++;
    }
    sum = i;
}

/*����Ա���������溯��*/
void manager_use::Adm_Windows()
{
    system("cls");
    cout << endl << endl << endl << endl;
    cout << "\t\t\t�q����������������Ա���ڡ����������r" << endl;
    cout << "\t\t\t*������������************����������*" << endl;
    cout << "\t\t\t*            1 �� �� ��  ѯ        * " << endl;
    cout << "\t\t\t*            2 �� Ʒ ��  ��        * " << endl;
    cout << "\t\t\t*            3 �� Ʒ ɾ  ��        * " << endl;
    cout << "\t\t\t*            4 �� Ʒ ��  ��        * " << endl;
    cout << "\t\t\t*            5 ѧ����Ϣ¼��        * " << endl;
    cout << "\t\t\t*            6 �� �� ��  ��        * " << endl;
    cout << "\t\t\t*            7 ���� �� һ��        * " << endl;
    cout << "\t\t\t*            8 ���� �� �˵�        * " << endl;
    cout << "\t\t\t*            0 �� �� ϵ  ͳ        * " << endl;
    cout << "\t\t\t*������������************����������*" << endl;
    cout << "\t\t\t�t���������������������������������s" << endl;
    cout << endl << endl;
    cout << "\t\t\t��������Ҫѡ������֣�";
    int a;
    cin >> a;
    switch(a)
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
        cout << "\t\t\t��ѡ��0��1��2��3��4��5��6��7��8�Ÿ����ܼ�...";
        getch();
        manager1.Adm_Windows();
        break;
    }
}

/*����Ա�˵���Ϣ��ѯ�Ӻ�����ͨ����Ʒ��Ų�ѯ��*/
void User::searchfood_number(int h)
{
    system("cls");
    ifstream f("����.txt", ios::binary);
    string a;
    int n = 0;
    cout << endl << endl << endl << endl;
    cout << "\t\t\t�q�������������˵���ѯ���������������r" << endl;
    cout << "\t\t\t*����������************��������������*" << endl;
    cout << "\t\t\t*         **************             *" << endl;
    cout << "\t\t\t*      ��ӭ������Ʒ��Ų�ѯϵͳ      *" << endl;
    cout << "\t\t\t*         **************             *" << endl;
    cout << "\t\t\t*����������************��������������*" << endl;
    cout << "\t\t\t�t�����������������������������������s" << endl;
    cout << endl << endl;
    cout << "\t\t\t������������ѯ�Ĳ�Ʒ��ţ�";
    cin >> a;
    string information[20][3];
    for(int i = 0; i < 20; i++)
    {
        f >> information[i][0] >> information[i][1] >> information[i][2];
        if(a == information[i][0])
        {
            cout << endl << endl << "\t���" << "\t����" << "\t�۸�" << endl;
            cout << "\t" << information[i][0] << "\t" << information[i][1] << "\t" << information[i][2];
            n = 1;
            cout << endl << endl << "\t\t\t��ѯ��ɣ�" << "\n\t\t\t1 ���أ�   2 ������ѯ  ";
            int a;
            cin >> a;
            switch(a)
            {
            case 1:
                manager1.searchfood(0);
            case 2:
                manager1.searchfood_number(0);
            default:
                cout << "\t\t\t��ѡ��1��2�������ܼ�...";
                getch();
                manager1.searchfood_number(0);
                break;
            }
        }
    }
    if(n == 0)
    {
        cout << "\t\t\t������ѯ�Ĳ�Ʒ�����ڣ�" << "\n\t\t\t1 ���أ�   2 ������ѯ        " << endl;
        int a;
        cin >> a;
        switch(a)
        {
        case 1:
            manager1.searchfood(0);
        case 2:
            manager1.searchfood_number(0);
        default:
            cout << "\t\t\t��ѡ��1��2�������ܼ�...";
            getch();
            manager1.searchfood_number(0);
            break;
        }
    }
}

/*����Ա��Ʒ��Ϣ��ѯ�Ӻ�����ͨ����Ʒ���ֲ�ѯ��*/
void User::searchfood_name(int h)
{
    system("cls");
    ifstream f("����.txt", ios::binary);
    string a;
    int n = 0;
    cout << endl << endl << endl << endl;
    cout << "\t\t\t�q�������������˵���ѯ���������������r" << endl;
    cout << "\t\t\t*����������************��������������*" << endl;
    cout << "\t\t\t*         **************             *" << endl;
    cout << "\t\t\t*      ��ӭ������Ʒ���Ʋ�ѯϵͳ      *" << endl;
    cout << "\t\t\t*         **************             *" << endl;
    cout << "\t\t\t*����������************��������������*" << endl;
    cout << "\t\t\t�t�����������������������������������s" << endl;
    cout << endl << endl;
    cout << "\t\t\t������������ѯ�Ĳ�Ʒ���ƣ�";
    cin >> a;
    string information[20][3];
    for(int i = 0; i < 20; i++)
    {
        f >> information[i][0] >> information[i][1] >> information[i][2];
        if(a == information[i][1])
        {
            cout << endl << endl << "\t���" << "\t����" << "\t�۸�" << endl;
            cout << "\t" << information[i][0] << "\t" << information[i][1] << "\t" << information[i][2];
            n = 1;
            cout << endl << endl << "\t\t\t��ѯ��ɣ�" << endl << endl << "\n\t\t\t1 ���أ�   2 ������ѯ  " << endl;
            int a;
            cin >> a;
            switch(a)
            {
            case 1:
                manager1.searchfood(0);
            case 2:
                manager1.searchfood_name(0);
            default:
                cout << "\t\t\t��ѡ��1��2�������ܼ�...";
                getch();
                manager1.searchfood_name(0);
                break;
            }
        }
    }
    if(n == 0)
    {
        cout << "\n\t\t\t������ѯ�Ĳ�Ʒ�����ڣ�" << endl << "\n\t\t\t1 ���أ�   2 ������ѯ        " << endl << "\t\t\t";
        int a;
        cin >> a;
        switch(a)
        {
        case 1:
            manager1.searchfood(0);
        case 2:
            manager1.searchfood_name(0);
        default:
            cout << "\t\t\t��ѡ��1��2�������ܼ�...";
            getch();
            manager1.searchfood_name(0);
            break;
        }
    }
}

/*����Ա��Ʒ��Ϣ��ѯ������*/
void User::searchfood(int h)
{
    system("cls");
    cout << endl << endl << endl << endl;
    cout << "\t\t\t�q�������������˵���ѯ���������������r" << endl;
    cout << "\t\t\t*������������************������������*" << endl;
    cout << "\t\t\t*            1 ��ѯ���в�Ʒ          *" << endl;
    cout << "\t\t\t*            2 �� ��� ��ѯ          *" << endl;
    cout << "\t\t\t*            3 �� ���� ��ѯ          *" << endl;
    cout << "\t\t\t*            4 ���� �� һ��          *" << endl;
    cout << "\t\t\t*            5 ���� �� �˵�          *" << endl;
    cout << "\t\t\t*            0 �� �� ϵ  ͳ          *" << endl;
    cout << "\t\t\t*������������************������������*" << endl;
    cout << "\t\t\t�t�����������������������������������s" << endl;
    cout << endl << endl;
    cout << "\t\t\t��������Ҫѡ������֣�";
    int a;
    cin >> a;
    switch(a)
    {
    case 1:
    {
        system("cls");
        ifstream f("����.txt");
        while(!f.eof())
        {
            char a;
            a = f.get();
            cout << a;
        }
        cout << "\t\t\t��ѯ��ɣ������������";
        getch();
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
        cout << "\t\t\t��ѡ��0��1��2��3��4��5�������ܼ�...";
        getch();
        manager1.searchfood(0);
        break;
    }
}

/*��Ʒ��Ϣ���������*/
void manager_use::addfood()
{
    system("cls");
    string a, b, c;
    ofstream f("����.txt", ios::app);
    cout << endl << endl << endl << endl;
    cout << "\t\t\t�q��������������Ʒ���ӡ��������������r" << endl;
    cout << "\t\t\t*����������************��������������*" << endl;
    cout << "\t\t\t*          **************            *" << endl;
    cout << "\t\t\t*        ��ӭ������Ʒ����ϵͳ        *" << endl;
    cout << "\t\t\t*          **************            *" << endl;
    cout << "\t\t\t*����������************��������������*" << endl;
    cout << "\t\t\t�t�����������������������������������s" << endl;
    cout << endl << endl;
    cout << "\t\t\t����������ӵĲ�Ʒ��ţ�";
    cin >> a;
    f << endl << a << "        ";
    cout << "\n\t\t\t����������ӵĲ�Ʒ���ƣ�";
    cin >> b;
    f << b << "           ";
    cout << "\n\t\t\t����������ӵĲ�Ʒ�۸�";
    cin >> c;
    f << c << endl;
    cout << "\n\t\t\t�����ɣ����������...";
    getch();
    manager1.Adm_Windows();
}

/*��Ʒ��Ϣɾ���Ӻ�����ͨ����Ʒ���ɾ����*/
void manager_use::deletefood_number()
{
    system("cls");
    ifstream f("����.txt", ios::binary);
    string a;
    int n = 0;
    cout << endl << endl << endl << endl;
    cout << "\t\t\t�q��������������Ʒɾ�����������������r" << endl;
    cout << "\t\t\t*����������************��������������*" << endl;
    cout << "\t\t\t*          **************            *" << endl;
    cout << "\t\t\t*      ��ӭ������Ʒ���ɾ��ϵͳ      *" << endl;
    cout << "\t\t\t*          **************            *" << endl;
    cout << "\t\t\t*����������************��������������*" << endl;
    cout << "\t\t\t�t�����������������������������������s" << endl;
    cout << endl << endl;
    cout << "\t\t\t����������Ҫɾ���Ĳ�Ʒ��ţ�";
    cin >> a;
    cout << endl << endl << endl << endl;
    cout << "\t\t\t�q��������************�����������r                " << endl;
    cout << "\t\t\t*�������� ************���������� *                 " << endl;
    cout << "\t\t\t*           1 ȷ��               *                " << endl;
    cout << "\t\t\t*           2 ȡ��               *                " << endl;
    cout << "\t\t\t*����������************����������*                " << endl;
    cout << "\t\t\t�t��������************�����������s                 " << endl;
    cout << "\t\t\t��ѡ��";
    int d;
    cin >> d;
    switch(d)
    {
    case 1:
    {
        int m = 0;
        string information[20][3];
        int i;
        for(i = 0; i < 20; i++)
        {
            f >> information[i][0] >> information[i][1] >> information[i][2];
            m++;
            if(a == information[i][0])
            {
                n = 1;
                information[i][0] = "0";
            }
            if(information[i][0] == "") break;
        }
        f.close();
        ofstream g("����.txt", ios::binary);
        for(i = 0; i < m; i++)
        {
            if(information[i][0] != "0")
            {
                g << information[i][0] << "\t" << information[i][1] << "\t" << information[i][2] << endl;
            }
        }
        g.close();
        if(n == 0)
        {
            cout << "\t\t\t����Ҫɾ���Ĳ�Ʒ�����ڣ�" << endl << "\t\t\t1 ���أ�   2 ����ɾ��        ";
            int a;
            cin >> a;
            switch(a)
            {
            case 1:
                manager1.deletefood();
            case 2:
                manager1.deletefood_number();
            default:
                cout << "\t\t\t��ѡ��1��2�������ܼ�...";
                getch();
                manager1.deletefood_number();
                break;
            }
        }
        if(n == 1)
        {
            cout << "\t\t\t��ɾ�������������...";
            getch();
            manager1.deletefood();
        }
    }
    case 2:
        manager1.deletefood();
    }
}

/*��Ʒ��Ϣɾ���Ӻ�����ͨ����Ʒ����ɾ����*/
void manager_use::deletefood_name()
{
    system("cls");
    ifstream f("����.txt", ios::binary);
    string a;
    int n = 0;
    cout << endl << endl << endl << endl;
    cout << "\t\t\t�q��������������Ʒɾ�����������������r" << endl;
    cout << "\t\t\t*����������************��������������*" << endl;
    cout << "\t\t\t*          **************            *" << endl;
    cout << "\t\t\t*      ��ӭ������Ʒ����ɾ��ϵͳ      *" << endl;
    cout << "\t\t\t*          **************            *" << endl;
    cout << "\t\t\t*����������************��������������*" << endl;
    cout << "\t\t\t�t�����������������������������������s" << endl;
    cout << endl << endl;
    cout << "\t\t\t����������Ҫɾ���Ĳ�Ʒ���ƣ�";
    cin >> a;
    cout << endl << endl;
    cout << "\t\t\t�q��������************�����������r                " << endl;
    cout << "\t\t\t*�������� ************���������� *                 " << endl;
    cout << "\t\t\t*           1 ȷ��               *                " << endl;
    cout << "\t\t\t*           2 ȡ��               *                " << endl;
    cout << "\t\t\t*����������************����������*                " << endl;
    cout << "\t\t\t�t��������************�����������s                 " << endl;
    cout << "\n\t\t\t��ѡ��";
    int d;
    cin >> d;
    switch(d)
    {
    case 1:
    {
        int m = 0;
        string information[20][3];
        int i;
        for(i = 0; i < 20; i++)
        {
            f >> information[i][0] >> information[i][1] >> information[i][2];
            m++;
            if(a == information[i][1])
            {
                n = 1;
                information[i][1] = "0";
            }
            if(information[i][0] == "") break;
        }
        f.close();
        ofstream g("����.txt", ios::binary);
        for(i = 0; i < m; i++)
        {
            if(information[i][1] != "0") g << information[i][0] << "\t" << information[i][1] << "\t" << information[i][2] << endl;
        }
        f.close();
        if(n == 0)
        {
            cout << "\t\t\t����Ҫɾ���Ĳ�Ʒ�����ڣ�" << endl << "\t\t\t1 ���أ�   2 ����ɾ��        ";
            int a;
            cin >> a;
            switch(a)
            {
            case 1:
                manager1.deletefood();
            case 2:
                manager1.deletefood_name();
            }
        }
        if(n == 1)
        {
            cout << "\n\t\t\t��ɾ�������������...";
            getch();
            manager1.deletefood();
        }
    }
    case 2:
        manager1.deletefood();
    default:
        cout << "\t\t\t��ѡ��1��2�������ܼ�...";
        getch();
        break;
    }
}

/*��Ʒ��Ϣɾ��������*/
void manager_use::deletefood()
{
    system("cls");
    cout << endl << endl << endl << endl << endl;
    cout << endl << endl << endl << endl;
    cout << "\t\t\t�q��������������Ʒɾ�����������������r" << endl;
    cout << "\t\t\t*����������************��������������*" << endl;
    cout << "\t\t\t*         ***************            *" << endl;
    cout << "\t\t\t*        ��ӭ������Ʒɾ��ϵͳ        *" << endl;
    cout << "\t\t\t*         ***************            *" << endl;
    cout << "\t\t\t*           1.�����ɾ��             *" << endl;
    cout << "\t\t\t*           2.������ɾ��             *" << endl;
    cout << "\t\t\t*           3.������һ��             *" << endl;
    cout << "\t\t\t*           4.�������˵�             *" << endl;
    cout << "\t\t\t*           0.�˳�ϵ  ͳ             *" << endl;
    cout << "\t\t\t*����������************��������������*" << endl;
    cout << "\t\t\t�t�����������������������������������s" << endl;
    cout << endl << endl;
    int a;
    cin >> a;
    switch(a)
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
        cout << "\t\t\t��ѡ��0��1��2��3��4������ܼ�...";
        getch();
        break;
    }
}

/*��Ʒ��Ϣ�޸��Ӻ�����ͨ����Ʒ����޸ģ�*/
void manager_use::changefood_number()
{
    system("cls");
    string a, b;
    int n = 0;
    cout << endl << endl << endl << endl;
    cout << "\t\t\t�q��������������Ʒ����޸ġ������������r" << endl;
    cout << "\t\t\t*������������************��������������*" << endl;
    cout << "\t\t\t*          *******************         *" << endl;
    cout << "\t\t\t*        ��ӭ������Ʒ����޸�ϵͳ      *" << endl;
    cout << "\t\t\t*          *******************         *" << endl;
    cout << "\t\t\t*������������************��������������*" << endl;
    cout << "\t\t\t�t�������������������������������������s" << endl;
    cout << endl << endl;
    cout << endl << endl << "\t\t\t����������Ҫ�޸ĵĲ�Ʒ��ţ�";
    cin >> a;
    cout << endl << "\t\t\t��������Ҫ������޸�Ϊ��";
    cin >> b;
    cout << endl << endl;
    cout << "\t\t\t�q��������************�����������r                " << endl;
    cout << "\t\t\t*�������� ************���������� *                 " << endl;
    cout << "\t\t\t*           1 ȷ��               *                " << endl;
    cout << "\t\t\t*           2 ȡ��               *                " << endl;
    cout << "\t\t\t*����������************����������*                " << endl;
    cout << "\t\t\t�t��������************�����������s                 " << endl;
    cout << "\n\t\t\t��ѡ��";
    int d;
    cin >> d;
    switch(d)
    {
    case 1:
    {
        int m = 0;
        ifstream f("����.txt", ios::binary);
        string information[20][3];
        int i;
        for(i = 0; i < 20; i++)
        {
            f >> information[i][0] >> information[i][1] >> information[i][2];
            m++;
            if(information[i][0] == "") break;
        }
        f.close();
        for(i = 0; i < m; i++)
        {
            if(a == information[i][0])
            {
                information[i][0] = b;
                n = 1;
            }
        }
        ofstream g("����.txt", ios::binary);
        for(i = 0; i < m; i++)
        {
            g << information[i][0] << "\t" << information[i][1] << "\t" << information[i][2] << endl;
        }
        if(n == 0)
        {
            cout << "\t\t\t����Ҫ�޸ĵĲ�Ʒ�����ڣ�" << endl << "\t\t\t1 ���أ�   2 �����޸�        ";
            int a;
            cin >> a;
            switch(a)
            {
            case 1:
                manager1.changefood();
            case 2:
                manager1.changefood_number();
            default:
                cout << "\t\t\t��ѡ��1��2�������ܼ�...";
                getch();
                break;
            }
        }
        else if(n == 1)
        {
            cout << "\t\t\t���޸ģ����������...";
            getch();
            manager1.changefood();
        }
    }
    case 2:
        manager1.changefood();
    default:
        cout << "\t\t\t��ѡ��1��2�������ܼ�...";
        getch();
        break;
    }
}

/*��Ʒ��Ϣ�޸��Ӻ�����ͨ����Ʒ�����޸ģ�*/
void manager_use::changefood_name()
{
    system("cls");
    string a, b;
    int n = 0;
    cout << endl << endl << endl << endl;
    cout << "\t\t\t�q��������������Ʒ�����޸ġ������������r" << endl;
    cout << "\t\t\t*������������************��������������*" << endl;
    cout << "\t\t\t*          *******************         *" << endl;
    cout << "\t\t\t*       ��ӭ������Ʒ�����޸�ϵͳ       *" << endl;
    cout << "\t\t\t*          *******************         *" << endl;
    cout << "\t\t\t*������������************��������������*" << endl;
    cout << "\t\t\t�t�������������������������������������s" << endl;
    cout << endl << endl;
    cout << "\t\t\t����������Ҫ�޸ĵĲ�Ʒ���ƣ�";
    cin >> a;
    cout << endl << "\t\t\t��������Ҫ�������޸�Ϊ��";
    cin >> b;
    cout << endl << endl;
    cout << "\t\t\t�q��������************�����������r                " << endl;
    cout << "\t\t\t*�������� ************���������� *                 " << endl;
    cout << "\t\t\t*           1 ȷ��               *                " << endl;
    cout << "\t\t\t*           2 ȡ��               *                " << endl;
    cout << "\t\t\t*����������************����������*                " << endl;
    cout << "\t\t\t�t��������************�����������s                 " << endl;
    cout << "\n\t\t\t��ѡ��";
    int d;
    cin >> d;
    switch(d)
    {
    case 1:
    {
        int m = 0;
        ifstream f("����.txt", ios::binary);
        string information[20][3];
        int i;
        for(i = 0; i < 20; i++)
        {
            f >> information[i][0] >> information[i][1] >> information[i][2];
            m++;
            if(information[i][0] == "") break;
        }
        f.close();
        for(i = 0; i < m; i++)
        {
            if(a == information[i][1])
            {
                information[i][1] = b;
                n = 1;
            }
        }
        ofstream g("����.txt", ios::binary);
        for(i = 0; i < m; i++)
        {
            g << information[i][0] << "\t" << information[i][1] << "\t" << information[i][2] << endl;
        }
        if(n == 0)
        {
            cout << "\n\t\t\t����Ҫ�޸ĵĲ�Ʒ�����ڣ�" << endl << "\t\t\t1 ���أ�   2 �����޸�        ";
            int a;
            cin >> a;
            switch(a)
            {
            case 1:
                manager1.changefood();
            case 2:
                manager1.changefood_name();
            }
        }
        else if(n == 1)
        {
            cout << "\n\t\t\t���޸ģ����������...";
            getch();
            manager1.changefood();
        }
    }
    case 2:
        manager1.changefood();
    default:
        cout << "\t\t\t��ѡ��1��2�������ܼ�...";
        getch();
        break;
    }
}

/*��Ʒ�۸��޸ĺ�����ͨ����Ʒ����޸ģ�*/
void manager_use::changefood_price_number()
{
    system("cls");
    string a, b;
    int n = 0;
    cout << endl << endl << endl << endl;
    cout << "\t\t\t�q��������������Ʒ�۸��޸ġ������������r" << endl;
    cout << "\t\t\t*������������************��������������*" << endl;
    cout << "\t\t\t*          *******************         *" << endl;
    cout << "\t\t\t*      ��ӭ��������Ʒ����޸ļ۸�ϵͳ  *" << endl;
    cout << "\t\t\t*          *******************         *" << endl;
    cout << "\t\t\t*������������************��������������*" << endl;
    cout << "\t\t\t�t�������������������������������������s" << endl;
    cout << endl << endl;
    cout << "\t\t\t����������Ҫ�޸ĵĲ�Ʒ��ţ�";
    cin >> a;
    cout << endl << "\t\t\t��������Ҫ���۸��޸�Ϊ��";
    cin >> b;
    cout << endl << endl;
    cout << "\t\t\t�q��������************�����������r                " << endl;
    cout << "\t\t\t*�������� ************���������� *                 " << endl;
    cout << "\t\t\t*           1 ȷ��               *                " << endl;
    cout << "\t\t\t*           2 ȡ��               *                " << endl;
    cout << "\t\t\t*����������************����������*                " << endl;
    cout << "\t\t\t�t��������************�����������s                 " << endl;
    cout << "\n\t\t\t��ѡ��";
    int e;
    cin >> e;
    switch(e)
    {
    case 1:
    {
        int m = 0;
        ifstream f("����.txt", ios::binary);
        string information[20][3];
        int i;
        for(i = 0; i < 20; i++)
        {
            f >> information[i][0] >> information[i][1] >> information[i][2];
            m++;
            if(information[i][0] == "") break;
        }
        f.close();
        for(i = 0; i < m; i++)
        {
            if(a == information[i][0])
            {
                information[i][2] = b;
                n = 1;
            }
        }
        ofstream g("����.txt", ios::binary);
        for(i = 0; i < m; i++)
        {
            g << information[i][0] << "\t" << information[i][1] << "\t" << information[i][2] << endl;
        }
        if(n == 0)
        {
            cout << "\n\t\t\t����Ҫ�޸ĵĲ�Ʒ�����ڣ�" << endl << "\t\t\t1 ���أ�   2 �����޸�        ";
            int a;
            cin >> a;
            switch(a)
            {
            case 1:
                manager1.changefood();
            case 2:
                manager1.changefood_price_number();
            }
        }
        else if(n == 1)
        {
            cout << "\n\t\t\t���޸ģ����������...";
            getch();
            manager1.changefood();
        }
    }
    case 2:
        manager1.changefood();
    default:
        cout << "\t\t\t��ѡ��1��2�������ܼ�...";
        getch();
        break;
    }
}

/*��Ʒ�۸��޸ĺ�����ͨ����Ʒ�����޸ģ�*/
void manager_use::changefood_price_name()
{
    system("cls");
    string a, b;
    int n = 0;
    cout << endl << endl << endl << endl;
    cout << "\t\t\t�q��������������Ʒ�۸��޸ġ������������r" << endl;
    cout << "\t\t\t*������������************��������������*" << endl;
    cout << "\t\t\t*          *******************         *" << endl;
    cout << "\t\t\t*      ��ӭ��������Ʒ�����޸ļ۸�ϵͳ  *" << endl;
    cout << "\t\t\t*          *******************         *" << endl;
    cout << "\t\t\t*������������************��������������*" << endl;
    cout << "\t\t\t�t�������������������������������������s" << endl;
    cout << endl << endl;
    cout << "\t\t\t����������Ҫ�޸ĵĲ�Ʒ���ƣ�";
    cin >> a;
    cout << endl << "\t\t\t��������Ҫ���۸��޸�Ϊ��";
    cin >> b;
    cout << endl << endl;
    cout << "\t\t\t�q��������************�����������r                " << endl;
    cout << "\t\t\t*�������� ************���������� *                 " << endl;
    cout << "\t\t\t*           1 ȷ��               *                " << endl;
    cout << "\t\t\t*           2 ȡ��               *                " << endl;
    cout << "\t\t\t*����������************����������*                " << endl;
    cout << "\t\t\t�t��������************�����������s                 " << endl;
    cout << "\n\t\t\t��ѡ��";
    int e;
    cin >> e;
    switch(e)
    {
    case 1:
    {
        int m = 0;
        ifstream f("����.txt", ios::binary);
        string information[20][3];
        int i;
        for(i = 0; i < 20; i++)
        {
            f >> information[i][0] >> information[i][1] >> information[i][2];
            m++;
            if(information[i][0] == "") break;
        }
        f.close();
        for(i = 0; i < m; i++)
        {
            if(a == information[i][1])
            {
                information[i][2] = b;
                n = 1;
            }
        }
        ofstream g("����.txt", ios::binary);
        for(i = 0; i < m; i++)
        {
            g << information[i][0] << "\t" << information[i][1] << "\t" << information[i][2] << endl;
        }
        if(n == 0)
        {
            cout << "\n\t\t\t����Ҫ�޸ĵĲ�Ʒ�����ڣ�" << endl << "\t\t\t1 ���أ�   2 �����޸�        ";
            int a;
            cin >> a;
            switch(a)
            {
            case 1:
                manager1.changefood();
            case 2:
                manager1.changefood_price_name();
            default:
                cout << "\t\t\t��ѡ��1��2�������ܼ�...";
                getch();
                break;
            }
        }
        else if(n == 1)
        {
            cout << "\n\t\t\t���޸ģ����������...";
            getch();
            manager1.changefood();
        }
    }
    case 2:
        manager1.changefood();
    default:
        cout << "\t\t\t��ѡ��1��2�������ܼ�...";
        getch();
        break;
    }
}

/*�޸Ĳ�Ʒ��Ϣ������*/
void manager_use::changefood()
{
    system("cls");
    cout << endl << endl << endl << endl << endl;
    cout << "\t\t\t�q��������������Ʒ�޸ġ��������������r" << endl;
    cout << "\t\t\t*������������************������������*" << endl;
    cout << "\t\t\t*            1 �޸ı�  ��            *" << endl;
    cout << "\t\t\t*            2 �޸Ĳ�  ��            *" << endl;
    cout << "\t\t\t*            3 �޸ļ�  ��            *" << endl;
    cout << "\t\t\t*            4 ������һ��            *" << endl;
    cout << "\t\t\t*            5 �������˵�            *" << endl;
    cout << "\t\t\t*            0 �˳�ϵ  ͳ            *" << endl;
    cout << "\t\t\t*������������************������������*" << endl;
    cout << "\t\t\t�t�����������������������������������s" << endl;
    cout << endl << endl << "\t\t\t��ѡ��";
    int a;
    cin >> a;
    switch(a)
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
        cout << "\t\t\t�q��������������Ʒ�۸��޸ġ��������������r" << endl;
        cout << "\t\t\t*������������************����������������*" << endl;
        cout << "\t\t\t*          *****************             *" << endl;
        cout << "\t\t\t*        ��ӭ������Ʒ�۸��޸�ϵͳ        *" << endl;
        cout << "\t\t\t*          ******************            *" << endl;
        cout << "\t\t\t*           1.������޸ļ۸�             *" << endl;
        cout << "\t\t\t*           2.�������޸ļ۸�             *" << endl;
        cout << "\t\t\t*           3.������  һ  ��             *" << endl;
        cout << "\t\t\t*           4.������  ��  ��             *" << endl;
        cout << "\t\t\t*           0.�˳�  ϵ    ͳ             *" << endl;
        cout << "\t\t\t*������������************����������������*" << endl;
        cout << "\t\t\t�t���������������������������������������s" << endl;
        cout << endl << endl;
        cout << "\t\t\t��ѡ��";
        int d;
        cin >> d;
        switch(d)
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
        cout << "\t\t\t��ѡ��1��2�������ܼ�...";
        getch();
        break;
    }
}

/*��ȡѧ��ID����*/
void readID(char *ID)
{
    cin >> ID;
}

/*ѧ���˻�������*/
void student_use::stu_account(int n )
{
    system("cls");
    cout << endl << endl << endl << endl;
    cout << "\t\t\t�q������������ ѧ���˻� �����������r" << endl;
    cout << "\t\t\t*������������************����������*" << endl;
    cout << "\t\t\t*            1 �� �� ��  ѯ        * " << endl;
    cout << "\t\t\t*            2 �� �� ��  ѯ        * " << endl;
    cout << "\t\t\t*            3 ��        ֵ        * " << endl;
    cout << "\t\t\t*            4 �� �� ��  Ʒ        * " << endl;
    cout << "\t\t\t*            5 �� Ʒ ��  ��        * " << endl;
    cout << "\t\t\t*            6 ���� �� һ��        * " << endl;
    cout << "\t\t\t*            7 ���� �� �˵�        * " << endl;
    cout << "\t\t\t*            0 �� �� ϵ  ͳ        * " << endl;
    cout << "\t\t\t*������������************����������*" << endl;
    cout << "\t\t\t�t���������������������������������s" << endl;
    cout << endl << endl;
    cout << "\t\t\t������Ҫѡ������֣�";
    int k;
    cin >> k;
    switch(k)
    {
    case 1:
        student1.searchfood('h');
    case 2:
        cout << "\t\t\t������Ϊ��   " << members[n].money << endl;
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
        cout << "\t\t\t��ѡ��0��1��2��3��4��5��6��7�˸����ܼ�...";
        getch();
        manager1.Adm_Windows();
        break;
    }
    stu_account(n);
}

/*ѧ�����ϵͳ����*/
void student_use::buy(int n)
{
    char num[40];
    cout << endl << endl << endl << "\t\t\t�����빺��Ĳ�Ʒ���:";
    cin >> num;
    string information[20][3];
    ifstream f("����.txt", ios::binary);
    for(int i = 0; i < 20; i++)
    {
        f >> information[i][0] >> information[i][1] >> information[i][2];
        if(num == information[i][0])
        {
            cout << endl << endl << "\t���" << "\t����" << "\t�۸�" << endl;
            cout << "\t" << information[i][0] << "\t" << information[i][1] << "\t" << information[i][2];
            char buf[10];
            strcpy(buf, information[i][2].c_str());
            sscanf(buf, "%d", &i);
            if(members[n].money - i > 0)
            {
                members[n].money -= i;
                cout << endl << endl << "\t\t\t������ɣ����Ϊ��" << members[n].money << endl << "\t\t\t1 ���أ�   2 ��������  ";
                ofstream g("ѧ����Ϣ.txt", ios::binary);
                for(i = 0; i < sum; i++)
                {
                    g << members[i].number << "\t" << members[i].name << "\t" << members[i].money << endl;
                }
            }
            else
            {
                cout << endl << endl << "\t\t\t����ʧ�ܣ����㣡" << endl << endl << "                          1 ���أ�   2 ��������  ";
            }
            int a;
            cin >> a;
            switch(a)
            {

            case 1:
                stu_account(n);
            case 2:
                buy(n);
            }
        }
    }
    if(n == 0)
    {
        cout << "\t\t\t��������Ĳ�Ʒ�����ڣ�" << endl << "\t\t\t1 ���أ�   2 ��������        " << endl;
        int a;
        cin >> a;
        switch(a)
        {
        case 1:
            stu_account(n);
        case 2:
            buy(n);
        }
    }
}

/*ѧ����ֵ����*/
void student_use::save_money(int n)
{
    int i;
    cout << endl << endl << endl << "\t\t\t�������ֵ�Ľ��:";
    int money;
    cin >> money;
    members[n].money += money;
    ofstream g("ѧ����Ϣ.txt", ios::binary);
    for(i = 0; i < sum; i++)
        g << members[i].number << "\t" << members[i].name << "\t" << members[i].money << endl;
    cout << endl << "\t\t\t��ֵ�ɹ��������Ϊ��" << members[n].money << endl << endl << "\t\t\t1.������ֵ	        2.����" << endl;
    cin >> i;
    switch(i)
    {

    case 1:
        save_money(n);
    case 2:
        stu_account(n);
    }
}

/*ѧ���û���¼����*/
void student_use::readnumber()
{
    char a[40];
    system("cls");
    cout << endl << endl << endl << endl;
    cout << "\t\t\t�q������������ѧ���û���¼���������������r" << endl;
    cout << "\t\t\t*                                        *" << endl;
    cout << "\t\t\t*          *****************             *" << endl;
    cout << "\t\t\t*         ��ӭ����ѧ������ϵͳ          *" << endl;
    cout << "\t\t\t*          *****************             *" << endl;
    cout << "\t\t\t�t���������������������������������������s" << endl;
    cout << endl << endl << endl << endl;
    cout << endl << endl << "\t\t\t���������ѧ�ţ�";
    cin >> a;
    cout << endl;
    int t = 0, flag = 0;
    for(t = 0; t < sum; t++)
        if(!strcmp(members[t].number, a))
        {
            flag = 1;
            break;
        }
    if(flag)
    {
        cout << "\t\t\t��½�ɹ�(���������)...";
        student1.stu_account(t);
        getch();
        return;
    }
    else
    {
        cout << "\t\t\t��ѧ��û��ע��...";
        getch();
        mainmenu();
    }
}

/*ѧ���˵���Ϣ��ѯ�Ӻ�����ͨ����Ʒ��Ų�ѯ��*/
void User::searchfood_number(char h)
{
    system("cls");
    ifstream f("����.txt", ios::binary);
    string a;
    int n = 0;
    cout << endl << endl << endl << endl;
    cout << "\t\t\t�q�������������˵���ѯ���������������r" << endl;
    cout << "\t\t\t*����������************��������������*" << endl;
    cout << "\t\t\t*         **************             *" << endl;
    cout << "\t\t\t*      ��ӭ������Ʒ��Ų�ѯϵͳ      *" << endl;
    cout << "\t\t\t*         **************             *" << endl;
    cout << "\t\t\t*����������************��������������*" << endl;
    cout << "\t\t\t�t�����������������������������������s" << endl;
    cout << endl << endl;
    cout << "\t\t\t������������ѯ�Ĳ�Ʒ��ţ�";
    cin >> a;
    string information[20][3];
    for(int i = 0; i < 20; i++)
    {
        f >> information[i][0] >> information[i][1] >> information[i][2];
        if(a == information[i][0])
        {
            cout << endl << endl << "\t���" << "\t����" << "\t�۸�" << endl;
            cout << "\t" << information[i][0] << "\t" << information[i][1] << "\t" << information[i][2];
            n = 1;
            cout << endl << endl << "\t\t\t��ѯ��ɣ�" << "\n\t\t\t1 ���أ�   2 ������ѯ  ";
            int a;
            cin >> a;
            switch(a)
            {
            case 1:
                student1.searchfood(h);
            case 2:
                student1.searchfood_number(h);
            default:
                cout << "\t\t\t��ѡ��1��2�������ܼ�...";
                getch();
                student1.searchfood_number(h);
                break;
            }
        }
    }
    if(n == 0)
    {
        cout << "\t\t\t������ѯ�Ĳ�Ʒ�����ڣ�" << "\n\t\t\t1 ���أ�   2 ������ѯ        " << endl;
        int a;
        cin >> a;
        switch(a)
        {
        case 1:
            student1.searchfood(h);
        case 2:
            student1.searchfood_number(h);
        default:
            cout << "\t\t\t��ѡ��1��2�������ܼ�...";
            getch();
            student1.searchfood_number(h);
            break;
        }
    }
}

/*ѧ����Ʒ��Ϣ��ѯ�Ӻ�����ͨ����Ʒ���Ʋ�ѯ��*/
void User::searchfood_name(char h)
{
    system("cls");
    ifstream f("����.txt", ios::binary);
    string a;
    int n = 0;
    cout << endl << endl << endl << endl;
    cout << "\t\t\t�q�������������˵���ѯ���������������r" << endl;
    cout << "\t\t\t*����������************��������������*" << endl;
    cout << "\t\t\t*         **************             *" << endl;
    cout << "\t\t\t*      ��ӭ������Ʒ���Ʋ�ѯϵͳ      *" << endl;
    cout << "\t\t\t*         **************             *" << endl;
    cout << "\t\t\t*����������************��������������*" << endl;
    cout << "\t\t\t�t�����������������������������������s" << endl;
    cout << endl << endl;
    cout << "\t\t\t������������ѯ�Ĳ�Ʒ���ƣ�";
    cin >> a;
    string information[20][3];
    for(int i = 0; i < 20; i++)
    {
        f >> information[i][0] >> information[i][1] >> information[i][2];
        if(a == information[i][1])
        {
            cout << endl << endl << "\t���" << "\t����" << "\t�۸�" << endl;
            cout << "\t" << information[i][0] << "\t" << information[i][1] << "\t" << information[i][2];
            n = 1;
            cout << endl << endl << "\t\t\t��ѯ��ɣ�" << endl << endl << "\n\t\t\t1 ���أ�   2 ������ѯ  " << endl;
            int a;
            cin >> a;
            switch(a)
            {
            case 1:
                student1.searchfood(h);
            case 2:
                student1.searchfood_name(h);
            default:
                cout << "\t\t\t��ѡ��1��2�������ܼ�...";
                getch();
                student1.searchfood_name(h);
                break;
            }
        }
    }
    if(n == 0)
    {
        cout << "\n\t\t\t������ѯ�Ĳ�Ʒ�����ڣ�" << endl << "\n\t\t\t1 ���أ�   2 ������ѯ        " << endl << "\t\t\t";
        int a;
        cin >> a;
        switch(a)
        {
        case 1:
            student1.searchfood(h);
        case 2:
            student1.searchfood_name(h);
        default:
            cout << "\t\t\t��ѡ��1��2�������ܼ�...";
            getch();
            student1.searchfood_name(h);
            break;
        }
    }
}

/*ѧ����Ʒ��Ϣ��ѯ������*/
void User::searchfood(char h)
{
    system("cls");
    cout << endl << endl << endl << endl << endl;
    cout << "\t\t\t�q�������������˵���ѯ���������������r" << endl;
    cout << "\t\t\t*������������************������������*" << endl;
    cout << "\t\t\t*            1 ��ѯ���в�Ʒ          *" << endl;
    cout << "\t\t\t*            2 ����Ų�ѯ            *" << endl;
    cout << "\t\t\t*            3 ��������ѯ            *" << endl;
    cout << "\t\t\t*            4 ���� �� һ��          *" << endl;
    cout << "\t\t\t*            5 ���� �� �˵�          *" << endl;
    cout << "\t\t\t*            0 �� �� ϵ  ͳ          *" << endl;
    cout << "\t\t\t*������������************������������*" << endl;
    cout << "\t\t\t�t�����������������������������������s" << endl;
    cout << endl << endl << endl << endl;
    cout << "\t\t\t��������Ҫѡ������֣�";
    int p;
    cin >> p;
    switch(p)
    {
    case 1:
    {
        system("cls");
        ifstream f("����.txt");
        while(!f.eof())
        {
            char a;
            a = f.get();
            cout << a;
        }
        cout << "\t\t\t��ѯ��ɣ������������";
        getch();
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
        cout << "\t\t\t��ѡ��0��1��2��3��4��5�������ܼ�...";
        getch();
        student1.searchfood(h);
        break;

    }
}

//��������.txt�е�����
void InitialScore()
{
    FILE *fp;
    if((fp = fopen("����.txt", "a")) == NULL)
    {
        printf("can't open the file ����.txt\n");
        exit(0);
    }
    fclose(fp);
    //�������еĲ�Ʒȫ������������FoodMssage������
    if((fp = fopen("����.txt", "r")) == NULL)
    {
        printf("can't open the file ����.txt\n");
        exit(0);
    }
    int num = 0;
    char foodname[20];
    char foodid[20];
    char foodprice[20];
    fseek(fp, 0, SEEK_SET);     /*��дλ���ƶ����ļ���ʼ��*/
    while(!feof(fp))                    /*����ļ��Ƿ����*/
    {
        fscanf(fp, "%s %s %s", foodid, foodname, foodprice);
        strcpy(FoodMssage[num].FoodId, foodid);
        strcpy(FoodMssage[num].FoodName, foodname);
        FoodMssage[num].socre = 0;
        FoodMssage[num].socernum = 0;
        foodnum = num;
        num++;
    }
    fclose(fp);
    //������.txt�е�������Ϣȫ�����뵽FoodMssage������
    if((fp = fopen("����.txt", "r")) == NULL)
    {
        printf("can't open the file ����.txt\n");
        exit(0);
    }
    num = 0;
    int foodscore = 0;
    int foodscorenum = 0;
    fseek(fp, 0, SEEK_SET);    /*��дλ���ƶ����ļ���ʼ��*/
    while(!feof(fp))                    /*����ļ��Ƿ����*/
    {
        fscanf(fp, "%s %s %d %d", foodid, foodname, &foodscore, &foodscorenum);
        for (num = 0; num < 20; num++)
        {
            if ((strcmp(FoodMssage[num].FoodId, foodid) == 0) && (strcmp(FoodMssage[num].FoodName, foodname) == 0))
            {
                FoodMssage[num].socre = foodscore;
                FoodMssage[num].socernum = foodscorenum;
            }
        }
    }
    fclose(fp);
    //��FoodMssage�����и��º��������Ϣȫ�����뵽����.txt��
    if((fp = fopen("����.txt", "w")) == NULL)
    {
        printf("can't open the file ����.txt\n");
        exit(0);
    }
    for (num = 0; num < foodnum; num++)
    {
        fprintf(fp, "%s %s %d %d \n", FoodMssage[num].FoodId, FoodMssage[num].FoodName, FoodMssage[num].socre, FoodMssage[num].socernum);
    }
    fclose(fp);

}

//������.txt��������ݵ�������
NodeTp *GetData()
{
    NodeTp *h, *p, *last;
    CreateNode(h);//����ͷ���
    last = h;
    FILE *fp;
    if((fp = fopen("����.txt", "r")) == NULL)
    {
        printf("can't open the file ����.txt\n");
        exit(0);
    }

    fseek(fp, 0, SEEK_SET);    //��дλ���ƶ����ļ���ʼ��
    while(!feof(fp))                    //����ļ��Ƿ����
    {
        CreateNode(p);//����һ���µĽڵ�
        fscanf(fp, "%s %s %d %d", p->data.FoodId, p->data.FoodName, &p->data.socre, &p->data.socernum);
        last ->next = p;
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

/*����Ա�鿴ѧ�������������*/
void ShowFoodScore()
{
    system("cls");
    NodeTp *h, *p;
    h = GetData();
    cout << "\t   ��Ʒ���\t   ��Ʒ����\t   ��Ʒ����\t   ����������" << endl;
    p = h->next;//hΪͷָ��
    //��������е���Ϣ
    while(p)
    {
        cout << "\t\t" << p->data.FoodId << "\t\t" << p->data.FoodName << "\t\t" << p->data.socre << "\t\t" << p->data.socernum << endl;
        p = p->next;
    }
    getch();
    manager1.Adm_Windows();
}

/*ѧ�������������*/

void WriteScore()
{
    InitialScore();
    int num = 0;
    char foodname[20];
    char foodid[20];
    int foodscore = 0;
    cout << "\t\t\t�����������۵Ĳ�Ʒ���:";
    cin >> foodid;
    cout << "\t\t\t�����������۵Ĳ�Ʒ����:";
    cin >> foodname;
    cout << "\t\t\t��������������:";
    cin >> foodscore;
    for (num = 0; num < 20; num++)
    {
        if ((strcmp(FoodMssage[num].FoodId, foodid) == 0) && (strcmp(FoodMssage[num].FoodName, foodname) == 0)) //��֤��Ʒ��ź������Ƿ���ȷ
        {
            FoodMssage[num].socernum++;
            FoodMssage[num].socre = (FoodMssage[num].socre + foodscore) / FoodMssage[num].socernum;
            break;
        }
    }
    if (20 == num)
    {
        cout << "\t\t\t������Ĳ�Ʒ��Ż��߲�Ʒ��������!";
        return;
    }
    FILE *fp;
    if((fp = fopen("����.txt", "w")) == NULL)
    {
        printf("can't open the file ����.txt\n");
        exit(0);
    }
    for (num = 0; num < foodnum; num++)
    {
        fprintf(fp, "%s %s %d %d \n", FoodMssage[num].FoodId, FoodMssage[num].FoodName, FoodMssage[num].socre, FoodMssage[num].socernum); //������Ϣ�������ļ���
    }
    fclose(fp);
}

/************������**************/
int main()
{
    InitialFile();
    InitialScore();
    FILE *fin = fopen("ѧ����Ϣ.txt", "r");
    int i = 0;
    while(fscanf(fin, "%s %s %d", members[i].number, members[i].name, &members[i].money) != EOF)
        i++;
    sum = i;
    mainmenu();
    return 0;
}



