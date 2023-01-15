#include <iostream>
#include <cmath>
#include <vector>
#include <memory>

class masina {
    int an;
    std::string nume;
    int vitezaMaxima;
protected:
    int greutate;
public:
    const std::string &getNume() const {
        return nume;
    }


    masina(int an, const std::string &nume, int vitezaMaxima, int greutate) : an(an), nume(nume),
                                                                              vitezaMaxima(vitezaMaxima),
                                                                              greutate(greutate) {}

    bool operator==(const masina &rhs) const {
        return an == rhs.an &&
               nume == rhs.nume &&
               vitezaMaxima == rhs.vitezaMaxima &&
               greutate == rhs.greutate;
    }

    bool operator!=(const masina &rhs) const {
        return !(rhs == *this);
    }

    friend std::ostream &operator<<(std::ostream &os, const masina &masina) {
        os << "an: " << masina.an << " nume: " << masina.nume << " vitezaMaxima: " << masina.vitezaMaxima
           << " greutate: " << masina.greutate;
        return os;
    }

    virtual float autonomie(){

    };

};

class electrica : public masina{
    int capacitateBaterie;
public:
    electrica(int an, const std::string &nume, int vitezaMaxima, int greutate, int capacitateBaterie) : masina(an, nume,
                                                                                                                      vitezaMaxima,
                                                                                                                      greutate),
                                                                                                               capacitateBaterie(
                                                                                                                capacitateBaterie) {}

    friend std::ostream &operator<<(std::ostream &os, const electrica &electrica) {
        os << static_cast<const masina &>(electrica) << " capacitateBaterie: " << electrica.capacitateBaterie;
        return os;
    }
    float autonomie() override{
        int x = electrica::capacitateBaterie;
        int y = electrica::greutate;
        return float(x*x)/float(y*y);
    };
};
class fosila: public masina{
    std::string tipCombustibil;
    int capacitateRezervor;
public:
    fosila(int an, const std::string &nume, int vitezaMaxima, int greutate, const std::string &tipCombustibil,
           int capacitateRezervor) : masina(an, nume, vitezaMaxima, greutate), tipCombustibil(tipCombustibil),
                                     capacitateRezervor(capacitateRezervor) {}

    bool operator==(const fosila &rhs) const {
        return static_cast<const masina &>(*this) == static_cast<const masina &>(rhs) &&
               tipCombustibil == rhs.tipCombustibil &&
               capacitateRezervor == rhs.capacitateRezervor;
    }

    const std::string &getTipCombustibil() const {
        return tipCombustibil;
    }

    bool operator!=(const fosila &rhs) const {
        return !(rhs == *this);
    }

    friend std::ostream &operator<<(std::ostream &os, const fosila &fosila) {
        os << static_cast<const masina &>(fosila) << " tipCombustibil: " << fosila.tipCombustibil
           << " capacitateRezervor: " << fosila.capacitateRezervor;
        return os;
    }

    float autonomie() override {
        int x = fosila::capacitateRezervor;
        int y = fosila::greutate;//in kg,transformat in tone
        return float(x)/sqrt(float(y)/1000);
    }
};
class hibrida: public masina{
    std::string tipCombustibil;
    int capacitateRezervor;
    int capacitateBaterie;
public:
    hibrida(int an, const std::string &nume, int vitezaMaxima, int greutate, const std::string &tipCombustibil,
            int capacitateRezervor, int capacitateBaterie) : masina(an, nume, vitezaMaxima, greutate),
                                                             tipCombustibil(tipCombustibil),
                                                             capacitateRezervor(capacitateRezervor),
                                                             capacitateBaterie(capacitateBaterie) {}

    bool operator==(const hibrida &rhs) const {
        return static_cast<const masina &>(*this) == static_cast<const masina &>(rhs) &&
               tipCombustibil == rhs.tipCombustibil &&
               capacitateRezervor == rhs.capacitateRezervor &&
               capacitateBaterie == rhs.capacitateBaterie;
    }

