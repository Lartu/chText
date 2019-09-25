#ifndef CHTEXT
#define CHTEXT
#define CHARS_TO_GET_AT_A_TIME 100
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class chText {
    private:
    vector<string> buffer;
    // Gets length of utf8-encoded c++ string
    size_t chText_get_str_utf8length(const string cstr){
        size_t len = cstr.size();
        size_t utf8len = 0;
        unsigned int c;
        for (size_t i = 0; i < len; i++)
        {
            size_t l = 0;
            c = (unsigned char) cstr[i];
            if (c >= 0 && c <= 127) l = 0;
            else if ((c & 0xE0) == 0xC0) l = 1;
            else if ((c & 0xF0) == 0xE0) l = 2;
            else if ((c & 0xF8) == 0xF0) l = 3;
            else if (c>=248 && c<=255) return 0; //invalid utf8
            i += l;
            utf8len++;
        }
        return utf8len;
    }
    // Fills buffer with utf8-encoded c++ string
    void createFromString(const string & cstr){
        size_t cstrlen = cstr.size();
        size_t chPos = 0;
        for(size_t i = 0; i < cstrlen; ++i){
            string ch = "";
            char c = cstr[i];
            if (c >= 0 && c <= 127){
                ch += c;
            }
            else if ((c & 0xE0) == 0xC0){
                ch += c;
                ch += cstr[++i];
            }
            else if ((c & 0xF0) == 0xE0){
                ch += c;
                ch += cstr[++i];
                ch += cstr[++i];
            }
            else if ((c & 0xF8) == 0xF0){
                ch += c;
                ch += cstr[++i];
                ch += cstr[++i];
                ch += cstr[++i];
            }
            buffer.push_back(ch);
            chPos++;
        }
    }
    // Fills buffer with utf8-encoded c++ string
    void createFromChar(const char * cstr){
        size_t cstrlen = strlen(cstr);
        size_t chPos = 0;
        for(size_t i = 0; i < cstrlen; ++i){
            string ch = "";
            char c = cstr[i];
            if (c >= 0 && c <= 127){
                ch += c;
            }
            else if ((c & 0xE0) == 0xC0){
                ch += c;
                ch += cstr[++i];
            }
            else if ((c & 0xF0) == 0xE0){
                ch += c;
                ch += cstr[++i];
                ch += cstr[++i];
            }
            else if ((c & 0xF8) == 0xF0){
                ch += c;
                ch += cstr[++i];
                ch += cstr[++i];
                ch += cstr[++i];
            }
            buffer.push_back(ch);
            chPos++;
        }
    }

    public:
    size_t size(){
        return buffer.size();
    }
    // conversion from string (constructor):
    chText (const string& x) {
        createFromString(x);
    }
    // conversion from string (assignment):
    chText& operator= (const string& x) {
        createFromString(x);
        return *this;
    }
    // conversion from char * (constructor):
    chText (const char * x) {
        createFromChar(x);
    }
    // conversion from char * (assignment):
    chText& operator= (const char * x) {
        createFromChar(x);
        return *this;
    }
    // [] for reading
    chText operator [](size_t i) const {
        chText c = buffer[i];
        return c;
    }
    // Output operator
    friend ostream & operator << (ostream &out, const chText &c);
    // + operator
    friend chText operator+(const chText &c1, const chText &c2);
    // + operator
    friend chText operator+(const string &c1, const chText &c2);
    // + operator
    friend chText operator+(const chText &c1, const string &c2);
    // + operator
    friend chText operator+(const char * c1, const chText &c2);
    // + operator
    friend chText operator+(const chText &c1, const char * c2);
    // Equality operator
    friend bool operator==(const chText& ch1, const chText& ch2);
    // Load a file into this chText
    bool loadFile(const string &fileName){
        string line;
        string fileContents = "";
        ifstream myfile (fileName);
        if (myfile.is_open())
        {
            while ( getline (myfile,line) )
            {
                fileContents += line + "\n";
            }
            myfile.close();
        }
        else return false; 
        createFromString(fileContents);
        return true;
    }

    // [] for setting
    //unsigned long & operator [](int i) {return registers[i];}
    // conversion to A (type-cast operator)
    //operator A() {return A();}
};

ostream & operator << (ostream &out, const chText &c){
    for(const string & s : c.buffer){
        out << s;
    }
    return out;
}

chText operator+(const chText &c1, const chText &c2){
    chText res = c1;
	for(const string & s : c2.buffer){
        res.buffer.push_back(s);
    }
    return res;
}

chText operator+(const string &c1, const chText &c2){
    chText res = c1;
	for(const string & s : c2.buffer){
        res.buffer.push_back(s);
    }
    return res;
}

chText operator+(const chText &c1, const string &str){
    chText res = c1;
    chText c2 = str;
	for(const string & s : c2.buffer){
        res.buffer.push_back(s);
    }
    return res;
}

chText operator+(const char * c1, const chText &c2){
    chText res = c1;
	for(const string & s : c2.buffer){
        res.buffer.push_back(s);
    }
    return res;
}

chText operator+(const chText &c1, const char * str){
    chText res = c1;
    chText c2 = str;
	for(const string & s : c2.buffer){
        res.buffer.push_back(s);
    }
    return res;
}

bool operator==(const chText& ch1, const chText& ch2){
    return ch1.buffer == ch2.buffer;
}

bool operator==(const string& c1, const chText& ch2){
    const chText ch1 = c1;
    return ch1 == ch2;
}

bool operator==(const chText& ch1, const string& c2){
    const chText ch2 = c2;
    return ch1 == ch2;
}

bool operator==(const char * c1, const chText& ch2){
    const chText ch1 = c1;
    return ch1 == ch2;
}

bool operator==(const chText& ch1, const char * c2){
    const chText ch2 = c2;
    return ch1 == ch2;
}

#endif