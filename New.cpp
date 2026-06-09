#include<iostream>
#include<string>
#include <sstream>
#include <bits/stdc++.h>
#include<windows.h>
#include"queue1.h"
#include"animation.h"
#include"stackme.h"

using namespace std;

int search(int);
int display();
string check(int);

////////////////////////////////////////////////////////////////////
struct node
{
	int ID;
	string proName;
	double prePrice;
	int quantity;
    struct node* next;
};

struct node *head=NULL;

////////////////////////////////////////////////////////////////////
bool adminLogin() 
{
    string user, pass;
    system("cls");
    cout << "\n\n\t\t===== Admin Login =====\n";
    cout << "\nEnter username: ";
    cin >> user;
    cout << "Enter password: ";
    cin >> pass;

    if (user == "admin" && pass == "12345") 
    {
        cout << "\nLogin successful!\n";
        system("pause");
        system("cls");
        return true;
    }
    else 
    {
        cout << "\nInvalid username or password!\n";
        system("pause");
        system("cls");
        return false;
    }
}

////////////////////////////////////////////////////////////////////
void beg()
{
	system("cls");
	int id,quant;
	string name;
	double pre;
	struct node *t=new node;
	struct node *p=head;

	cout<<"\t\t\tEnter product ID:-";
	cin>>id;
	t->ID=id;
	cout<<"\t\t\tEnter product Name:-";
	cin>>name;
	t->proName=name;
	cout<<"\t\t\tEnter product price:-";
	cin>>pre;
	t->prePrice=pre;
	cout<<"\t\t\tEnter product quantity:-";
	cin>>quant;
	t->quantity=quant;
	if(head==NULL)
	{
		t->next=head;
		head=t;
	}
	else
	{
		while(p->next!=NULL)
		{
			p=p->next;
		}
		p->next=t;
		t->next=NULL;
	}	
	system("cls");
    cout<<"\n\n\t\t\t\tThis product is Inserted!\n\n\n";
}

///////////////////////////////////////////////////////////////////////////////////////////
int search(int id)
{
	int count=1;
	struct node *p=head;
	while(p!=NULL)
	{
		if(p->ID==id)
			break;
		else
			count++;
		p=p->next;
	}
	return count;
}

///////////////////////////////////////////////////////////////////////
int hash(int x, int mod)
{
	return x % mod;
}

////////////////////////////////////////////////////////////////////////
void delPro()
{
	system("cls");
	display();
	int id;
	struct node *cur=head;
	struct node *pre=head;
	cout<<"\n\nEnter ID to delete that product:\n\n";
	cin>>id;
	if (head == NULL)
	{
		system("cls");
		cout<<"List is empty"<<endl;
	}
	int pos=0;
	int count=display();
	pos=search(id);
	if(pos<=count)
	{
		while(cur->ID!=id)
		{
			pre=cur;
			cur=cur->next;
		}
		pre->next=cur->next;
		system("cls");
		cout<<"\n<<item is deleted>>\n";
	}
	else
	{
		cout<<"\n<<<Not found>>\n\n";
	}
}

