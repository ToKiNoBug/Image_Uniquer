#include <QCoreApplication>
#include <QApplication>
#include <iostream>
//#include <vector>
#include <QHash>
#include <QString>
#include  <QFile>
#include <QDir>
#include <QFileDialog>
#include <QCryptographicHash>

#include "tokifiles.h"
//#include <QD
using namespace std;

inline bool operator==(const TokiFiles&a,const TokiFiles &b)
{
    return ((unsigned long long *)b.md5[0]==(unsigned long long *)a.md5[0])&&((unsigned long long *)b.md5[1]==(unsigned long long *)a.md5[1]);

}

uint qHash(const TokiFiles &key, uint seed = 0) {
return ((unsigned long long *)key.md5)[0]+((unsigned long long *)key.md5)[1];
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QWidget b;
    cout<<"��ѡ���ļ���"<<endl;

    int RawCount=0,delCount=0,uniCount=0;

    QString RootPath=QFileDialog::getExistingDirectory(NULL,"Select a folder");
    if(!RootPath.isEmpty())
        cout<<"��"<<RootPath.toLocal8Bit().data()<<endl;
    else
    {cout<<"δѡ���ļ���"<<endl;return a.exec();}


    QDir Root(RootPath);
    RootPath+='/';

    //TokiFiles f;
    //f.rootPath=RootPath;

    QHash<TokiFiles, TokiFiles> hash;

    QStringList filters;
    filters<<"*.jpg"<<"*.png"<<"*.gif";
    QStringList FileList=Root.entryList(filters);
    RawCount=FileList.size();
    cout<<"���й�"<<RawCount<<"���ļ�������ļ�����ȫ���ļ���"<<endl;
    QHash<TokiFiles, TokiFiles>::iterator it;

    for(int i=0;i<FileList.size();i++)
    {
        cout<<i+1<<":  "<<FileList.at(i).toLocal8Bit().data()<<endl;
        QFile curFile(RootPath+FileList.at(i));
        curFile.open(QIODevice::ReadOnly);
        QByteArray md5 = QCryptographicHash::hash(curFile.readAll(), QCryptographicHash::Md5);

        TokiFiles cur(i,md5);
        it=hash.find(cur);
        if(it!=hash.end()&&it.value()==cur)
        {
            //cout<<"�����ظ��ļ�"<<endl;
            QFileInfo oldConfFileInfo(RootPath+FileList.at(it.value().index));
            QFileInfo curFileInfo(curFile);

            if(curFileInfo.birthTime()>oldConfFileInfo.birthTime())
            {
                curFile.remove();
                cout<<"ɾ�����ظ��ļ�"<<FileList.at(i).toLocal8Bit().data()<<endl;
            }
            else
                if((curFileInfo.birthTime()==oldConfFileInfo.birthTime())&&(RootPath+FileList.at(it.value().index)<=FileList.at(i)))
                {
                    curFile.remove();
                    cout<<"ɾ�����ظ��ļ�"<<FileList.at(i).toLocal8Bit().data()<<endl;
                }
            else
            {
                QFile(RootPath+FileList.at(it.value().index)).remove();
                //hash.erase(it);
                hash[cur]=cur;
                cout<<"ɾ�����ظ��ļ�"<<FileList.at(it.value().index).toLocal8Bit().data()<<endl;
            }
            curFile.close();
            delCount++;
            continue;
        }

        hash[cur]=cur;
        uniCount++;

        //qDebug()<<"md5����:"<<ba.size();

        curFile.close();
        //cout<<ba.toBase64().data()<<endl;
    }


    cout<<"�������"<<endl;
    cout<<"ɾ����"<<delCount<<"���ظ��ļ�������"<<uniCount<<"��"<<endl;
    return a.exec();
}
