#include "mainwindow.h"

#include <QApplication>
#include <hashtable.h>

namespace Tests {
    HashMap<string> HASHMAP;
    void TestDefautConstructor()
    {
        assert(HASHMAP.getSize() == 0);
        cout<<"Default constructor is ok"<<endl;
        HASHMAP.clear();
    }
    void TestInsert()
    {
        HASHMAP.insert("1",3);
        assert(HASHMAP.getSize() == 1);
        HASHMAP.insert("1",12);
        assert(HASHMAP.getSize() == 1);
        assert(HASHMAP["1"] == 4);
        cout<<"Insert is ok"<<endl;
        HASHMAP.clear();
    }
    void TestFind()
    {
        HASHMAP.insert("1",3);
        assert(HASHMAP.find("1"));
        assert(!HASHMAP.find("123124"));
        cout<<"Find is ok"<<endl;
        HASHMAP.clear();
    }
    void TestGet()
    {
        HASHMAP.insert("1",9);
        assert(HASHMAP["1"]==9);
        cout<<"Get is ok"<<endl;
        HASHMAP.clear();
    }
    void TestRemove()
    {
        HASHMAP.insert("1",9);
        HASHMAP.insert("2",9);
        HASHMAP.remove("1");
        assert(HASHMAP.getSize()==1);
        HASHMAP.remove("12314");
        assert(HASHMAP.getSize()==1);
        cout<<"Remove is ok"<<endl;
        assert(!HASHMAP.find("1"));
        cout<<"Find after remove is ok"<<endl;
        HASHMAP.clear();
    }
    void TestEqual()
    {
        HashMap<string> h2;
        HASHMAP.insert("1",9);
        h2.insert("1",9);
        assert(HASHMAP==h2);
        cout<<"Equal is ok"<<endl;
        HASHMAP.clear();
    }

    void TestCopy()
    {
        HASHMAP.insert("1",9);
        HASHMAP.insert("2",93);
        HashMap<string> h2(HASHMAP);
        assert(HASHMAP==h2);
        cout<<"Copy is ok"<<endl;
        HASHMAP.clear();
    }
    void TestSaveLoad()
    {
        HASHMAP.insert("1",9);
        HASHMAP.insert("2",93);
        HASHMAP.saveHash("6.json");
        HashMap<string> h2;
        h2.loadHash("6.json");
        assert(HASHMAP==h2);
        cout<<"SaveLoad is ok"<<endl;
        HASHMAP.clear();
    }
}

int main(int argc, char *argv[])
{
    Tests::TestDefautConstructor();
    Tests::TestInsert();
    Tests::TestFind();
    Tests::TestGet();
    Tests::TestRemove();
    Tests::TestEqual();
    Tests::TestCopy();
    Tests::TestSaveLoad();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
    return 0;
}
