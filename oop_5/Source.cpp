#include<iostream>
#include<cstring>

using namespace std;

class Masina {
private:
    const int idMasina;
    static int numarMasini;
    char* marca;
    string model;
    float pret;
    int anFabricatie;
    int nrRevizii;
    float* costRevizii;

public:
    void setPret(float pret) {
        if (pret > 0) {
            this->pret = pret;
        }
    }

    float getPret() {
        return this->pret;
    }

    char* getMarca() {
        return this->marca;
    }

    void setMarca(const char* marca) {
        if (marca != nullptr && strlen(marca) > 0) {
            if (this->marca != nullptr) {
                delete[] this->marca;
            }
            this->marca = new char[strlen(marca) + 1];
            strcpy_s(this->marca, strlen(marca) + 1, marca);
        }
    }

    void setModel(string model) {
        if (!model.empty()) {
            this->model = model;
        }
    }

    void setCostRevizii(int nrRevizii, float* costRevizii) {
        if (nrRevizii > 0 && costRevizii != nullptr) {
            this->nrRevizii = nrRevizii;
            if (this->costRevizii != nullptr) {
                delete[] this->costRevizii;
            }
            this->costRevizii = new float[nrRevizii];
            for (int i = 0; i < nrRevizii; i++) {
                this->costRevizii[i] = costRevizii[i];
            }
        }
    }

    float* getCostRevizii() {
        return this->costRevizii;
    }

    float getCostRevizie(int pozitie) {
        if (pozitie >= 0 && pozitie < nrRevizii) {
            return this->costRevizii[pozitie];
        }
        throw 404;
    }

    int getIdMasina() {
        return this->idMasina;
    }

    static int getNumarMasini() {
        return numarMasini;
    }

    void setNumarMasini(int nrMasini) {
        numarMasini = nrMasini;
    }

    Masina() : idMasina(++numarMasini) {
        this->model = "Necunoscut";
        this->pret = 0;
        this->anFabricatie = 0;
        this->nrRevizii = 0;
        this->costRevizii = nullptr;
        this->marca = nullptr;
    }

    Masina(const char* marca, string model, float pret,
        int anFabricatie, int nrRevizii, const float* costRevizii)
        : idMasina(++numarMasini)
    {
        this->model = model;
        this->pret = pret;
        this->anFabricatie = anFabricatie;
        this->nrRevizii = nrRevizii;

        if (nrRevizii > 0 && costRevizii != nullptr) {
            this->costRevizii = new float[nrRevizii];
            for (int i = 0; i < nrRevizii; i++) {
                this->costRevizii[i] = costRevizii[i];
            }
        }
        else {
            this->costRevizii = nullptr;
            this->nrRevizii = 0;
        }

        if (marca != nullptr) {
            this->marca = new char[strlen(marca) + 1];
            strcpy_s(this->marca, strlen(marca) + 1, marca);
        }
        else {
            this->marca = nullptr;
        }
    }

    Masina(const Masina& copie) : idMasina(++numarMasini) {
        this->model = copie.model;
        this->pret = copie.pret;
        this->anFabricatie = copie.anFabricatie;
        this->nrRevizii = copie.nrRevizii;

        if (copie.costRevizii != nullptr && copie.nrRevizii > 0) {
            this->costRevizii = new float[copie.nrRevizii];
            for (int i = 0; i < copie.nrRevizii; i++) {
                this->costRevizii[i] = copie.costRevizii[i];
            }
        }
        else {
            this->costRevizii = nullptr;
        }

        if (copie.marca != nullptr) {
            this->marca = new char[strlen(copie.marca) + 1];
            strcpy_s(this->marca, strlen(copie.marca) + 1, copie.marca);
        }
        else {
            this->marca = nullptr;
        }
    }

    void operator=(const Masina& copie) {
        if (this == &copie) return;

        this->model = copie.model;
        this->pret = copie.pret;
        this->anFabricatie = copie.anFabricatie;
        this->nrRevizii = copie.nrRevizii;

        if (this->costRevizii != nullptr) {
            delete[] this->costRevizii;
            this->costRevizii = nullptr;
        }

        if (copie.costRevizii != nullptr && copie.nrRevizii > 0) {
            this->costRevizii = new float[copie.nrRevizii];
            for (int i = 0; i < copie.nrRevizii; i++) {
                this->costRevizii[i] = copie.costRevizii[i];
            }
        }
        else {
            this->costRevizii = nullptr;
            this->nrRevizii = 0;
        }

        if (this->marca != nullptr) {
            delete[] this->marca;
            this->marca = nullptr;
        }

        if (copie.marca != nullptr) {
            this->marca = new char[strlen(copie.marca) + 1];
            strcpy_s(this->marca, strlen(copie.marca) + 1, copie.marca);
        }
        else {
            this->marca = nullptr;
        }
    }

    int getAnFabricatie() {
        return this->anFabricatie;
    }

    string getModel() {
        return this->model;
    }

    int getNrRevizii() {
        return this->nrRevizii;
    }

