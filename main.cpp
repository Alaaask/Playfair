//
// Created by yu on 2018/3/26.
//

#include <iostream>
#include <fstream>
#include "cmake-build-debug/playfair.h"

using namespace std;

int main(void) {

    // 密钥 明文 密文
    string key, PLAINTEXT, plaintext, ciphertext;

    // 打开密文文件
    ifstream inFile("Playfair-密文.txt");
    if(!inFile) {
        cout << "Failed in opening the ciphertext file." << endl;
        return 0;
    }


    // 统计字母频率
    char ch;
    float frequency[26] = {0};
    while (inFile >> ch) {
        ciphertext += ch;
        frequency[int(ch) - 65]++;
    }

    for (int i = 0; i < 26; i++){
        frequency[i] = frequency[i]/ciphertext.size();
        cout << char(i + 65) << frequency[i]<< endl;
    }

    inFile.close();

    // 输入密钥
    cout << "Key:" << endl;
    cin >> key;

    // 解密
    Playfair p(ciphertext, key);
    PLAINTEXT = p.decrypt();

    // 输出大小写明文
    transform(PLAINTEXT.begin(), PLAINTEXT.end(), back_inserter(plaintext), ::tolower);
    cout << PLAINTEXT << endl << plaintext << endl;



    return 0;

}


	