#include "serializationbase.h"
#include <iomanip>
#include <sstream>
#include <assert.h>

void SerializationBase::operator <<(const std::string &value)
{
    std::string* cpyOfString = new std::string(value.c_str());

    SerializeContent *content = new SerializeContent();
    content->length = (size_t)((cpyOfString->length() + 1) * sizeof(char));
    content->content = const_cast<char *>(cpyOfString->c_str());
    mPackedBytes.push_back(content);

    mTotalLength += SIZE_T_LENGTH + content->length;
}

void SerializationBase::operator >>(std::string &value)
{
    value.assign(mPackedBytes.front()->content);

    mTotalLength -= (SIZE_T_LENGTH + mPackedBytes.front()->length);
    mPackedBytes.pop_front();
}

void SerializationBase::operator <<(const SerializationBase &value)
{
    appendPackedString(value.getPackedString(), value.getTotalLength());
}

void SerializationBase::operator >>(SerializationBase &value)
{
    value.setPackedString(mPackedBytes.front()->content);
    mTotalLength -= (SIZE_T_LENGTH + mPackedBytes.front()->length);
    delete mPackedBytes.front();
    mPackedBytes.pop_front();
}

const char* SerializationBase::getPackedString() const
{
    char* packed = new char[mTotalLength + sizeof(mTotalLength)];

    memmove(&(packed[0]), &mTotalLength, sizeof(mTotalLength));
    size_t currentPtr = sizeof(mTotalLength);
    for(size_t i = 0; i < mPackedBytes.size(); i ++)
    {
        memmove(&(packed[currentPtr]), &(mPackedBytes.at(i)->length), SIZE_T_LENGTH);
        memmove(&(packed[currentPtr]) + SIZE_T_LENGTH, mPackedBytes.at(i)->content, mPackedBytes.at(i)->length);
        currentPtr += SIZE_T_LENGTH + mPackedBytes.at(i)->length;
    }

    assert(currentPtr == mTotalLength + sizeof(mTotalLength));

    return packed;
}

void SerializationBase::setPackedString(const char *packedString, int offset)
{
    offset < 0 ? offset = 0 : offset;
    mPackedBytes.clear();
    mTotalLength = -1;

    memmove(&mTotalLength, packedString + offset, sizeof(mTotalLength));

    size_t currentPtr = sizeof(mTotalLength) + offset;

    while(currentPtr != mTotalLength + sizeof(mTotalLength) + offset)
    {
        SerializeContent * serializeContent = new SerializeContent();
        memmove(&(serializeContent->length), &(packedString[currentPtr]), SIZE_T_LENGTH);

        char * payload = new char[serializeContent->length];
        memmove(payload, &(packedString[currentPtr + SIZE_T_LENGTH]), serializeContent->length);

        serializeContent->content = payload;

        mPackedBytes.push_back(serializeContent);

        currentPtr += SIZE_T_LENGTH + serializeContent->length;
    }

    assert(currentPtr == mTotalLength + sizeof(mTotalLength) + offset);
}

void SerializationBase::appendPackedString(const char *packedString, unsigned int start, unsigned int end)
{
    unsigned int length = end - start;

    SerializeContent *content = new SerializeContent();
    content->length = length;

    char *payload = new char[length];
    memmove(payload, packedString, length);
    content->content = payload;


    mPackedBytes.push_back(content);

    mTotalLength += length;
}

void SerializationBase::appendPackedString(const char *packedString, unsigned int size)
{
    appendPackedString(packedString, 0, size);
}


int SerializationBase::getTotalLength() const
{
    return mTotalLength;
}

void SerializationBase::clearContent()
{
    mTotalLength = 0;

    std::deque<SerializeContent *>::iterator iter = mPackedBytes.begin();

    while(iter != mPackedBytes.end())
    {
        delete *iter;
        iter ++;
    }

    mPackedBytes.clear();

    assert(mPackedBytes.size() == 0);
    assert(mTotalLength == 0);
}

SerializationBase::SerializationBase()
    : mTypeId(BASE_SERIALIZER),
      SIZE_T_LENGTH(sizeof(size_t)),
      mTotalLength(0)
{

}

SerializationBase::SerializationBase(SerializerTypeId typeId)
    : mTypeId(typeId),
      SIZE_T_LENGTH(sizeof(size_t)),
      mTotalLength(0)
{

}

SerializationBase::~SerializationBase()
{
    for(unsigned int i = 0; i < mPackedBytes.size(); ++ i)
    {
        delete mPackedBytes[i];
    }
    mPackedBytes.clear();
}

