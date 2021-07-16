#include "tokifiles.h"

TokiFiles::TokiFiles()
{
index=-1;
    return;
}

TokiFiles::TokiFiles(const int &_index,QByteArray &_md5)
{
    index=_index;
    qstrcpy((char*)md5,_md5.data());
}




bool TokiFiles::operator <(const TokiFiles &a){
    if((unsigned long long *)md5[0]>(unsigned long long *)a.md5[0])
        return false;
    else
        return (unsigned long long *)md5[1]<(unsigned long long *)a.md5[1];
}

bool TokiFiles::operator ==(const TokiFiles &a)
{
    return ((unsigned long long *)md5[0]==(unsigned long long *)a.md5[0])&&((unsigned long long *)md5[1]==(unsigned long long *)a.md5[1]);

}

bool TokiFiles::operator >(const TokiFiles &a)
{
    if((unsigned long long *)md5[0]<(unsigned long long *)a.md5[0])
        return false;
    else
        return (unsigned long long *)md5[1]>(unsigned long long *)a.md5[1];
}

/*bool TokiFiles::operator <(const TokiFiles &a)
{
    short i=0;
    return !((md5[i]>a.md5[i++])&&(md5[i]>a.md5[i++])&&(md5[i]>a.md5[i++])&&(md5[i]>a.md5[i++])&&(md5[i]>a.md5[i++])&&(md5[i]>a.md5[i++])&&(md5[i]>a.md5[i++])&&(md5[i]>a.md5[i++])&&(md5[i]>a.md5[i++])&&(md5[i]>a.md5[i++])&&(md5[i]>a.md5[i++])&&(md5[i]>a.md5[i++])&&(md5[i]>a.md5[i++])&&(md5[i]>a.md5[i++])&&(md5[i]>a.md5[i++])&&(md5[i]>a.md5[i++]));
}
bool TokiFiles::operator ==(const TokiFiles &a)
{
    short i=0;
    return (md5[i]==a.md5[i++])&&(md5[i]==a.md5[i++])&&(md5[i]==a.md5[i++])&&(md5[i]==a.md5[i++])&&(md5[i]==a.md5[i++])&&(md5[i]==a.md5[i++])&&(md5[i]==a.md5[i++])&&(md5[i]==a.md5[i++])&&(md5[i]==a.md5[i++])&&(md5[i]==a.md5[i++])&&(md5[i]==a.md5[i++])&&(md5[i]==a.md5[i++])&&(md5[i]==a.md5[i++])&&(md5[i]==a.md5[i++])&&(md5[i]==a.md5[i++])&&(md5[i]==a.md5[i++]);
}

bool TokiFiles::operator >(const TokiFiles &a)
{
    short i=0;
    return !((md5[i]<a.md5[i++])&&(md5[i]<a.md5[i++])&&(md5[i]<a.md5[i++])&&(md5[i]<a.md5[i++])&&(md5[i]<a.md5[i++])&&(md5[i]<a.md5[i++])&&(md5[i]<a.md5[i++])&&(md5[i]<a.md5[i++])&&(md5[i]<a.md5[i++])&&(md5[i]<a.md5[i++])&&(md5[i]<a.md5[i++])&&(md5[i]<a.md5[i++])&&(md5[i]<a.md5[i++])&&(md5[i]<a.md5[i++])&&(md5[i]<a.md5[i++])&&(md5[i]<a.md5[i++]));
}*/
