#include<iostream>
#include<cstring>

using namespace std;

class ProgramTV {
private:
    const int idProgram;
    static int numarPrograme;
    char* titlu;
    string canal;
    float durata;
    int oraDifuzare;      
    int nrDifuzari;
    float* ratingDifuzari;

public:
    void setDurata(float durata) {
        if (durata > 0) {
            this->durata = durata;
        }
    }

    float getDurata() {
        return this->durata;
    }

    char* getTitlu() {
        return this->titlu;
    }

    void setTitlu(const char* titlu) {
        if (titlu != nullptr && strlen(titlu) > 0) {
            if (this->titlu != nullptr) {
                delete[] this->titlu;
            }
            this->titlu = new char[strlen(titlu) + 1];
            strcpy_s(this->titlu, strlen(titlu) + 1, titlu);
        }
    }

    void setCanal(string canal) {
        if (!canal.empty()) {
            this->canal = canal;
        }
    }

    void setRatingDifuzari(int nrDifuzari, float* ratingDifuzari) {
        if (nrDifuzari > 0 && ratingDifuzari != nullptr) {
            this->nrDifuzari = nrDifuzari;
            if (this->ratingDifuzari != nullptr) {
                delete[] this->ratingDifuzari;
            }
            this->ratingDifuzari = new float[nrDifuzari];
            for (int i = 0; i < nrDifuzari; i++) {
                this->ratingDifuzari[i] = ratingDifuzari[i];
            }
        }
    }

    float* getRatingDifuzari() {
        return this->ratingDifuzari;
    }

    float getRatingDifuzare(int pozitie) {
        if (pozitie >= 0 && pozitie < nrDifuzari) {
            return this->ratingDifuzari[pozitie];
        }
        throw 404;
    }

    int getIdProgram() {
        return this->idProgram;
    }

    static int getNumarPrograme() {
        return numarPrograme;
    }

    void setNumarPrograme(int nr) {
        numarPrograme = nr;
    }

    ProgramTV() : idProgram(++numarPrograme) {
        this->canal = "Necunoscut";
        this->durata = 0;
        this->oraDifuzare = 0;
        this->nrDifuzari = 0;
        this->ratingDifuzari = nullptr;
        this->titlu = nullptr;
    }

    ProgramTV(const char* titlu, string canal, float durata,
        int oraDifuzare, int nrDifuzari, const float* ratingDifuzari)
        : idProgram(++numarPrograme)
    {
        this->canal = canal;
        this->durata = durata;
        this->oraDifuzare = oraDifuzare;
        this->nrDifuzari = nrDifuzari;

        if (nrDifuzari > 0 && ratingDifuzari != nullptr) {
            this->ratingDifuzari = new float[nrDifuzari];
            for (int i = 0; i < nrDifuzari; i++) {
                this->ratingDifuzari[i] = ratingDifuzari[i];
            }
        }
        else {
            this->ratingDifuzari = nullptr;
            this->nrDifuzari = 0;
        }

        if (titlu != nullptr && strlen(titlu) > 0) {
            this->titlu = new char[strlen(titlu) + 1];
            strcpy_s(this->titlu, strlen(titlu) + 1, titlu);
        }
        else {
            this->titlu = nullptr;
        }
    }

    ProgramTV(const ProgramTV& copie) : idProgram(++numarPrograme) {
        this->canal = copie.canal;
        this->durata = copie.durata;
        this->oraDifuzare = copie.oraDifuzare;
        this->nrDifuzari = copie.nrDifuzari;

        if (copie.ratingDifuzari != nullptr && copie.nrDifuzari > 0) {
            this->ratingDifuzari = new float[copie.nrDifuzari];
            for (int i = 0; i < copie.nrDifuzari; i++) {
                this->ratingDifuzari[i] = copie.ratingDifuzari[i];
            }
        }
        else {
            this->ratingDifuzari = nullptr;
        }

        if (copie.titlu != nullptr) {
            this->titlu = new char[strlen(copie.titlu) + 1];
            strcpy_s(this->titlu, strlen(copie.titlu) + 1, copie.titlu);
        }
        else {
            this->titlu = nullptr;
        }
    }

