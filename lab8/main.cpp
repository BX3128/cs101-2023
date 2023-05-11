// Lab#8, cs_12.pdf  p.9
#include <iostream>
#include <string>

using namespace std;
/*
class Engine {
    private:
        int m_EngineCapacity;
        int m_Horsepower;
        bool m_EngineRunning;
    public:
        Engine(int EngineCapacity=2000, int Horsepower=200) {
            m_EngineCapacity = EngineCapacity;
            m_Horsepower = Horsepower;
            m_EngineRunning = false;
        }
        bool EngineStart() {
            m_EngineRunning = true;
            return true;
        };
        bool EngineStop() {
            m_EngineRunning = false;
            return true;
        };
        bool get_EngineStatus() {
            return m_EngineRunning;
        };
        bool get_EngineStatus() {
            return m_EngineRunning;
        };
};
*/

class Fueltank {
    private:
        int m_FueltankCapacity;
        int m_Gas_grade;
    public:
        Fueltank(int FueltankCapacity=3000, int Gas=98) {
            m_FueltankCapacity = FueltankCapacity;
            m_Gas_grade = Gas;
        }
        int fuel_up(int v, int gas) {
            if (v > m_FueltankCapacity) {
                cout << "Error: FueltankCapacity: " << m_FueltankCapacity << " ";
                cout << "but fuel up: " << v << endl;
                //cout << "fuel_up: " << v << " Gas_grade: " << m_Gas_grade << endl;
            }
            if (gas != m_Gas_grade) {
                cout << "Error: Gas_grade: " << gas << " ";
                cout << "Correct Gas_grade: " << m_Gas_grade << endl;
                return 0;
            }
            cout << "fuel_up: " << v << " Gas_grade: " << m_Gas_grade << endl;
            m_Gas_grade = gas;
            return 1;
        }
        int set_Gas_grade(int Gas_grade) {
            m_Gas_grade = Gas_grade;
            cout << "Set Gas_grade = " << m_Gas_grade << endl;
            return m_Gas_grade;
        }
        int get_Gas_grade() {
            return m_Gas_grade;
        }
};

class Car {
    private:
        //Engine m_Engine;
        Fueltank m_Fueltank;
        int m_MaxSeating;
        int m_price;
        int m_base;
        string m_brand;
        string m_model;
        int m_year;
        void m_UpdatePrice(int base=500000) {}
    public:
        Car(string x, string y, int z, int s) {
            m_brand = x;
            m_model = y;
            m_year = z;
            m_MaxSeating = s;
            cout << "Constructing " << m_brand << "_Car" << endl;
        }
        int get_MaxSeating() {
            return m_MaxSeating;
        }
        int get_Price() {
            return m_price;
        }
        void set_base(int n) {
            m_base = n;
        }
        string get_brand() {
            return m_brand;
        }
        bool get_EngineStatus() {
            return true;
        }
        bool startEngine() {
            return true;
        }
        bool stopEngine() {
            return true;
        }
        int get_Gas_grade() {
            return m_Fueltank.get_Gas_grade();
        }
        int set_Gas_grade(int gas=98) {
            m_Fueltank.set_Gas_grade(gas);
            return m_Fueltank.get_Gas_grade();
        }
        int fuel_up(int v, int gas=98) {
            m_Fueltank.fuel_up(v, gas);
            return m_Fueltank.get_Gas_grade();
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
    // 正常結果
    cout << "正常結果" << endl;
    AUDI_Car car_2("A1", 2021, 2);
    cout << car_2.get_brand() << " : Gas_grade = " << car_2.get_Gas_grade() << endl;
    car_2.set_Gas_grade(95);
    cout << car_2.get_brand() << " : Gas_grade = " << car_2.get_Gas_grade() << endl;
    car_2.fuel_up(300, 95);
    cout << endl;

    // 加錯油
    cout << "加錯油" << endl;
    AUDI_Car car_3("A1", 2021, 2);
    cout << car_3.get_brand() << " : Gas_grade = " << car_3.get_Gas_grade() << endl;
    car_3.set_Gas_grade(95);
    cout << car_3.get_brand() << " : Gas_grade = " << car_3.get_Gas_grade() << endl;
    car_3.fuel_up(300, 99);
    cout << endl;

    // 加的量太大！
    cout << "加的量太大！" << endl;
    AUDI_Car car_4("A1", 2021, 2);
    cout << car_4.get_brand() << " : Gas_grade = " << car_4.get_Gas_grade() << endl;
    car_4.set_Gas_grade(95);
    cout << car_4.get_brand() << " : Gas_grade = " << car_4.get_Gas_grade() << endl;
    car_4.fuel_up(3000000, 95);
    cout << endl;

    // 加錯油而且加的量太大！
    cout << "加錯油而且加的量太大！" << endl;
    AUDI_Car car_5("A1", 2021, 2);
    cout << car_5.get_brand() << " : Gas_grade = " << car_5.get_Gas_grade() << endl;
    car_5.set_Gas_grade(95);
    cout << car_5.get_brand() << " : Gas_grade = " << car_5.get_Gas_grade() << endl;
    car_5.fuel_up(100000, 98);
    
    return 0;
}
