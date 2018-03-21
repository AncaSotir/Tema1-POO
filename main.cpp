#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
ifstream f("date.in");
ofstream g("date.out");


class ListaDubluInlantuita;

class nod
{
    friend class ListaDubluInlantuita;


    double info;
    nod * next;
    nod * prev;
public:
    nod (double x)
    {
        info=x;
        next=prev=NULL;
    }
    nod ()
    {
        info=0;
        next=prev=NULL;
    }

    friend istream& operator>> (istream &,nod &);
    friend ostream& operator<< (ostream &,nod);

    friend istream& operator>> (istream &,ListaDubluInlantuita&);
    friend ostream& operator<< (ostream &,ListaDubluInlantuita);
};

istream& operator>> (istream &in, nod &x)
{
    in>>x.info;
    return in;
}
ostream& operator<< (ostream &out,nod x)
{
    out<<x.info<<' ';
    return out;
}


class ListaDubluInlantuita
{
    nod * first;
    nod * last;
    int length;

public:

    ListaDubluInlantuita ()
    {
        first=last=NULL;
        length=0;
    }
    ListaDubluInlantuita (const ListaDubluInlantuita& sursa)
    {
        nod *p;
        first=last=NULL;
        p=sursa.first;
        while(p!=NULL)
        {
            push(p->info);
            p=p->next;
        }
        length=sursa.length;
    }
    ~ListaDubluInlantuita ()
    {
        while(first!=NULL)
            pop();
    }
    int size()
    {
        return length;
    }
    void push(double x)     ///se adauga la sfarsitul listei
    {
        if(first==NULL)     ///el adaugat va fi primul
        {
            nod * p = new nod(x);
            first=p;
            last=p;
        }
        else                ///el adaugat va fi ultimul
        {
            nod * p = new nod(x);
            last->next=p;
            p->prev=last;
            last=p;
        }
        length++;
    }
    void push(double x, int poz)
    {
        if(first==NULL) ///lista e vida. orice val are poz, el va fi primul.
        {
            nod *p=new  nod(x);
            first=last=p;
        }
        else if(poz==0) ///adaug la inceput
        {
            nod *c=new nod(x);
            c->next=first;
            first->prev=c;
            first=c;
        }
        else    ///adaug la lista[poz]
        {
            nod*p;
            int i;
            for(p=first,i=1 ; i<=poz && p->next!=NULL  ;  ++i, p=p->next);
            if(i<=poz)   ///adaug la sfarsit
            {
                nod *c=new nod(x);
                last->next=c;
                c->prev=last;
                last=c;
            }
            else
            {
                nod *c=new nod(x);
                c->next=p;
                c->prev=p->prev;
                p->prev->next=c;
                p->prev=c;
            }

        }
        length++;
    }
    void pop()       ///se sterge ultimul
    {
        if(last!=NULL)
        {
            nod *p;
            p=last;
            if(p->prev!=NULL)
                p->prev->next=NULL;
            else
            {
                first=NULL;
            }
            last=p->prev;
            delete p;
        }
        length--;
    }
    void look_for(double x)
    {
        nod *p=first;
        int poz[100];
        int i=0,contor=-1;
        while(p!=NULL)
        {
            if(p->info==x)
                poz[++contor]=i;
            p=p->next;
            ++i;
        }
        if(contor==-1)
            cout<<"Elementul "<<x<<" nu apartine listei.\n";
        else

        {
            cout<<"Elementul "<<x<<" apartine listei, pe pozitiile:";
            for(i=0; i<=contor; ++i)
                cout<<' '<<poz[i];
            cout<<".\n";
        }
    }
    ListaDubluInlantuita break_at (int poz)
    {
        /// obiectul implicit va deveni "capul listei rupte"
        /// metoda returneaza "coada listei rupte"

        ///exceptie la poz=0 sau poz>=length. nu are sens?
        nod *p;
        int i;
        for(i=1,p=first; i<=poz&&p!=NULL; ++i,p=p->next);
        ListaDubluInlantuita tail;
        if(p==NULL)
            return tail;
        nod *c=p->prev;
        ///copiere coada lista
        while(p!=NULL)
        {
            tail.push(p->info);
            p=p->next;
        }
        ///modificare cap lista (eliminare noduri din coada)
        while(last!=c)
            pop();
        return tail;
    }
    ListaDubluInlantuita operator= (const ListaDubluInlantuita lista)
    {
        while(first!=NULL)
            pop();

        nod *p;
        first=last=NULL;
        p=lista.first;
        while(p!=NULL)
        {
            push(p->info);
            p=p->next;
        }
        length=lista.length;
        return *this;
    }
    ListaDubluInlantuita operator+ (const ListaDubluInlantuita &lista)
    {
        ListaDubluInlantuita *temp=this;
        temp->last->next=lista.first;
        temp->last->next->prev=temp->last;
        temp->last=lista.last;
        temp->length=lista.length+length;
        return *temp;
    }
    double operator[] (int n)
    {
        int i=0;
        //if(first==NULL)
        //    return NULL;          ////EXCEPTII
        nod *p=first;
        do
        {
            if(i==n)
                return p->info;
            if(p!=NULL)
            {
                p=p->next;
                i++;
            }
        }
        while(p!=NULL);
        ///EXCEPTIE (i!=n)
    }
    bool operator==(const ListaDubluInlantuita lista)
    {
        if(length!=lista.length)
            return false;
        nod*p=first;
        nod*q=lista.first;
        while(p!=NULL)
        {
            if(p->info!=q->info)
                return false;
            p=p->next;
            q=q->next;
        }
        return true;
    }
    bool operator!=(const ListaDubluInlantuita lista)
    {
        if(length!=lista.length)
            return true;
        nod*p=first;
        nod*q=lista.first;
        while(p!=NULL)
        {
            if(p->info!=q->info)
                return true;
            p=p->next;
            q=q->next;
        }
        return false;
    }
    bool operator<(const ListaDubluInlantuita lista)
    {
        ///ordonez lexicografic
        nod*p=first;
        nod*q=lista.first;
        while(p!=NULL&&q!=NULL)
        {
            if(p->info<q->info)
                return true;
            if(p->info>q->info)
                return false;
            p=p->next;
            q=q->next;
        }
        if(p!=NULL)
            return false;
        if(p==NULL&&q==NULL)
            return false;
        return true;
    }

