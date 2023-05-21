#include <iostream>
#include <string.h>
#include <exception>
#include<functional>
#include <memory>
using namespace std;

class VenitInvalidException : public exception
{
private:
    float suma1;
public:
    VenitInvalidException(float suma) : suma1(suma) {}

    const char* what() const noexcept override
    {
        return "Salariu invalid: Valoare negativa!";
    }

    float GetSuma() const
    {
        return suma1;
    }


};
class NrTricouInvalidException : public exception
{
private:
    int nrTricou;
public:
    NrTricouInvalidException(int nr) : nrTricou(nr) {}

    virtual const char* what() const throw()
    {
        return "Numarul tricoului este invalid!";
    }

    int GetNrTric() const throw()
    {
        return nrTricou;
    }
};
class PointGuardException : public exception
{
private:
    float height;
public:
    PointGuardException(float h) : height(h) {}
    virtual const char* what() const throw()
    {
        return "Inaltimea jucatorului nu este intre 1.70 si 1.90 metri";
    }
    float GetHeight() const throw()
    {
        return height;
    }

};
class CenterException : public exception
{
private:
    int recup;
public:
    CenterException(int r) : recup(r) {}
    virtual const char* what() const throw()
    {
        return "Nr de rebound-uri al jucatorului este 0 ceea ce inseamna ca nu este center";
    }
    int GetRecup() const throw()
    {
        return recup;
    }

};
class NrPuncteInvalidException : public exception
{
private:
    int nrPuncte;
public:
    NrPuncteInvalidException(int p) : nrPuncte(p) {}

    virtual const char* what() const throw()
    {
        return "Numarul punctelor este invalid!";
    }