    bool operator!=(const hibrida &rhs) const {
        return !(rhs == *this);
    }

    friend std::ostream &operator<<(std::ostream &os, const hibrida &hibrida) {
        os << static_cast<const masina &>(hibrida) << " tipCombustibil: " << hibrida.tipCombustibil
           << " capacitateRezervor: " << hibrida.capacitateRezervor << " capacitateBaterie: "
           << hibrida.capacitateBaterie;
        return os;
    }

    float autonomie() override {
        int x = hibrida::capacitateRezervor;
        int y = hibrida::capacitateBaterie;
        int z = hibrida::greutate;
        return float(y*y)/float(z*z) + float(x)/sqrt(float(z)/1000);
    }
};
class tranzactie{
    std::string nume;
    std::string data;
    std::vector <std::shared_ptr<masina>> masini;
public:
    tranzactie(const std::string &nume, const std::string &data, const std::vector<std::shared_ptr<masina>> &masini)
            : nume(nume), data(data), masini(masini) {}

    friend std::ostream &operator<<(std::ostream &os, const tranzactie &tranzactie) {
        std::string x = "[";
        for(int i=0;i < tranzactie.masini.size();i++)
        {
            x.append(tranzactie.masini[i]->getNume());
            if(i<tranzactie.masini.size()-1)
            x.append(" ");
        }
        x.append("]");
        os << "nume: " << tranzactie.nume << " data: " << tranzactie.data << " Masini: " << x;
        return os;
    }

    virtual ~tranzactie() {

    }
};
int main() {

    std::vector <std::shared_ptr<masina>> cars;
    std::vector<tranzactie> tranzactii;

    int x=0;
    do {
        std::cout<<"Citeste cazuri, program se opreste cand scriem 6:\n";
        std::cin >> x;
        if (x == 1) {
            std::string y;
            std::cout<<"Tip masina:\n";
            std::cin>>y;
            if(y=="fosila"){
                std::cout<<"an nume maxSpeed greutate tipCombustibil capacitateRezervor";
                int an,greutate,maxSpeed,capacitateRezervor;
                std::string nume;
                std::string tipCombustibil;
                std::cin>>an>>nume>>maxSpeed>>greutate>>tipCombustibil>>capacitateRezervor;
                cars.emplace_back(std::make_shared<fosila>(an,nume,maxSpeed,greutate,tipCombustibil,capacitateRezervor));
            }
            else if(y=="electrica"){
                std::cout<<"an nume maxSpeed greutate capacitateBaterie";
                int an,greutate,maxSpeed,capacitateBaterie;
                std::string nume;
                std::cin>>an>>nume>>maxSpeed>>greutate>>capacitateBaterie;
                cars.emplace_back(std::make_shared<electrica>(an,nume,maxSpeed,greutate,capacitateBaterie));
            }
            else if(y=="hibrida"){

            }
            else std::cout<<"NU\n";
        }
    } while (x!=6);
    std::cout<<*cars[0]<<std::endl;
    for(int i=0; i<cars.size(); i++){
        std::shared_ptr<electrica> u = std::dynamic_pointer_cast<electrica>(cars[i]);
        if(u)
            std::cout<<*u;
        else
            std::cout<<"FOSILA IMPUTITA\n";
    }
    std::cout<<cars[0]->autonomie();
//    electrica tesla(2019,"Tesla",250,1700,40000);
//    cars.push_back(tesla);
//    fosila chevy(2019,"chevy",400,1700,"benzina",90);
//    cars.push_back(chevy);
//    hibrida dacia(2024,"dacia",250,1700,"benzina",90,40000);
//    cars.push_back(dacia);
//    tranzactie tranzactia1("Marius","5 5 2019",cars);
//    std::cout<<tranzactia1<<std::endl;
//    std::cout<<dacia.autonomie()<<std::endl;
//    std::cout<<chevy.autonomie()<<std::endl;
//    std::cout<<tesla.autonomie();
    return 0;
}
