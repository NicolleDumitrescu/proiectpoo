#include <iostream>
#include <string.h>
using namespace std;
class Salariu
{
private:
    float valoare;
public:
    Salariu()
    {
        valoare=0;
        cout<<"S-a apelat constructorul"<<endl;
    };
    Salariu(const Salariu& v)
    {
        valoare=v.valoare;
        cout<<"S-a apelat constructorul de copiere"<<endl;
    };
    Salariu& operator=(const Salariu& v1)
    {
        valoare=v1.valoare;
        return *this;
    };
    void SetValoare(float n)
    {
        valoare=n;
    }
    float GetValoare() const
    {
        return valoare;
    }
    friend ostream& operator<<(ostream& out, const Salariu& sal)
    {
        out<<sal.valoare;
        return out;
    }
    ~Salariu()
    {
        cout<<"S-a apelat destructorul"<<endl;
    };
};
class Jucator
{
private:
    string Nume;
    int varsta;
    Salariu Venit;
    Jucator* next;
public:
    Jucator()
    {
        cout<<"S-a apelat constructorul"<<endl;
    };
    Jucator(string Nume,int varsta,Salariu Venit, Jucator* next)
    {
        this->Nume=Nume;
        this->varsta=varsta;
        this->Venit=Venit;
        this->next=next;
        cout<<"S-a apelat constructorul"<<endl;
    };
    void SetNume(string s)
    {
        Nume=s;
    }
    void SetVarsta(int n)
    {
        varsta=n;
    }
    void SetVenit(Salariu venit)
    {
        Venit=venit;
    }
    void SetNext(Jucator* n)
    {
        next=n;
    }
    string GetNume() const
    {
        return Nume;
    }
    Jucator* GetNext()
    {
        return next;
    }
    int GetVarsta() const
    {
        return varsta;
    }
    Salariu GetVenit() const
    {
        return Venit;
    }
    friend ostream& operator<<(ostream& out, const Jucator& j)
    {
        out<<"Nume:"<<j.GetNume()<<endl<<"Varsta:"<<j.GetVarsta()<<endl<<"Salariu:"<<j.GetVenit().GetValoare();
        return out;
    }
    Jucator& operator=(const Jucator& j)
    {
        if(this!=&j)
        {
            Nume=j.Nume;
            varsta=j.varsta;
            Venit=j.Venit;
            if(j.next!=nullptr)
            {
                next=new Jucator(*j.next);
            }
            else
            {
                next=nullptr;
            }

        }
        return *this;
    }
    void CresteSalariu()
    {
        float valoareNoua=Venit.GetValoare()*1.15;
        Venit.SetValoare(valoareNoua);
    }
    float SalariuMediu(Jucator* jucatori, int nrJucatori)
    {
        float sumaSalarii=0;
        for(int i=0; i<nrJucatori; i++)
        {
            sumaSalarii+=jucatori[i].GetVenit().GetValoare();
        }
        return sumaSalarii/nrJucatori;
    }
    ~Jucator()
    {
        if(next!=nullptr)
        {
            delete next;
            next=nullptr;
        }
        cout<<"S-a apelat destructorul"<<endl;
    }
};
class Echipa
{
private:
    string nume;
    Jucator* juchi;
public:
    Echipa()
    {
        juchi=nullptr;
        cout<<"S-a aepelat constructorul"<<endl;
    };
    Echipa(const Echipa& e)
    {
        juchi=e.juchi;
        cout<<"S-a apelat constructorul de copiere"<<endl;
    };
    void SetJucator(Jucator* j)
    {
        juchi=j;
    }
    Jucator* GetJucator()
    {
        return juchi;
    }
    friend ostream& operator<<(ostream& out, const Echipa& e)
    {
        {
            out<<e.juchi->GetNume()<<endl;
            out<<e.juchi->GetVarsta()<<endl;
            out<<e.juchi->GetVenit()<<endl;
            Jucator* curent=e.juchi->GetNext();
            while(curent!=nullptr)
            {
                out<<curent->GetNume()<<endl<<curent->GetVarsta()<<endl<<curent->GetVenit()<<endl;
                curent=curent->GetNext();
            }
        }
        return out;
    }
    ~Echipa()
    {
        cout<<"S-a apelat destructorul"<<endl;
    };

};
class Campionat
{
private:
    string denumire;
    Echipa echipi;
public:
    Campionat()
    {
        cout<<"S-a apelat constructorul"<<endl;

    };
    ~Campionat()
    {
        cout<<"S-a apelat destructorul"<<endl;
    };
};
class Sala
{
private:
    string locatie;
    Campionat liga;
public:
    Sala()
    {
        cout<<"S-a apelat constructorul"<<endl;
    };
    ~Sala()
    {
cout<<"S-a apelat destructorul"<<endl:
    };
};
void TestConstructorIntSalariu()
{
    Salariu i;
}
void TestDestructorSalariu()
{
    Salariu i;
}
}
void TestConstructorCopiereSalariu()
{
    Salariu i;
    Salariu j;
    j=i;
    cout<<i.GetValoare()<<endl;
    cout<<j.GetValoare()<<endl;
}
void TestOperatorSalariu()
{
    Salariu i;
    i.SetValoare(5);
    Salariu j;
    j=i;
    cout<<i.GetValoare()<<endl;
    cout<<j.GetValoare()<<endl;
}
void TestConstructorIntJucator()
{
    Salariu salariu;
    salariu.SetValoare(5000);
    Jucator("Alex",21,salariu,nullptr);

}
void TestDestructorJucator()
{
    Salariu salariu;
    salariu.SetValoare(5000);
    Jucator("Alex",21,salariu,nullptr);

}
void TestConstructorIntEchipa()
{
    Echipa i;
}
void TestConstructorCopiereEchipa()
{
    Echipa i;
    Echipa j=i;
}
void TestOperatorEgalJucator()
{
    Jucator j;
    Salariu s;
    s.SetValoare(1000);
    j.SetNume("Alex");
    j.SetVarsta(18);
    j.SetVenit(s);
    j.SetNext(nullptr);
    Jucator g=j;
    cout<<g;
}
void TestAfisareSalariu()
{
    Salariu s;
    s.SetValoare(5);
    cout<<s;
}
void TestAfisareJucator()
{
    Salariu s;
    s.SetValoare(1000);
    Jucator j;
    j.SetNume("Alex");
    j.SetVarsta(18);
    j.SetVenit(s);
    cout<<j;
}
void TestAfisareEchipa()
{
    Echipa e;
    Salariu s;
    s.SetValoare(1000);
    Jucator j;
    j.SetNume("Alex");
    j.SetVarsta(18);
    j.SetVenit(s);
    j.SetNext(nullptr);
    Jucator i;
    i.SetNume("Andrei");
    i.SetVarsta(20);
    i.SetVenit(s);
    i.SetNext(&j);
    Jucator k;
    k.SetNume("Alexandra");
    k.SetVarsta(19);
    k.SetVenit(s);
    k.SetNext(&i);
    e.SetJucator(&k);
    cout<<e<<endl;
}
void TestConstructorIntCampionat()
{
    Campionat i;
}
void TestDestructorCampionat()
{
    Campionat i;
}
void TestConstructorIntSala()
{
    Sala i;
}
void TestDestructorSala()
{
    Sala i;
}
int main()
{
    TestConstructorIntSalariu();
    TestDestructorSalariu();
    TestConstructorCopiereSalariu();
    TestOperatorSalariu();
    TestConstructorIntJucator();
    TestDestructorJucator();
    TestConstructorIntEchipa();
    TestConstructorCopiereEchipa();
    TestOperatorEgalJucator();
    TestAfisareSalariu();
    TestAfisareJucator();
    TestAfisareEchipa();
    TestConstructorIntCampionat();
    TestDestructorCampionat();
    TestConstructorIntSala();
    TestDestructorSala();
}


