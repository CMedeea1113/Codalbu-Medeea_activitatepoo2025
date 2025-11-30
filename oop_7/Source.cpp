#include<iostream>
#include<cstring>

using namespace std;

class Florarie {
private:
    const int idFlorarie;
    static int numarFlorarii;
    char* nume;
    string adresa;
    float profitAnual;
    int nrTipuriFlori;
    float* preturiFlori;

public:
    void setProfitAnual(float profit) {
        if (profit >= 0) {
            this->profitAnual = profit;
        }
    }

    float getProfitAnual() {
        return this->profitAnual;
    }

    char* getNume() {
        return this->nume;
    }

    void setNume(const char* nume) {
        if (nume != nullptr && strlen(nume) > 0) {
            if (this->nume != nullptr) {
                delete[] this->nume;
            }
            this->nume = new char[strlen(nume) + 1];
            strcpy_s(this->nume, strlen(nume) + 1, nume);
        }
    }

    void setAdresa(string adresa) {
        if (!adresa.empty()) {
            this->adresa = adresa;
        }
    }

    void setPreturiFlori(int nrTipuriFlori, float* preturiFlori) {
        if (nrTipuriFlori > 0 && preturiFlori != nullptr) {
            this->nrTipuriFlori = nrTipuriFlori;
            if (this->preturiFlori != nullptr) {
                delete[] this->preturiFlori;
            }
            this->preturiFlori = new float[nrTipuriFlori];
            for (int i = 0; i < nrTipuriFlori; i++) {
                this->preturiFlori[i] = preturiFlori[i];
            }
        }
    }

    float* getPreturiFlori() {
        return this->preturiFlori;
    }

    float getPretFloare(int pozitie) {
        if (pozitie >= 0 && pozitie < nrTipuriFlori) {
            return this->preturiFlori[pozitie];
        }
        throw 404;
    }

    int getIdFlorarie() {
        return this->idFlorarie;
    }

    static int getNumarFlorarii() {
        return numarFlorarii;
    }

    void setNumarFlorarii(int nr) {
        numarFlorarii = nr;
    }

    Florarie() : idFlorarie(++numarFlorarii) {
        this->adresa = "Necunoscuta";
        this->profitAnual = 0;
        this->nrTipuriFlori = 0;
        this->preturiFlori = nullptr;
        this->nume = nullptr;
    }

    Florarie(const char* nume, string adresa, float profitAnual,
        int nrTipuriFlori, const float* preturiFlori)
        : idFlorarie(++numarFlorarii)
    {
        this->adresa = adresa;
        this->profitAnual = (profitAnual >= 0 ? profitAnual : 0);
        this->nrTipuriFlori = nrTipuriFlori > 0 ? nrTipuriFlori : 0;

        if (this->nrTipuriFlori > 0 && preturiFlori != nullptr) {
            this->preturiFlori = new float[this->nrTipuriFlori];
            for (int i = 0; i < this->nrTipuriFlori; i++) {
                this->preturiFlori[i] = preturiFlori[i];
            }
        }
        else {
            this->preturiFlori = nullptr;
            this->nrTipuriFlori = 0;
        }

        if (nume != nullptr && strlen(nume) > 0) {
            this->nume = new char[strlen(nume) + 1];
            strcpy_s(this->nume, strlen(nume) + 1, nume);
        }
        else {
            this->nume = nullptr;
        }
    }

    Florarie(const Florarie& copie) : idFlorarie(++numarFlorarii) {
        this->adresa = copie.adresa;
        this->profitAnual = copie.profitAnual;
        this->nrTipuriFlori = copie.nrTipuriFlori;

        if (copie.preturiFlori != nullptr && copie.nrTipuriFlori > 0) {
            this->preturiFlori = new float[copie.nrTipuriFlori];
            for (int i = 0; i < copie.nrTipuriFlori; i++) {
                this->preturiFlori[i] = copie.preturiFlori[i];
            }
        }
        else {
            this->preturiFlori = nullptr;
        }

        if (copie.nume != nullptr) {
            this->nume = new char[strlen(copie.nume) + 1];
            strcpy_s(this->nume, strlen(copie.nume) + 1, copie.nume);
        }
        else {
            this->nume = nullptr;
        }
    }

