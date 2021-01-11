/* Bejan-Topse Lucian-Cosmin -  GRUPA 211
GNU GCC - COMPILER
Szmeteanca Eduard Gabriel */

#include <iostream>
#include <vector>
#include <list>
#include <string.h>


using namespace std;

//clasa explicata de un prieten
//gasita si in git-ul lui liviu bouruc

class InputOutput //
{
public:
    virtual void citire(istream&) = 0;
    virtual void afisare(ostream&) = 0;

    friend istream& operator >>(istream& in, InputOutput& ob)
    {
        ob.citire(in);
        return in;
    }
    friend ostream& operator <<(ostream& out, InputOutput& ob)
    {
        ob.afisare(out);
        return out;
    }

    virtual ~InputOutput() {}
};
class Vaccin:public InputOutput
{

protected:
    float pret;
    float temp;
    vector <string> substante;
    int nrSubst;
    string numeProducator;

public:
    Vaccin()
    {
        pret=0;
        temp=0;
        substante={};
        nrSubst=0;
    };

    string getNume(){return this->numeProducator;}

    ~Vaccin(){};

};



class VaccinAntigripal:public Vaccin
{
private:
    string tulpina;
    bool recomandari;
public:


    void afisare(ostream& out)
    {
        out<<"\nVaccin Antigripal: ";
        out<<"\nPret: "<<pret;
        out<<"\nTemperatura minima depozitare: "<<temp;
        out<<"\nContine substantele: ";
        for (int i=0;i<substante.size();i++)
            out<<substante[i]<<" ";
        out<<"\n";
        out<<"\nTulpina: "<<tulpina;
        out<<"\nRespecta recomandarile OMS? "<<recomandari;

    }
    void citire(istream& in)
    {
        cout<<"\nScrie pret: ";
        in>>pret;
        cout<<"\nScrie temperatura minima de depozitare: ";
        in>>temp;
        cout<<"Cate substante contine vaccinul? ";
        in>>nrSubst;
        cout<<"Enumera substantele: ";
        string sb;
        for(int i=0;i<nrSubst;i++)
        {
            in>>sb;
            substante.push_back(sb);
        }
        cout<<"\nTulpina vaccinului antigripal: ";
        in>>tulpina;
        cout<<"\nRespecta recomandarile date de OMS? [true\false]";
        in>>recomandari;
        cout<<"\n";
        cout<<"\nProducator: ";
        in>>numeProducator;

    }
    void afisareSchemaVaccinare()
    {
        cout<<"cel Antigripal se administreaza la adulți o doza de 0.5 ml, iar la copii și adolescenți o doză de 0.3 ml, repetandu-se din 2 in 2 ani;";
    }
};

class VaccinAntiheptic:public Vaccin
{
private:
    string tip;
    string mod;
public:

    void afisare(ostream& out)
    {
        out<<"\nVaccin Antiheptic: ";
        out<<"\nPret: "<<pret;
        out<<"\nTemperatura minima depozitare: "<<temp;
        out<<"\nContine substantele: ";
        for (int i=0;i<substante.size();i++)
            out<<substante[i]<<" ";
        out<<"\n";
        out<<"\nTip (A,B,C): "<<tip;
        out<<"\nMod vaccinare (intramuscular,subcutanat, intradermic): "<<mod;

    }
    void citire(istream& in)
    {
        cout<<"\nScrie pret: ";
        in>>pret;
        cout<<"\nScrie temperatura minima de depozitare: ";
        in>>temp;
        cout<<"Cate substante contine vaccinul? ";
        in>>nrSubst;
        cout<<"Enumera substantele: ";
        string sb;
        for(int i=0;i<nrSubst;i++)
        {
            in>>sb;
            substante.push_back(sb);
        }
        cout<<"\nTip (A,B,C): ";
        in>>tip;
        cout<<"\nMod vaccinare (intramuscular,subcutanat, intradermic): ";
        in>>mod;
        cout<<"\n";
        cout<<"\nProducator: ";
        in>>numeProducator;

    }
    void afisareSchemaVaccinare()
    {
        cout<<"cel Antihepatita A și B, la copii cu varsta mai mică de 1 an se adminstrează 2injectari la un interval de o luna, ";
        cout<<"a treia injectare după 6 luni de la prima administrare, la adulti conform schemei de imunizare recomandata de medic;";
        cout<<"cel Antihepatita C doar la recomandarea medicului;";
    }


};

class VaccinAntiSarsCov2:public Vaccin
{

    float rataEficienta;
    vector <string> medicamente;
    vector <string> reactii;
    int nrReactii;
    int nrMedicamente;
private:
    void afisare(ostream& out)
    {
        out<<"\nVaccin Antisarscov2: ";
        out<<"\nPret: "<<pret;
        out<<"\nTemperatura minima depozitare: "<<temp;
        out<<"\nContine substantele: ";
        for (int i=0;i<substante.size();i++)
            out<<substante[i]<<" ";
        out<<"\n";
        out<<"\nAre reactiile: ";
        for (int i=0;i<reactii.size();i++)
            out<<reactii[i]<<" ";

        out<<"\nMedicamente : ";
        for (int i=0;i<medicamente.size();i++)
            out<<medicamente[i]<<" ";

        out<<"\nRata de eficienta";
        out<<rataEficienta;
        out<<"\n";



    }
    void citire(istream& in)
    {
        cout<<"\nScrie pret: ";
        in>>pret;
        cout<<"\nScrie temperatura minima de depozitare: ";
        in>>temp;
        cout<<"Cate substante contine vaccinul? ";
        in>>nrSubst;
        cout<<"Enumera substantele: ";
        string sb;
        for(int i=0;i<nrSubst;i++)
        {
            in>>sb;
            substante.push_back(sb);
        }
        char aux[200];
        cout<<"\nNumar reactii adverse: ";
        in>>nrReactii;
        cout<<"\nReactii adverse: ";
        string r;
        for(int i=0;i<nrReactii;i++)
        {
            in>>r;
            reactii.push_back(r);
        }

        cout<<"\nRata de eficienta: ";
        in>>rataEficienta;
        cout<<"\nNumar medicamente: ";
        in>>nrMedicamente;
        cout<<"\nLista medicamente: ";
        string md;
        for(int i=0;i<nrMedicamente;i++)
        {
            in>>md;
            medicamente.push_back(md);
        }
        cout<<"\nProducator: ";
        in>>numeProducator;

    }
    void afisareSchemaVaccinare()
    {
        cout<<"cel anti Sars-Cov2 se administreaza persoanelor cu varsta de peste 16 ani, 2 doze la o perioada de 21 zile. ";
    }




};

