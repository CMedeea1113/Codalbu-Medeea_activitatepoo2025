#include<iostream>
#include<cstring>

using namespace std;

class Film {
private:
    const int idFilm;
    static int numarFilme;
    char* titlu;
    string regizor;
    float durata;
    int anLansare;
    int nrActori;
    float* onorariiActori;

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

    void setRegizor(string regizor) {
        if (!regizor.empty()) {
            this->regizor = regizor;
        }
    }

    void setOnorariiActori(int nrActori, float* onorariiActori) {
        if (nrActori > 0 && onorariiActori != nullptr) {
            this->nrActori = nrActori;
            if (this->onorariiActori != nullptr) {
                delete[] this->onorariiActori;
            }
            this->onorariiActori = new float[nrActori];
            for (int i = 0; i < nrActori; i++) {
                this->onorariiActori[i] = onorariiActori[i];
            }
        }
    }

    float* getOnorariiActori() {
        return this->onorariiActori;
    }

    float getOnorariuActor(int pozitie) {
        if (pozitie >= 0 && pozitie < nrActori) {
            return this->onorariiActori[pozitie];
        }
        throw 404;
        // sau throw "Pozitie in afara intervalului vectorului!";
    }

    int getIdFilm() {
        return this->idFilm;
    }

    static int getNumarFilme() {
        return numarFilme;
    }

    void setNumarFilme(int nrFilme) {
        numarFilme = nrFilme;
    }

    Film() : idFilm(++numarFilme) {
        this->regizor = "Necunoscut";
        this->durata = 0;
        this->anLansare = 0;
        this->nrActori = 0;
        this->onorariiActori = nullptr;
        this->titlu = nullptr;
    }

    Film(const char* titlu, string regizor, float durata,
        int anLansare, int nrActori, const float* onorariiActori)
        : idFilm(++numarFilme)
    {
        this->regizor = regizor;
        this->durata = durata;
        this->anLansare = anLansare;
        this->nrActori = nrActori;

        if (nrActori > 0 && onorariiActori != nullptr) {
            this->onorariiActori = new float[nrActori];
            for (int i = 0; i < nrActori; i++) {
                this->onorariiActori[i] = onorariiActori[i];
            }
        }
        else {
            this->onorariiActori = nullptr;
            this->nrActori = 0;
        }

        if (titlu != nullptr) {
            this->titlu = new char[strlen(titlu) + 1];
            strcpy_s(this->titlu, strlen(titlu) + 1, titlu);
        }
        else {
            this->titlu = nullptr;
        }
    }

    Film(const Film& copie) : idFilm(++numarFilme) {
        this->regizor = copie.regizor;
        this->durata = copie.durata;
        this->anLansare = copie.anLansare;
        this->nrActori = copie.nrActori;

        if (copie.onorariiActori != nullptr && copie.nrActori > 0) {
            this->onorariiActori = new float[copie.nrActori];
            for (int i = 0; i < copie.nrActori; i++) {
                this->onorariiActori[i] = copie.onorariiActori[i];
            }
        }
        else {
            this->onorariiActori = nullptr;
        }

        if (copie.titlu != nullptr) {
            this->titlu = new char[strlen(copie.titlu) + 1];
            strcpy_s(this->titlu, strlen(copie.titlu) + 1, copie.titlu);
        }
        else {
            this->titlu = nullptr;
        }
    }