    int GetNrPunct() const throw()
    {
        return nrPuncte;
    }
};
class Salariu
{
private:
    float valoare;
public:
    Salariu()
    {
        valoare=0;
        //cout<<"S-a apelat constructorul Salariu1"<<endl;
    };
    Salariu(const Salariu& v)
    {
        valoare=v.valoare;
        //cout<<"S-a apelat constructorul de copiere Salariu2"<<endl;
    };
    Salariu& operator=(const Salariu& v1)
    {
        valoare=v1.valoare;
        return *this;
    };
    void SetValoare(float n)
    {
        if (n < 0)
        {
            throw VenitInvalidException(n); //exceptie custom
        }
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
        //cout<<"S-a apelat destructorul Salariu"<<endl;
    };
};
class Jucator
{
private:
    string Nume;
    int varsta;
    Salariu Venit;
    Jucator* next;
protected:
    int licenta;
    int nrTricou;

public:
    Jucator()
    {
        //cout<<"S-a apelat constructorul Jucator1"<<endl;
    };
    Jucator(string Nume,int varsta,Salariu Venit, Jucator* next,int licenta,int nrTricou)
    {
        this->Nume=Nume;
        this->varsta=varsta;
        this->Venit=Venit;
        this->next=next;
        this->licenta=licenta;
        this->nrTricou=nrTricou;
        //cout<<"S-a apelat constructorul Jucator2"<<endl;
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
    void SetLicenta(int n)
    {
        licenta=n;
    }
    void SetNrTricou(int n)
    {
        if(n>99 || n<0)
        {
            throw NrTricouInvalidException(n); //exceptie custom
        }
        nrTricou=n;

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
    int GetLicenta() const
    {
        return licenta;
    }
    int GetNrTricou() const
    {
        return nrTricou;
    }

    friend ostream& operator<<(ostream& out, const Jucator& j)
    {
        out<<"Nume:"<<j.GetNume()<<endl<<"Varsta:"<<j.GetVarsta()<<endl<<"Salariu:"<<j.GetVenit().GetValoare();
        return out;
    }
    Jucator& operator=(const Jucator& j) //al din
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
    //metoda
    void afisareDetalii()
    {
        cout<<"Licenta:"<<GetLicenta()<<endl;
        cout<<"Numar tricou:"<<GetNrTricou()<<endl;
    }
    virtual ~Jucator()
    {
        if(next!=nullptr)
        {
            delete next;
            next=nullptr;
        }
        //cout<<"S-a apelat destructorul Jucator"<<endl;
    }



};
//interfata
class AbilitatiJucator
{
public:
    virtual void afisareAbilitati()=0;
    virtual float indiceEficienta()=0;
    virtual ~AbilitatiJucator()
    {

    }
};
//ierahii de mostenire
class pointGuard: public Jucator
{
private:
    float inaltime;
    string medieMinute;

public:
    pointGuard(): Jucator()
    {
        //cout<<"s-a apelat constructorul PointGuard1"<<endl;
    };
    pointGuard(string Nume,int varsta, Salariu Venit, Jucator *next, float inaltime,string medieMinute): Jucator(Nume, varsta,Venit, next,licenta,nrTricou)
    {
        this->inaltime=inaltime;
        this->medieMinute=medieMinute;
        //cout<<"S-a apelat constructorul PointGuard 2"<<endl;
    };
    void SetInaltime(float n)
    {
        try
        {
            if(n<1.70 || n>1.90)
            {
                throw PointGuardException(n); //exceptie custom
            }

        }
        catch (const PointGuardException& pge)
        {
            cout<<"Exceptia:"<<pge.what()<<"-Inaltime jucatorului este "<<pge.GetHeight()<<" metrii"<<endl;
        }
        inaltime=n;
    }
    float GetInaltime() const
    {
        return inaltime;
    }
    void SetMedieMinute(string n)
    {
        medieMinute=n;
    }
    string GetMedieMinute() const
    {
        return medieMinute;
    }
    void afisareDetaliiPG()
    {
        cout<<"Nume:"<<GetNume()<<endl;
        cout<<"Varsta:"<<GetVarsta()<<endl;
        cout<<"Salariu:"<<GetVenit().GetValoare()<<endl;
        cout<<"Inaltime:"<<GetInaltime()<<endl;
        cout<<"Medie minute pe meci:"<<GetMedieMinute()<<endl;
        afisareDetalii();
    }

    void dynamic_cast_aloc_din_pg()
    {
        Jucator* jucatori[10];
        int nrJucatori=5;
        Salariu salariu;
        salariu.SetValoare(3500);
        Jucator* juchitus = new pointGuard("Radu", 23, salariu, nullptr, 1.75, "06:12");
        pointGuard* pg = dynamic_cast<pointGuard*>(juchitus);

        if (pg != nullptr)
        {
            pg->SetInaltime(1.9);
            pg->afisareDetaliiPG();
        }
        else
        {
            cout << "Nu a mers" << endl;
        }
        jucatori[nrJucatori]=pg;
        nrJucatori++;
        delete jucatori[5];
        jucatori[5]=nullptr;
    }

    ~pointGuard()
    {
        //cout<<"S-a apelat destructorul PointGuard"<<endl;
    };


};
class center: public Jucator, public AbilitatiJucator
{
private:
    int rebounds;
    int medieNrPuncte;
public:
    center(): Jucator()
    {
        //cout<<"s-a apelat constructorul Center"<<endl;
    };
    center(string Nume,int varsta, Salariu Venit, Jucator *next, int rebounds,int medieNrPuncte): Jucator(Nume, varsta,Venit, next,licenta,nrTricou)
    {
        this->rebounds=rebounds;
        this->medieNrPuncte=medieNrPuncte;
        //cout<<"S-a apelat constructorul PointGuard 2"<<endl;
    };
    void SetRebounds(int n)
    {
        try
        {
            if (n==0)
            {
                throw CenterException(n); //exceptie custom
            }
        }
        catch ( const CenterException& ce)
        {
            cout<< "Exceptie: " << ce.what() << " - Jucatorul a recuperat " << ce.GetRecup() << " mingi" <<endl;
            throw NrPuncteInvalidException(n); //try...catch care arunca in alta exceptie;
        }
        rebounds=n;
    }
    int GetRebounds() const
    {
        return rebounds;
    }
    void SetMedieNrPuncte(int n)
    {
        medieNrPuncte=n;
    }
    int GetMedieNrPuncte() const
    {
        return medieNrPuncte;
    }
    void afisareAbilitati() override
    {
        cout<<"Rebounds:"<<GetRebounds()<<endl;
        cout<<"Medie nr puncte:"<<GetMedieNrPuncte()<<endl;
    }
    float indiceEficienta() override
    {
        float indice=((GetRebounds()+GetMedieNrPuncte())*3)/7;
        return indice;
    }
    void afisareDetaliiCenter()
    {
        cout<<"Nume:"<<GetNume()<<endl;
        cout<<"Varsta:"<<GetVarsta()<<endl;
        cout<<"Salariu:"<<GetVenit().GetValoare()<<endl;
        cout<<"Inaltime:"<<GetRebounds()<<endl;
        cout<<"Medie minute pe meci:"<<GetMedieNrPuncte()<<endl;
        afisareDetalii();
    }
    void dynamic_cast_aloc_din_center()
    {
        Jucator* jucatori[10];
        int nrJucatori=5;
        Salariu salariu;
        salariu.SetValoare(3500);
        Jucator* juchitus = new center("Radu", 23, salariu, nullptr,4, 13);
        center* c = dynamic_cast<center*>(juchitus);

        if (c != nullptr)
        {
            c->SetRebounds(5);
            c->afisareDetaliiCenter();
        }
        else
        {
            cout << "Nu a mers" << endl;
        }
        jucatori[nrJucatori]=c;
        nrJucatori++;
        delete jucatori[5];
        jucatori[5]=nullptr;
    }

    ~center()
    {
        //cout<<"S-a apelat destructorul Center"<<endl;
    };


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
        //cout<<"S-a apelat constructorul Echipa"<<endl;
    };
    Echipa(const Echipa& e)
    {
        juchi=e.juchi;
        //cout<<"S-a apelat constructorul de copiere"<<endl;
    };
    void SetJucator(Jucator* j)
    {
        juchi=j;
    }
    void SetNume(string s)
    {
        nume=s;
    }
    string GetNume() const
    {
        return nume;
    }
    Jucator* GetJucator()
    {
        return juchi;
    }
    friend ostream& operator<<(ostream& out, const Echipa& e) //supr
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
        //cout<<"S-a apelat destructorul Echipa"<<endl;
    };

};
//mostenire multipla
class Antrenor: public Salariu, public Echipa
{
private:
    string nume;
    int licentaCarnet;
    static int varsta;
public:

