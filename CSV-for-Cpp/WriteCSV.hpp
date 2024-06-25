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




#ifndef _INCLUDEGUARD_WRITECSV_HPP_
#define _INCLUDEGUARD_WRITECSV_HPP_




#include "CSV.hpp"




// , ‚ð’Ç‰Á‚·‚éB
void Sanae::WriteCSV::Insert() {
    if (this->WriteBuffer.size() != 0) {
        char buf = *(this->WriteBuffer.end() - 1);
        if (buf != ',' && buf != '\n')
            this->WriteBuffer += ',';
    }
}


template<typename T>bool Sanae::WriteCSV::NewLine
(
    T Data
)
{
    std::string Buffer;
    Buffer = Data;

    bool IsChar =
    {
        typeid(T) == typeid(std::string)
        or
        typeid(T) == typeid(const char*)
        or
        typeid(T) == typeid(const char)
        or
        typeid(T) == typeid(char*)
        or
        typeid(T) == typeid(char)
    };

    if (IsChar and Buffer == (std::string)"\n") {
        WriteBuffer += '\n';

        this->Ofs.write(WriteBuffer.c_str(), WriteBuffer.size());
        WriteBuffer.clear();
        return true;
    }
    return false;
}


template<typename T, class Dummy>
void Sanae::WriteCSV::BufferWrite(T Data) {
    if (NewLine(Data))
        return;

    Insert();
    this->WriteBuffer += std::to_string(Data);
}


void Sanae::WriteCSV::BufferWrite(const char* Data) {
    if (NewLine(Data))
        return;

    Insert();
    this->WriteBuffer += Data;
}


void Sanae::WriteCSV::BufferWrite(std::string Data) {
    if (NewLine(Data))
        return;

    Insert();
    this->WriteBuffer += Data;
}


Sanae::WriteCSV::WriteCSV(const char* FileName, bool DoInit) {
    if (DoInit)
        this->Ofs.open(FileName, std::ios::out);
    else
        this->Ofs.open(FileName, std::ios::app);

    if (!this->Ofs.is_open())
        throw std::runtime_error("Can't open file.");
}


Sanae::WriteCSV::~WriteCSV() {
    this->Close();
}


Sanae::WriteCSV& Sanae::WriteCSV::Open(const char* FileName, bool DoInit) {
    if (DoInit)
        this->Ofs.open(FileName, std::ios::out);
    else
        this->Ofs.open(FileName, std::ios::app);

    if (!this->Ofs.is_open())
        throw std::runtime_error("Can't open file.");
    return *this;
}


Sanae::WriteCSV& Sanae::WriteCSV::Close() {
    this->Ofs << this->WriteBuffer.c_str();
    this->WriteBuffer.clear();
    this->Ofs.close();
    return *this;
}


template<typename DataType>
Sanae::WriteCSV& Sanae::WriteCSV::operator<<(DataType Data) {
    this->BufferWrite(Data);
    return *this;
}


template<typename DataType>
Sanae::WriteCSV& Sanae::WriteCSV::operator<<(std::initializer_list<DataType> DataList) {
    for (DataType i : DataList)
        this->BufferWrite(i);
    return *this;
}


Sanae::WriteCSV& Sanae::WriteCSV::Flush() {
    if (WriteBuffer.size() >= 1) {
        this->Ofs << std::string(WriteBuffer.begin(), WriteBuffer.end() - 1);
        WriteBuffer.erase(WriteBuffer.begin(), WriteBuffer.end() - 1);
    }
    this->Ofs.flush();
    return *this;
}




#endif // _INCLUDEGUARD_WRITECSV_HPP_