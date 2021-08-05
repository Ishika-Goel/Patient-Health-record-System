#include <iostream>
#include <windows.h>
#include <mysql.h>
#include<cstdio>
#include<cstdlib>
#include<conio.h>
#include <sstream>
#include <mmsystem.h>
#include<bits/stdc++.h>
#pragma comment (lib, "winmm.lib")
#include<tchar.h>
#include<algorithm>
#include<graphics.h>
#include<string>

using namespace std;
MYSQL* conn;
int qstate;
MYSQL_RES* res;
MYSQL_ROW row;
queue<string> q1;
queue<string> q2;
queue<string> q3;
queue<string> q4;
queue<string> q5;
queue<string> q6;
int r1,r2,r3,r4,r5,r6=0;
vector<string> v;

const char* hostname = "localhost";
const char* username = "root";
const char* password = "";
const char* database = "cppdatabase";
unsigned int port = 3306;
const char* unixsocket = NULL;
unsigned long clientflag = 0;

void welcome();
void display_menu();


MYSQL* connectdatabase(){

    conn=mysql_init(0);
    conn=mysql_real_connect(conn,hostname,username,password,database,port,unixsocket,clientflag);
    if(conn){
        cout<<"connected to database"<<endl;
        return conn;
    }
    else{
        cout<<"Failed to connect to database"<<endl;\
        return conn;
    }
}

class patient{
	private:
		string history,symptoms,d_remarks,mode,medicines;
		string room_no,bill_no;
		string bill;


	public:
		string f_name,l_name,gender,pid,date;
		string height,weight;
		string doc_id,mob,marital,address,bg,disease;
		string dob,no_of_visits;
     	void patientbiodata();
        void patient_treatment_data();
        void display_all();
        void search_patient();
        void update_record();
        void schedule_appointment(string patientID);
        void display_appointments(string docID);
        void generate_bill(string patient_id);
        int unique_id(string pid);
        int unique_appointments(string id);
	};

class doctor{
	public:
		string doc_id,doc_name,gender,Ddob,doc_email;
		string specialization,doc_mob,timings,address;
		void doctor_information();
		void display_all();
		void search_doctor();
		void doctor_update();


};