    void operator=(const ProgramTV& copie) {
        if (this == &copie) return;

        this->canal = copie.canal;
        this->durata = copie.durata;
        this->oraDifuzare = copie.oraDifuzare;
        this->nrDifuzari = copie.nrDifuzari;

        if (this->ratingDifuzari != nullptr) {
            delete[] this->ratingDifuzari;
            this->ratingDifuzari = nullptr;
        }

        if (copie.ratingDifuzari != nullptr && copie.nrDifuzari > 0) {
            this->ratingDifuzari = new float[copie.nrDifuzari];
            for (int i = 0; i < copie.nrDifuzari; i++) {
                this->ratingDifuzari[i] = copie.ratingDifuzari[i];
            }
        }
        else {
            this->ratingDifuzari = nullptr;
            this->nrDifuzari = 0;
        }

        if (this->titlu != nullptr) {
            delete[] this->titlu;
            this->titlu = nullptr;
        }

        if (copie.titlu != nullptr) {
            this->titlu = new char[strlen(copie.titlu) + 1];
            strcpy_s(this->titlu, strlen(copie.titlu) + 1, copie.titlu);
        }
        else {
            this->titlu = nullptr;
        }
    }

    int getOraDifuzare() {
        return this->oraDifuzare;
    }

    string getCanal() {
        return this->canal;
    }

    int getNrDifuzari() {
        return this->nrDifuzari;
    }

    void afisareProgram() {
        cout << endl << this->getIdProgram() << ". Programul TV ";
        if (this->getTitlu() != nullptr) {
            cout << this->getTitlu();
        }
        else {
            cout << "Neidentificat";
        }
        cout << " pe canalul " << this->getCanal()
            << ", durata " << this->getDurata() << " minute,"
            << " ora difuzare " << this->getOraDifuzare()
            << ":00, difuzat de " << this->getNrDifuzari()
            << " ori";
        if (this->getNrDifuzari() > 0) {
            cout << " cu urmatoarele ratinguri: ";
            for (int i = 0; i < this->getNrDifuzari() - 1; i++) {
                cout << this->getRatingDifuzare(i) << ", ";
            }
            cout << this->getRatingDifuzare(this->getNrDifuzari() - 1) << ".";
        }
    }

    ~ProgramTV() {
        if (this->ratingDifuzari != nullptr) {
            delete[] this->ratingDifuzari;
        }
        if (this->titlu != nullptr) {
            delete[] this->titlu;
        }
    }

    void operator+=(float valoareDeAdaugatLaDurata) {
        this->durata += valoareDeAdaugatLaDurata;
    }

    friend ProgramTV operator+=(float valoareDeAdaugatLaDurata, ProgramTV& p) {
        p.durata += valoareDeAdaugatLaDurata;
        return p;
    }

    bool operator<(const ProgramTV& p) {
        return this->durata < p.durata;
    }

    bool operator!() {
        return this->oraDifuzare != 0;
    }

    float operator()(int pozitie) {
        return this->getRatingDifuzare(pozitie);
    }

    char& operator[](int index) {
        if (this->titlu == nullptr) {
            throw "Titlu inexistent!";
        }
        if (index >= 0 && index < (int)strlen(this->titlu)) {
            return this->titlu[index];
        }
        else {
            throw "Indexul nu se afla in interval!";
        }
    }

    friend void operator<<(ostream& consola, ProgramTV p) {
        consola << endl << "Id: " << p.idProgram;
        consola << endl << (p.titlu != nullptr ? "Titlu: " + string(p.titlu) : "Titlu nespecificat");
        consola << endl << "Canal: " << p.canal;
        consola << endl << "Durata: " << p.durata;
        consola << endl << "Ora difuzare: " << p.oraDifuzare;
        consola << endl << "Nr. difuzari: " << p.nrDifuzari;
        if (p.ratingDifuzari != nullptr) {
            consola << endl << "Ratinguri difuzari: ";
            for (int i = 0; i < p.getNrDifuzari() - 1; i++) {
                consola << p.getRatingDifuzare(i) << ", ";
            }
            consola << p.getRatingDifuzare(p.getNrDifuzari() - 1) << ".";
        }
        else {
            consola << endl << "Ratinguri nespecificate";
        }
    }

