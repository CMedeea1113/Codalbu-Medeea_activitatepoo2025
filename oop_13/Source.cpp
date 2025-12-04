#include <iostream>
#include <cstring>
using namespace std;

class OrarFacultate {
private:
    const int idOrar;
    static int numarOrare;
    char* grupa;
    string specializare;
    int semestru;
    int nrDiscipline;
    int* orePeDisciplina;
    float oreTotaleSaptamana;

public:
    void setOreTotaleSaptamana(float ore) {
        if (ore >= 0) this->oreTotaleSaptamana = ore;
    }

    float getOreTotaleSaptamana() {
        return this->oreTotaleSaptamana;
    }

    char* getGrupa() {
        return this->grupa;
    }

    void setGrupa(const char* grupaNoua) {
        if (grupaNoua && strlen(grupaNoua) > 0) {
            if (this->grupa) delete[] this->grupa;
            this->grupa = new char[strlen(grupaNoua) + 1];
            strcpy_s(this->grupa, strlen(grupaNoua) + 1, grupaNoua);
        }
    }

    void setSpecializare(string sp) {
        if (!sp.empty()) this->specializare = sp;
    }

    string getSpecializare() {
        return this->specializare;
    }

    void setOrePeDisciplina(int nr, int* ore) {
        if (nr > 0 && ore) {
            this->nrDiscipline = nr;
            if (this->orePeDisciplina) delete[] this->orePeDisciplina;
            this->orePeDisciplina = new int[nr];
            oreTotaleSaptamana = 0;
            for (int i = 0; i < nr; i++) {
                this->orePeDisciplina[i] = ore[i];
                oreTotaleSaptamana += ore[i];
            }
        }
    }

    int getOreDisciplina(int index) {
        if (index >= 0 && index < nrDiscipline) return orePeDisciplina[index];
        throw 404;
    }

    int getNrDiscipline() {
        return this->nrDiscipline;
    }

    int getIdOrar() {
        return this->idOrar;
    }

    int getSemestru() {
        return this->semestru;
    }

    void setSemestru(int s) {
        if (s > 0) this->semestru = s;
    }

    static int getNumarOrare() {
        return numarOrare;
    }

    OrarFacultate() : idOrar(++numarOrare) {
        grupa = nullptr;
        specializare = "Necunoscuta";
        semestru = 0;
        nrDiscipline = 0;
        orePeDisciplina = nullptr;
        oreTotaleSaptamana = 0;
    }

    OrarFacultate(const char* grupa, string specializare,
        int semestru, int nrDiscipline, const int* ore)
        : idOrar(++numarOrare)
    {
        this->specializare = specializare;
        this->semestru = semestru > 0 ? semestru : 0;
        this->nrDiscipline = nrDiscipline > 0 ? nrDiscipline : 0;

        if (grupa && strlen(grupa) > 0) {
            this->grupa = new char[strlen(grupa) + 1];
            strcpy_s(this->grupa, strlen(grupa) + 1, grupa);
        }
        else {
            this->grupa = nullptr;
        }

        if (this->nrDiscipline > 0 && ore) {
            this->orePeDisciplina = new int[this->nrDiscipline];
            oreTotaleSaptamana = 0;
            for (int i = 0; i < this->nrDiscipline; i++) {
                this->orePeDisciplina[i] = ore[i];
                oreTotaleSaptamana += ore[i];
            }
        }
        else {
            this->orePeDisciplina = nullptr;
            this->nrDiscipline = 0;
            oreTotaleSaptamana = 0;
        }
    }

    OrarFacultate(const OrarFacultate& o) : idOrar(++numarOrare) {
        specializare = o.specializare;
        semestru = o.semestru;
        nrDiscipline = o.nrDiscipline;
        oreTotaleSaptamana = o.oreTotaleSaptamana;

        if (o.grupa) {
            grupa = new char[strlen(o.grupa) + 1];
            strcpy_s(grupa, strlen(o.grupa) + 1, o.grupa);
        }
        else grupa = nullptr;

        if (o.orePeDisciplina && o.nrDiscipline > 0) {
            orePeDisciplina = new int[o.nrDiscipline];
            for (int i = 0; i < o.nrDiscipline; i++)
                orePeDisciplina[i] = o.orePeDisciplina[i];
        }
        else orePeDisciplina = nullptr;
    }

