#ifndef _BYTE_BUF_H_
#define _BYTE_BUF_H_

#include <vector>
#include <exception>

class bytebuf
{
private:
    unsigned int        capacity_;
    unsigned int        writeIndex_;
    unsigned int        readIndex_;
    std::vector<char>   buf_;
public:
    static const unsigned int MAX_CAPACITY = INT32_MAX;
    static const int DEFAULT_CAPACITY = 128;
public:
    bytebuf(unsigned int capacity = DEFAULT_CAPACITY);
    ~bytebuf() = default;
    bytebuf(const bytebuf& other) = default;
    bytebuf& operator=(const bytebuf& other) = default;
public:
    unsigned int writableBytes() const {return capacity_ - writeIndex_;}
    unsigned int readablebytes() const {return writeIndex_ - readIndex_;}
    bool isReadable() const {return readIndex_ > 0;}
    bool isWritable() const {return writableBytes() > 0;}
    unsigned int capacity() const {return capacity_;}
    unsigned int readIndex() const {return readIndex_;}
    unsigned int writeIndex() const {return writeIndex_;}

    template <typename T> void read(T* dest);
    template <typename T> void peek(T* dest);
    template <typename T> void write(const T& source);

    void discardReadBytes();
    void clear();
};

bytebuf::bytebuf(unsigned int capacity) 
    : capacity_(capacity > MAX_CAPACITY ? MAX_CAPACITY : capacity)
    , writeIndex_(0)
    , readIndex_(0)
    , buf_(capacity_)
{
}

template <typename T>
void bytebuf::read(T* dest)
{
    this->peek(dest);
    readIndex_ += sizeof(T);
}

template <typename T> 
void bytebuf::peek(T* dest)
{
    if(dest == 0) throw std::invalid_argument("Dest is a nullptr...");
    if(this->readablebytes() < sizeof(T)) throw std::out_of_range("Not enough bytes to read...");

    memcpy(dest, &buf_[readIndex_], sizeof(T));
}

template <typename T>
void bytebuf::write(const T& source)
{
    if(this->writableBytes < sizeof(T)) throw std::out_of_range("Not enough bytes to write...");
    memcpy(&buf_[writeIndex_], source, sizeof(T));
    writeIndex_ += sizeof(T);
}

void bytebuf::discardReadBytes()
{

}

void bytebuf::clear()
{

}

#endif // _BYTE_BUF_H_