    void operator=(const Film& copie) {
        if (this == &copie) return;

        this->regizor = copie.regizor;
        this->durata = copie.durata;
        this->anLansare = copie.anLansare;
        this->nrActori = copie.nrActori;

        if (this->onorariiActori != nullptr) {
            delete[] this->onorariiActori;
            this->onorariiActori = nullptr;
        }

        if (copie.onorariiActori != nullptr && copie.nrActori > 0) {
            this->onorariiActori = new float[copie.nrActori];
            for (int i = 0; i < copie.nrActori; i++) {
                this->onorariiActori[i] = copie.onorariiActori[i];
            }
        }
        else {
            this->onorariiActori = nullptr;
            this->nrActori = 0;
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

    int getAnLansare() {
        return this->anLansare;
    }

    string getRegizor() {
        return this->regizor;
    }

    int getNrActori() {
        return this->nrActori;
    }

    void afisareFilm() {
        cout << endl << this->getIdFilm() << ". Filmul ";
        if (this->getTitlu() != nullptr) {
            cout << this->getTitlu();
        }
        else {
            cout << "Neidentificat";
        }
        cout << ", regizat de " << this->getRegizor()
            << ", durata " << this->getDurata() << " minute,"
            << " lansat in anul " << this->getAnLansare()
            << ". Are " << this->getNrActori() << " actori";
        if (this->getNrActori() > 0) {
            cout << " cu urmatoarele onorarii: ";
            for (int i = 0; i < this->getNrActori() - 1; i++) {
                cout << this->getOnorariuActor(i) << ", ";
            }
            cout << this->getOnorariuActor(this->getNrActori() - 1) << ".";
        }
    }

    ~Film() {
        if (this->onorariiActori != nullptr) {
            delete[] this->onorariiActori;
        }
        if (this->titlu != nullptr) {
            delete[] this->titlu;
        }
    }

    void operator+=(float valoareDeAdaugatLaDurata) {
        this->durata += valoareDeAdaugatLaDurata;
    }

    friend Film operator+=(float valoareDeAdaugatLaDurata, Film& f) {
        f.durata += valoareDeAdaugatLaDurata;
        return f;
    }

    bool operator<(const Film& f) {
        return this->durata < f.durata;
    }

    bool operator!() {
        return this->anLansare != 0;
    }

    float operator()(int pozitie) {
        return this->getOnorariuActor(pozitie);
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

    friend void operator<<(ostream& consola, Film f) {
        consola << endl << "Id: " << f.idFilm;
        consola << endl << (f.titlu != nullptr ? "Titlu: " + string(f.titlu) : "Titlu nespecificat");
        consola << endl << "Regizor: " << f.regizor;
        consola << endl << "Durata: " << f.durata;
        consola << endl << "An lansare: " << f.anLansare;
        consola << endl << "Nr. actori: " << f.nrActori;
        if (f.onorariiActori != nullptr) {
            consola << endl << "Onorarii actori: ";
            for (int i = 0; i < f.getNrActori() - 1; i++) {
                consola << f.getOnorariuActor(i) << ", ";
            }
            consola << f.getOnorariuActor(f.getNrActori() - 1) << ".";
        }
        else {
            consola << endl << "Onorarii actori nespecificate";
        }
    }

    friend void operator>>(istream& in, Film& f);

    explicit operator int() {
        return this->anLansare;
    }

    Film operator++(int) {
        Film copie = *this;
        this->anLansare++;
        return copie;
    }

    Film operator++() {
        this->anLansare++;
        return *this;
    }
};

int Film::numarFilme = 0;

void operator>>(istream& cititor, Film& f) {
    cout << endl << "Titlu: ";
    if (f.titlu != nullptr) {
        delete[] f.titlu;
        f.titlu = nullptr;
    }
    char buffer[100];
    cititor >> buffer;
    f.titlu = new char[strlen(buffer) + 1];
    strcpy_s(f.titlu, strlen(buffer) + 1, buffer);

    cout << endl << "Regizor: ";
    cititor >> f.regizor;

    cout << endl << "Durata: ";
    cititor >> f.durata;

    cout << endl << "An lansare: ";
    cititor >> f.anLansare;

    cout << endl << "Nr. actori: ";
    cititor >> f.nrActori;

    if (f.onorariiActori != nullptr) {
        delete[] f.onorariiActori;
        f.onorariiActori = nullptr;
    }

    if (f.nrActori > 0) {
        cout << endl << "Onorarii actori: ";
        f.onorariiActori = new float[f.nrActori];
        for (int i = 0; i < f.getNrActori(); i++) {
            cout << endl << "Onorariu[" << i << "]: ";
            cititor >> f.onorariiActori[i];
        }
    }
}

void main() {
    float* v = new float[3] { 1000, 2000, 3000 };

    Film film("Inception", "Nolan", 148, 2010, 3, v);
    try {
        cout << endl << film.getOnorariuActor(3);
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

    cout << endl << "Id film constructor toti parametrii: " << film.getIdFilm();

    Film film2 = film;
    cout << endl << "Id film constructor copiere: " << film2.getIdFilm();

    Film filmDefault;
    filmDefault.afisareFilm();

    filmDefault = film;
    cout << endl << "Id film dupa op =: " << filmDefault.getIdFilm();

    film.afisareFilm();
    film2.afisareFilm();
    filmDefault.afisareFilm();

    film += 10;
    5.0f += film;

    film.afisareFilm();

    if (film < film2) {
        cout << endl << "Primul film are durata mai mica!";
    }
    else {
        cout << endl << "Al doilea film are durata mai mica!";
    }

    if (!film) {
        cout << endl << "Filmul are anul de lansare setat!";
    }
    else {
        cout << endl << "Anul de lansare nu este setat!";
    }

    cout << endl << film(2);

    cout << endl << "Litera de pe pozitia 2 din titlu este: " << film[1];
    film[1] = 'E';
    cout << endl << "Litera de pe pozitia 2 din titlu este: " << film[1];

    cout << endl << (int)film;

    Film f1 = film++;
    cout << f1;

    Film f2 = ++film;
    cout << f2;

    cout << endl << "Am initializat " << Film::getNumarFilme() << " obiect/e!";

    delete[] v;
}