int patient::unique_id(string pid){
 string find_by_id="select * from patient_biodata where Pid like '%"+pid+"%'";
        const char* qn = find_by_id.c_str();
        qstate = mysql_query(conn, qn);

    cout << endl;
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {
            if(!row[0])
                return 1;
            else return 0;
        }

    }

}


	void patient::patientbiodata(){
        system("CLS");
        cout<<"\n\n\tPATIENT REGISTRATION - \n";
        cout<<"\t____________________________________"<<endl;
     iid:
        cout<<"\n\t - ID                        : ";
        cin>>pid;
        if(unique_id(pid)==0){
            cout<<"\n\tID already exists.\n\tEnter Unique ID\n";
            pid="";
            goto iid;
        }

        cout<<"\n\t - Date                : ";
		cin>>date;
		cout<<"\n\t - First Name                : ";
		cin>>f_name;
		cout<<"\n\t - Last Name                 : ";
		cin>>l_name;
		cout<<"\n\t - Gender                    : ";
		cin>>gender;
		cout<<"\n\t - Date of birth              : ";
		cin>>dob;
        cout<<"\n\t - Height                    : ";
		cin>>height;
		cout<<"\n\t - Weight                    : ";
		cin>>weight;
	    cout<<"\n\t - Mobile Number             : ";
		cin>>mob;
		cout<<"\n\t - Address                   : ";
		cin>>address;
		cout<<"\n\t - Marital status            : ";
		cin>>marital;
		cout<<"\n\t - Blood group               : ";
		cin>>bg;
        stringstream ss;
       ss <<"INSERT INTO patient_biodata (Date,Pid,Fname, Lname,Gender,DOB,Height,Weight,MOB,Address,MaritalStatus,Bloodgroup) VALUES ('"+date+"','"+pid+"', '"+f_name+"', '"+l_name+"','"+gender+"','"+dob+"','"+height+"','"+weight+"','"+mob+"','"+address+"','"+marital+"','"+bg+"')";
        string query=ss.str();
const char* q = query.c_str();
qstate = mysql_query(conn,q);
cout<<qstate<<endl;
if(!qstate){
    cout<<"Record inserted.....\n";
}
else{
    cout<<"failed to insert.....\n";
}

        getch();

	}

	void patient::patient_treatment_data(){
	system("CLS");
	    cout<<"\n\n\tPATIENTS TREATMENT DATA\n";
	    cout<<"\t__________________________________\n\n";
        cout<<"\n - ID                        : ";
        cin>>pid;
     	cout<<"\n - Medical history if any    : ";
        cin>>history;
		cout<<"\n - Symptoms                  : ";
		cin>>symptoms;
		//cout<<"\n - Disease                   : ";
	//	cin>>disease;
      //  cout<<"\n - Prescribed medicines      : ";
	//	cin>>medicines;
        cout<<"\n - No. of visits             : ";
		cin>>no_of_visits;
		cout<<"\n - Room alloted              : ";
		cin>>room_no;
		cout<<"\n - Consulting Doctor_id      : ";
		cin>>doc_id;

		  stringstream ss;
       ss <<"INSERT INTO patient_treatment_data(Pid, MedicalHistory, Symptoms,visits, RoomAlloted, DoctorId) VALUES ('"+pid+"', '"+history+"', '"+symptoms+"','"+no_of_visits+"','"+room_no+"','"+doc_id+"')";
       string query = ss.str();
       const char* q = query.c_str();
qstate = mysql_query(conn,q);
if(qstate==0){
    cout<<"Record inserted.....\n";
}
else{
    cout<<"failed to insert.....\n";
}

  if(unique_appointments(pid)==1){
         schedule_appointment(pid);
         v.push_back(pid);
    }
    else{
        cout<<"\n\tAppointment is already scheduled for this ID.\n\t";
    }

}

    void patient::display_all(){
    system("CLS");
    cout<<"\n\n\t\t\t\t\t\t\t\tPATIENTS BIODATA\n\n\n";
    qstate = mysql_query(conn, "select * from patient_biodata");
     if (!qstate)
    {
        res = mysql_store_result(conn);
        cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------\n";
        printf("| %-5s | %-15s | %-15s | %-5s | %-10s | %-5s | %-5s | %-10s | %-25s | %-10s | %-5s \n","Pid", "Fname", "Lname", "Gender", "DOB", "Height","Weight","MOB","Address","MaritalStatus","Bloodgroup");
        cout<<("------------------------------------------------------------------------------------------------------------------------------------------------------\n");

        while ((row = mysql_fetch_row(res)))
        {
            printf("| %-5s | %-15s | %-15s | %-5s | %-10s | %-5s | %-5s | %-10s | %-30s | %-10s | %-5s \n", row[1], row[2], row[3], row[4], row[5], row[6],row[7],row[8],row[9],row[10],row[11]);
        }
        cout<<"--------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    }
    else
    {
        cout << "Query Execution Problem!" << endl;
    }


    /* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
    cout<<"\nPress enter to view Patients treatment data\n";
    getch();

    system("CLS");
    qstate = mysql_query(conn, "select * from patient_treatment_data");
    cout<<"\n\t\t\t\t\t\t\t\t\PATIENTS TREATMENT DATA\n\n";
     if (!qstate)
    {
        res = mysql_store_result(conn);
        cout<<"-----------------------------------------------------------------------------------------------------------------------------\n";
        printf("| %-15s  %-15s | %-15s | %-15s \n","Pid", "visits","RoomAlloted","DoctorId");
        cout<<("----------------------------------------------------------------------------------------------------------------------------\n");

        while ((row = mysql_fetch_row(res)))
        {
            printf("| %-15s  %-15s | %-15s | %-15s \n", row[0], row[5], row[6],row[7]);
        }
        cout<<"-----------------------------------------------------------------------------------------------------------------------------\n";
    }
    else
    {
        cout << "Query Execution Problem!" << endl;
    }

    cout<<"\nPATIENT'S DISEASE AND DIAGONISTIC REPORTS ARE PRIVATE, THEY CAN'T BE SHOWN ALL AT ONCE......\n\n";
    cout<<"\nPress ENTER to continue\n";
    getch();

}

    void patient::search_patient(){
        char *path;
        string reports;
 l:
     system("CLS");
        cout<<"\n\tPatient's TREATMENT data can be seen only by PATIENTS ID\n\n";
        cout<<"\n\t1 Search by ID.\n\t2 Search by Fname.\n\t3 Search by Lname.\n\t4 Search by DOB.\n\t5 Search by Blood group.\n\n\t";

        int k;
        cin>>k;
        cout<<endl;
        if(k==1){
        cout<<"\n\tEnter ID : ";
        string input;
        cin>>input;
        string find_by_id="select * from patient_biodata where Pid like '"+input+"'";
        const char* qn = find_by_id.c_str();
        qstate = mysql_query(conn, qn);

    cout << endl;
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {
             printf("\t| %-5s | %-10s | %-15s | %-15s | %-8s | %-6s | %-6s | %-10s | %-20s | %-5s \n","Pid", "Fname", "Lname", "Gender", "DOB", "Height","Weight","MOB","Address","Bloodgroup");
        cout<<("\t------------------------------------------------------------------------------------------------------------------------------------------\n");
             printf("\t| %-5s | %-10s | %-15s | %-15s | %-8s | %-6s | %-6s | %-10s | %-20s | %-5s \n", row[1], row[2], row[3], row[4], row[5], row[6],row[7],row[8],row[9],row[11]);

        }
    }
        getch();
        cout<<"\nDo you want to view Patient's treatment data?[Y/N]\n\n";
        char x;
        cin>>x;
        if(x=='y'||x=='Y'){

    system("CLS");
    string find_= "select * from patient_treatment_data where Pid like '%"+input+"%'";
    const char* qn=find_.c_str();
    qstate = mysql_query(conn,qn);

     if (!qstate)
    {
        res = mysql_store_result(conn);
      //  cout<<"\t-----------------------------------------------------------------------------------------------------------------------------------------------\n";
     //   printf("\n\t%-5s\n\t%-20s\n\t%-40s\n\t%-25s | %-45s| %-15s| %-15s| %-15s\n","Pid","MedicalHistory","Symptoms","Disease","Medicines", "visits","RoomAlloted","DoctorId");
       // cout<<("\t----------------------------------------------------------------------------------------------------------------------------------------------\n");

        while ((row = mysql_fetch_row(res)))
        {
            printf("\n\n\n\tPID: %-5s\n\n\tMedical History: %-20s\n\n\tSymptoms: %-40s\n\n\tDisease: %-25s\n\n\tMedicines: %-45s\n\n\tVisits: %-15s\n\n\tRoom:  %-10s\n\n\tDoctorId: %-15s\n\n\t", row[0],row[1],row[2],row[3],row[4],row[5], row[6], row[7]);
             path=row[8];
             reports=row[9];
        }

    cout<<"----------------------------------------------------------------------------------------------------------------\n";

    }
    else
    {
        cout << "Query Execution Problem!" << endl;
    }
        }
         getch();

         if(reports!=""){
        cout<<"\nDo you want to View Patient's Diagonistic  Reports?[Y/N]\n\n";
        char t;
        cin>>t;

        if(t=='y'||t=='Y'){

 ShellExecute(NULL,"open",path,NULL,NULL,SW_NORMAL);

        }


    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }
    getch();


        }
        }
       else if(k==2){
        cout<<"\nEnter first name"<<endl;
        string input;
        cin>>input;
        string find_by_fname="select * from patient_biodata where Fname like '"+input+"'";
        const char* qn = find_by_fname.c_str();
        qstate = mysql_query(conn, qn);

    cout << endl;
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {
            printf("\t| %-5s | %-10s | %-15s | %-15s | %-8s | %-6s | %-6s | %-10s | %-20s | %-5s \n","Pid", "Fname", "Lname", "Gender", "DOB", "Height","Weight","MOB","Address","Bloodgroup");
        cout<<("\t------------------------------------------------------------------------------------------------------------------------------------------\n");
             printf("\t| %-5s | %-10s | %-15s | %-15s | %-8s | %-6s | %-6s | %-10s | %-20s | %-5s \n", row[1], row[2], row[3], row[4], row[5], row[6],row[7],row[8],row[9],row[11]);

        }
    }

    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }
getch();
       }
   else if(k==3){
        cout<<"\nEnter last name"<<endl;
        string input;
        cin>>input;
        string find_by_lname="select * from patient_biodata where Lname like '%"+input+"%'";
        const char* qn = find_by_lname.c_str();
        qstate = mysql_query(conn, qn);

    cout << endl;
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {
             printf("\t| %-5s | %-10s | %-15s | %-15s | %-8s | %-6s | %-6s | %-10s | %-20s | %-5s \n","Pid", "Fname", "Lname", "Gender", "DOB", "Height","Weight","MOB","Address","Bloodgroup");
        cout<<("\t------------------------------------------------------------------------------------------------------------------------------------------\n");
             printf("\t| %-5s | %-10s | %-15s | %-15s | %-8s | %-6s | %-6s | %-10s | %-20s | %-5s \n", row[1], row[2], row[3], row[4], row[5], row[6],row[7],row[8],row[9],row[11]);

        }
    }

    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }
getch();
   }
   else if(k==4){
        cout<<"\nEnter DOB."<<endl;
    string input;
        cin>>input;
        string find_by_DOB="select * from patient_biodata where DOB like '%"+input+"%'";
        const char* qn = find_by_DOB.c_str();
        qstate = mysql_query(conn, qn);

    cout << endl;
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {
            printf("\t| %-5s | %-10s | %-15s | %-15s | %-8s | %-6s | %-6s | %-10s | %-20s | %-5s \n","Pid", "Fname", "Lname", "Gender", "DOB", "Height","Weight","MOB","Address","Bloodgroup");
        cout<<("\t------------------------------------------------------------------------------------------------------------------------------------------\n");
             printf("\t| %-5s | %-10s | %-15s | %-15s | %-8s | %-6s | %-6s | %-10s | %-20s | %-5s \n", row[1], row[2], row[3], row[4], row[5], row[6],row[7],row[8],row[9],row[11]);

        }
    }

    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }
getch();
   }
    else if(k==5){
        string input;
        cin>>input;
        string find_by_name="select * from patient_biodata where Bloodgroup like '%"+input+"%'";
        const char* qn = find_by_name.c_str();
        qstate = mysql_query(conn, qn);

    cout << endl;
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {
             printf("\t| %-5s | %-10s | %-15s | %-15s | %-8s | %-6s | %-6s | %-10s | %-20s | %-5s \n","Pid", "Fname", "Lname", "Gender", "DOB", "Height","Weight","MOB","Address","Bloodgroup");
        cout<<("\t------------------------------------------------------------------------------------------------------------------------------------------\n");
             printf("\t| %-5s | %-10s | %-15s | %-15s | %-8s | %-6s | %-6s | %-10s | %-20s | %-5s \n", row[1], row[2], row[3], row[4], row[5], row[6],row[7],row[8],row[9],row[11]);

        }
    }

    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }
getch();
    }
   else{
    cout<<"Invalid input"<<endl;
    cout<<"Try again...."<<endl;
    getch();
    goto l;
   }

    }

	void doctor::doctor_information(){
	      system("CLS");
        cout<<"\n - Doctor's ID               : ";
        cin>>doc_id;
		cout<<"\n - Dr. Name                : ";
		cin>>doc_name;
		cout<<"\n - Gender                    : ";
		cin>>gender;
		cout<<"\n - Specialization                    : ";
		cin>>specialization;
		cout<<"\n - Date of birth              : ";
		cin>>Ddob;
	    cout<<"\n - Mobile Number             : ";
		cin>>doc_mob;
		cout<<"\n - Timings                    : ";
		cin>>timings;
		cout<<"\n - Email                    : ";
		cin>>doc_email;
		cout<<"\n - Address                   : ";
		cin>>address;
        stringstream ss;
		ss <<"INSERT INTO doctors_record (Did, Name, Gender, Specialization, DOB, MOB, Timings, Email, Address) VALUES ('"+doc_id+"', '"+doc_name+"', '"+gender+"','"+specialization+"','"+Ddob+"','"+doc_mob+"','"+timings+"','"+doc_email+"','"+address+"')";
        string query=ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn,q);
        cout<<qstate<<endl;
        if(!qstate){
            cout<<"Record inserted.....\n";
    }
        else{
            cout<<"failed to insert.....\n";
    }

        getch();


	}

	void doctor::display_all(){
	  qstate = mysql_query(conn, "select * from doctors_record");

     if (!qstate)
    {
        res = mysql_store_result(conn);
        cout<<"----------------------------------------------------------------------------------------------------------------------------------------------------\n";
        printf("| %-5s | %-20s | %-5s | %-25s | %-10s | %-10s | %-15s | %-15s \n","Did", "Name", "Gender", "Specialization", "DOB", "MOB","Timings","Email");
        cout<<("---------------------------------------------------------------------------------------------------------------------------------------------------\n");

        while ((row = mysql_fetch_row(res)))
        {
            printf("| %-5s | %-20s | %-5s | %-25s | %-10s | %-10s | %-15s | %-15s \n", row[0],row[1], row[2], row[3], row[4], row[5], row[6],row[7]);
        }
        cout<<"-----------------------------------------------------------------------------------------------------------------------------------------------------\n";
    }
    else
    {
        cout << "Query Execution Problem!" << endl;
    }
    getch();
    getch();

	}

	void doctor::search_doctor(){
	lm:
	    system("CLS");
    cout<<"\n1 Search by ID.\n2 Search by name.\n3 Search by Specialization.\n4 Search by Timings.\n";
	int u;
	cin>>u;
	if(u==1){
       string input;
       cout<<"\nEnter ID"<<endl;
       cin>>input;
       string find_by_ID="select * from doctors_record where Did like '%"+input+"%'";
       const char* qn = find_by_ID.c_str();
       qstate=mysql_query(conn,qn);

    cout << endl;
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {
             printf("| %-15s | %-20s | %-5s | %-20s | %-15s | %-15s | %-15s | %-20s | %-25s\n","Did", "Name", "Gender", "Specialization", "DOB", "MOB","Timings","Email","Address");
        cout<<("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
             printf("| %-15s | %-20s | %-5s | %-20s | %-15s | %-15s | %-15s | %-20s | %-25s \n", row[0],row[1], row[2], row[3], row[4], row[5], row[6],row[7],row[8]);

        }
    }

    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }
    cout<<"\nPress ENTER to continue..\n";
getch();
getch();
	}
	else if(u==2){
         string input;
       cout<<"\nEnter name"<<endl;
       cin>>input;
       string find_by_name="select * from doctors_record where Name like '%"+input+"%'";
       const char* qn = find_by_name.c_str();
       qstate=mysql_query(conn,qn);

    cout << endl;
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {
              printf("| %-15s | %-20s | %-5s | %-20s | %-15s | %-15s | %-15s | %-20s | %-25s\n","Did", "Name", "Gender", "Specialization", "DOB", "MOB","Timings","Email","Address");
        cout<<("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
             printf("| %-15s | %-20s | %-5s | %-20s | %-15s | %-15s | %-15s | %-20s | %-25s \n", row[0],row[1], row[2], row[3], row[4], row[5], row[6],row[7],row[8]);

        }
    }

    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }
         cout<<"\nPress ENTER to continue..\n";
getch();
getch();
	}
	else if(u==3){
         string input;
       cout<<"\nEnter Specialization"<<endl;
       cin>>input;
       string find_by_spec="select * from doctors_record where Specialization like '%"+input+"%'";
       const char* qn = find_by_spec.c_str();
       qstate=mysql_query(conn,qn);

    cout << endl;
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {
             printf("| %-15s | %-20s | %-5s | %-20s | %-15s | %-15s | %-15s | %-20s | %-25s\n","Did", "Name", "Gender", "Specialization", "DOB", "MOB","Timings","Email","Address");
        cout<<("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
             printf("| %-15s | %-20s | %-5s | %-20s | %-15s | %-15s | %-15s | %-20s | %-25s \n", row[0],row[1], row[2], row[3], row[4], row[5], row[6],row[7],row[8]);

        }
    }

    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }
 cout<<"\nPress ENTER to continue..\n";
getch();
getch();
	}
	else if(u==4){
         string input;
       cout<<"\nEnter timings"<<endl;
       cin>>input;
       string find_by_timing="select * from doctors_record where Timings like '%"+input+"%'";
       const char* qn = find_by_timing.c_str();
       qstate=mysql_query(conn,qn);

    cout << endl;
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {
              printf("| %-15s | %-20s | %-5s | %-20s | %-15s | %-15s | %-15s | %-20s | %-25s\n","Did", "Name", "Gender", "Specialization", "DOB", "MOB","Timings","Email","Address");
        cout<<("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
             printf("| %-15s | %-20s | %-5s | %-20s | %-15s | %-15s | %-15s | %-20s | %-25s \n", row[0],row[1], row[2], row[3], row[4], row[5], row[6],row[7],row[8]);

        }
    }

    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }
    cout<<"\nPress ENTER to continue..\n";
getch();
getch();

	}
	else{
        cout<<"Invalid input"<<endl;
        cout<<"\nPlease try again\n";
    getch();
    goto lm;
	}
	}

	void doctor::doctor_update(){
  string id;
    pq:
        system("CLS");
     cout<<"\nEnter Doctor's ID to be updated:  ";
     cin>>id;
     getch();
   ir:
     cout<<"\nSelect what do you want to update?\n1 Name\n2 Gender\n3 Specialization\n4 DOB\n5 MOB\n6 Timings\n7 Email\n8 Address\n9 Exit\n"<<endl;
     int change;
     cin>>change;
     if(change==1){
        string qq="select * from doctors_record where Did like '%"+id+"%'";
        const char* qn=qq.c_str();
        qstate=mysql_query(conn,qn);
        if(!qstate){
            res=mysql_store_result(conn);
            while((row=mysql_fetch_row(res))){
                cout<<"\nCurrent data is: Name - "<<row[1]<<endl;
            }
        }

        cout<<"\nEnter the updated data\n";
        string updated_input;
        cin>>updated_input;
        string update_query="update doctors_record set Name='"+updated_input+"' where Did like '%"+id+"%'";
        const char* qu = update_query.c_str();
        qstate = mysql_query(conn, qu);
            if (!qstate)
            {
                cout << endl << "Successfully Updated." << endl;
            }
            else
            {
                cout << "Failed To Update!" << mysql_errno(conn) << endl;
            }
            getch();

            cout<<"\nDo you want to update anything else of the current doctor[y/n]?\n"<<endl;
            char c;
            cin>>c;
            if(c=='y'||c=='Y'){
                goto ir;
            }
            else{
                cout<<"\nDo you want to update any other doctor details?[y/n]\n"<<endl;
                char e;
                cin>>e;
                if(e=='y'||e=='Y'){
                    goto pq;
                }

            }
     }
     else if(change==2){
   string qq="select * from doctors_record where Did like '%"+id+"%'";
        const char* qn=qq.c_str();
        qstate=mysql_query(conn,qn);
        if(!qstate){
            res=mysql_store_result(conn);
            while((row=mysql_fetch_row(res))){
                cout<<"\nCurrent data is: Gender - "<<row[2]<<endl;
            }
        }

        cout<<"\nEnter the updated data\n";
        string updated_input;
        cin>>updated_input;
        string update_query="update doctors_record set Gender='"+updated_input+"' where Did like '%"+id+"%'";
        const char* qu = update_query.c_str();
        qstate = mysql_query(conn, qu);
            if (!qstate)
            {
                cout << endl << "Successfully Updated." << endl;
            }
            else
            {
                cout << "Failed To Update!" << mysql_errno(conn) << endl;
            }
            getch();

            cout<<"\nDo you want to update anything else of the current doctor[y/n]?\n"<<endl;
            char c;
            cin>>c;
            if(c=='y'||c=='Y'){
              goto ir;
            }
            else{
                cout<<"\nDo you want to update any other doctor details?[y/n]\n"<<endl;
                char e;
                cin>>e;
                if(e=='y'||e=='Y'){
                    goto pq;
                }

            }
     }
     else if(change==3){

   string qq="select * from doctors_record where Did like '%"+id+"%'";
        const char* qn=qq.c_str();
        qstate=mysql_query(conn,qn);
        if(!qstate){
            res=mysql_store_result(conn);
            while((row=mysql_fetch_row(res))){
                cout<<"\nCurrent data is: Name - "<<row[3]<<endl;
            }
        }

        cout<<"\nEnter the updated data\n";
        string updated_input;
        cin>>updated_input;
        string update_query="update doctors_record set Name='"+updated_input+"' where 'Did'=id";
        const char* qu = update_query.c_str();
        qstate = mysql_query(conn, qu);
            if (!qstate)
            {
                cout << endl << "Successfully Updated." << endl;
            }
            else
            {
                cout << "Failed To Update!" << mysql_errno(conn) << endl;
            }
            getch();

            cout<<"\nDo you want to update anything else of the current doctor[y/n]?\n"<<endl;
            char c;
            cin>>c;
            if(c=='y'||c=='Y'){
            goto ir;
            }
            else{
                cout<<"\nDo you want to update any other doctor details?[y/n]\n"<<endl;
                char e;
                cin>>e;
                if(e=='y'||e=='Y'){
                    goto pq;
                }

            }
     }
     else if(change==4){
         string qq="select * from doctors_record where Did like '%"+id+"%'";
        const char* qn=qq.c_str();
        qstate=mysql_query(conn,qn);
        if(!qstate){
            res=mysql_store_result(conn);
            while((row=mysql_fetch_row(res))){
                cout<<"\nCurrent data is: DOB - "<<row[4]<<endl;
            }
        }

        cout<<"\nEnter the updated data\n";
        string updated_input;
        cin>>updated_input;
        string update_query="update doctors_record set DOB='"+updated_input+"' where Did like '%"+id+"%'";
        const char* qu = update_query.c_str();
        qstate = mysql_query(conn, qu);
            if (!qstate)
            {
                cout << endl << "Successfully Updated." << endl;
            }
            else
            {
                cout << "Failed To Update!" << mysql_errno(conn) << endl;
            }
            getch();

            cout<<"\nDo you want to update anything else of this patient[y/n]?\n"<<endl;
            char c;
            cin>>c;
            if(c=='y'||c=='Y'){
goto ir;
            }
            else{
                cout<<"\nDo you want to update any other patient details?[y/n]\n"<<endl;
                char e;
                cin>>e;
                if(e=='y'||e=='Y'){
                    goto pq;
                }

            }
     }
     else if(change==5){
 string qq="select * from doctors_record where Did like '%"+id+"%'";
        const char* qn=qq.c_str();
        qstate=mysql_query(conn,qn);
        if(!qstate){
            res=mysql_store_result(conn);
            while((row=mysql_fetch_row(res))){
                cout<<"\nCurrent data is: MOB - "<<row[5]<<endl;
            }
        }

        cout<<"\nEnter the updated data\n";
        string updated_input;
        cin>>updated_input;
        string update_query="update doctors_record set Timings='"+updated_input+"' where Did like '%"+id+"%'";
        const char* qu = update_query.c_str();
        qstate = mysql_query(conn, qu);
            if (!qstate)
            {
                cout << endl << "Successfully Updated." << endl;
            }
            else
            {
                cout << "Failed To Update!" << mysql_errno(conn) << endl;
            }
            getch();

            cout<<"\nDo you want to update anything else of this patient[y/n]?\n"<<endl;
            char c;
            cin>>c;
            if(c=='y'||c=='Y'){
            goto ir;
            }
            else{
                cout<<"\nDo you want to update any other patient details?[y/n]\n"<<endl;
                char e;
                cin>>e;
                if(e=='y'||e=='Y'){
                    goto pq;
                }

            }
     }
     else if(change==6){
 string qq="select * from doctors_record where Did like '%"+id+"%'";
        const char* qn=qq.c_str();
        qstate=mysql_query(conn,qn);
        if(!qstate){
            res=mysql_store_result(conn);
            while((row=mysql_fetch_row(res))){
                cout<<"\nCurrent data is: Timings - "<<row[6]<<endl;
            }
        }

        cout<<"\nEnter the updated data\n";
        string updated_input;
        cin>>updated_input;
        string update_query="update doctors_record set Timings='"+updated_input+"' where Did like '%"+id+"%'";
        const char* qu = update_query.c_str();
        qstate = mysql_query(conn, qu);
            if (!qstate)
            {
                cout << endl << "Successfully Updated." << endl;
            }
            else
            {
                cout << "Failed To Update!" << mysql_errno(conn) << endl;
            }
            getch();

            cout<<"\nDo you want to update anything else of this patient[y/n]?\n"<<endl;
            char c;
            cin>>c;
            if(c=='y'||c=='Y'){
                goto ir;
            }
            else{
                cout<<"\nDo you want to update any other patient details?[y/n]\n"<<endl;
                char e;
                cin>>e;
                if(e=='y'||e=='Y'){
                    goto pq;
                }

            }
     }
     else if(change==7){
 string qq="select * from doctors_record where Did like '%"+id+"%'";
        const char* qn=qq.c_str();
        qstate=mysql_query(conn,qn);
        if(!qstate){
            res=mysql_store_result(conn);
            while((row=mysql_fetch_row(res))){
                cout<<"\nCurrent data is:  Email - "<<row[7]<<endl;
            }
        }

        cout<<"\nEnter the updated data\n";
        string updated_input;
        cin>>updated_input;
        string update_query="update doctors_record set Email='"+updated_input+"' where Did like '%"+id+"%'";
        const char* qu = update_query.c_str();
        qstate = mysql_query(conn, qu);
            if (!qstate)
            {
                cout << endl << "Successfully Updated." << endl;
            }
            else
            {
                cout << "Failed To Update!" << mysql_errno(conn) << endl;
            }
            getch();

            cout<<"\nDo you want to update anything else of this patient[y/n]?\n"<<endl;
            char c;
            cin>>c;
            if(c=='y'||c=='Y'){
            goto ir;
            }
            else{
                cout<<"\nDo you want to update any other patient details?[y/n]\n"<<endl;
                char e;
                cin>>e;
                if(e=='y'||e=='Y'){
                    goto pq;
                }

            }
     }
     else if(change==8){
         string qq="select * from doctors_record where Did like '%"+id+"%'";
        const char* qn=qq.c_str();
        qstate=mysql_query(conn,qn);
        if(!qstate){
            res=mysql_store_result(conn);
            while((row=mysql_fetch_row(res))){
                cout<<"\nCurrent data is: Address - "<<row[8]<<endl;
            }
        }

        cout<<"\nEnter the updated data\n";
        string updated_input;
        cin>>updated_input;
        string update_query="update doctors_record set Address='"+updated_input+"' where Did like '%"+id+"%'";
        const char* qu = update_query.c_str();
        qstate = mysql_query(conn, qu);
            if (!qstate)
            {
                cout << endl << "Successfully Updated." << endl;
            }
            else
            {
                cout << "Failed To Update!" << mysql_errno(conn) << endl;
            }
            getch();

            cout<<"\nDo you want to update anything else of this patient[y/n]?\n"<<endl;
            char c;
            cin>>c;
            if(c=='y'||c=='Y'){
            goto ir;

            }
            else{
                cout<<"\nDo you want to update any other patient details?[y/n]\n"<<endl;
                char e;
                cin>>e;
                if(e=='y'||e=='Y'){
                    goto pq;
                }

            }
     }
     else if(change==9){
        exit(0);
     }
     else{
            cout<<"\nINVALID INPUT.\nPlease try again...\n";
            getch();
            goto pq;
	}
	}

	void patient::update_record(){
    string id;
    pq:
        system("CLS");
     cout<<"\n\n\tEnter Patient's ID to be updated:  ";
     cin>>id;
     getch();
   ir:
     cout<<"\n\tSelect what do you want to update?\n\t1 First Name\n\t2 Last Name\n\t3 Gender \n\t4 DOB\n\t5 Height\n\t6 Weight\n\t7 MOB\n\t8 Address\n\t9 MaritalStatus\n\t10 Bloodgroup\n\t11 Medical History\n\t12 Symptoms\n\t13 Disease\n\t14 Medicines\n\t15 visits\n\t16 Room Alloted\n\t17 Doctor ID\n\t18 Reports\n\t19 Exit\n\t"<<endl;
     int change;
     cin>>change;
     if(change==1){
        string qq="select * from patient_biodata where Pid like '"+id+"'";
        const char* qn=qq.c_str();
        qstate=mysql_query(conn,qn);
        if(!qstate){
            res=mysql_store_result(conn);
            while((row=mysql_fetch_row(res))){
                cout<<"\nCurrent data is: First Name - "<<row[2]<<endl;
            }
        }

        cout<<"\n\tEnter the updated data\n\t";
        string updated_input;
        cin>>updated_input;
        string update_query="update patient_biodata set Fname='"+updated_input+"' where Pid like '%"+id+"%'";
        const char* qu = update_query.c_str();
        qstate = mysql_query(conn, qu);
            if (!qstate)
            {
                cout << endl << "\tSuccessfully Updated." << endl;
            }
            else
            {
                cout << "Failed To Update!" << mysql_errno(conn) << endl;
            }
            getch();

            cout<<"\n\tDo you want to update anything else of this patient[y/n]?\n\t";
            char c;
            cin>>c;
            if(c=='y'||c=='Y'){

            }
            else{
                cout<<"\n\tDo you want to update any other patient details?[y/n]\n\t";
                char e;
                cin>>e;
                if(e=='y'||e=='Y'){
                    goto pq;
                }

            }
     }
     else if(change==2){
 string qq="select * from patient_biodata where Pid like '"+id+"'";
        const char* qn=qq.c_str();
        qstate=mysql_query(conn,qn);
        if(!qstate){
            res=mysql_store_result(conn);
            while((row=mysql_fetch_row(res))){
                cout<<"\n\tCurrent data is: Last Name - "<<row[3]<<endl;
            }
        }

        cout<<"\n\tEnter the updated data\n\t";
        string updated_input;
        cin>>updated_input;
        string update_query="update patient_biodata set Lname='"+updated_input+"' where Pid like '%"+id+"%'";
        const char* qu = update_query.c_str();
        qstate = mysql_query(conn, qu);
            if (!qstate)
            {
                cout << endl << "\tSuccessfully Updated." << endl;
            }
            else
            {
                cout << "\tFailed To Update!" << mysql_errno(conn) << endl;
            }
            getch();

            cout<<"\n\tDo you want to update anything else of this patient[y/n]?\n\t"<<endl;
            char c;
            cin>>c;
            if(c=='y'||c=='Y'){

            }
            else{
                cout<<"\n\tDo you want to update any other patient details?[y/n]\n\t"<<endl;
                char e;
                cin>>e;
                if(e=='y'||e=='Y'){
                    goto pq;
                }

            }
     }
     else if(change==3){
 string qq="select * from patient_biodata where Pid like '%"+id+"%'";
        const char* qn=qq.c_str();
        qstate=mysql_query(conn,qn);
        if(!qstate){
            res=mysql_store_result(conn);
            while((row=mysql_fetch_row(res))){
                cout<<"\n\tCurrent data is: Gender - "<<row[4]<<endl;
            }
        }

        cout<<"\n\tEnter the updated data\n\t";
        string updated_input;
        cin>>updated_input;
        string update_query="update patient_biodata set Gender='"+updated_input+"' where Pid like '%"+id+"%'";
        const char* qu = update_query.c_str();
        qstate = mysql_query(conn, qu);
            if (!qstate)
            {
                cout << endl << "\tSuccessfully Updated." << endl;
            }
            else
            {
                cout << "Failed To Update!" << mysql_errno(conn) << endl;
            }
            getch();

            cout<<"\n\tDo you want to update anything else of this patient[y/n]?\n"<<endl;
            char c;
            cin>>c;
            if(c=='y'||c=='Y'){

            }
            else{
                cout<<"\n\tDo you want to update any other patient details?[y/n]\n"<<endl;
                char e;
                cin>>e;
                if(e=='y'||e=='Y'){
                    goto pq;
                }

            }
     }
     else if(change==4){
         string qq="select * from patient_biodata where Pid like '%"+id+"%'";
        const char* qn=qq.c_str();
        qstate=mysql_query(conn,qn);
        if(!qstate){
            res=mysql_store_result(conn);
            while((row=mysql_fetch_row(res))){
                cout<<"\nCurrent data is: DOB - "<<row[5]<<endl;
            }
        }

        cout<<"\nEnter the updated data\n";
        string updated_input;
        cin>>updated_input;
        string update_query="update patient_biodata set DOB='"+updated_input+"' where Pid like '%"+id+"%'";
        const char* qu = update_query.c_str();
        qstate = mysql_query(conn, qu);
            if (!qstate)
            {
                cout << endl << "Successfully Updated." << endl;
            }
            else
            {
                cout << "Failed To Update!" << mysql_errno(conn) << endl;
            }
            getch();

            cout<<"\nDo you want to update anything else of this patient[y/n]?\n"<<endl;
            char c;
            cin>>c;
            if(c=='y'||c=='Y'){

            }
            else{
                cout<<"\nDo you want to update any other patient details?[y/n]\n"<<endl;
                char e;
                cin>>e;
                if(e=='y'||e=='Y'){
                    goto pq;
                }

            }
     }
     else if(change==5){
 string qq="select * from patient_biodata where Pid like '%"+id+"%'";
        const char* qn=qq.c_str();
        qstate=mysql_query(conn,qn);
        if(!qstate){
            res=mysql_store_result(conn);
            while((row=mysql_fetch_row(res))){
                cout<<"\nCurrent data is: Height - "<<row[6]<<endl;
            }
        }

        cout<<"\nEnter the updated data\n";
        string updated_input;
        cin>>updated_input;
        string update_query="update patient_biodata set Height='"+updated_input+"' where Pid like '%"+id+"%'";
        const char* qu = update_query.c_str();
        qstate = mysql_query(conn, qu);
            if (!qstate)
            {
                cout << endl << "Successfully Updated." << endl;
            }
            else
            {
                cout << "Failed To Update!" << mysql_errno(conn) << endl;
            }
            getch();

            cout<<"\nDo you want to update anything else of this patient[y/n]?\n"<<endl;
            char c;
            cin>>c;
            if(c=='y'||c=='Y'){

            }
            else{
                cout<<"\nDo you want to update any other patient details?[y/n]\n"<<endl;
                char e;
                cin>>e;
                if(e=='y'||e=='Y'){
                    goto pq;
                }

            }
     }
     else if(change==6){
 string qq="select * from patient_biodata where Pid like '%"+id+"%'";
        const char* qn=qq.c_str();
        qstate=mysql_query(conn,qn);
        if(!qstate){
            res=mysql_store_result(conn);
            while((row=mysql_fetch_row(res))){
                cout<<"\nCurrent data is: Weight - "<<row[7]<<endl;
            }
        }

        cout<<"\nEnter the updated data\n";
        string updated_input;
        cin>>updated_input;
        string update_query="update patient_biodata set Weight='"+updated_input+"' where Pid like '%"+id+"%'";
        const char* qu = update_query.c_str();
        qstate = mysql_query(conn, qu);
            if (!qstate)
            {
                cout << endl << "Successfully Updated." << endl;
            }
            else
            {
                cout << "Failed To Update!" << mysql_errno(conn) << endl;
            }
            getch();

            cout<<"\nDo you want to update anything else of this patient[y/n]?\n"<<endl;
            char c;
            cin>>c;
            if(c=='y'||c=='Y'){

            }
            else{
                cout<<"\nDo you want to update any other patient details?[y/n]\n"<<endl;
                char e;
                cin>>e;
                if(e=='y'||e=='Y'){
                    goto pq;
                }

            }
     }
     else if(change==7){
 string qq="select * from patient_biodata where Pid like '"+id+"'";
        const char* qn=qq.c_str();
        qstate=mysql_query(conn,qn);
        if(!qstate){
            res=mysql_store_result(conn);
            while((row=mysql_fetch_row(res))){
                cout<<"\n\tCurrent data is:  MOB - "<<row[8]<<endl;
            }
        }

        cout<<"\n\tEnter the updated data\n";
        string updated_input;
        cin>>updated_input;
        string update_query="update patient_biodata set MOB='"+updated_input+"' where Pid like '%"+id+"%'";
        const char* qu = update_query.c_str();
        qstate = mysql_query(conn, qu);
            if (!qstate)
            {
                cout << endl << "\tSuccessfully Updated." << endl;
            }
            else
            {
                cout << "Failed To Update!" << mysql_errno(conn) << endl;
            }
            getch();

            cout<<"\n\tDo you want to update anything else of this patient[y/n]?\n"<<endl;
            char c;
            cin>>c;
            if(c=='y'||c=='Y'){

            }
            else{
                cout<<"\n\tDo you want to update any other patient details?[y/n]\n"<<endl;
                char e;
                cin>>e;
                if(e=='y'||e=='Y'){
                    goto pq;
                }

            }
     }
     else if(change==8){
         string qq="select * from patient_biodata where Pid like '"+id+"'";
        const char* qn=qq.c_str();
        qstate=mysql_query(conn,qn);
        if(!qstate){
            res=mysql_store_result(conn);
            while((row=mysql_fetch_row(res))){
                cout<<"\nCurrent data is: Address - "<<row[9]<<endl;
            }
        }

        cout<<"\nEnter the updated data\n";
        string updated_input;
        cin>>updated_input;
        string update_query="update patient_biodata set Address='"+updated_input+"' where Pid like '%"+id+"%'";
        const char* qu = update_query.c_str();
        qstate = mysql_query(conn, qu);
            if (!qstate)
            {
                cout << endl << "Successfully Updated." << endl;
            }
            else
            {
                cout << "Failed To Update!" << mysql_errno(conn) << endl;
            }
            getch();

            cout<<"\nDo you want to update anything else of this patient[y/n]?\n"<<endl;
            char c;
            cin>>c;
            if(c=='y'||c=='Y'){

            }
            else{
                cout<<"\nDo you want to update any other patient details?[y/n]\n"<<endl;
                char e;
                cin>>e;
                if(e=='y'||e=='Y'){
                    goto pq;
                }

            }
     }
     else if(change==9){
     string qq="select * from patient_biodata where Pid like '%"+id+"%'";
        const char* qn=qq.c_str();
        qstate=mysql_query(conn,qn);
        if(!qstate){
            res=mysql_store_result(conn);
            while((row=mysql_fetch_row(res))){
                cout<<"\nCurrent data is: Marital Status - "<<row[10]<<endl;
            }
        }

        cout<<"\nEnter the updated data\n";
        string updated_input;
        cin>>updated_input;
        string update_query="update patient_biodata set MaritalStatus='"+updated_input+"' where Pid like '%"+id+"%'";
        const char* qu = update_query.c_str();
        qstate = mysql_query(conn, qu);
            if (!qstate)
            {
                cout << endl << "Successfully Updated." << endl;
            }
            else
            {
                cout << "Failed To Update!" << mysql_errno(conn) << endl;
            }
            getch();

            cout<<"\nDo you want to update anything else of this patient[y/n]?\n"<<endl;
            char c;
            cin>>c;
            if(c=='y'||c=='Y'){

            }
            else{
                cout<<"\nDo you want to update any other patient details?[y/n]\n"<<endl;
                char e;
                cin>>e;
                if(e=='y'||e=='Y'){
                    goto pq;
                }

            }
     }
     else if(change==10){
      string qq="select * from patient_biodata where Pid like '"+id+"'";
        const char* qn=qq.c_str();
        qstate=mysql_query(conn,qn);
        if(!qstate){
            res=mysql_store_result(conn);
            while((row=mysql_fetch_row(res))){
                cout<<"\nCurrent data is: Blood Group - "<<row[11]<<endl;
            }
        }

        cout<<"\nEnter the updated data\n";
        string updated_input;
        cin>>updated_input;
        string update_query="update patient_biodata set Bloodgroup='"+updated_input+"' where Pid like '%"+id+"%'";
        const char* qu = update_query.c_str();
        qstate = mysql_query(conn, qu);
            if (!qstate)
            {
                cout << endl << "Successfully Updated." << endl;
            }
            else
            {
                cout << "Failed To Update!" << mysql_errno(conn) << endl;
            }
            getch();

            cout<<"\nDo you want to update anything else of this patient[y/n]?\n"<<endl;
            char c;
            cin>>c;
            if(c=='y'||c=='Y'){

            }
            else{
                cout<<"\nDo you want to update any other patient details?[y/n]\n"<<endl;
                char e;
                cin>>e;
                if(e=='y'||e=='Y'){
                    goto pq;
                }

            }
     }
     else if(change==11){
        string qq="select * from patient_treatment_data where Pid like '"+id+"'";
        const char* qn=qq.c_str();
        qstate=mysql_query(conn,qn);
        if(!qstate){
            res=mysql_store_result(conn);
            while((row=mysql_fetch_row(res))){
                cout<<"\nCurrent data is: Medical History - "<<row[1]<<endl;
            }
        }

        cout<<"\nEnter the updated data\n";
        string updated_input;
        cin>>updated_input;
        string update_query="update patient_treatment_data set MedicalHistory='"+updated_input+"' where Pid like '%"+id+"%'";
        const char* qu = update_query.c_str();
        qstate = mysql_query(conn, qu);
            if (!qstate)
            {
                cout << endl << "Successfully Updated." << endl;
            }
            else
            {
                cout << "Failed To Update!" << mysql_errno(conn) << endl;
            }
            getch();

            cout<<"\nDo you want to update anything else of this patient[y/n]?\n"<<endl;
            char c;
            cin>>c;
            if(c=='y'||c=='Y'){
            goto ir;
            }
            else{
                cout<<"\nDo you want to update any other patient details?[y/n]\n"<<endl;
                char e;
                cin>>e;
                if(e=='y'||e=='Y'){
                    goto pq;
                }

            }
     }
      else if(change==12){
           string qq="select * from patient_treatment_data where Pid like '"+id+"'";
        const char* qn=qq.c_str();
        qstate=mysql_query(conn,qn);
        if(!qstate){
            res=mysql_store_result(conn);
            while((row=mysql_fetch_row(res))){
                cout<<"\nCurrent data is: Symptoms - "<<row[2]<<endl;
            }
        }

        cout<<"\nEnter the updated data\n";
        string updated_input;
        cin>>updated_input;
        string update_query="update patient_treatment_data set Symptoms='"+updated_input+"' where Pid like '%"+id+"%'";
        const char* qu = update_query.c_str();
        qstate = mysql_query(conn, qu);
            if (!qstate)
            {
                cout << endl << "Successfully Updated." << endl;
            }
            else
            {
                cout << "Failed To Update!" << mysql_errno(conn) << endl;
            }
            getch();

            cout<<"\nDo you want to update anything else of this patient[y/n]?\n"<<endl;
            char c;
            cin>>c;
            if(c=='y'||c=='Y'){
            goto ir;
            }
            else{
                cout<<"\nDo you want to update any other patient details?[y/n]\n"<<endl;
                char e;
                cin>>e;
                if(e=='y'||e=='Y'){
                    goto pq;
                }

            }
     }
      else if(change==13){
          string qq="select * from patient_treatment_data where Pid like '"+id+"'";
        const char* qn=qq.c_str();
        qstate=mysql_query(conn,qn);
        if(!qstate){
            res=mysql_store_result(conn);
            while((row=mysql_fetch_row(res))){
                cout<<"\n\tCurrent data is: Disease - "<<row[3]<<endl;
            }
        }

        cout<<"\n\tEnter the updated data\n\t";
        string updated_input;
        cin>>updated_input;
        string update_query="update patient_treatment_data set Disease='"+updated_input+"' where Pid like '%"+id+"%'";
        const char* qu = update_query.c_str();
        qstate = mysql_query(conn, qu);
            if (!qstate)
            {
                cout << endl << "\tSuccessfully Updated." << endl;
            }
            else
            {
                cout << "Failed To Update!" << mysql_errno(conn) << endl;
            }
            getch();

            cout<<"\n\tDo you want to update anything else of this patient[y/n]?\n"<<endl;
            char c;
            cin>>c;
            if(c=='y'||c=='Y'){
            goto ir;
            }
            else{
                cout<<"\n\tDo you want to update any other patient details?[y/n]\n"<<endl;
                char e;
                cin>>e;
                if(e=='y'||e=='Y'){
                    goto pq;
                }

            }
     }
      else if(change==14){
         string qq="select * from patient_treatment_data where Pid like '"+id+"'";
        const char* qn=qq.c_str();
        qstate=mysql_query(conn,qn);
        if(!qstate){
            res=mysql_store_result(conn);
            while((row=mysql_fetch_row(res))){
                cout<<"\n\tCurrent data is: Medicines - "<<row[4]<<endl;
            }
        }

        cout<<"\n\tEnter the updated data\n\t";
        string updated_input;
        cin>>updated_input;
        string update_query="update patient_treatment_data set Medicines='"+updated_input+"' where Pid like '%"+id+"%'";
        const char* qu = update_query.c_str();
        qstate = mysql_query(conn, qu);
            if (!qstate)
            {
                cout << endl << "\tSuccessfully Updated." << endl;
            }
            else
            {
                cout << "\tFailed To Update!" << mysql_errno(conn) << endl;
            }
            getch();

            cout<<"\n\tDo you want to update anything else of this patient[y/n]?\n\t";
            char c;
            cin>>c;
            if(c=='y'||c=='Y'){
            goto ir;
            }
            else{
                cout<<"\n\tDo you want to update any other patient details?[y/n]\n\t";
                char e;
                cin>>e;
                if(e=='y'||e=='Y'){
                    goto pq;
                }

            }
     }
      else if(change==15){
         string qq="select * from patient_treatment_data where Pid like '%"+id+"%'";
        const char* qn=qq.c_str();
        qstate=mysql_query(conn,qn);
        if(!qstate){
            res=mysql_store_result(conn);
            while((row=mysql_fetch_row(res))){
                cout<<"\nCurrent data is: Visits - "<<row[5]<<endl;
            }
        }

        cout<<"\nEnter the updated data\n";
        string updated_input;
        cin>>updated_input;
        string update_query="update patient_treatment_data set visits='"+updated_input+"' where Pid like '"+id+"'";
        const char* qu = update_query.c_str();
        qstate = mysql_query(conn, qu);
            if (!qstate)
            {
                cout << endl << "Successfully Updated." << endl;
            }
            else
            {
                cout << "Failed To Update!" << mysql_errno(conn) << endl;
            }
            getch();

            cout<<"\nDo you want to update anything else of this patient[y/n]?\n"<<endl;
            char c;
            cin>>c;
            if(c=='y'||c=='Y'){
            goto ir;
            }
            else{
                cout<<"\nDo you want to update any other patient details?[y/n]\n"<<endl;
                char e;
                cin>>e;
                if(e=='y'||e=='Y'){
                    goto pq;
                }

            }
     }
      else if(change==16){
           string qq="select * from patient_treatment_data where Pid like '"+id+"'";
        const char* qn=qq.c_str();
        qstate=mysql_query(conn,qn);
        if(!qstate){
            res=mysql_store_result(conn);
            while((row=mysql_fetch_row(res))){
                cout<<"\nCurrent data is: Room Alloted - "<<row[6]<<endl;
            }
        }

        cout<<"\nEnter the updated data\n";
        string updated_input;
        cin>>updated_input;
        string update_query="update patient_treatment_data set RoomAlloted='"+updated_input+"' where Pid like '%"+id+"%'";
        const char* qu = update_query.c_str();
        qstate = mysql_query(conn, qu);
            if (!qstate)
            {
                cout << endl << "Successfully Updated." << endl;
            }
            else
            {
                cout << "Failed To Update!" << mysql_errno(conn) << endl;
            }
            getch();

            cout<<"\nDo you want to update anything else of this patient[y/n]?\n"<<endl;
            char c;
            cin>>c;
            if(c=='y'||c=='Y'){
            goto ir;
            }
            else{
                cout<<"\nDo you want to update any other patient details?[y/n]\n"<<endl;
                char e;
                cin>>e;
                if(e=='y'||e=='Y'){
                    goto pq;
                }

            }
     }
      else if(change==17){
           string qq="select * from patient_treatment_data where Pid like '%"+id+"%'";
        const char* qn=qq.c_str();
        qstate=mysql_query(conn,qn);
        if(!qstate){
            res=mysql_store_result(conn);
            while((row=mysql_fetch_row(res))){
                cout<<"\nCurrent data is: Doctor ID - "<<row[7]<<endl;
            }
        }

        cout<<"\nEnter the updated data\n";
        string updated_input;
        cin>>updated_input;
        string update_query="update patient_treatment_data set DoctorId='"+updated_input+"' where Pid like '%"+id+"%'";
        const char* qu = update_query.c_str();
        qstate = mysql_query(conn, qu);
            if (!qstate)
            {
                cout << endl << "Successfully Updated." << endl;
            }
            else
            {
                cout << "Failed To Update!" << mysql_errno(conn) << endl;
            }
            getch();

            cout<<"\nDo you want to update anything else of this patient[y/n]?\n"<<endl;
            char c;
            cin>>c;
            if(c=='y'||c=='Y'){
            goto ir;
            }
            else{
                cout<<"\nDo you want to update any other patient details?[y/n]\n"<<endl;
                char e;
                cin>>e;
                if(e=='y'||e=='Y'){
                    goto pq;
                }

            }
      }
    else if(change==18){
           string qq="select * from patient_treatment_data where Pid like '"+id+"'";
        const char* qn=qq.c_str();
        qstate=mysql_query(conn,qn);
        if(!qstate){
            res=mysql_store_result(conn);
            while((row=mysql_fetch_row(res))){
                cout<<"\nCurrent data is: Doctor ID - "<<row[8]<<endl;
            }
        }

        cout<<"\nEnter the updated data\n";
        string updated_input;
        cin>>updated_input;
        string update_query="update patient_treatment_data set DiagonisticReport='"+updated_input+"' where Pid like '%"+id+"%'";
        const char* qu = update_query.c_str();
        qstate = mysql_query(conn, qu);
            if (!qstate)
            {
                cout << endl << "Successfully Updated." << endl;
            }
            else
            {
                cout << "Failed To Update!" << mysql_errno(conn) << endl;
            }
            getch();

            cout<<"\nDo you want to update anything else of this patient[y/n]?\n"<<endl;
            char c;
            cin>>c;
            if(c=='y'||c=='Y'){
            goto ir;
            }
            else{
                cout<<"\nDo you want to update any other patient details?[y/n]\n"<<endl;
                char e;
                cin>>e;
                if(e=='y'||e=='Y'){
                    goto pq;
                }

            }
    }
     else if(change==19){
        exit(0);
     }
     else{
            cout<<"\nInvalid input.\n"<<endl;
            system("CLS");
            goto ir;


     }
	}

	 void patient::generate_bill(string patientid){
	 system("cls");
	 string f,l,date,medical_history,symptoms,disease,medicines;
	 string f1= "select * from patient_biodata where Pid like '%"+patientid+"%'";
    const char* qn1=f1.c_str();
    qstate = mysql_query(conn,qn1);

     if (!qstate)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {

             date=row[0];
             f=row[2];
             l=row[3];

        }
    }
    else
    {
        cout << "Query Execution Problem!" << endl;
    }




     string f2= "select * from patient_treatment_data where Pid like '%"+patientid+"%'";
    const char* qn2=f2.c_str();
    qstate = mysql_query(conn,qn2);

     if (!qstate)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {

            medical_history=row[1];
            symptoms=row[2];
            disease=row[3];
            medicines=row[4];
        }
    }
    else
    {
        cout << "Query Execution Problem!" << endl;
    }


	 // cout<<"\n\n\n\n\n\n\n\n\t---------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t"<<" "<<"PATIENT  RECORD  MANAGEMENT\n"<<endl;
    cout<<"\t\t\t\t\t\t\t\t\tPRESCRIPTION"<<endl;

    cout<<"\t------------------------------------------------------------------------------\n"<<endl;

//cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t||||||||||||||||\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|"<<endl;

    cout<<"\tNAME             :   "<<f<<" "<<l<<"\t\t\tDATE :  "<<date<<endl;
    cout<<endl;
   // cout<<"\t|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|"<<endl;
  //  cout<<"\t|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|"<<endl;

    cout<<"\tMEDICAL HISTORY  :   "<<medical_history<<endl;
    cout<<endl;
   // cout<<"\t|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|"<<endl;
   // cout<<"\t|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|"<<endl;

    cout<<"\tSYMPTOMS         :   "<<symptoms<<endl;
    cout<<endl;
 //  cout<<"\t|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|"<<endl;
 //   cout<<"\t|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|"<<endl;

    cout<<"\tDISEASE          :   "<<disease<<endl;
    cout<<endl;
   //cout<<"\t|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|"<<endl;
   // cout<<"\t|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|"<<endl;
    cout<<"\tMEDICINES        :   "<<medicines<<endl;
    cout<<endl;
//  cout<<"\t|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|"<<endl;
  //  cout<<"\t|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|"<<endl;

 //   cout<<"\t|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|"<<endl;
 //    cout<<"\t---------------------------------------------------------------------------------------------------------------------------------"<<endl;

cout<<"\n\n\n\n\n";

	 }

    int patient::unique_appointments(string id){
    if (std::find(v.begin(), v.end(),id)!=v.end())
    return 0;    //id is present. appointment is not unique.
    else return 1; //it is unique id
}
void welcome(){
	cout<<"\n\n\n\n\t\t\t\t\t\t\t\t\tW E L C O M E\n\n\t\t\t\t\t\t P A T I E N T   H E A L T H   R E C O R D   S Y S T E M\n\n\n\n\n";
}

void display_menu(){
cout<<"\n"<<"  "<<"1.  Create Patient's record.\n";
cout<<"\n"<<"  "<<"2.  View Patient's record.\n";
cout<<"\n"<<"  "<<"3.  Update Patient's record.\n";
cout<<"\n"<<"  "<<"4.  View Doctor details.\n";
cout<<"\n"<<"  "<<"5.  Update Doctor's details.\n";
cout<<"\n\n\n"<<"  "<< "Enter your choice.\n";
}

void passwd(char *ar,int max){
char ch;
int x=0;
while(1){
ch=getch();
if(ch==13){
ar[x]='\0';
break;
}
if(ch==8&& x!=0)
{
printf("\b \b");
if(x<=max && x>0)
x--;
}
else
if(x<max&&ch!=8){
printf("*");
ar[x]=ch;
x++;
}
}
}

unsigned int SHF(string input){
	unsigned int Init = 124564352;
	unsigned Magic = 5674356;
	unsigned int Hash;
	for(int i=0;i<input.length();i++){
		Hash = Hash ^ (input[i]);
		Hash = Hash * Magic;
	}
	return Hash;
}

string ToHex(unsigned int input){
	string HexHash;
	stringstream hexstream;
	hexstream <<hex <<input;
	HexHash = hexstream.str();
	transform(HexHash.begin(),HexHash.end(),HexHash.begin(),::toupper);
	return HexHash;
}

void patient::schedule_appointment(string pId){
    string ddid;
     string find_by_pid="select * from patient_treatment_data where Pid like '%"+pId+"%'";
        const char* qn = find_by_pid.c_str();
        qstate = mysql_query(conn, qn);

    cout << endl;
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {
           ddid=row[7];
        }
    }
    string dId;
    cout<<"\n\tConsulting doctor id in DB:  "<<ddid<<endl;
      cout<<"\n\tEnter Doctor ID for appointment: ";
    cin>>dId;

if(dId.compare("D1")==0){
	q1.push(pId);
	r1++;
	cout<<"\n\tAppointment scheduled.\n\tAppointment no. "<<r1<<"\n\t";
}

else if(dId.compare("D2")==0){
    	q2.push(pId);
    	r2++;
    	cout<<"\n\tAppointment scheduled.\n\tAppointment no. "<<r2<<"\n\t";
}
else if(dId.compare("D3")==0){
    	q3.push(pId);
    	r3++;
        cout<<"\n\tAppointment scheduled.\n\tAppointment no. "<<r3<<"\n\t";

}
else if(dId.compare("D4")==0){
    q4.push(pId);
    r4++;
				cout<<"\n\tAppointment scheduled.\n\tAppointment no. "<<r4<<"\n\t";

}
else if(dId.compare("D5")==0){
 	q5.push(pId);
 	r5++;
				cout<<"\n\tAppointment scheduled.\n\tAppointment no. "<<r5<<"\n\t";
}

else if(dId.compare("D6")==0){
  q6.push(pId);
  r6++;
				cout<<"\n\tAppointment scheduled.\n\tAppointment no. "<<r6<<"\n\t";
}



}

void patient::display_appointments(string docID){


if(docID=="D1"){
        string det,f,l;
cout<<"\n\tScheduled Appointments for Dr.Sanjay Gupta: \n\n";
cout<<"\t-----------------------------------------------";
if(q1.empty()){
    cout<<"\n\n\tNo Appointments scheduled till now.\n\t";
}
   while(!q1.empty()){
       cout<<det<<endl;
		det=q1.front();
		 string search_="select * from patient_biodata where pid like '"+det+"'";
       const char* qn = search_.c_str();
       qstate=mysql_query(conn,qn);
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {
            f= row[2];
            l= row[3];
        }
    }
		cout<<"\n\t"<<f<<" "<<l<<" : "<<det<<endl;
		q1.pop();
	}
}

else if(docID=="D2"){
    string det,f,l;
cout<<"\n\tScheduled Appointments for Dr.Ashi Kukade: \n\n";
cout<<"\t-----------------------------------------------";

if(q2.empty()){
    cout<<"\n\n\tNo Appointments scheduled till now.\n\t";
}
   while(!q2.empty()){
       string det,f,l;
		det=q2.front();

		 string search_="select * from patient_biodata where pid like '"+det+"'";
       const char* qn = search_.c_str();
       qstate=mysql_query(conn,qn);
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {
            f= row[2];
            l= row[3];
        }
    }
		cout<<"\n\t"<<f<<" "<<l<<" : "<<det<<endl;
		q2.pop();
	}
}

else if(docID=="D3"){
    string det,f,l;
cout<<"\n\tScheduled Appointments for Dr.Rajendra Singh: \n\n";
cout<<"\t-----------------------------------------------";
if(q3.empty()){
    cout<<"\n\n\tNo Appointments scheduled till now.\n\t";
}
   while(!q3.empty()){
		det=q3.front();
        cout<<det<<endl;
        string search_="select * from patient_biodata where pid like '"+det+"'";
       const char* qn = search_.c_str();
       qstate=mysql_query(conn,qn);
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {
            f= row[2];
            l= row[3];
        }
    }
		cout<<"\n\t"<<f<<" "<<l<<" : "<<det<<endl;
		q3.pop();
	}
}


else if(docID=="D4"){
    string det,f,l;
cout<<"\n\tScheduled Appointments for Dr.Kalindi Bose: \n\n";
cout<<"\t-----------------------------------------------";
   while(!q4.empty()){
		det=q4.front();

		 string search_="select * from patient_biodata where pid like '"+det+"'";
       const char* qn = search_.c_str();
       qstate=mysql_query(conn,qn);
       if(q4.empty()){
    cout<<"\n\n\tNo Appointments scheduled till now.\n\t";
}
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {
            f= row[2];
            l= row[3];
        }
    }
		cout<<"\n\t"<<f<<" "<<l<<" : "<<det<<endl;
		q4.pop();
	}

}
else if(docID=="D5"){
    string det,f,l;
cout<<"\n\tScheduled Appointments for Dr.Lakshman Rajwade: \n\n";
cout<<"\t-----------------------------------------------";
   while(!q5.empty()){
		det=q5.front();

		 string search_="select * from patient_biodata where pid like '"+det+"'";
       const char* qn = search_.c_str();
       qstate=mysql_query(conn,qn);
       if(q5.empty()){
    cout<<"\n\n\tNo Appointments scheduled till now.\n\t";
}
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {
            f= row[2];
            l= row[3];
        }
    }
		cout<<"\n\t"<<f<<" "<<l<<" : "<<det<<endl;
		q5.pop();
	}
}
else if(docID=="D6"){
    string det,f,l;
cout<<"\n\tScheduled Appointments for Dr.Kitri Verma: \n\n";
cout<<"\t-----------------------------------------------";
if(q6.empty()){
    cout<<"\n\n\tNo Appointments scheduled till now.\n\t";
}
   while(!q6.empty()){
		det=q6.front();

		 string search_="select * from patient_biodata where pid like '"+det+"'";
       const char* qn = search_.c_str();
       qstate=mysql_query(conn,qn);
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {
            f= row[2];
            l= row[3];
        }
    }
		cout<<"\n\t"<<f<<" "<<l<<" : "<<det<<endl;
		q6.pop();
	}
}


}


int main(){
    patient p;

    doctor d;
    v:
        system("cls");
welcome();
db:
cout<<"\n\n\tLOG IN AS:\n\n\t1. DOCTOR\n\n\t2. RECEPTIONIST\n\n";
cout<<"\tEnter your choice: ";
int log_in;
cin>>log_in;
system("cls");
MYSQL* conn=connectdatabase();

if(log_in==1){


    string uname,db_password;
    char ps[9];

	printf("\n\n\tEnter username: ");
	cin>>uname;
	printf("\n\tEnter Password: ");
	passwd(ps,9);
    string hex=ToHex(SHF(ps));
	string find_query="select * from users where username like '%"+uname+"%'";
	const char* q=find_query.c_str();
	qstate=mysql_query(conn,q);
	if(!qstate){
        res=mysql_store_result(conn);
        while ((row = mysql_fetch_row(res))){
            db_password=row[1];
        }
	}
else{
    cout << "Query Execution Problem!" << endl;
}



 if(db_password==hex){
    cout<<"\n\n\tlogin successful!";
    getch();
    system("cls");
    cout<<"\n\t\t\t\t\t\t\t\t\t\t\tLOGGED IN AS DOCTOR\n\n";
    cout<<"\n";
    again1:
        system("cls");
    cout<<"\n\n\n\tSELECT OPERATION - \n";
    cout<<"\n\n\t1. View Patient Details\n\n\t2. Update Patient Medical Record\n\n\t3. Generate Prescription\n\n\t4. Exit\n\n\t";
    int operation;
    cin>>operation;
    if(operation==1){
           system("cls");
        cout<<"\n\tView Patient Record\n\n";

        int i;
        //view patient's record
    ab:
        cout<<"\n\tPress 0 to view all Patient's record\n\n\tPress 1 to search for a particular patient\n\n\t";
        cin>>i;
        cout<<endl;
        if(i==0){
            p.display_all();
            goto again1;
        }
        else if(i==1){
            p.search_patient();
            goto again1;
        }
        else{
            cout<<"Invalid input.\nPlease select again.\n";
            goto ab;
        }


    }
    else if(operation==2){
        p.update_record();
    goto again1;
    }
    else if(operation==3){
    cout<<"\n\tEnter patient's ID: ";
    string th;
    cin>>th;
    cout<<endl;
    p.generate_bill(th);

    }
    else if(operation==4){
        goto v;
    }



 }
 else{
    cout<<"\nInvalid details.\nTRY AGAIN...";
    getchar();
    system("cls");
    goto db;

 }



}
else if(log_in==2){


  string uname,db_password;
    char ps[20];

	printf("\n\tEnter username: ");
	cin>>uname;
	printf("\n\tEnter Password: ");
	passwd(ps,20);
    string hex=ToHex(SHF(ps));
	string find_query="select * from users where username like '%"+uname+"%'";
	const char* q=find_query.c_str();
	qstate=mysql_query(conn,q);
	if(!qstate){
        res=mysql_store_result(conn);
        while ((row = mysql_fetch_row(res))){
            db_password=row[1];
        }
	}
else{
    cout << "Query Execution Problem!" << endl;
}


 if(db_password==hex){
    cout<<"\n\n\tlogin successful!\n\n";
    getch();
    system("cls");
    cout<<"\n\t\t\t\t\t\t\t\t\t\t\tLOGGED IN AS RECEPTIONIST\n\n";
    cout<<"\n\n";
    again2:
        system("cls");
    cout<<"\n\n\n\tSELECT OPERATION - \n";
    cout<<"\n\t1. Schedule appointment\n\n\t2. View Patient Record\n\n\t3. Update Patient Record\n\n\t4. View Doctor Record\n\n\t5. Update Doctor Record\n\n\t6. Display appointment\n\n\t7. Exit\n\n\t";
    int operation;
    cin>>operation;
      if(operation==1){
            int k;
            system("cls");
    cout<<"\n\t1. New Patient\n\n\t2. Follow up\n\n\t";
    cin>>k;
    if(k==1){
        getch();

        p.patientbiodata();
        p.patient_treatment_data();
        getch();
        goto again2;
    }
    else if(k==2){
            string pid;
            cout<<"\n\tEnter Patient ID: ";
    cin>>pid;
    if(p.unique_appointments(pid)==1){
         p.schedule_appointment(pid);
         v.push_back(pid);
    }
    else{
        cout<<"\n\tAppointment is already scheduled for this ID.\n\t";
    }
         getch();
         goto again2;
    }

    }
 else if(operation==2){
        system("cls");
        cout<<"\tView Patient Record\n\n\t";

        int i;
        //view patient's record
    ab1:
        cout<<"Press 0 to view all Patient's record\n\n\tPress 1 to search for a particular patient\n\n\t";
        cin>>i;
        cout<<endl;
        if(i==0){
            p.display_all();
            goto again2;
        }
        else if(i==1){
            p.search_patient();
            goto again2;
        }
        else{
            cout<<"Invalid input.\nPlease select again.\n";
            goto ab1;
        }



 }
 else if(operation==3){
    p.update_record();
    goto again2;
 }
 else if(operation==4){
    system("cls");
    cout<<"\tView Doctor Records\n\n";
    int j;
     bc:
        cout<<"\tPress 0 to view all Doctor's record\n\n\tPress 1 to search for a particular Doctor\n\n\t";
        cin>>j;
        cout<<endl;
         if(j==0){
            d.display_all();
            goto again2;
        }
        else if(j==1){
            d.search_doctor();
            goto again2;
        }
        else{
            cout<<"\tInvalid input.\n\tPlease select again.\n";
            goto bc;
        }
 }
 else if(operation==5){
    d.doctor_update();
    goto again2;
 }
else if(operation==6){
    system("cls");
    string inp;
    cout<<"\n\tEnter Doctor ID:\n\t";
    cin>>inp;
    p.display_appointments(inp);
    getch();
    goto again2;
}
else if(operation==7){
    goto v;
}
}
else{
     cout<<"\nInvalid details.\nTRY AGAIN...";
    getchar();
    system("cls");
    goto db;

 }

}

}
