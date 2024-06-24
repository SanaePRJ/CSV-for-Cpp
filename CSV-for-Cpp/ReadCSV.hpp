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




#ifndef _INCLUDEGUARD_READCSV_HPP_
#define _INCLUDEGUARD_READCSV_HPP_




#include "CSV.hpp"




void Sanae::ReadCSV::Read
(
    std::string* Data
)
{
    if (!Ifs.is_open())
        throw std::runtime_error("Must be open.");

    while (true) {
        unsigned char buffer = 0;
        this->Ifs.read((char*)&buffer, sizeof(unsigned char));

        if (buffer == '\n')
            this->IsNewLine = true;
        else
            this->IsNewLine = false;

        if (buffer == ',' or buffer == '\n' or Ifs.eof())
            break;

        *Data += buffer;
    }
}


Sanae::ReadCSV::ReadCSV() {}

Sanae::ReadCSV::ReadCSV
(
    const char* FileName
)
{
    Ifs.open(FileName, std::ios_base::in);
    if (!Ifs)
        throw std::runtime_error("Can't open file.");
}

Sanae::ReadCSV::~ReadCSV() {
    Ifs.close();
}


Sanae::ReadCSV& Sanae::ReadCSV::Open
(
    const char* FileName
)
{
    Ifs.close();
    Ifs.open(FileName, std::ios_base::in);
    if (!Ifs)
        throw std::runtime_error("Can't open file.");

    return *this;
}


Sanae::ReadCSV& Sanae::ReadCSV::Close() {
    Ifs.close();
    return *this;
}


Sanae::ReadCSV& Sanae::ReadCSV::operator>>
(
    std::string& Data
)
{
    Data = this->ReadData();
    return *this;
}


Sanae::ReadCSV& Sanae::ReadCSV::operator>>
(
    std::vector<std::string>& Data
)
{
    this->ReadLine(&Data);
    return *this;
}


std::string Sanae::ReadCSV::ReadData() {
    std::string data;
    this->Read(&data);
    return data;
}


void Sanae::ReadCSV::ReadLine
(
    std::vector<std::string>* Store, 
    unsigned long long Surplus
)
{
    this->IsNewLine = false;
    while (!this->IsNewLine) {
        if (Store->size() + 1 >= Store->capacity())
            Store->reserve(Surplus);

        Store->push_back(this->ReadData());
    }
    this->IsNewLine = false;
}




#endif // _INCLUDEGUARD_READCSV_HPP_