    Antrenor(): Salariu(), Echipa()
    {
        //cout<<"S-a apelat constructorul Antrenor"<<endl;
    };
    static void afiseazaVarsta()
    {
        cout << "Varsta antrenorului este: " << Antrenor::varsta << endl;
    }
    static void SetVarsta(int n)
    {
        varsta=n;
    }
    ~Antrenor()
    {
        //cout<<"S-a apelat destructorul Antrenor"<<endl;
    };
};
int Antrenor::varsta = 0;
class Campionat
{
private:
    string perioada;
    Echipa echipi;
public:
    Campionat()
    {
        //cout<<"S-a apelat constructorul Campionat"<<endl;

    };
    ~Campionat()
    {
        //cout<<"S-a apelat destructorul Campionat"<<endl;
    };
};
//clasa abstracta
class MeciuriPerWeekend
{
private:
    int nrWeekenduri;
public:
    void SetNrWeekenduri(int n)
    {
        nrWeekenduri=n;
    }
    int GetNrWeekenduri() const
    {
        return nrWeekenduri;
    }
    virtual void afisareDetaliiLiga()=0;
    virtual float calculMeciuriPerWeekend()=0;
    virtual ~MeciuriPerWeekend()
    {

    }
};
//ierahie mostenire
class LNBM: public Campionat, public MeciuriPerWeekend
{
private:
    int nrEchipe;
    int nrEtape;
public:
    LNBM(): Campionat()
    {
        //cout<<"S-a apelat constructorul LNBM"<<endl;
    };
    LNBM(string perioada, Echipa echipi,int nrEchipe, int nrEtape): Campionat()
    {
        this->nrEchipe=nrEchipe;
        this->nrEtape=nrEtape;
        //cout<<"S-a apelat constructorul PointGuard 2"<<endl;
    };
    void SetNrEchipe(int n)
    {
        nrEchipe=n;
    }
    void SetNrEtape(int n)
    {
        nrEtape=n;
    }
    int GetNrEchipe() const
    {
        return nrEchipe;
    }
    int GetNrEtape() const
    {
        return nrEtape;
    }