    friend istream& operator>> (istream &,ListaDubluInlantuita&);
    friend ostream& operator<< (ostream &,ListaDubluInlantuita);
};

istream& operator>> (istream &in, ListaDubluInlantuita & lista)
{
    while(lista.first!=NULL)
        lista.pop();
    int n;
    in>>n;
    nod*x=new nod;
    for(int i=1; i<=n; ++i)
    {

        in>>(*x);
        lista.push(x->info);

    }
    delete x;
    return in;
}
ostream& operator<< (ostream &out,ListaDubluInlantuita lista)
{
    nod *p=lista.first;
    if(lista.first!=NULL)
    {
        do
        {
            out<<*p;
            p=p->next;
        }
        while(p!=NULL);

        out<<'\n';

        p=lista.last;

        do
        {
            out<<*p;
            p=p->prev;
        }
        while(p!=NULL);

        out<<"\n\n";
    }
    return out;
}


int main()
{
    g<<"*************************\nSortarea si afisarea listelor:\n\n";
    int n;
    f>>n;
    ListaDubluInlantuita v[100];
    for(int i=0; i<n; ++i)
    {
        f>>v[i];
    }
    sort(v,v+n);
    for(int i=0; i<n; ++i)
        g<<v[i];
    g<<"*************************\nStergerea ultimului element din lista:\n\n";
    ListaDubluInlantuita lista;
    f>>lista;
    g<<lista;
    lista.pop();
    g<<lista;
    g<<"*************************\nConcatenarea a doua liste:\n\n";
    ListaDubluInlantuita l, l1, l2;
    f>>l1>>l2;
    g<<l1<<l2;
    l=l1+l2;
    g<<l;
    g<<"*************************\nSupraincarcarea operatorului []:\n\n";
    g<<"l[0]="<<l[0]<<'\n';
    g<<"l[1]="<<l[1]<<'\n';
    g<<"l[2]="<<l[2]<<'\n';
    g<<"*************************\nAdaugarea unui element la o pozitie data:\n\n";
    g<<l;
    l.push(0,1);
    g<<l;
    cout<<"*************************\nDeterminarea existentei unui element si pozitiile la care apare:\n\n";
    f>>l;
    l.look_for(2);
    g<<"*************************\nRuperea listei la o pozitie data:\n\n";
    f>>l;
    g<<l;
    ListaDubluInlantuita tail=l.break_at(2);
    g<<l<<tail;
    return 0;
}
