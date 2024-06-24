/* ---------------------------------------------------------------------------------------------
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 --------------------------------------------------------------------------------------------- */




#ifndef _INCLUDEGUARD_CSV_HPP_
#define _INCLUDEGUARD_CSV_HPP_




#include "CppVer.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>




namespace Sanae {
    class ReadCSV;
    class WriteCSV;
}


class Sanae::ReadCSV {
private:
    std::ifstream Ifs; // ファイル編集用
    bool IsNewLine = false; // 改行フラグ

    void Read(std::string*); // 第一引数に1要素を読み取り格納します。

public:
    ReadCSV();
    ReadCSV(const char*);
    ~ReadCSV();

    ReadCSV& Open(const char*);
    ReadCSV& Close();

    ReadCSV& operator>>(std::string&); // 第一引数に1要素を格納します。
    ReadCSV& operator>>(std::vector<std::string>& Data); // 第一引数に1行分の要素を格納します。

    std::string ReadData(); // 1要素を読み取り返します。
    void ReadLine(std::vector<std::string>* Store, unsigned long long Surplus = 10); // 1行分を読み取ります。
};


class Sanae::WriteCSV {
private:
    std::ofstream Ofs; // 編集用
    std::string WriteBuffer; // 書き込み用バッファ

    void Insert(); // , を挿入する。
    template<typename T> bool NewLine(T Data); // 改行します。

    // バッファへ書き込みます。
    template<typename T, class Dummy = void> void BufferWrite(T Data);
    void BufferWrite(const char* Data);
    void BufferWrite(std::string Data);

public:
    WriteCSV(const char*, bool);
    ~WriteCSV();

    WriteCSV& Open(const char*, bool);
    WriteCSV& Close();

    template<typename DataType> WriteCSV& operator<<(DataType Data);
    template<typename DataType> WriteCSV& operator<<(std::initializer_list<DataType> DataList);

    WriteCSV& Flush(); // バッファの内容を書き込みバッファをクリアします。
};




#endif // _INCLUDEGUARD_CSV_HPP_