    friend void operator>>(istream& in, ProgramTV& p);

    explicit operator int() {
        return this->oraDifuzare;
    }

    ProgramTV operator++(int) {
        ProgramTV copie = *this;
        this->oraDifuzare++;
        if (this->oraDifuzare >= 24) this->oraDifuzare = 0;
        return copie;
    }

    ProgramTV operator++() {
        this->oraDifuzare++;
        if (this->oraDifuzare >= 24) this->oraDifuzare = 0;
        return *this;
    }
};

int ProgramTV::numarPrograme = 0;

void operator>>(istream& cititor, ProgramTV& p) {
    cout << endl << "Titlu program: ";
    if (p.titlu != nullptr) {
        delete[] p.titlu;
        p.titlu = nullptr;
    }
    char buffer[100];
    cititor >> buffer;
    p.titlu = new char[strlen(buffer) + 1];
    strcpy_s(p.titlu, strlen(buffer) + 1, buffer);

    cout << endl << "Canal: ";
    cititor >> p.canal;

    cout << endl << "Durata (minute): ";
    cititor >> p.durata;

    cout << endl << "Ora difuzare: ";
    cititor >> p.oraDifuzare;

    cout << endl << "Nr. difuzari: ";
    cititor >> p.nrDifuzari;

    if (p.ratingDifuzari != nullptr) {
        delete[] p.ratingDifuzari;
        p.ratingDifuzari = nullptr;
    }

    if (p.nrDifuzari > 0) {
        cout << endl << "Ratinguri difuzari: ";
        p.ratingDifuzari = new float[p.nrDifuzari];
        for (int i = 0; i < p.getNrDifuzari(); i++) {
            cout << endl << "Rating[" << i << "]: ";
            cititor >> p.ratingDifuzari[i];
        }
    }
}

int main() {
    float* v = new float[3] { 7.5f, 8.2f, 9.1f };

    ProgramTV prog("News24", "Canal24", 60, 20, 3, v);
    try {
        cout << endl << prog.getRatingDifuzare(3);
    }
    catch (int cod) {
        cout << endl << cod;
    }
    catch (const char* mesaj) {
        cout << endl << mesaj;
    }
    catch (...) {
        cout << endl << "Pozitia este in afara intervalului!";
    }

    cout << endl << "Id program constructor toti parametrii: " << prog.getIdProgram();

    ProgramTV prog2 = prog;
    cout << endl << "Id program constructor copiere: " << prog2.getIdProgram();

    ProgramTV progDefault;
    progDefault.afisareProgram();

    progDefault = prog;
    cout << endl << "Id program dupa op =: " << progDefault.getIdProgram();

    prog.afisareProgram();
    prog2.afisareProgram();
    progDefault.afisareProgram();

    prog += 10;
    5.0f += prog;

    prog.afisareProgram();

    if (prog < prog2) {
        cout << endl << "Primul program are durata mai mica!";
    }
    else {
        cout << endl << "Al doilea program are durata mai mica!";
    }

    if (!prog) {
        cout << endl << "Programul are ora de difuzare setata!";
    }
    else {
        cout << endl << "Ora de difuzare nu este setata!";
    }

    cout << endl << prog(2);

    cout << endl << "Litera de pe pozitia 2 din titlu este: " << prog[1];
    prog[1] = 'X';
    cout << endl << "Litera de pe pozitia 2 din titlu este: " << prog[1];

    cout << endl << (int)prog;

    ProgramTV p1 = prog++;
    cout << p1;

    ProgramTV p2 = ++prog;
    cout << p2;

    cout << endl << "Am initializat " << ProgramTV::getNumarPrograme() << " obiect/e!";

    delete[] v;
    return 0;
}
