#include<iostream>
using namespace std;


class Doctor {

    public:

        Doctor::Doctor(const std::string& name, const std::string& telephone)
            :name(name),
            telephone(telephone){

            cout << "Doctor constructor" << endl;
        }

        Doctor::Doctor(const Doctor& d1) {

            name = d1.name;
            telephone = d1.telephone;
        }

    private:

        std::string name;
        std::string telephone;
};


class Surgeon :private Doctor {
    
    public:

        Surgeon(int id)::Doctor(const std::string& name, const std::string& telephone)
            :name(name),
            telephone(telephone)
            id(id){

                cout << "Surgeon constructor" << endl;
            }

            Surgeon::~Surgeon() {

                delete[] id;
                cout << "Surgeon destructor" << endl;
            }

            private:

                int id;
};


class Uncopyable {

    protected:

        Uncopyable() {}
        ~Uncopyable() {}

    private:

        Uncopyable(const Uncopyable&);
        Uncopyable& operator=(const Uncopyable&);
};


class Hospital : private Uncopyable {

    public:

        Hospital()::Uncopyable() {}

    private:

        int Hospital;
}
    

int main() {

    Doctor d1("Stanciu Dan", "0756416489");
    Doctor p2 = d1;
    Doctor d3("Stanciu Mara", "0773410725");

    Surgeon s1();

    Hospital h1();
    Hospital h2();
    Hospital h3(h1);
    h1 = h2;

}