#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class myString {
    private:
        string m_str;
    public:
        myString(string s) {
            m_str = s;
        }
};

class ReadClass {
    private:
        int m_classCount = 0;
        string m_className[100];
    public:
        ReadClass() {}
        void showClass() {
            ifstream in;
            string line;
            in.open("main.cpp");
            if (in.fail()) {
                cout << "Error opening the file main.cpp" << endl;
            }

            while (getline(in, line)) {
                if (line.find("class") == 0) { // a class must be declared at the begining of a line with "class"
                    m_className[m_classCount++] = line;
                }
            }
            in.close();
            
            if (m_classCount) {
                string plural = (m_classCount > 1) ? "es" : "";
                cout << m_classCount << " class" << plural << " in main.cpp" << endl;
                for (int i=0; i<m_classCount; i++) {
                    stringstream str(m_className[i]);
                    for (int j=0; j<2; j++) {
                        getline(str, line, ' ');
                        cout << line << " ";
                    }
                    cout << endl;
                }
            }
        }
};

int main() {
    ReadClass rfile;
    rfile.showClass();
    return 0;
}
