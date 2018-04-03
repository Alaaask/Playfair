//
// Created by yu on 2018/3/26.
//

#ifndef INC_20180321_PLAYFAIR_H
#define INC_20180321_PLAYFAIR_H

#include <string>
#include <algorithm>
#define SIZE 5

class Playfair{
public:
    Playfair(std::string c, std::string k) { ciphertext = c; key = k;}
    ~Playfair() {}
    std::string decrypt();

private:
    std::string ciphertext, key, plaintext;
    int alphabet[26] = {0};   // 统计Key中出现的字母，有为1，无为0
    char M[SIZE][SIZE];

    std::string to_upper(std::string);
    std::string JtoI(std::string);
    void get_distinct_key();
    void bulid_matrix();
    void find_letter(int &, int &, char);
    void delete_x();

};


std::string Playfair::decrypt () {

    if(ciphertext.size() % 2) {
        return "Uncompleted Ciphertext!";
    }

    ciphertext = to_upper(ciphertext);
    ciphertext = JtoI(ciphertext);

    key = to_upper(key);
    key = JtoI(key);

    get_distinct_key();

    bulid_matrix();

    for(int i = 0; i < ciphertext.size() - 1; i += 2) {

        char C1 = ciphertext[i], C2 = ciphertext[i + 1];
        int x1, y1, x2, y2;

        find_letter(x1, y1, C1);
        find_letter(x2, y2, C2);

        if (x1 == x2 && y1 == y2) {
            return "Wrong Ciphertext!";
        }
        else if(x1 == x2) {
            y1 = (y1 + 4) % SIZE;
            y2 = (y2 + 4) % SIZE;
        }
        else if(y1 == y2) {
            x1 = (x1 + 4) % SIZE;
            x2 = (x2 + 4) % SIZE;
        }
        else {
            int temp = y1;
            y1 = y2;
            y2 = temp;
        }

        plaintext += M[x1][y1];
        plaintext += M[x2][y2];

    }

    delete_x();

    return plaintext;

}

std::string Playfair::JtoI (std::string s) {

    int i = 0;
    while(i < s.size()) {
        if (s[i] == 'J')
            s[i] = 'I';
        i++;
    }

    return s;

}

std::string Playfair::to_upper(std::string src) {

    std::string dst;
    std::transform(src.begin(), src.end(), back_inserter(dst), ::toupper);

    return dst;
}

void Playfair::get_distinct_key() { //在IJ统一之后调用

    // alphabet[26] = {0}; 这里已经不能初始化了

    for(int i = 0 ; i < key.size(); i++) {
        if(alphabet[int(key[i]) - 65])
            key.erase(i, 1);
        else alphabet[int(key[i]) - 65]++;
    }

}

void Playfair::bulid_matrix() {

    int i = 0, j = 0, k = 0;

    while (j < key.size()) {
        M[i / 5][i - i / 5 * 5] = key[j];
        i++, j++;
    }

    while(i < SIZE * SIZE) {
        if(!alphabet[k] && k != 9) { // 剩余字符(不包括J)
            M[i / 5][i - i / 5 * 5] = char(k + 65);
            i++;
        }
        k++;
    }

}

void Playfair::find_letter(int &x, int &y, char ch) {

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (M[i][j] == ch) {
                x = i, y = j;
                return;
            }
        }
    }

    x = y = -1;
    return;

}

void Playfair::delete_x () {

    for(int i = 1; i < plaintext.size() - 1; i++) {

        if (plaintext[i] == 'X' && plaintext[i - 1] == plaintext[i + 1])
            plaintext.erase(i, 1);
    }

}

#endif //INC_20180321_PLAYFAIR_H