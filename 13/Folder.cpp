#include"Folder.h"

// Message
void Message::save(Folder &f){
    // folder添加Folder列表
    folders.insert(&f);
    // 将本message添加到目录集合,注意这里的this是指针
    f.addMsg(this);
}

void Message::remove(Folder& f){
    folders.erase(&f);
    f.remMeg(this);
}
void Message::add_to_folders(const Message &m){
    // 本消息所属的每个目录集合都要添加这条消息
    for(auto f:m.folders){
        f->addMsg(this);
    }
}
void Message::remove_from_folder(){
    // 从所有目录删除本条消息
    for(auto f:folders){
        f->remMeg(this);
    }
}
// 拷贝构造函数
Message::Message(const Message& m):contents(m.contents),folders(m.folders){
    add_to_folders(m);
}
// 拷贝赋值运算符
// 注意这个拷贝赋值运算符需要保证即使自身赋值也可以正常执行
Message& Message::operator=(const Message&rhs){
    remove_from_folder();
    contents = rhs.contents;
    folders = rhs.folders;
    add_to_folders(rhs);
    return *this;
}
Message::~Message(){
    remove_from_folder();
}
void swap(Message &lhs,Message& rhs){
    using std::swap;

}



// Folder类
// 本目录下添加一条消息
void Folder::save(Message &m){
    msgs.insert(&m);
    m.addFldr(this);
}
// 本目录下删除一条消息
void Folder::remove(Message &m){
    msgs.erase(&m);
    m.remFldr(this);
}
void Folder::moveMessage(Folder *f){
    f->msgs.clear();
    for(auto m:msgs){
        m->remFldr(f);
        m->addFldr(this);
    }
}

void Folder::add_to_message(const Folder& f){
    for(auto msg:f.msgs){
        // 添加本目录到每个消息列表
        msg->addFldr(this);
    }
}
//  从每个消息中删除本目录
void Folder::remove_from_message(){
    while(!msgs.empty()){
        (*msgs.begin())->remove(*this);
    }
}
Folder::Folder(const Folder& f):msgs(f.msgs){
    add_to_message(f);
}
Folder& Folder::operator=(const Folder& rhs){
    remove_from_message();
    msgs = rhs.msgs;
    add_to_message(rhs);
    return *this;
}
Folder::~Folder(){
    remove_from_message();
}
