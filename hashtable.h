#ifndef HASHMAP_H
#define HASHMAP_H

#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>
#include <QJsonObject>
#include <QFile>
#include <QJsonDocument>
#include <QString>
#include <QTableWidget>
#include <QLabel>
using namespace std;

using HashType = unsigned char;

template<typename K>
class HashMap {
public:
    HashMap() = default;
    HashMap(const HashMap& other) = default;
    ~HashMap() = default;
    void insert(const K& key,int value);
    int get(const K& key);
    int operator[](const K& key)
    {
        return get(key);
    }
    void operator<<(const K& key)
    {
        auto h = hash(key);
        auto& subVector = _map[h];
        for (auto& kv : subVector) {
            if (kv.first == key) {
                kv.second++;
                return;
            }
        }
        subVector.push_back({key, 1});
        _size++;
        return subVector.back().second;
    }
    friend bool operator==(const HashMap& h1,const HashMap& h2)
    {
        return h1._map==h2._map;
    }
    bool find(const K& key);
    void clear();
    void remove(const K& key);
    int getSize() {return _size;};
    void printToTable(QTableWidget* table) {
            for(auto& subVector : _map)
            {
                for (auto& kv : subVector)
                {
                    table->setRowCount(table->rowCount() + 1);
                    QTableWidgetItem* item = new QTableWidgetItem;
                    item->setText(QString::fromStdString(kv.first));
                    table->setItem(table->rowCount() - 1, 0, item);
                    QTableWidgetItem* item2 = new QTableWidgetItem;
                    item2->setText(QString::number(kv.second));
                    table->setItem(table->rowCount() - 1, 1, item2);
                }
            }
    }
    void loadHash(QString path);
    void saveHash(QString path);
    void findBest(QLabel* label)
    {
        int best1=0,best2=0,best3=0;
        string bestName1,bestName2,bestName3;
        for(auto& subVector : _map)
        {
            for (auto& kv : subVector)
            {
                if(kv.second>best1)
                {
                    best3=best2;
                    best2=best1;
                    best1=kv.second;
                    bestName3=bestName2;
                    bestName2=bestName1;
                    bestName1=kv.first;
                }
                else if(kv.second>best2)
                {
                    best3=best2;
                    best2=kv.second;
                    bestName3=bestName2;
                    bestName2=kv.first;
                }
                else if(kv.second>best3)
                {
                    best3=kv.second;
                    bestName3=kv.first;
                }
            }
        }
        QString finalText = QString::fromStdString(bestName1)+" - "+QString::number(best1)+", ";
        finalText+=QString::fromStdString(bestName2)+" - "+QString::number(best2)+", ";
        finalText+=QString::fromStdString(bestName3)+" - "+QString::number(best3);
        label->setText(finalText);
    }
private:
    static constexpr size_t MAX_HASH = (2 << (sizeof(HashType) * 8 - 1));
    vector<vector<pair<K,int>>> _map = vector<vector<pair<K,int>>>(MAX_HASH);
    int _size {0};
    HashType hash(const string& key) {
        HashType retVal{0};
        for (const auto c : key) {
            retVal += c;
        }
        return retVal;
    }

    HashType hash(int key) {
        return key % 256;
    }
};



template<typename K>
void HashMap<K>::insert(const K& key,int value) {
    auto h = hash(key);
    auto& subVector = _map[h];
    for (auto& kv : subVector) {
        if (kv.first == key) {
            kv.second++;
            return;
        }
    }
    subVector.push_back({key, value});
    _size++;
}

template<typename K>
int HashMap<K>::get(const K& key) {
    auto h = hash(key);
    auto& subVector = _map[h];
    for (auto& kv : subVector) {
        if (kv.first == key) {
            return kv.second;
        }
    }
    throw invalid_argument("Wrong key");
}
template<typename K>
bool HashMap<K>::find(const K& key)
{
    auto h = hash(key);
    auto& subVector = _map[h];
    for (auto& kv : subVector) {
        if (kv.first == key) {
            return true;
        }
    }
    return false;
}

template<typename K>
void HashMap<K>::remove(const K& key)
{
    auto h = hash(key);
    auto& subVector = _map[h];
    for (auto& kv : subVector) {
        if (kv.first == key) {
            subVector.clear();
            _size--;
            return;
        }
    }
}

template<typename K>
void HashMap<K>::clear()
{
    for(int i = 0;i<MAX_HASH;i++)
        _map[i].clear();
    _size=0;
}
template<typename K>
void HashMap<K>::saveHash(QString path)
{
    QJsonObject object;
    for(auto& subVector : _map)
    {
        for (auto& kv : subVector)
        {
            object.insert(QString::fromStdString(kv.first),kv.second);
        }
    }
    QFile json(path);
    QJsonDocument dataDocument;
    dataDocument.setObject(object);
    json.open(QFile::WriteOnly);
    json.write(dataDocument.toJson());
    json.close();
}

template<typename K>
void HashMap<K>::loadHash(QString path)
{
    QFile json(path);
       if(json.open(QFile::ReadOnly))
       {
           clear();
           QJsonDocument dataDocument = QJsonDocument().fromJson(json.readAll());
           QJsonObject object = dataDocument.object();
           for(QString key : object.keys())
               insert(key.toUtf8().constData(),object[key].toInt());
       }
}
#endif // HASHMAP_H