    void operator=(const OrarFacultate& o) {
        if (this == &o) return;

        specializare = o.specializare;
        semestru = o.semestru;
        nrDiscipline = o.nrDiscipline;
        oreTotaleSaptamana = o.oreTotaleSaptamana;

        if (grupa) delete[] grupa;
        if (o.grupa) {
            grupa = new char[strlen(o.grupa) + 1];
            strcpy_s(grupa, strlen(o.grupa) + 1, o.grupa);
        }
        else grupa = nullptr;

        if (orePeDisciplina) delete[] orePeDisciplina;
        if (o.orePeDisciplina && o.nrDiscipline > 0) {
            orePeDisciplina = new int[o.nrDiscipline];
            for (int i = 0; i < o.nrDiscipline; i++)
                orePeDisciplina[i] = o.orePeDisciplina[i];
        }
        else {
            orePeDisciplina = nullptr;
            nrDiscipline = 0;
            oreTotaleSaptamana = 0;
        }
    }

    ~OrarFacultate() {
        if (grupa) delete[] grupa;
        if (orePeDisciplina) delete[] orePeDisciplina;
    }

    void operator+=(float x) {
        oreTotaleSaptamana += x;
    }

    friend OrarFacultate operator+=(float x, OrarFacultate& o) {
        o.oreTotaleSaptamana += x;
        return o;
    }

    bool operator<(const OrarFacultate& o) {
        return oreTotaleSaptamana < o.oreTotaleSaptamana;
    }

    bool operator!() {
        return semestru == 0;
    }

    int operator()(int index) {
        return getOreDisciplina(index);
    }

    char& operator[](int index) {
        if (!grupa) throw "Grupa inexistenta!";
        if (index < 0 || index >= (int)strlen(grupa)) throw "Index invalid!";
        return grupa[index];
    }

    explicit operator int() {
        return nrDiscipline;
    }

    OrarFacultate operator++(int) {
        OrarFacultate copie = *this;
        semestru++;
        return copie;
    }

    OrarFacultate operator++() {
        semestru++;
        return *this;
    }

    void afisare() {
        cout << endl << idOrar << ". Orar grupa "
            << (grupa ? grupa : "N/A")
            << " | specializare: " << specializare
            << " | semestru: " << semestru
            << " | nr discipline: " << nrDiscipline
            << " | ore/saptamana: " << oreTotaleSaptamana;
        if (nrDiscipline > 0 && orePeDisciplina) {
            cout << " | ore pe disciplina: ";
            for (int i = 0; i < nrDiscipline; i++)
                cout << orePeDisciplina[i] << (i < nrDiscipline - 1 ? ", " : "");
        }
    }

    friend void operator<<(ostream& out, OrarFacultate o) {
        out << endl << "ID: " << o.idOrar;
        out << endl << "Grupa: " << (o.grupa ? o.grupa : (char*)"N/A");
        out << endl << "Specializare: " << o.specializare;
        out << endl << "Semestru: " << o.semestru;
        out << endl << "Nr discipline: " << o.nrDiscipline;
        out << endl << "Ore totale/saptamana: " << o.oreTotaleSaptamana;
        if (o.orePeDisciplina && o.nrDiscipline > 0) {
            out << endl << "Ore pe disciplina: ";
            for (int i = 0; i < o.nrDiscipline; i++)
                out << o.orePeDisciplina[i] << " ";
        }
    }

    friend void operator>>(istream& in, OrarFacultate& o) {
        char buf[100];
        in >> buf;
        o.setGrupa(buf);
        in >> o.specializare;
        in >> o.semestru;
        in >> o.nrDiscipline;
        if (o.orePeDisciplina) {
            delete[] o.orePeDisciplina;
            o.orePeDisciplina = nullptr;
        }
        o.oreTotaleSaptamana = 0;
        if (o.nrDiscipline > 0) {
            o.orePeDisciplina = new int[o.nrDiscipline];
            for (int i = 0; i < o.nrDiscipline; i++) {
                in >> o.orePeDisciplina[i];
                o.oreTotaleSaptamana += o.orePeDisciplina[i];
            }
        }
    }
};

int OrarFacultate::numarOrare = 0;

int main() {
    int ore[4] = { 4, 3, 2, 2 };

    OrarFacultate o1("311AC", "Calculatoare", 3, 4, ore);
    OrarFacultate o2 = o1;

    o1.afisare();
    o2.afisare();

    cout << o1;

    o1 += 1;
    o1.afisare();

    cout << endl << "Ore disciplina 2: " << o1(1);
    cout << endl << "Litera din grupa[1]: " << o1[1];

    cout << endl << "Nr discipline (cast la int): " << (int)o1;

    cout << endl << "Numar orare create: " << OrarFacultate::getNumarOrare();

    return 0;
}
