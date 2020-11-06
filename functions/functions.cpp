#include "functions.h"
string ArturoHash(string inputString)
{
    auto start=std::chrono::high_resolution_clock::now();
    int keys[]= {3,5,7,11,13,17,19,23};
    unsigned long long sum=0x54e55;
    for(int i=0; i<inputString.size(); i++)
    {
        sum^=(sum<<keys[i%8])+inputString[i]+(sum>>keys[(i+1)%8]);
    }
    sum = ((sum >> 8) ^ sum) * k[0];//0x45d9f3b;
    sum = ((sum << 8) ^ sum) * k[1];//0x45d9f3b;
    sum = (sum >> 8) ^ sum;
    auto end=std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff=end-start;
    //cout<<std::hex<<sum<<std::dec<<endl;
    //std::cout<<"Hashavimas uztruko: "<<diff.count()<<endl;
    stringstream stream;
    for(int i=0;i<4;i++)
    {
        stream<<hex<<sum*k[i];
    }
//    while(stream.str().size()<64)
//    {
//        stream<<hex<<sum*k[stream.str().size()%16];
//    }
//    while(stream.str().size()>64)
//    {
//        stream.str().erase(stream.str().size()-1);
//    }
    //cout<<stream.str().size()<<endl;
    int i=0;
    string result;
    while(stream.str().size()<64)
    {
        stream<<hex<<sum*k[i%64];
        i++;
    }
    result=stream.str();
    while(result.size()>64)
    {
        result=result.substr(0,result.size()-1);
    }
    //cout<<result<<" "<<result.size()<<endl;
    return result;
}
