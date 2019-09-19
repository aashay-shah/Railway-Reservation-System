#include<iostream>
#include<cstdio>
#include<fstream>
#include<sstream>
#include<string>
#include<cstdlib>
#include<conio.h>
#include<windows.h>
#include<mysql.h>
using namespace std;
int qstate;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;
class db_response
{
public:
    static void ConnectionFunction()
    {
        conn = mysql_init(0);
        if (conn)
        {
            cout << "Database Connected" << endl;
            cout << "Press any key to continue..." << endl;
            // getch();
            system("cls");
        }
        else
            cout << "Failed To Connect!" << mysql_errno(conn) << endl;
        conn = mysql_real_connect(conn, "localhost", "root", "123456", "railway", 0, NULL, 0);
        if (conn)
        {
            cout << "Database Connected To MySql" << conn << endl;
            cout << "Press any key to continue..." << endl;
            // getch();
            system("cls");
        }
        else
            cout << "Failed To Connect!" << mysql_errno(conn) << endl;
    }
};
void Welcome()
{
    cout << "Welcome To Railway Reservation System" << endl << endl;
}
void admin();
void user();
void new_user();
void disp_user();
void block_user();
void disp_pas();
void reserve();
void cancel();
void enquire();
int main()
{
    //clrscr();
    system("cls");
    db_response::ConnectionFunction();
    int choice;
    //string u,p;
    do
    {
        Welcome();
        cout<<"^^^^^^^^^^^^^^^^^^^^^^MAIN MENU^^^^^^^^^^^^^^^^^^^^\n";
        cout<<"1.Admin mode\n2.User mode\n3.New User\n4.Exit\n";
        cout<<"Enter your choice:";
        cin>>choice;
        cout<<endl;
        switch(choice)
        {
        case 1:admin();
            break;
        case 2:user();
            break;
        case 3:new_user();
            break;
        case 4:break;
        }
    }while(choice!=4);
return 0;
}
void admin()
{
    string u,p;
    cout<<"Enter User-Id:"<<endl;
    cin>>u;
    cout<<"Enter Password:"<<endl;
    cin>>p;
    system("cls");
    qstate = mysql_query(conn, "SELECT * FROM login where ROLE='admin'");
    if(!qstate)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {
            if(row[1]==u && row[2]==p)
            {
                cout<<"Login Successfull"<<endl;
                int choice;
                do
                {
                    cout<<"...........ADMINISTRATOR MENU...........\n";
                    cout<<"1. Display User Details\n2. Block User\n3. Display Passenger Details\n4. Return to Main Menu"<<endl;
                    cout<<"Enter your choice:";
                    cin>>choice;
                    cout<<endl;
                    switch(choice)
                    {
                        case 1:disp_user();
                            break;
                        case 2:block_user();
                            break;
                        case 3:disp_pas();
                            break;
                        case 4:break;
                    }
                }while(choice!=4);
            }
            else
            {
                cout<<"Password Incorrect"<<endl;
            }
        }

    }
}
void user()
{
    string u,p;
    int c=0;
    cout<<"Enter User-Id:"<<endl;
    cin>>u;
    cout<<"Enter Password:"<<endl;
    cin>>p;
    system("cls");
    qstate = mysql_query(conn, "SELECT * FROM login where ROLE='user'");
    if(!qstate)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {
            if(row[1]==u && row[2]==p)
            {
                c++;
            }
        }
    }
    if(c==1)
    {
        cout<<"Login Successful"<<endl;
        int choice;
        do
        {
            cout<<"...........USER MENU...........\n";
            cout<<"1. Book Ticket\n2. Cancel Ticket\n3. Enquire\n4. Return to Main Menu"<<endl;
            cout<<"Enter your choice:";
            cin>>choice;
            switch(choice)
            {
                case 1:reserve();
                    break;
                case 2:cancel();
                    break;
                case 3:enquire();
                    break;
                case 4:break;
            }
        }while(choice!=4);
    }
    else
    {
        cout<<"Incorrect Password"<<endl;
    }
}
void new_user()
{
    string name,pswrd,role;
    cout<<"Create a User Name:"<<endl;
    cin>>name;
    cout<<"Create a Password:"<<endl;
    cin>>pswrd;
    role="user";
    system("cls");
    string create_user ="INSERT INTO login(USER_NAME,PASSWORD,ROLE) VALUES ('"+name+"','"+pswrd+"','"+role+"')";
    const char* q = create_user.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {
        cout<<"Account Successfully Created"<< endl;
    }
    else
    {
        cout<<"User Name Already Exists"<<endl;
    }
}
void disp_user()
{
    system("cls");
    qstate = mysql_query(conn, "SELECT * FROM login");
    if (!qstate)
    {
        res = mysql_store_result(conn);
        printf("| %-15s | %-15s | %-15s | %-15s |\n", "User ID", "User Name", "Password", "Role");
        while ((row = mysql_fetch_row(res)))
        {
            printf("| %-15s | %-15s | %-15s | %-15s |\n", row[0], row[1], row[2], row[3]);
        }
    }
}
void block_user()
{
    string id;
    cout<<"Enter User Id whose Account needs to be Blocked:";
    cin>>id;
    cout<<endl;
    system("cls");
    string delete_record ="DELETE FROM login WHERE USER_ID = '"+id+"'";
    const char* q = delete_record.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {
        cout<<"Account Successfully Blocked"<<endl;
    }
    else
    {
        cout<<"Error Occured" << mysql_errno(conn)<<endl;
    }
}
void disp_pas()
{
    system("cls");
    qstate = mysql_query(conn, "SELECT p.P_ID,p.P_NAME,p.AGE,p.TRAIN_ID,t.T_NAME,p.CLASS,p.COST FROM passenger p INNER JOIN train t ON p.TRAIN_ID=t.PNR");
    if (!qstate)
    {
        res = mysql_store_result(conn);
        printf("| %-5s | %-10s | %-5s | %-8s | %-10s | %-5s | %-5s |\n", "Pass ID", "Pass Name", "Age", "Train ID", "Train Name", "Class", "Cost");
        while ((row = mysql_fetch_row(res)))
        {
            printf("| %-5s | %-10s | %-5s | %-8s | %-10s | %-5s | %-5s |\n", row[0], row[1], row[2], row[3], row[4], row[5], row[6],row[7]);
        }
    }
}
void reserve()
{
    string name,cl;
    int age,pnr,costf,costs,cf,cs;
    cout<<endl;
    cout<<"Enter name:";
    cin>>name;
    cout<<"Enter age:";
    cin>>age;
    cout<<"Enter PNR number:";
    cin>>pnr;
    cout<<"Enter class - First or Second:";
    cin>>cl;
    system("cls");
    qstate = mysql_query(conn, "SELECT FC_T,FC_C,SC_T,SC_C FROM train WHERE PNR='pnr'");
    if(!qstate)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {
            cf=int(row[0]);
            costf=int(row[1]);
            cs=int(row[2]);
            costs=int(row[3]);
        }
    }
    if(cl=="First")
    {
        //cout<<cf<<endl;
        //cout<<costf<<endl;
        if(cf!=0)
        {
            system("cls");
            string add_book ="INSERT INTO passenger(P_NAME,AGE,TRAIN_ID,CLASS,COST) VALUES ('"+name+"','+age+','+pnr+','"+cl+"','+costf+')";
            const char* q1 = add_book.c_str();
            qstate = mysql_query(conn, q1);
            cout<<"Payment to be made:"<<costf<<endl;
            cf--;
            string update_avail="UPDATE train SET FC_T=cf WHERE PNR='pnr'";
            const char* q2 = update_avail.c_str();
            qstate = mysql_query(conn, q2);
        }
        else
        {
            cout<<"No Tickets Available in this class"<<endl;
        }
    }
    if(cl=="Second")
    {
        if(cs!=0)
        {
            system("cls");
            string add_booking="INSERT INTO passenger(P_NAME,AGE,TRAIN_ID,CLASS,COST) VALUES ('"+name+"','+age+','+pnr+','"+cl+"','+costs+')";
            const char* q3 = add_booking.c_str();
            qstate = mysql_query(conn, q3);
            cout<<"Payment to be made:"<<costs<<endl;
            cs--;
            string update_avail="UPDATE train SET SC_T=cs WHERE PNR='pnr'";
            const char* q4 = update_avail.c_str();
            qstate = mysql_query(conn, q4);
        }
        else
        {
            cout<<"No Tickets Available in this class"<<endl;
        }
    }
}
void cancel()
{
    string cl;
    int id,tid;
    cout<<endl;
    cout<<"Enter Passenger ID:";
    cin>>id;
    system("cls");
    qstate = mysql_query(conn, "SELECT CLASS,TRAIN_ID FROM passenger WHERE PNR='pnr'");
    if(!qstate)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {
            cl=row[0];
            tid=int(row[1]);
        }
    }
    system("cls");
    string remove_booking="DELETE FROM passenger WHERE P_ID='id'";
    const char* q = remove_booking.c_str();
    qstate = mysql_query(conn, q);
    if(cl=="First")
    {
        system("cls");
        string update_avail="UPDATE train SET FC_T=(FC_T+1) WHERE PNR='tid'";
        const char* q1 = update_avail.c_str();
        qstate = mysql_query(conn, q1);
    }
    if(cl=="Second")
    {
        system("cls");
        string update_avail="UPDATE train SET SC_T=(SC_T+1) WHERE PNR='tid'";
        const char* q2 = update_avail.c_str();
        qstate = mysql_query(conn, q2);
    }
    cout<<"Ticket Successfully Cancelled"<<endl;
}
void enquire()
{
    int pnr;
    cout<<endl;
    cout<<"Enter PNR Number:";
    cin>>pnr;
    system("cls");
    qstate = mysql_query(conn, "SELECT * FROM train WHERE PNR=pnr");
    if (!qstate)
    {
        res = mysql_store_result(conn);
        printf("| %-3s | %-8s | %-5s | %-5s | %-3s | %-3s | %-3s | %-3s |\n", "PNR", "Train Name", "Source", "Dest", "Ist Avail", "Ist Cost", "IInd Avail", "IInd Cost");
        while ((row = mysql_fetch_row(res)))
        {
            printf("| %-3s | %-8s | %-5s | %-5s | %-3s | %-3s | %-3s | %-3s |\n", row[0], row[1], row[2], row[3], row[4], row[5], row[6],row[7],row[8]);
        }
    }

}

