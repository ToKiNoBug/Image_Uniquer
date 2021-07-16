#ifndef TOKIFILES_H
#define TOKIFILES_H
#include <QCoreApplication>
#include <QApplication>
#include <iostream>
#include <vector>
#include <hash_map>
#include <QString>
#include  <QFile>
#include <QDir>
#include <QFileDialog>
#include <QCryptographicHash>

class TokiFiles
{
public:
    //static QString rootPath;
    TokiFiles();
    TokiFiles(const int &_index,QByteArray &_md5);
    int index;
    unsigned char md5[16];

    //bool same(const TokiFiles & another);
    bool operator <(const TokiFiles & another);
    bool operator ==(const TokiFiles & another);
    bool operator >(const TokiFiles & another);

};

#endif // TOKIFILES_H