    void afisareMasina() {
        cout << endl << this->getIdMasina() << ". Masina ";
        if (this->getMarca() != nullptr) {
            cout << this->getMarca();
        }
        else {
            cout << "Neidentificata";
        }
        cout << " model " << this->getModel()
            << ", pret " << this->getPret() << " EUR,"
            << " an fabricatie " << this->getAnFabricatie()
            << ". Are " << this->getNrRevizii()
            << " revizii";
        if (this->getNrRevizii() > 0) {
            cout << " cu urmatoarele costuri: ";
            for (int i = 0; i < this->getNrRevizii() - 1; i++) {
                cout << this->getCostRevizie(i) << ", ";
            }
            cout << this->getCostRevizie(this->getNrRevizii() - 1) << ".";
        }
    }

    ~Masina() {
        if (this->costRevizii != nullptr) {
            delete[] this->costRevizii;
        }
        if (this->marca != nullptr) {
            delete[] this->marca;
        }
    }

    void operator+=(float valoareDeAdaugatLaPret) {
        this->pret += valoareDeAdaugatLaPret;
    }

    friend Masina operator+=(float valoareDeAdaugatLaPret, Masina& m) {
        m.pret += valoareDeAdaugatLaPret;
        return m;
    }

    bool operator<(const Masina& m) {
        return this->pret < m.pret;
    }

    bool operator!() {
        return this->anFabricatie != 0;
    }

    float operator()(int pozitie) {
        return this->getCostRevizie(pozitie);
    }

    char& operator[](int index) {
        if (this->marca == nullptr) {
            throw "Marca inexistenta!";
        }
        if (index >= 0 && index < (int)strlen(this->marca)) {
            return this->marca[index];
        }
        else {
            throw "Indexul nu se afla in interval!";
        }
    }

    friend void operator<<(ostream& consola, Masina m) {
        consola << endl << "Id: " << m.idMasina;
        consola << endl << (m.marca != nullptr ? "Marca: " + string(m.marca) : "Marca nespecificata");
        consola << endl << "Model: " << m.model;
        consola << endl << "Pret: " << m.pret;
        consola << endl << "An fabricatie: " << m.anFabricatie;
        consola << endl << "Nr. revizii: " << m.nrRevizii;
        if (m.costRevizii != nullptr) {
            consola << endl << "Costuri revizii: ";
            for (int i = 0; i < m.getNrRevizii() - 1; i++) {
                consola << m.getCostRevizie(i) << ", ";
            }
            consola << m.getCostRevizie(m.getNrRevizii() - 1) << ".";
        }
        else {
            consola << endl << "Costuri revizii nespecificate";
        }
    }

    friend void operator>>(istream& in, Masina& m);

    explicit operator int() {
        return this->anFabricatie;
    }

    Masina operator++(int) {
        Masina copie = *this;
        this->anFabricatie++;
        return copie;
    }

    Masina operator++() {
        this->anFabricatie++;
        return *this;
    }
};

int Masina::numarMasini = 0;

void operator>>(istream& cititor, Masina& m) {
    cout << endl << "Marca: ";
    if (m.marca != nullptr) {
        delete[] m.marca;
        m.marca = nullptr;
    }
    char buffer[100];
    cititor >> buffer;
    m.marca = new char[strlen(buffer) + 1];
    strcpy_s(m.marca, strlen(buffer) + 1, buffer);

    cout << endl << "Model: ";
    cititor >> m.model;

    cout << endl << "Pret: ";
    cititor >> m.pret;

    cout << endl << "An fabricatie: ";
    cititor >> m.anFabricatie;

    cout << endl << "Nr. revizii: ";
    cititor >> m.nrRevizii;

    if (m.costRevizii != nullptr) {
        delete[] m.costRevizii;
        m.costRevizii = nullptr;
    }

    if (m.nrRevizii > 0) {
        cout << endl << "Costuri revizii: ";
        m.costRevizii = new float[m.nrRevizii];
        for (int i = 0; i < m.getNrRevizii(); i++) {
            cout << endl << "Cost[" << i << "]: ";
            cititor >> m.costRevizii[i];
        }
    }
}

void main() {
    float* v = new float[3] { 500, 700, 900 };

    Masina masina("Dacia", "Logan", 5000, 2012, 3, v);
    try {
        cout << endl << masina.getCostRevizie(3);
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

    cout << endl << "Id masina constructor toti parametrii: " << masina.getIdMasina();

    Masina masina2 = masina;
    cout << endl << "Id masina constructor copiere: " << masina2.getIdMasina();

    Masina masinaDefault;
    masinaDefault.afisareMasina();

    masinaDefault = masina;
    cout << endl << "Id masina dupa op =: " << masinaDefault.getIdMasina();

    masina.afisareMasina();
    masina2.afisareMasina();
    masinaDefault.afisareMasina();

    masina += 1000;
    500.0f += masina;

    masina.afisareMasina();

    if (masina < masina2) {
        cout << endl << "Prima masina are pret mai mic!";
    }
    else {
        cout << endl << "A doua masina are pret mai mic!";
    }

    if (!masina) {
        cout << endl << "Masina are anul de fabricatie setat!";
    }
    else {
        cout << endl << "Anul de fabricatie nu este setat!";
    }

    cout << endl << masina(2);

    cout << endl << "Litera de pe pozitia 2 din marca este: " << masina[1];
    masina[1] = 'E';
    cout << endl << "Litera de pe pozitia 2 din marca este: " << masina[1];

    cout << endl << (int)masina;

    Masina m1 = masina++;
    cout << m1;

    Masina m2 = ++masina;
    cout << m2;

    cout << endl << "Am initializat " << Masina::getNumarMasini() << " obiect/e!";

    delete[] v;
}
