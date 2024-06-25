# CSV.hpp 解説

このファイルは、CSVファイルの読み込みと書き込みを行うためのクラス `ReadCSV` と `WriteCSV` を提供します。以下にそれぞれのクラスとそのメンバ関数について詳しく説明します。

```cpp
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
```

## ReadCSV使用例
```cpp
#include "CSV.hpp"
#include <iostream>
#include <vector>

int main() {
    Sanae::ReadCSV reader("example.csv");
    std::string element;
    std::vector<std::string> row;

    // 1要素を読み取る
    reader >> element;
    std::cout << "Element: " << element << std::endl;

    // 1行分の要素を読み取る
    reader >> row;
    std::cout << "Row: ";
    for (const auto& elem : row) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}

```

## WriteCSV使用例
```cpp
#include "CSV.hpp"
#include <iostream>

int main() {
    Sanae::WriteCSV writer("example.csv", true);

    // 1要素を書き込む
    writer << "Hello";

    // 初期化リストのデータを書き込む
    writer << {"World", "!"};

    // バッファの内容を書き込みバッファをクリアする
    writer.Flush();

    return 0;
}

```