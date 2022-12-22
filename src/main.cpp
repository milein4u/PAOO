#include<iostream>
using namespace std;


class Doctor {

    public:

        //constructor 
        Doctor::Doctor(const std::string& name, const std::string& telephone, const bool& doctorLocked)
            :name(name),
            telephone(telephone),
            doctorLocked{}

        Doctor::Doctor(const Doctor& d1) {

            name = d1.name;
            telephone = d1.telephone;
            doctorLocked = d1.doctorLocked;
        }

        // copy assignment operator
        Doctor& operator= (const Doctor& d1) {
            
            if (this == &d1)
            {
                cout << "copy assignment of Doctor \n";
                return *this;
            }

            this->name = d1.name;
            this->telephone = d1.telephone;
            this->doctorLocked = d1.doctorLocked;
            return *this;
        }

        //destructor
        ~Doctor()
        {
            cout << "Object Doctor removed";
        }


        void setDoctorLocked(bool value)
        {
            this->doctorLocked = value;
        }

        void display()
        {
            cout << "Doctor " << this->name << "\n" << "Phone number " << this->telephone;
        }

    private:

        std::string name;
        std::string telephone;
        bool doctorLocked;
};


class Uncopyable {

    protected:

        Uncopyable() {}
        ~Uncopyable() {}

    private:

        Uncopyable(const Uncopyable&);
        Uncopyable& operator=(const Uncopyable&);
};

//item 14 resource managing classes - copying behaviour


//declaram 2 functii lock si unlock pentru a facilita manevrarea obiectelor
void lock(Doctor& doctor)
{
    doctor.setDoctorLocked(true);
    cout << "Blocam obiectul de tip Doctor \n";
    
};


void unlock(Doctor& doctor)
{
    doctor.setDoctorLocked(false);
    cout << "Deblocam obiectul de tip Doctorv\n";
};


// facem clasa uncopyable pentru a nu permite copierea acesteia
class LockedDoctor : private Uncopyable
{
    public:
        //blocam obiectul de tip Doctor
        LockedDoctor(Doctor& doc) : pDoc(doc)
        {
            lockObject(pDoc);
        }

        //deblocam obiectul folosindu-ne de destructor
        ~LockedDoctor()
        {
            unlockObject(pDoc);
            cout << "Object Doctor removed ";
        }

    private:
        Doctor& pDoc;
};


//Returneaza un pointer in urma alocarii dinamice a obiectului de tip Doctor
Doctor* ptrDoc(const std::string& name, const std::string& telephone, const bool& doctorLocked)
{
    return new (name, telephone, doctorLocked);
}

//functie in care primim resursa spre care va pointa ,iar la final o vom sterge prin destructor
void printNewDoctor(const std::string& name, const std::string& telephone, const bool& doctorLocked)
{   
    std::auto_ptr<Doctor> pDoc(ptrDoc(name, telephone, doctorLocked));
    pDoc->display();
}

    
int main() {

    //Doctor doctor1("Stanciu Dan", "0756416489");
   
    //item 13 use objects to manage resources 
    //exemplificam acest lucru folosinf auto_ptr si shared_ptr
    
    //utilizam auto_ptr pentru a preveni resource leak
    auto_ptr<Doctor> doctor1(ptrDoc("Stanciu Dan", "0756416489", false));
    doctor1->display();

    //copiem auto-ptr pentru a-l seta pe null dupa ce a sters spre ce pointa anterior, dupa distrugere
    //doctor2 pointeaza spre obiectul creat de ptrDoc iar doctor1 e null
    auto_ptr<Doctor> doctor2(doctor1); 
    doctor2->display();

    //utilizam "shared_ptr" pentru a putea avea mai multi pointeri care pointeaza spre un obiect si care se sterge automat
    //in momentul in care nu mai pointeaza nimic spre aceea resursa
    shared_ptr<Doctor> doctor3(ptrDoc("Pop Andreea", "0775348902", false));
    doctor3->display();

    //aici doctor 4 si doctor3 pointeaza spre acelasi obiect returnat de ptrDoc
    shared_ptr<Doctor> doctor4(doctor3);   
    doctor4->display();
    cout<<"\n;
        "
    //item 14 exemplu de folosire in main
    Doctor doctor5("Pop Mara", "0774329006", false);
    {
        LockedDoctor doctor6(doctor5);
    }
    
    return 0;
}