    float calculMeciuriPerWeekend() override
    {
        int nrMeciuri=((GetNrEchipe()/2)*GetNrWeekenduri())/GetNrEtape();
        return nrMeciuri;
    }
    void afisareDetaliiLiga() override
    {
        cout<<"Numar echipe:"<<GetNrEchipe()<<endl;
        cout<<"Numar etape:"<<GetNrEtape()<<endl;
        cout<<"Numar weekenduri:"<<GetNrWeekenduri()<<endl;
    }
    ~LNBM()
    {
        //cout<<"S-a apelat destructorul LNBM"<<endl;
    }
};
class LNBF: public Campionat
{
private:
    int nrEchipe;
    int nrEtape;
    static int editie;
public:
    LNBF(): Campionat()
    {
        //cout<<"S-a apelat constructorul LNBF"<<endl;
    };
    void SetNrEchipe(int n)
    {
        nrEchipe=n;
    }
    void SetNrEtape(int n)
    {
        nrEtape=n;
    }
    int GetNrEchipe()
    {
        return nrEchipe;
    }
    int GetNrEtape()
    {
        return nrEtape;
    }
    static void afiseazaEditie()   // metoda statica
    {
        cout << "Numarul total de echipe este: " << LNBF::editie << endl;
    }
    static void SetEditie(int n)
    {
        LNBF::editie = n;
    }
    template <typename T>
    int CalculeazaNumarMeciuriEtapa(const T& nrMeciuri) {  //functie sablon
        return nrMeciuri/nrEtape;
    }
    ~LNBF()
    {
        //cout<<"S-a apelat destructorul LNBF"<<endl;
    }
};
int LNBF::editie=0;
class Sala
{
private:
    string locatie;
    Campionat liga;
public:
    Sala()
    {
        //cout<<"S-a apelat constructorul Sala"<<endl;
    };
    void SetLocatie(function<void(string&)> lambda)      //lambda
    {
        lambda(locatie);
    }
    string GetLocatie() const
    {
        return locatie;
    }

    ~Sala()
    {
        //cout<<"S-a apelat destructorul Sala"<<endl;
    };
};
template <typename T>
class Polivalenta: public Sala
{
private:
    T nrLocuri;
public:
    Polivalenta()
    {
        nrLocuri=T();
        //cout<<"S-a apelat contructorul Polivalenta1"<<endl;
    }
    Polivalenta(T value)
    {
        nrLocuri=value;
        //cout<<"S-a apelat constructorul Polivalenta2"<<endl;
    }
    void SetValue(T value)
    {
        nrLocuri=value;
    }

