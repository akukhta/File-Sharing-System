#ifndef REQUESTWRITTER_H
#define REQUESTWRITTER_H
#include <vector>
#include <iostream>
#include <memory>

class RequestWritter
{
public:
    RequestWritter(){;};

     template<class T,typename std::enable_if_t<std::is_fundamental<T>::value>* = nullptr>
     void write(T const & arg)
     {
        char const *dataPtr = reinterpret_cast<char const *>(&arg);
        for (size_t i = 0; i < sizeof(T); i++)
            buffer.push_back(dataPtr[i]);
     }

     template<class T, typename std::enable_if_t<std::is_same<std::vector<char>,T>::value>* = nullptr>
     void write(std::vector<char> const &arg)
     {
         size_t blockSize = arg.size();
         write<size_t>(blockSize);
         for (auto i : arg)
             buffer.push_back(i);
     }

     template<class T, typename std::enable_if_t<std::is_same<std::string,T>::value>* = nullptr>
     void write(std::string const& arg)
     {
         write<std::vector<char>>(std::vector<char>(arg.begin(),arg.end()));
     }

     std::vector<char>  getBuffer()
     {
         return buffer;
     }

private:
     std::vector<char> buffer;
};

#endif // REQUESTWRITTER_H