    void operator=(const Florarie& copie) {
        if (this == &copie) return;

        this->adresa = copie.adresa;
        this->profitAnual = copie.profitAnual;
        this->nrTipuriFlori = copie.nrTipuriFlori;

        if (this->preturiFlori != nullptr) {
            delete[] this->preturiFlori;
            this->preturiFlori = nullptr;
        }

        if (copie.preturiFlori != nullptr && copie.nrTipuriFlori > 0) {
            this->preturiFlori = new float[copie.nrTipuriFlori];
            for (int i = 0; i < copie.nrTipuriFlori; i++) {
                this->preturiFlori[i] = copie.preturiFlori[i];
            }
        }
        else {
            this->preturiFlori = nullptr;
            this->nrTipuriFlori = 0;
        }

        if (this->nume != nullptr) {
            delete[] this->nume;
            this->nume = nullptr;
        }

        if (copie.nume != nullptr) {
            this->nume = new char[strlen(copie.nume) + 1];
            strcpy_s(this->nume, strlen(copie.nume) + 1, copie.nume);
        }
        else {
            this->nume = nullptr;
        }
    }

    string getAdresa() {
        return this->adresa;
    }

    int getNrTipuriFlori() {
        return this->nrTipuriFlori;
    }

    void afisareFlorarie() {
        cout << endl << this->getIdFlorarie() << ". Floraria ";
        if (this->getNume() != nullptr) {
            cout << this->getNume();
        }
        else {
            cout << "Neidentificata";
        }
        cout << " situata la adresa " << this->getAdresa()
            << ", are profit anual " << this->getProfitAnual() << " RON"
            << " si comercializeaza " << this->getNrTipuriFlori()
            << " tipuri de flori";
        if (this->getNrTipuriFlori() > 0) {
            cout << " cu urmatoarele preturi: ";
            for (int i = 0; i < this->getNrTipuriFlori() - 1; i++) {
                cout << this->getPretFloare(i) << ", ";
            }
            cout << this->getPretFloare(this->getNrTipuriFlori() - 1) << ".";
        }
    }

    ~Florarie() {
        if (this->preturiFlori != nullptr) {
            delete[] this->preturiFlori;
        }
        if (this->nume != nullptr) {
            delete[] this->nume;
        }
    }

    void operator+=(float valoareDeAdaugatLaProfit) {
        this->profitAnual += valoareDeAdaugatLaProfit;
    }

    friend Florarie operator+=(float valoareDeAdaugatLaProfit, Florarie& f) {
        f.profitAnual += valoareDeAdaugatLaProfit;
        return f;
    }

    bool operator<(const Florarie& f) {
        return this->profitAnual < f.profitAnual;
    }

    bool operator!() {
        return this->profitAnual != 0;
    }

    float operator()(int pozitie) {
        return this->getPretFloare(pozitie);
    }

    char& operator[](int index) {
        if (this->nume == nullptr) {
            throw "Nume inexistent!";
        }
        if (index >= 0 && index < (int)strlen(this->nume)) {
            return this->nume[index];
        }
        else {
            throw "Indexul nu se afla in interval!";
        }
    }

    friend void operator<<(ostream& consola, Florarie f) {
        consola << endl << "Id: " << f.idFlorarie;
        consola << endl << (f.nume != nullptr ? "Nume: " + string(f.nume) : "Nume nespecificat");
        consola << endl << "Adresa: " << f.adresa;
        consola << endl << "Profit anual: " << f.profitAnual;
        consola << endl << "Nr. tipuri flori: " << f.nrTipuriFlori;
        if (f.preturiFlori != nullptr) {
            consola << endl << "Preturi flori: ";
            for (int i = 0; i < f.getNrTipuriFlori() - 1; i++) {
                consola << f.getPretFloare(i) << ", ";
            }
            consola << f.getPretFloare(f.getNrTipuriFlori() - 1) << ".";
        }
        else {
            consola << endl << "Preturi flori nespecificate";
        }
    }

