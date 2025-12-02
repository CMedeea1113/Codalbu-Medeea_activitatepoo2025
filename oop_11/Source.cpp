#include <iostream>
#include <cstring>
using namespace std;

class Avion {
private:
    const int idAvion;
    static int numarAvioane;
    char* companie;
    string model;
    float autonomie;
    int anFabricatie;
    int nrZboruri;
    float* durateZboruri;

public:
    void setAutonomie(float autonomie) {
        if (autonomie > 0) this->autonomie = autonomie;
    }

    float getAutonomie() {
        return this->autonomie;
    }

    char* getCompanie() {
        return this->companie;
    }

    void setCompanie(const char* companie) {
        if (companie && strlen(companie) > 0) {
            if (this->companie) delete[] this->companie;
            this->companie = new char[strlen(companie) + 1];
            strcpy_s(this->companie, strlen(companie) + 1, companie);
        }
    }

    void setModel(string model) {
        if (!model.empty()) this->model = model;
    }

    string getModel() {
        return this->model;
    }

    void setDurateZboruri(int nrZboruri, float* durate) {
        if (nrZboruri > 0 && durate) {
            this->nrZboruri = nrZboruri;
            if (this->durateZboruri) delete[] this->durateZboruri;
            this->durateZboruri = new float[nrZboruri];
            for (int i = 0; i < nrZboruri; i++) this->durateZboruri[i] = durate[i];
        }
    }

    float getDurataZbor(int poz) {
        if (poz >= 0 && poz < nrZboruri) return durateZboruri[poz];
        throw 404;
    }

    int getNrZboruri() {
        return this->nrZboruri;
    }

    int getIdAvion() {
        return this->idAvion;
    }

    int getAnFabricatie() {
        return this->anFabricatie;
    }

    static int getNumarAvioane() {
        return numarAvioane;
    }

    Avion() : idAvion(++numarAvioane) {
        companie = nullptr;
        model = "Necunoscut";
        autonomie = 0;
        anFabricatie = 0;
        nrZboruri = 0;
        durateZboruri = nullptr;
    }

    Avion(const char* companie, string model, float autonomie,
        int anFabricatie, int nrZboruri, const float* durate)
        : idAvion(++numarAvioane)
    {
        this->model = model;
        this->autonomie = autonomie > 0 ? autonomie : 0;
        this->anFabricatie = anFabricatie;
        this->nrZboruri = nrZboruri > 0 ? nrZboruri : 0;

        if (companie && strlen(companie) > 0) {
            this->companie = new char[strlen(companie) + 1];
            strcpy_s(this->companie, strlen(companie) + 1, companie);
        }
        else {
            this->companie = nullptr;
        }

        if (this->nrZboruri > 0 && durate) {
            this->durateZboruri = new float[this->nrZboruri];
            for (int i = 0; i < this->nrZboruri; i++)
                this->durateZboruri[i] = durate[i];
        }
        else {
            this->durateZboruri = nullptr;
            this->nrZboruri = 0;
        }
    }

    Avion(const Avion& a) : idAvion(++numarAvioane) {
        model = a.model;
        autonomie = a.autonomie;
        anFabricatie = a.anFabricatie;
        nrZboruri = a.nrZboruri;

        if (a.companie) {
            companie = new char[strlen(a.companie) + 1];
            strcpy_s(companie, strlen(a.companie) + 1, a.companie);
        }
        else companie = nullptr;

        if (a.durateZboruri && a.nrZboruri > 0) {
            durateZboruri = new float[a.nrZboruri];
            for (int i = 0; i < a.nrZboruri; i++)
                durateZboruri[i] = a.durateZboruri[i];
        }
        else durateZboruri = nullptr;
    }

