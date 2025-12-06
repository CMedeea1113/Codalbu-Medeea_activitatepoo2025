#include <iostream>
#include <cstring>
using namespace std;

class SalaFitness {
private:
    const int idSala;
    static int numarSali;
    char* nume;
    string locatie;
    float pretAbonamentLunar;
    int nrClase;
    float* durataClase;      // ore / clasa pe saptamana

public:
    void setPretAbonamentLunar(float pret) {
        if (pret >= 0) this->pretAbonamentLunar = pret;
    }

    float getPretAbonamentLunar() {
        return this->pretAbonamentLunar;
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

    void setDurataClase(int nr, float* durate) {
        if (nr > 0 && durate) {
            this->nrClase = nr;
            if (this->durataClase) delete[] this->durataClase;
            this->durataClase = new float[nr];
            for (int i = 0; i < nr; i++)
                this->durataClase[i] = durate[i];
        }
    }

    float getDurataClasa(int index) {
        if (index >= 0 && index < nrClase) return durataClase[index];
        throw 404;
    }

    int getNrClase() {
        return this->nrClase;
    }

    int getIdSala() {
        return this->idSala;
    }

    static int getNumarSali() {
        return numarSali;
    }

    SalaFitness() : idSala(++numarSali) {
        nume = nullptr;
        locatie = "Necunoscuta";
        pretAbonamentLunar = 0;
        nrClase = 0;
        durataClase = nullptr;
    }

    SalaFitness(const char* nume, string locatie, float pretAbonamentLunar,
        int nrClase, const float* durate)
        : idSala(++numarSali)
    {
        this->locatie = locatie;
        this->pretAbonamentLunar = pretAbonamentLunar >= 0 ? pretAbonamentLunar : 0;
        this->nrClase = nrClase > 0 ? nrClase : 0;

        if (nume && strlen(nume) > 0) {
            this->nume = new char[strlen(nume) + 1];
            strcpy_s(this->nume, strlen(nume) + 1, nume);
        }
        else {
            this->nume = nullptr;
        }

        if (this->nrClase > 0 && durate) {
            this->durataClase = new float[this->nrClase];
            for (int i = 0; i < this->nrClase; i++)
                this->durataClase[i] = durate[i];
        }
        else {
            this->durataClase = nullptr;
            this->nrClase = 0;
        }
    }

    SalaFitness(const SalaFitness& s)
        : idSala(++numarSali)
    {
        locatie = s.locatie;
        pretAbonamentLunar = s.pretAbonamentLunar;
        nrClase = s.nrClase;

        if (s.nume) {
            nume = new char[strlen(s.nume) + 1];
            strcpy_s(nume, strlen(s.nume) + 1, s.nume);
        }
        else nume = nullptr;

        if (s.durataClase && s.nrClase > 0) {
            durataClase = new float[s.nrClase];
            for (int i = 0; i < s.nrClase; i++)
                durataClase[i] = s.durataClase[i];
        }
        else durataClase = nullptr;
    }

    void operator=(const SalaFitness& s) {
        if (this == &s) return;

        locatie = s.locatie;
        pretAbonamentLunar = s.pretAbonamentLunar;
        nrClase = s.nrClase;

        if (nume) delete[] nume;
        if (s.nume) {
            nume = new char[strlen(s.nume) + 1];
            strcpy_s(nume, strlen(s.nume) + 1, s.nume);
        }
        else nume = nullptr;

        if (durataClase) delete[] durataClase;
        if (s.durataClase && s.nrClase > 0) {
            durataClase = new float[s.nrClase];
            for (int i = 0; i < s.nrClase; i++)
                durataClase[i] = s.durataClase[i];
        }
        else {
            durataClase = nullptr;
            nrClase = 0;
        }
    }

    ~SalaFitness() {
        if (nume) delete[] nume;
        if (durataClase) delete[] durataClase;
    }

    void operator+=(float x) {
        pretAbonamentLunar += x;
    }

    friend SalaFitness operator+=(float x, SalaFitness& s) {
        s.pretAbonamentLunar += x;
        return s;
    }

    bool operator<(const SalaFitness& s) {
        return pretAbonamentLunar < s.pretAbonamentLunar;
    }

    bool operator!() {
        return pretAbonamentLunar == 0;
    }

    float operator()(int index) {
        return getDurataClasa(index);
    }

    char& operator[](int index) {
        if (!nume) throw "Nume inexistent!";
        if (index < 0 || index >= (int)strlen(nume)) throw "Index invalid!";
        return nume[index];
    }

    explicit operator int() {
        return nrClase;
    }

    SalaFitness operator++(int) {
        SalaFitness copie = *this;
        pretAbonamentLunar++;
        return copie;
    }

    SalaFitness operator++() {
        pretAbonamentLunar++;
        return *this;
    }

    void afisare() {
        cout << endl << idSala << ". Sala fitness: "
            << (nume ? nume : "Fara nume")
            << " | Locatie: " << locatie
            << " | Abonament lunar: " << pretAbonamentLunar
            << " | Nr. clase: " << nrClase;
        if (nrClase > 0 && durataClase) {
            cout << " | Durata clase (ore): ";
            for (int i = 0; i < nrClase; i++)
                cout << durataClase[i] << (i < nrClase - 1 ? ", " : "");
        }
    }

    friend void operator<<(ostream& out, SalaFitness s) {
        out << endl << "ID: " << s.idSala;
        out << endl << "Nume: " << (s.nume ? s.nume : (char*)"N/A");
        out << endl << "Locatie: " << s.locatie;
        out << endl << "Abonament lunar: " << s.pretAbonamentLunar;
        out << endl << "Nr. clase: " << s.nrClase;
        if (s.durataClase && s.nrClase > 0) {
            out << endl << "Durata clase: ";
            for (int i = 0; i < s.nrClase; i++)
                out << s.durataClase[i] << " ";
        }
    }

    friend void operator>>(istream& in, SalaFitness& s) {
        char buf[100];
        in >> buf;
        s.setNume(buf);
        in >> s.locatie;
        in >> s.pretAbonamentLunar;
        in >> s.nrClase;
        if (s.durataClase) {
            delete[] s.durataClase;
            s.durataClase = nullptr;
        }
        if (s.nrClase > 0) {
            s.durataClase = new float[s.nrClase];
            for (int i = 0; i < s.nrClase; i++)
                in >> s.durataClase[i];
        }
        else {
            s.durataClase = nullptr;
        }
    }
};

int SalaFitness::numarSali = 0;

int main() {
    float v[4] = { 1.5f, 2.0f, 1.0f, 1.5f };

    SalaFitness s1("UPBFit", "Regie", 150.0f, 4, v);
    SalaFitness s2 = s1;

    s1.afisare();
    s2.afisare();

    cout << s1;

    s1 += 20;
    s1.afisare();

    cout << endl << "Durata clasa 2: " << s1(1);
    cout << endl << "Litera din nume[1]: " << s1[1];

    cout << endl << "Nr. clase (cast la int): " << (int)s1;

    cout << endl << "Numar sali fitness create: " << SalaFitness::getNumarSali();

    return 0;
}
