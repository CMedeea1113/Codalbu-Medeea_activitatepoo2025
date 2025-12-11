#include <iostream>
#include <cstring>
using namespace std;

class ScoalaSoferi {
private:
    const int idScoala;
    static int numarScoli;
    char* nume;
    string locatie;
    float pretPachetB;
    int nrInstructori;
    int* cursantiPerInstructor;

public:
    void setPretPachetB(float pret) {
        if (pret >= 0) this->pretPachetB = pret;
    }

    float getPretPachetB() {
        return this->pretPachetB;
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

    void setCursantiPerInstructor(int nr, int* valori) {
        if (nr > 0 && valori) {
            this->nrInstructori = nr;
            if (this->cursantiPerInstructor) delete[] this->cursantiPerInstructor;
            this->cursantiPerInstructor = new int[nr];
            for (int i = 0; i < nr; i++)
                this->cursantiPerInstructor[i] = valori[i];
        }
    }

    int getCursantiInstructor(int index) {
        if (index >= 0 && index < nrInstructori) return cursantiPerInstructor[index];
        throw 404;
    }

    int getNrInstructori() {
        return this->nrInstructori;
    }

    int getIdScoala() {
        return this->idScoala;
    }

    static int getNumarScoli() {
        return numarScoli;
    }

    ScoalaSoferi() : idScoala(++numarScoli) {
        nume = nullptr;
        locatie = "Necunoscuta";
        pretPachetB = 0;
        nrInstructori = 0;
        cursantiPerInstructor = nullptr;
    }

    ScoalaSoferi(const char* nume, string locatie, float pretPachetB,
        int nrInstructori, const int* cursanti)
        : idScoala(++numarScoli)
    {
        this->locatie = locatie;
        this->pretPachetB = pretPachetB >= 0 ? pretPachetB : 0;
        this->nrInstructori = nrInstructori > 0 ? nrInstructori : 0;

        if (nume && strlen(nume) > 0) {
            this->nume = new char[strlen(nume) + 1];
            strcpy_s(this->nume, strlen(nume) + 1, nume);
        }
        else {
            this->nume = nullptr;
        }

        if (this->nrInstructori > 0 && cursanti) {
            this->cursantiPerInstructor = new int[this->nrInstructori];
            for (int i = 0; i < this->nrInstructori; i++)
                this->cursantiPerInstructor[i] = cursanti[i];
        }
        else {
            this->cursantiPerInstructor = nullptr;
            this->nrInstructori = 0;
        }
    }

    ScoalaSoferi(const ScoalaSoferi& s)
        : idScoala(++numarScoli)
    {
        locatie = s.locatie;
        pretPachetB = s.pretPachetB;
        nrInstructori = s.nrInstructori;

        if (s.nume) {
            nume = new char[strlen(s.nume) + 1];
            strcpy_s(nume, strlen(s.nume) + 1, s.nume);
        }
        else nume = nullptr;

        if (s.cursantiPerInstructor && s.nrInstructori > 0) {
            cursantiPerInstructor = new int[s.nrInstructori];
            for (int i = 0; i < s.nrInstructori; i++)
                cursantiPerInstructor[i] = s.cursantiPerInstructor[i];
        }
        else cursantiPerInstructor = nullptr;
    }

    void operator=(const ScoalaSoferi& s) {
        if (this == &s) return;

        locatie = s.locatie;
        pretPachetB = s.pretPachetB;
        nrInstructori = s.nrInstructori;

        if (nume) delete[] nume;
        if (s.nume) {
            nume = new char[strlen(s.nume) + 1];
            strcpy_s(nume, strlen(s.nume) + 1, s.nume);
        }
        else nume = nullptr;

        if (cursantiPerInstructor) delete[] cursantiPerInstructor;
        if (s.cursantiPerInstructor && s.nrInstructori > 0) {
            cursantiPerInstructor = new int[s.nrInstructori];
            for (int i = 0; i < s.nrInstructori; i++)
                cursantiPerInstructor[i] = s.cursantiPerInstructor[i];
        }
        else {
            cursantiPerInstructor = nullptr;
            nrInstructori = 0;
        }
    }

    ~ScoalaSoferi() {
        if (nume) delete[] nume;
        if (cursantiPerInstructor) delete[] cursantiPerInstructor;
    }

    void operator+=(float x) {
        pretPachetB += x;
    }

    friend ScoalaSoferi operator+=(float x, ScoalaSoferi& s) {
        s.pretPachetB += x;
        return s;
    }

    bool operator<(const ScoalaSoferi& s) {
        return pretPachetB < s.pretPachetB;
    }

    bool operator!() {
        return pretPachetB == 0;
    }

    int operator()(int index) {
        return getCursantiInstructor(index);
    }

    char& operator[](int index) {
        if (!nume) throw "Nume inexistent!";
        if (index < 0 || index >= (int)strlen(nume)) throw "Index invalid!";
        return nume[index];
    }

    explicit operator int() {
        return nrInstructori;
    }

    ScoalaSoferi operator++(int) {
        ScoalaSoferi copie = *this;
        pretPachetB++;
        return copie;
    }

    ScoalaSoferi operator++() {
        pretPachetB++;
        return *this;
    }

    void afisare() {
        cout << endl << idScoala << ". Scoala de soferi: "
            << (nume ? nume : "Fara nume")
            << " | Locatie: " << locatie
            << " | Pret pachet B: " << pretPachetB
            << " | Nr. instructori: " << nrInstructori;
        if (nrInstructori > 0 && cursantiPerInstructor) {
            cout << " | Cursanti/instructor: ";
            for (int i = 0; i < nrInstructori; i++)
                cout << cursantiPerInstructor[i] << (i < nrInstructori - 1 ? ", " : "");
        }
    }

    friend void operator<<(ostream& out, ScoalaSoferi s) {
        out << endl << "ID: " << s.idScoala;
        out << endl << "Nume: " << (s.nume ? s.nume : (char*)"N/A");
        out << endl << "Locatie: " << s.locatie;
        out << endl << "Pret pachet B: " << s.pretPachetB;
        out << endl << "Nr. instructori: " << s.nrInstructori;
        if (s.cursantiPerInstructor && s.nrInstructori > 0) {
            out << endl << "Cursanti per instructor: ";
            for (int i = 0; i < s.nrInstructori; i++)
                out << s.cursantiPerInstructor[i] << " ";
        }
    }

    friend void operator>>(istream& in, ScoalaSoferi& s) {
        char buf[100];
        in >> buf;
        s.setNume(buf);
        in >> s.locatie;
        in >> s.pretPachetB;
        in >> s.nrInstructori;
        if (s.cursantiPerInstructor) {
            delete[] s.cursantiPerInstructor;
            s.cursantiPerInstructor = nullptr;
        }
        if (s.nrInstructori > 0) {
            s.cursantiPerInstructor = new int[s.nrInstructori];
            for (int i = 0; i < s.nrInstructori; i++)
                in >> s.cursantiPerInstructor[i];
        }
        else {
            s.cursantiPerInstructor = nullptr;
        }
    }
};

int ScoalaSoferi::numarScoli = 0;

int main() {
    int v[3] = { 12, 9, 15 };

    ScoalaSoferi s1("StarDrive", "Bucuresti", 2500.0f, 3, v);
    ScoalaSoferi s2 = s1;

    s1.afisare();
    s2.afisare();

    cout << s1;

    s1 += 200;
    s1.afisare();

    cout << endl << "Cursanti la instructorul 2: " << s1(1);
    cout << endl << "Litera din nume[1]: " << s1[1];

    cout << endl << "Nr. instructori (cast la int): " << (int)s1;

    cout << endl << "Numar scoli de soferi create: " << ScoalaSoferi::getNumarScoli();

    return 0;
}