class Comanda:public InputOutput
{
    static int id;
    int ID;
    string data;
    string nume;
    string numeVaccin;
    int nrVaccin;
public:
    Comanda()
    {
        id++;ID=id;
        data="";
        nume="";
        numeVaccin="";
        nrVaccin=0;
    }
    Comanda(string data,string nume, string numeVaccin, int nrVaccin)
    {
        this->data= data;
        this->nume= nume;
        this->numeVaccin = numeVaccin;
        this->nrVaccin = nrVaccin;
    }
    void citire(istream & in)
    {
        cout<<"\nData: ";in>>data;
        cout<<"\nNume Doritor : ";in>>data;
        cout<<"\nNr vaccinuri: ";in>>nrVaccin;
        cout<<"\nNume vaccin (Gripal, Covid, Hepatita): ";in>>numeVaccin;
        if(numeVaccin=="Gripal")
            cout<<"DA";


    }
    ~Comanda(){}
};

int Comanda::id=0;

class ListaComenzi
{
    vector <Comanda*> comenzi;

};




//SingleTone ul prezentat la ultimul laborator
class SingleTone
{
private:
    static SingleTone * instance;
    vector <Vaccin*> vaccinuri;
    //vector <Comanada*> comenzi;
public:
    static SingleTone* getInstance()
    {
        if(instance == NULL)
            instance = new SingleTone();

    }
    void adaugaVaccin()
    {
        Vaccin* v = nullptr;
        cout<<"1.Pt VaccinHepati / 2. Pt VaccinSarsCov / 3. Pt vaccinGripal : ";
        int var;
        cin>>var;
        try{
        if(var==1)
        {
            v= new VaccinAntiheptic();
            cin>>(*v);
            vaccinuri.push_back(v);
        }
        else if(var==2)
        {
            v= new VaccinAntiSarsCov2();
            cin>>(*v);
            vaccinuri.push_back(v);
        }
        else if(var==3)
        {
            v= new VaccinAntigripal();
            cin>>(*v);
            vaccinuri.push_back(v);
        }
        else throw runtime_error("Tip invalid\n");
        }
        catch(const exception& ex)
        {
            cout<<ex.what();
        }
    }

    void afisareVaccin()
    {
        for(int i=0;i<vaccinuri.size();i++)
            cout<<*(vaccinuri[i])<<endl;

    }

    void numeProducatori()
    {
        for(int i=0;i<vaccinuri.size();i++)
            cout<<i<<". "<<vaccinuri[i]->getNume()<<" ";
        cout<<"\n";
    }

    void adaugaComanda()
    {
        //Comanda* c = nullptr;;
        //c = new Comanda();
        //cin>>(*c);
        //comenzi.push_back(c);
        cout<<"Nu merge";
    }
    void afisareComenzi()
    {
        //for(int i=0;i<comenzi.size();i++)
        //    cout<<*(comenzi[i])<<endl;
        //cout<<endl;
        cout<<"Nu merge";
    }
};
SingleTone* SingleTone :: instance = NULL;

int main()
{
    SingleTone * S = SingleTone::getInstance();

    int var =0 ;
    bool working=true;


    //while lul in care se genereaz meniul (folosind un switch)
    while(working==true)
    {
        cout<<"Comenzi: 1. Adauga un vaccin.  2.Afisarea tuturor vaccinurilor . //3.Nume producatori  ";
        cin>>var;
        switch(var)
        {
        case 1:
            {
                S->adaugaVaccin();
                break;
            }
        case 2:
            {
                S->afisareVaccin();
                break;
            }
        case 3:
            {
                S->numeProducatori();
                break;
            }
        case 4:
            {
                S->adaugaComanda();
            }
        case 5:
            {
                S->afisareComenzi();
            }

        case 10:
            {
                working=false;
                break;
            }
        }
    }
    //VaccinAntigripal a;
    //a.afisareSchemaVaccinare();
    //VaccinAntihepatic b; +
    //VaccinAntiSarsCov2 c; +
    //cin>>a>>b>>c; +
    //cout<<a<<b<<c; +
    //Vaccin* list[3];
    //list[0]=new VaccinAntigripal();
    //list[1]=new VaccinAntihepatic ();
    //list[2]=new VaccinAntiSarsCov2();
    //cin>>list[0]; merge doar cu cin>>*(list[0]);
    //for(int i=0; i<3; i++)
    //list[i]-> afisareSchemaVaccinare();
    //Comanda com1(“20-12-2020”, ”SpitalX”, ”AntiSarsCov2”,20);
    //ListaComenzi lista;
    //lista=lista+com1;
    //cout<<lista[0];
    return 0;
}