    friend void operator>>(istream& in, Florarie& f);

    explicit operator int() {
        return (int)this->profitAnual;
    }

    Florarie operator++(int) {
        Florarie copie = *this;
        this->profitAnual++;
        return copie;
    }

    Florarie operator++() {
        this->profitAnual++;
        return *this;
    }
};

int Florarie::numarFlorarii = 0;

void operator>>(istream& cititor, Florarie& f) {
    cout << endl << "Nume florarie: ";
    if (f.nume != nullptr) {
        delete[] f.nume;
        f.nume = nullptr;
    }
    char buffer[100];
    cititor >> buffer;
    f.nume = new char[strlen(buffer) + 1];
    strcpy_s(f.nume, strlen(buffer) + 1, buffer);

    cout << endl << "Adresa: ";
    cititor >> f.adresa;

    cout << endl << "Profit anual: ";
    cititor >> f.profitAnual;

    cout << endl << "Numar tipuri flori: ";
    cititor >> f.nrTipuriFlori;

    if (f.preturiFlori != nullptr) {
        delete[] f.preturiFlori;
        f.preturiFlori = nullptr;
    }

    if (f.nrTipuriFlori > 0) {
        cout << endl << "Preturi flori: ";
        f.preturiFlori = new float[f.nrTipuriFlori];
        for (int i = 0; i < f.getNrTipuriFlori(); i++) {
            cout << endl << "Pret[" << i << "]: ";
            cititor >> f.preturiFlori[i];
        }
    }
}

int main() {
    float* v = new float[3] { 15.5f, 20.0f, 35.75f };

    Florarie florarie("Iris", "Bd. Florilor 10", 50000, 3, v);
    try {
        cout << endl << florarie.getPretFloare(3);
    }
    catch (int cod) {
        cout << endl << "Cod eroare: " << cod;
    }
    catch (const char* mesaj) {
        cout << endl << mesaj;
    }
    catch (...) {
        cout << endl << "Pozitia este in afara intervalului!";
    }

    cout << endl << "Id florarie constructor cu toti parametrii: " << florarie.getIdFlorarie();

    Florarie florarie2 = florarie;
    cout << endl << "Id florarie constructor copiere: " << florarie2.getIdFlorarie();

    Florarie florarieDefault;
    florarieDefault.afisareFlorarie();

    florarieDefault = florarie;
    cout << endl << "Id florarie dupa op =: " << florarieDefault.getIdFlorarie();

    florarie.afisareFlorarie();
    florarie2.afisareFlorarie();
    florarieDefault.afisareFlorarie();

    florarie += 1000;
    500.0f += florarie;

    florarie.afisareFlorarie();

    if (florarie < florarie2) {
        cout << endl << "Prima florarie are profit mai mic!";
    }
    else {
        cout << endl << "A doua florarie are profit mai mic!";
    }

    if (!florarie) {
        cout << endl << "Florariei i s-a setat profitul!";
    }
    else {
        cout << endl << "Profitul nu este setat!";
    }

    cout << endl << florarie(2);

    cout << endl << "Litera de pe pozitia 2 din nume este: " << florarie[1];
    florarie[1] = 'E';
    cout << endl << "Litera de pe pozitia 2 din nume este: " << florarie[1];

    cout << endl << (int)florarie;

    Florarie f1 = florarie++;
    cout << f1;

    Florarie f2 = ++florarie;
    cout << f2;

    cout << endl << "Am initializat " << Florarie::getNumarFlorarii() << " obiect/e!";

    delete[] v;
    return 0;
}