    T GetValue()
    {
        return nrLocuri;
    }
    ~Polivalenta()
    {
        //cout<<"S-a apelat destructorul Polivalenta"<<endl;
    }

};
void TestConstructorIntSalariu()
{
    Salariu i;
}
void TestDestructorSalariu()
{
    Salariu i;
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
    Jucator("Alex",21,salariu,nullptr,1234,15);

}
void TestDestructorJucator()
{
    Salariu salariu;
    salariu.SetValoare(5000);
    Jucator("Alex",21,salariu,nullptr,1234,15);

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
    s.SetValoare(-5);
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
    cout<<j<<endl;
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
void TestConstructorIntPointGuard()
{
    pointGuard i;
}
void TestConstructorIntCenter()
{
    center i;
}
void TestConstructorIntLNBM()
{
    LNBM i;
}
void TestConstructorIntLNBF()
{
    LNBF i;
}
void TestConstructorIntAntrenor()
{
    Antrenor i;
}
void TestConstructorListPointGuard()
{
    Salariu salariu;
    salariu.SetValoare(2500);
    Jucator* jucatorNext= new Jucator("Marian",25,salariu,nullptr,1234,84);
    pointGuard pg("Daniel",20,salariu,jucatorNext,1.50,"10:43");
    cout<<"Nume:"<<pg.GetNume()<<endl;
    cout<<"Varsta:"<<pg.GetVarsta()<<endl;
    cout<<"salariu:"<<pg.GetVenit().GetValoare()<<endl;
    cout<<"Inaltime:"<<pg.GetInaltime()<<endl;
    cout<<"Medie minute pe meci:"<<pg.GetMedieMinute()<<endl;
    if(pg.GetNext()!=nullptr)
    {
        cout<<"Jucator next:"<<pg.GetNext()->GetNume()<<endl;
        cout<<"Varsta:"<<pg.GetNext()->GetVarsta()<<endl;
        cout<<"Salariu:"<<pg.GetNext()->GetVenit().GetValoare()<<endl;

    }

}
void TestMetodaPG()
{
    Salariu salariu;
    salariu.SetValoare(5000);
    pointGuard pg;
    pg.SetNume("Vali");
    pg.SetVarsta(18);
    pg.SetVenit(salariu);
    pg.SetNext(NULL);
    pg.SetLicenta(58962);
    pg.SetNrTricou(85);
    pg.SetInaltime(1.80);
    pg.SetMedieMinute("8.6");
    pg.afisareDetaliiPG();

}
void TestConstructorListCenter()
{
    Salariu salariu;
    salariu.SetValoare(2500);
    Jucator* jucatorNext= new Jucator("Marian",25,salariu,nullptr,1234,15);
    center c("Daniel",20,salariu,jucatorNext,12,18);
    cout<<"Nume:"<<c.GetNume()<<endl;
    cout<<"Varsta:"<<c.GetVarsta()<<endl;
    cout<<"salariu:"<<c.GetVenit().GetValoare()<<endl;
    cout<<"Rebounds"<<c.GetRebounds()<<endl;
    cout<<"Medie nr puncte pe meci:"<<c.GetMedieNrPuncte()<<endl;
    if(c.GetNext()!=nullptr)
    {
        cout<<"Jucator next:"<<c.GetNext()->GetNume()<<endl;
        cout<<"Varsta:"<<c.GetNext()->GetVarsta()<<endl;
        cout<<"Salariu:"<<c.GetNext()->GetVenit().GetValoare()<<endl;

    }

}
void TestInterfataAbilJuchi()
{
    Salariu salariu;
    salariu.SetValoare(4550);
    center c("Flavius",17,salariu,nullptr,3,12);
    cout<<"Abilitatile jucatorului Flavius:"<<endl;
    c.afisareAbilitati();
    cout<<endl;
    cout<<"Indicele de eficienta al jucatorului Flavius:"<<c.indiceEficienta()<<endl;
}
void TestCalculNrMeciuriWeekend()
{
    Echipa echipa;
    echipa.SetNume("FC Arges");
    LNBM diva("2022-2023", echipa,23,14);
    diva.SetNrWeekenduri(11);
    cout<<"Detaliile ligii:"<<endl;
    diva.afisareDetaliiLiga();
    cout<<endl;
    cout<<"Numarul de meciuri pe weekend:"<<diva.calculMeciuriPerWeekend()<<endl;
}
void TestDynamicCastPG()
{

    Salariu salariu;
    salariu.SetValoare(3500);
    pointGuard pg1("Andrei", 22, salariu, nullptr, 1.8, "05:30");
    pg1.afisareDetaliiPG();
    pointGuard pg2;
    pg2.dynamic_cast_aloc_din_pg();




}
void TestDynamicCastC()
{
    Salariu salariu;
    salariu.SetValoare(3500);
    center c1("Andrei", 22, salariu, nullptr, 7, 20);
    c1.afisareDetaliiCenter();
    center c2;
    c2.dynamic_cast_aloc_din_center();
}
void TestVenitInvalidException()
{
    Salariu salariu;
    salariu.SetValoare(-2000);
}
void TestPointGuardException()
{
    pointGuard pg;
    pg.SetInaltime(1.5);
}
void TestNrInvalid()
{
    pointGuard pg;
    pg.SetNrTricou(123);
}
void TestCenterException()
{
    center c;
    c.SetRebounds(0);
}
void TestMetodaStatica()
{
    Antrenor antrenor;
    antrenor.SetVarsta(45);
    antrenor.afiseazaVarsta();

}
void TestMetodaStatica2()
{

    LNBF liga;
    liga.SetEditie(10);
    LNBF::afiseazaEditie();

}
void TestLambda()
{
    Sala s;
    s.SetLocatie([](string& locatie)
    {
        locatie = "Pitesti ARENA";
    });
    cout << "Locatia este: " << s.GetLocatie() << endl;
}
template<typename T>
void TestConstructorPolivalenta()
{
    Polivalenta<T> obj1;
    cout<<obj1.GetValue();
     T value1=T(500);
    Polivalenta<T> obj2(value1);
    cout<<obj2.GetValue();

}
void TestFunctieSablon()
 {
    LNBF campionat;
    campionat.SetNrEchipe(20);
    campionat.SetNrEtape(9);

    int numarMeciuri = 60;
    cout<<"Numarul de meciuri intr-o etapa: "<< campionat.CalculeazaNumarMeciuriEtapa(numarMeciuri)<<endl;
}
void TestImplementare()
{
    Polivalenta<int> polivalenta;
    polivalenta.SetValue(150);
    int locuri = polivalenta.GetValue();
    cout<<locuri;

}
int main()
{
    //TestConstructorIntSalariu();
    //TestDestructorSalariu();
    //TestConstructorCopiereSalariu();
    //TestOperatorSalariu();
    //TestConstructorIntJucator();
    //TestDestructorJucator();
    //TestConstructorIntEchipa();
    //TestConstructorCopiereEchipa();
    //TestOperatorEgalJucator();
    //TestAfisareSalariu(); //test exceptie VenitInvalid
    //TestAfisareJucator();
    //TestAfisareEchipa();
    //TestConstructorIntCampionat();
    //TestDestructorCampionat();
    //TestConstructorIntSala();
    //TestDestructorSala();
    //TestConstructorIntPointGuard();
    //TestConstructorIntCenter();
    //TestConstructorIntLNBM();
    //TestConstructorIntLNBF();
    //TestConstructorIntAntrenor();
    //TestConstructorListPointGuard();
    //TestMetodaPG();
    //TestConstructorListCenter();
    //TestInterfataAbilJuchi();
    //TestCalculNrMeciuriWeekend();
    //TestDynamicCastPG();
    //TestDynamicCastC();
    //TestPointGuardException(); //try...catch
    //TestNrInvalid();
    //TestVenitInvalidException();
    //TestCenterException();
    //TestMetodaStatica();
    //TestMetodaStatica2();
    //TestLambda();
    //TestConstructorPolivalenta<int>();
    //TestFunctieSablon();
    //TestImplementare();

}
