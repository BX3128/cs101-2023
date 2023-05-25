#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class ReplaceMyString {
    public:
    ReplaceMyString() {}
    void replaceString(string needle, string stick) {
        ifstream in("main.cpp");
        ofstream out("rmain.cpp");
        char c;
        while (true) {
            //in >> c; // 使用 >> 會直接忽略空白等特殊字元，可以嘗試 in.peek()
            in.get(c);
            if (in.eof()) {
                break;
            }
            // test: III
            if (c == needle[0]) {
                string buff="";
                buff += c;
                for (int i=1; i<needle.length(); i++) {
                    //in >> c;
                    in.get(c);
                    buff += c;
                    if (c != needle[i]) {
                        out << buff;
                        break;
                    }
                    if (i == needle.length()-1) {
                        for (int j=0; j<stick.length(); j++) {
                            out << stick[j];
                        }
                    }
                }
            } else {
                out << c;
            }
        }
        in.close();
        out.close();
    }
};

int main() {
    ReplaceMyString my;
    my.replaceString("IU", "IU is best");
    return 0;
}
