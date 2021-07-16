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
    cout<<"请选择文件夹"<<endl;

    int RawCount=0,delCount=0,uniCount=0;

    QString RootPath=QFileDialog::getExistingDirectory(NULL,"Select a folder");
    if(!RootPath.isEmpty())
        cout<<"打开"<<RootPath.toLocal8Bit().data()<<endl;
    else
    {cout<<"未选择文件夹"<<endl;return a.exec();}


    QDir Root(RootPath);
    RootPath+='/';

    //TokiFiles f;
    //f.rootPath=RootPath;

    QHash<TokiFiles, TokiFiles> hash;

    QStringList filters;
    filters<<"*.jpg"<<"*.png"<<"*.gif";
    QStringList FileList=Root.entryList(filters);
    RawCount=FileList.size();
    cout<<"现有共"<<RawCount<<"个文件，输出文件夹下全部文件："<<endl;
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
            //cout<<"发现重复文件"<<endl;
            QFileInfo oldConfFileInfo(RootPath+FileList.at(it.value().index));
            QFileInfo curFileInfo(curFile);

            if(curFileInfo.birthTime()>oldConfFileInfo.birthTime())
            {
                curFile.remove();
                cout<<"删除了重复文件"<<FileList.at(i).toLocal8Bit().data()<<endl;
            }
            else
                if((curFileInfo.birthTime()==oldConfFileInfo.birthTime())&&(RootPath+FileList.at(it.value().index)<=FileList.at(i)))
                {
                    curFile.remove();
                    cout<<"删除了重复文件"<<FileList.at(i).toLocal8Bit().data()<<endl;
                }
            else
            {
                QFile(RootPath+FileList.at(it.value().index)).remove();
                //hash.erase(it);
                hash[cur]=cur;
                cout<<"删除了重复文件"<<FileList.at(it.value().index).toLocal8Bit().data()<<endl;
            }
            curFile.close();
            delCount++;
            continue;
        }

        hash[cur]=cur;
        uniCount++;

        //qDebug()<<"md5长度:"<<ba.size();

        curFile.close();
        //cout<<ba.toBase64().data()<<endl;
    }


    cout<<"清理完成"<<endl;
    cout<<"删除了"<<delCount<<"个重复文件，现有"<<uniCount<<"个"<<endl;
    return a.exec();
}
