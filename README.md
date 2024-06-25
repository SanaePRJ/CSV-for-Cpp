# CSV.hpp ���

���̃t�@�C���́ACSV�t�@�C���̓ǂݍ��݂Ə������݂��s�����߂̃N���X `ReadCSV` �� `WriteCSV` ��񋟂��܂��B�ȉ��ɂ��ꂼ��̃N���X�Ƃ��̃����o�֐��ɂ��ďڂ����������܂��B

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
    std::ifstream Ifs; // �t�@�C���ҏW�p
    bool IsNewLine = false; // ���s�t���O

    void Read(std::string*); // ��������1�v�f��ǂݎ��i�[���܂��B

public:
    ReadCSV();
    ReadCSV(const char*);
    ~ReadCSV();

    ReadCSV& Open(const char*);
    ReadCSV& Close();

    ReadCSV& operator>>(std::string&); // ��������1�v�f���i�[���܂��B
    ReadCSV& operator>>(std::vector<std::string>& Data); // ��������1�s���̗v�f���i�[���܂��B

    std::string ReadData(); // 1�v�f��ǂݎ��Ԃ��܂��B
    void ReadLine(std::vector<std::string>* Store, unsigned long long Surplus = 10); // 1�s����ǂݎ��܂��B
};

class Sanae::WriteCSV {
private:
    std::ofstream Ofs; // �ҏW�p
    std::string WriteBuffer; // �������ݗp�o�b�t�@

    void Insert(); // , ��}������B
    template<typename T> bool NewLine(T Data); // ���s���܂��B

    // �o�b�t�@�֏������݂܂��B
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

    WriteCSV& Flush(); // �o�b�t�@�̓��e���������݃o�b�t�@���N���A���܂��B
};

#endif // _INCLUDEGUARD_CSV_HPP_
```

## ReadCSV�g�p��
```cpp
#include "CSV.hpp"
#include <iostream>
#include <vector>

int main() {
    Sanae::ReadCSV reader("example.csv");
    std::string element;
    std::vector<std::string> row;

    // 1�v�f��ǂݎ��
    reader >> element;
    std::cout << "Element: " << element << std::endl;

    // 1�s���̗v�f��ǂݎ��
    reader >> row;
    std::cout << "Row: ";
    for (const auto& elem : row) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}

```

## WriteCSV�g�p��
```cpp
#include "CSV.hpp"
#include <iostream>

int main() {
    Sanae::WriteCSV writer("example.csv", true);

    // 1�v�f����������
    writer << "Hello";

    // ���������X�g�̃f�[�^����������
    writer << {"World", "!"};

    // �o�b�t�@�̓��e���������݃o�b�t�@���N���A����
    writer.Flush();

    return 0;
}

```