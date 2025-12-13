#include <iostream>
#include <cstring>
using namespace std;

class StudioFoto {
private:
    const int idStudio;
    static int numarStudiori;
    char* nume;
    string locatie;
    float tarifOra;
    int nrZile;
    int* oreRezervatePeZi;

public:
    void setTarifOra(float tarif) {
        if (tarif >= 0) this->tarifOra = tarif;
    }

    float getTarifOra() {
        return this->tarifOra;
    }

    char* getNume() {
        return this->nume;
    }

    void setNume(const char* numeNou) {
        if (numeNou && strlen(numeNou) > 0) {
            if (this->nume) delete[] this->nume;
            this->nume = new char[strlen(numeNou) + 1];
            strcpy_s(this->nume, strlen(numeNou) + 1, numeNou);
        }
    }

    void setLocatie(string loc) {
        if (!loc.empty()) this->locatie = loc;
    }

    string getLocatie() {
        return this->locatie;
    }

    void setOreRezervate(int nrZile, int* ore) {
        if (nrZile > 0 && ore) {
            this->nrZile = nrZile;
            if (this->oreRezervatePeZi) delete[] this->oreRezervatePeZi;
            this->oreRezervatePeZi = new int[nrZile];
            for (int i = 0; i < nrZile; i++)
                this->oreRezervatePeZi[i] = ore[i];
        }
    }

    int getOreZi(int index) {
        if (index >= 0 && index < nrZile) return oreRezervatePeZi[index];
        throw 404;
    }

    int getNrZile() {
        return this->nrZile;
    }

    int getIdStudio() {
        return this->idStudio;
    }

    static int getNumarStudiori() {
        return numarStudiori;
    }

    StudioFoto() : idStudio(++numarStudiori) {
        nume = nullptr;
        locatie = "Necunoscuta";
        tarifOra = 0;
        nrZile = 0;
        oreRezervatePeZi = nullptr;
    }

    StudioFoto(const char* nume, string locatie, float tarifOra,
        int nrZile, const int* ore)
        : idStudio(++numarStudiori)
    {
        this->locatie = locatie;
        this->tarifOra = tarifOra >= 0 ? tarifOra : 0;
        this->nrZile = nrZile > 0 ? nrZile : 0;

        if (nume && strlen(nume) > 0) {
            this->nume = new char[strlen(nume) + 1];
            strcpy_s(this->nume, strlen(nume) + 1, nume);
        }
        else {
            this->nume = nullptr;
        }

        if (this->nrZile > 0 && ore) {
            this->oreRezervatePeZi = new int[this->nrZile];
            for (int i = 0; i < this->nrZile; i++)
                this->oreRezervatePeZi[i] = ore[i];
        }
        else {
            this->oreRezervatePeZi = nullptr;
            this->nrZile = 0;
        }
    }

    StudioFoto(const StudioFoto& s)
        : idStudio(++numarStudiori)
    {
        locatie = s.locatie;
        tarifOra = s.tarifOra;
        nrZile = s.nrZile;

        if (s.nume) {
            nume = new char[strlen(s.nume) + 1];
            strcpy_s(nume, strlen(s.nume) + 1, s.nume);
        }
        else nume = nullptr;

        if (s.oreRezervatePeZi && s.nrZile > 0) {
            oreRezervatePeZi = new int[s.nrZile];
            for (int i = 0; i < s.nrZile; i++)
                oreRezervatePeZi[i] = s.oreRezervatePeZi[i];
        }
        else oreRezervatePeZi = nullptr;
    }

    void operator=(const StudioFoto& s) {
        if (this == &s) return;

        locatie = s.locatie;
        tarifOra = s.tarifOra;
        nrZile = s.nrZile;

        if (nume) delete[] nume;
        if (s.nume) {
            nume = new char[strlen(s.nume) + 1];
            strcpy_s(nume, strlen(s.nume) + 1, s.nume);
        }
        else nume = nullptr;

        if (oreRezervatePeZi) delete[] oreRezervatePeZi;
        if (s.oreRezervatePeZi && s.nrZile > 0) {
            oreRezervatePeZi = new int[s.nrZile];
            for (int i = 0; i < s.nrZile; i++)
                oreRezervatePeZi[i] = s.oreRezervatePeZi[i];
        }
        else {
            oreRezervatePeZi = nullptr;
            nrZile = 0;
        }
    }