//////////////////////////////////////////////////////////////////////////////////
void modify()
{
	int id;
	double pre;
	string pName;
	int nid; int nq;
	if (head == NULL)
	{
		system("cls");
		cout<<"List is empty"<<endl;
	}
	else
	{    
	    display();
		cout<<"\n\nEnter ID to modify product Name and its price:\n";
		cin>>id;
		struct node *cur=head;
		int pos=0;
		int count=display();
	    pos=search(id);
	    if(pos<=count)
	    {
			while(cur->ID!=id)
			{
				cur=cur->next;
			}
			cout<<"\nOld ID : "<<cur->ID<<endl;
			cout<<"\nOld Name : "<<cur->proName<<endl;
			cout<<"\nOld Price : "<<cur->prePrice<<endl;
			cout<<"\nOld Quantity : "<<cur->quantity<<endl;

			cout<<"Enter new ID:";
			cin>>nid;
			cur->ID=nid;
			cout<<"Enter new Name:";
			cin>>pName;
			cur->proName=pName;
			cout<<"Enter new Price:";
			cin>>pre;
			cur->prePrice=pre;
			cout<<"Enter new Quantity:";
			cin>>nq;
			cur->quantity=nq;
	    }
	    else
	    {
			cout<<id<<" is <<<Not found>>\n\n";
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////
int display()
{
	system("cls");
	int c=0;
	struct node *p=head;
	cout<<"Existing products are:\n";
	cout<<"ID\t\tProduct Name\t\t\\Price\t\tQuantity\n";
	cout<<"=================================================================|\n";
	while(p!=NULL)
	{
		cout<<p->ID<<"\t\t"<<p->proName<<"\t\t\t"<<p->prePrice<<"\t\t\t"<<check(p->quantity)<<"\n"; 
		p=p->next;
		c=c+1;
	}
	cout<<"\nTotal products in our store is : "<<c<<"\n\n\n";
	return c;
}

////////////////////////////////////////////////////////////////////////////////////////
string check(int quant)
{
	int a = quant;
    stringstream ss;
    ss << a;
    string quantity = ss.str();

	if(quant<=0)
		return "out of stock!";
	else
		return quantity;
}

///////////////////////////////////////////////////////////////////////
void buy()
{
	system("cls");
	display();
	string products[20];
	int pay=0,no,c=0,price,id,i=1;

	if(head==NULL)
	{
		cout<<"\n<<<<There is no items to buy>>>>\n\n";
	}
	else
	{
		cout<<"How many items you wanna to buy!\n";
		cin>>no; 
		int count=display();
		while (i<=no)
		{
			struct node *cur=head;
			int quant,cho;
a:
			cout<<"Enter id of item that you want to buy: ";
			int id,pos=0;
			cin>>id;
			if(id==-1){system("cls"); return;}
			pos=search(id);
			if(pos<=count)
			{
				while(cur->ID!=id)
				{
					cur=cur->next;
				}
				cout<<"How many quantities you want:";
				cin>>quant;
				if(cur->quantity<quant)
				{
					cout<<"\n----The Quantity You Entered is not available---"<<endl;
					cout<<"\n-----(Press -1 for Back to Main Menu)------"<<endl;
					goto a;
				}
				products[c]=cur->proName;
				c++;
				pay=pay+(cur->prePrice*quant);
				cur->quantity=cur->quantity-quant;
				i++;
			}
			else
			{
				cout<<"\n<<<This item is not available>>>\n\n";
			}
		}
		string customer;
		cout<<"\nEnter Your Name :"; 
		cin>>customer;
		enqueue(customer);
		system("cls");
		cout<<"\n\nYou have bought : ";
		for(int i=0;i<no;i++)
		{
			cout<<products[i]<<",";
		}
		price=pay*(0.90);
		cout<<"\nOriginal price : "<<pay;
		cout<<"\n with 10% discount: "<<price<<"\nThank you!\n\n";
	}
}

////////////////////////////////////////////////////////////////////////////////////////
void administator()
{
	system("cls");
	int ch;
	do {
		cout<<"\t\t============================================"<<endl;
		cout<<"\t\t|          Administator Portal              |"<<endl;
		cout<<"\t\t============================================"<<endl;

		cout<<"\t\t 1) ADD a new product\n";
		cout<<"\t\t 2) Display all products\n";
		cout<<"\t\t 3) Modify product\n";
		cout<<"\t\t 4) Delete product\n";
		cout<<"\t\t 5) Customers List\n";
		cout<<"\t\t 6) Dequeue customer\n";
		cout<<"\t\t 7) Generate hash\n";
		cout<<"\t\t 0) Main Menu\n";

		cout<<"\nEnter Your choice >>>";   
		cin>>ch;
		switch(ch){
			case 1: beg(); break;
			case 2: system("cls"); display(); break;
			case 3: modify(); system("cls"); break;
			case 4: delPro(); break;
			case 5: system("cls"); displayQueue(); break;
			case 6: system("cls"); dequeue(); displayQueue(); break;
			case 7:
				int x,n;
				cout<<"Enter element: ";
				cin>>x;
				cout<<"Of total list number: ";
				cin>>n;
				cout<<"Hash = "<<::hash(x,n);
				break;
			default: system("cls");
		}
	} while(ch!=0);
}

///////////////////////////////////////////////////////////////////////
int main()
{
	for(int i=0;i<=51;i++)
	{
		push(i);
	}

	system("color F1");
	gotoxy(17,5);
	cout<<"--------------------------------------------------"<<endl;
	gotoxy(17,7);
	cout<<"||            Shopping Club System                ||"<<endl;
	gotoxy(17,9);
	cout<<"--------------------------------------------------"<<endl;
	gotoxy(17,11);
	cout<<"|Subject Teacher ->> Raut Sir <<-- |"<<endl;
	gotoxy(17,13);
	cout<<">>>----Project Implemented By-----<<<"<<endl;
	gotoxy(22,15);
	cout<<"Dnyaneshwar Pawar (49)"<<endl;
	gotoxy(22,16);
	cout<<"Sachin Dhamnekar (11)"<<endl;
	gotoxy(17,18);
	system("pause");
	system("cls");
	system("color Fc");

	int ch;
	while(ch!=3)
	{
		cout<<"\n\t\t|--------<Main Menu>-----------|";
		cout<<"\n\n";
		cout<<"\t\t 1)Administator of Market\n";
		cout<<"\t\t 2)Customer\n";
		cout<<"\t\t 3)Exit\n";

		cout<<"\nEnter Your choice >>>";
		cin>>ch;
		switch(ch)
		{
			case 1:
				if(adminLogin())
					administator();
				else
					cout<<"\nAccess Denied!\n";
				break;

			case 2:
				cout<<endl<<endl;
				bpop();
				system("pause");
				buy();
				break;

			case 3:
				cout<<"\n\n\t\t\tThank You\n";
				break;
		}
	}
	return 0;
}
