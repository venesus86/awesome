/*
 아래의 main 함수 코드가 실행 될 수 있도록 File 및 Folder 클래스를 만들어 주세요
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class IData
{
public:
    virtual size_t getSize() const = 0;
    virtual void print() const = 0;
    virtual ~IData() {}
};

class Folder : public IData
{
    string m_title;
    vector<IData*> v;

public:
    Folder(string title) { m_title = "[" + title + "]"; }
    virtual ~Folder()
    {
        for (const auto& d : v)
            d->~IData();
    }

    void add(IData* data)
    {
        v.push_back(data);
    }

    virtual size_t getSize() const override
    {
        size_t total_size = 0;
        for (const auto& d : v)
            total_size += d->getSize();
        return total_size;
    }

    virtual void print() const override
    {
        cout << m_title << endl;
        for (const auto& d : v)
            d->print();
    }
};

class File : public IData
{
    string m_title;
    size_t m_size;

public:
    File(string title, size_t size) : m_title(title), m_size(size) {}
    ~File() {}

    virtual size_t getSize() const override
    {
        return m_size;
    }

    virtual void print() const override
    {
        cout << "(" << m_title << ", " << m_size << ")" << endl;
    }
};

int main()
{
    // 조건 1. Folder와 File의 객체를 생성할 수 있어야 합니다.
    Folder *rootFolder = new Folder("ROOT"); // 폴더는 이름만 있습니다.
    Folder *aaaaFolder = new Folder("AAAA");
    Folder *bbbbFolder = new Folder("BBBB");
    File *file1 = new File("a.txt", 10); // 화일은 이름과 크기가 있습니다
    File *file2 = new File("b.txt", 20);
    File *file3 = new File("c.txt", 30);
    File *file4 = new File("d.txt", 40);
    // 조건 2. 폴더안에 파일 및 다른 폴더를 넣을 수 있어야 합니다.
    rootFolder->add(aaaaFolder);
    rootFolder->add(bbbbFolder);
    rootFolder->add(file1);
    aaaaFolder->add(file2);
    aaaaFolder->add(file3);
    bbbbFolder->add(file4);
    // 조건 3. 파일과 폴더 크기를 출력할 수 있어야 합니다.
    // 폴더는 자신만의 크기는 없지만 크기를 구할 수 는 있습니다.
    cout << file1->getSize() << endl;      // 10
    cout << aaaaFolder->getSize() << endl; // 50
    cout << rootFolder->getSize() << endl; // 100
    // 조건 4. 화면 출력
    file1->print(); // 파일이므로 이름과 크기만 출력해 주세요.
    // ex) (a.txt, 10)
    rootFolder->print(); // ROOT폴더 전체의 모양을 보기좋게 출력해 주세요
    // [ROOT]
    // [AAAA]
    // (b.txt, 20)
    // (b.txt, 30)
    // [BBBB]
    // (d.txt, 40)
    // (a.txt, 10)
    // 조건 5. 폴더 제거시 폴더 안에 있는 모든 파일과 폴더가 제거 되게 해주세요
    delete rootFolder;
}