    ~StudioFoto() {
        if (nume) delete[] nume;
        if (oreRezervatePeZi) delete[] oreRezervatePeZi;
    }

    void operator+=(float x) {
        tarifOra += x;
    }

    friend StudioFoto operator+=(float x, StudioFoto& s) {
        s.tarifOra += x;
        return s;
    }

    bool operator<(const StudioFoto& s) {
        return tarifOra < s.tarifOra;
    }

    bool operator!() {
        return tarifOra == 0;
    }

    int operator()(int index) {
        return getOreZi(index);
    }

    char& operator[](int index) {
        if (!nume) throw "Nume inexistent!";
        if (index < 0 || index >= (int)strlen(nume)) throw "Index invalid!";
        return nume[index];
    }

    explicit operator int() {
        return nrZile;
    }

    StudioFoto operator++(int) {
        StudioFoto copie = *this;
        tarifOra++;
        return copie;
    }

    StudioFoto operator++() {
        tarifOra++;
        return *this;
    }

    void afisare() {
        cout << endl << idStudio << ". Studio foto: "
            << (nume ? nume : "Fara nume")
            << " | Locatie: " << locatie
            << " | Tarif/ora: " << tarifOra
            << " | Zile monitorizate: " << nrZile;
        if (nrZile > 0 && oreRezervatePeZi) {
            cout << " | Ore rezervate/zi: ";
            for (int i = 0; i < nrZile; i++)
                cout << oreRezervatePeZi[i] << (i < nrZile - 1 ? ", " : "");
        }
    }

    friend void operator<<(ostream& out, StudioFoto s) {
        out << endl << "ID: " << s.idStudio;
        out << endl << "Nume: " << (s.nume ? s.nume : (char*)"N/A");
        out << endl << "Locatie: " << s.locatie;
        out << endl << "Tarif/ora: " << s.tarifOra;
        out << endl << "Zile monitorizate: " << s.nrZile;
        if (s.oreRezervatePeZi && s.nrZile > 0) {
            out << endl << "Ore rezervate/zi: ";
            for (int i = 0; i < s.nrZile; i++)
                out << s.oreRezervatePeZi[i] << " ";
        }
    }

    friend void operator>>(istream& in, StudioFoto& s) {
        char buf[100];
        in >> buf;
        s.setNume(buf);
        in >> s.locatie;
        in >> s.tarifOra;
        in >> s.nrZile;
        if (s.oreRezervatePeZi) {
            delete[] s.oreRezervatePeZi;
            s.oreRezervatePeZi = nullptr;
        }
        if (s.nrZile > 0) {
            s.oreRezervatePeZi = new int[s.nrZile];
            for (int i = 0; i < s.nrZile; i++)
                in >> s.oreRezervatePeZi[i];
        }
        else {
            s.oreRezervatePeZi = nullptr;
        }
    }
};

int StudioFoto::numarStudiori = 0;

int main() {
    int ore[5] = { 4, 6, 3, 5, 7 };

    StudioFoto s1("PixelArt", "Bucuresti", 150.0f, 5, ore);
    StudioFoto s2 = s1;

    s1.afisare();
    s2.afisare();

    cout << s1;

    s1 += 20.0f;
    s1.afisare();

    cout << endl << "Ore rezervate in ziua 2: " << s1(1);
    cout << endl << "Litera din nume[1]: " << s1[1];

    cout << endl << "Nr. zile (cast la int): " << (int)s1;

    cout << endl << "Numar studiouri create: " << StudioFoto::getNumarStudiori();

    return 0;
}
