/*
@time 2022-5-19
@description 拷贝控制实际使用示例——消息类
@author hjx
*/
#ifndef FOLDER_H
#define FOLDER_H

#include<iostream>
#include<string>
#include<set>
class Folder;
class Message{
    friend class Folder;
public:
    //构造函数
    Message(const std::string &str = ""):contents(str){}
    // 拷贝控制成员
    Message(const Message&);
    Message& operator=(const Message&);
    // 移动控制
    Message(Message&&);
    Message& operator=(Message &&);
    ~Message();
    // 将本message成员存放在folder中、删除本Message`
    void save(Folder &f);
    void remove(Folder &f);
private:
    //实际消息文本
    std::string contents;
    std::set<Folder*> folders;
    // 工具函数
    // 添加消息到特定目录
    void add_to_folders(const Message&);
    // 删除所有目录下的此消息
    void remove_from_folder();
    // 添加和删除文件目录
    void addFldr(Folder* f){folders.insert(f);}
    void remFldr(Folder* f){folders.erase(f);}
    // 指针移动函数
    void move_Folders(Message*);
};


class Folder{
    friend class Message;
public:
    Folder() = default;
    //添加一个消息目录
    Folder(const Folder&);
    // 目录位置的转移（删除一个，增加一个）
    Folder& operator=(const Folder&);
    // 添加一条消息到消息目录
    void save(Message& );
    // 移除此目录的此消息
    void remove(Message&);
    ~Folder();
private:
    // 消息目录
    std::set<Message*> msgs;
    //在该目录下添加或者删除消息
    void addMsg(Message* m){msgs.insert(m);}
    void remMeg(Message* m){msgs.erase(m);}
    // 目录添加消息
    void add_to_message(const Folder&);
    // 在每个消息文件下移除这个目录
    void remove_from_message();
    // 改变消息指针指向本Folder
    void moveMessage(Folder*);
};
#endif