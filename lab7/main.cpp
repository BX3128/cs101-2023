// cs_10.pdf  p.16
#include <iostream>
#include <string>

using namespace std;

class Car {
    public:
    string m_brand;
    string m_model;
    int m_year;

    protected:
    int m_MaxSeating;

    public:
    Car(string brand, string model, int year, int seat) {
        m_brand = brand;
        m_model = model;
        m_year = year;
        m_MaxSeating = seat;
        cout << "Constructing " << m_brand << "_Car" << endl;
    }
    int get_m_MaxSeating() {
        return m_MaxSeating;
    }
};

class BMW_Car : public Car {
    protected:
    string m_DriveMode;

    public:
    BMW_Car(string model, int year, int seat) :
        Car("BMW", model, year, seat) {
            m_DriveMode = "Rear-wheel";
        }
    
    string get_DriveMode() {
        return m_DriveMode;
    }
};

class AUDI_Car : public Car {
    protected:
    string m_DriveMode;

    public:
    AUDI_Car(string model, int year, int seat) :
        Car("AUDI", model, year, seat) {
            m_DriveMode = "Front-wheel";
        }
    
    string get_DriveMode() {
        return m_DriveMode;
    }
};

class BENZ_Car : public Car {
    protected:
    string m_DriveMode;

    public:
    BENZ_Car(string model, int year, int seat) :
        Car("BENZ", model, year, seat) {
            m_DriveMode = "Front-wheel";
        }
    
    string get_DriveMode() {
        return m_DriveMode;
    }
};

int main() {
    BMW_Car car_1("X5", 2023, 6);
    cout << car_1.m_brand;
    cout << " : Drive Mode = " << car_1.get_DriveMode() << endl;

    AUDI_Car car_2("A1", 2023, 5);
    cout << car_2.m_brand;
    cout << " : Drive Mode = " << car_2.get_DriveMode() << endl;

    BENZ_Car car_3("GLS", 2023, 4);
    cout << car_3.m_brand;
    cout << " : Drive Mode = " << car_3.get_DriveMode() << endl;

    return 0;
}