    void operator=(const Avion& a) {
        if (this == &a) return;

        model = a.model;
        autonomie = a.autonomie;
        anFabricatie = a.anFabricatie;
        nrZboruri = a.nrZboruri;

        if (companie) delete[] companie;
        if (a.companie) {
            companie = new char[strlen(a.companie) + 1];
            strcpy_s(companie, strlen(a.companie) + 1, a.companie);
        }
        else companie = nullptr;

        if (durateZboruri) delete[] durateZboruri;
        if (a.durateZboruri && a.nrZboruri > 0) {
            durateZboruri = new float[a.nrZboruri];
            for (int i = 0; i < a.nrZboruri; i++)
                durateZboruri[i] = a.durateZboruri[i];
        }
        else {
            durateZboruri = nullptr;
            nrZboruri = 0;
        }
    }

    ~Avion() {
        if (companie) delete[] companie;
        if (durateZboruri) delete[] durateZboruri;
    }

    void operator+=(float x) {
        autonomie += x;
    }

    friend Avion operator+=(float x, Avion& a) {
        a.autonomie += x;
        return a;
    }

    bool operator<(const Avion& a) {
        return autonomie < a.autonomie;
    }

    bool operator!() {
        return anFabricatie != 0;
    }

    float operator()(int poz) {
        return getDurataZbor(poz);
    }

    char& operator[](int index) {
        if (!companie) throw "Companie inexistenta!";
        if (index < 0 || index >= (int)strlen(companie)) throw "Index invalid!";
        return companie[index];
    }

    explicit operator int() {
        return anFabricatie;
    }

    Avion operator++(int) {
        Avion cpy = *this;
        anFabricatie++;
        return cpy;
    }

    Avion operator++() {
        anFabricatie++;
        return *this;
    }

    void afisareAvion() {
        cout << endl << idAvion << ". Avion ";
        if (companie) cout << companie; else cout << "Neidentificat";
        cout << " model " << model
            << ", autonomie " << autonomie
            << " km, an fabricatie " << anFabricatie
            << ", numar zboruri: " << nrZboruri;
        if (nrZboruri > 0 && durateZboruri) {
            cout << " cu duratele: ";
            for (int i = 0; i < nrZboruri - 1; i++)
                cout << durateZboruri[i] << ", ";
            cout << durateZboruri[nrZboruri - 1] << ".";
        }
    }

    friend void operator<<(ostream& out, Avion a) {
        out << endl << "ID: " << a.idAvion;
        out << endl << "Companie: " << (a.companie ? a.companie : (char*)"N/A");
        out << endl << "Model: " << a.model;
        out << endl << "Autonomie: " << a.autonomie;
        out << endl << "An fabricatie: " << a.anFabricatie;
        out << endl << "Nr zboruri: " << a.nrZboruri;
        if (a.durateZboruri && a.nrZboruri > 0) {
            out << endl << "Durate zboruri: ";
            for (int i = 0; i < a.nrZboruri; i++)
                out << a.durateZboruri[i] << " ";
        }
    }

    friend void operator>>(istream& in, Avion& a) {
        char buf[100];
        in >> buf;
        a.setCompanie(buf);
        in >> a.model;
        in >> a.autonomie;
        in >> a.anFabricatie;
        in >> a.nrZboruri;
        if (a.durateZboruri) delete[] a.durateZboruri;
        if (a.nrZboruri > 0) {
            a.durateZboruri = new float[a.nrZboruri];
            for (int i = 0; i < a.nrZboruri; i++)
                in >> a.durateZboruri[i];
        }
        else {
            a.durateZboruri = nullptr;
        }
    }
};

int Avion::numarAvioane = 0;

int main() {
    float v[3] = { 2.5f, 3.0f, 4.2f };

    Avion a1("TAROM", "A318", 3500, 2005, 3, v);
    Avion a2 = a1;

    a1.afisareAvion();
    a2.afisareAvion();

    cout << a1;

    a1 += 500;
    a1.afisareAvion();

    cout << endl << "Durata zbor 1: " << a1(1);
    cout << endl << "Litera din companie[1]: " << a1[1];

    cout << endl << "Numar avioane create: " << Avion::getNumarAvioane();

    return 0;
}
