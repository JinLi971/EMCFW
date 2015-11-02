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

void SerializationBase::operator <<(const int &value)
{
   cpyValue<int>(&value);
}

void SerializationBase::operator >>(int &value)
{
   getValue<int>(&value);
}

void SerializationBase::operator <<(const float &value)
{
   cpyValue<float>(&value);
}

void SerializationBase::operator >>(float &value)
{
   getValue<float>(&value);
}

void SerializationBase::operator <<(const double &value)
{
   cpyValue<double>(&value);
}

void SerializationBase::operator >>(double &value)
{
   getValue<double>(&value);
}

void SerializationBase::operator <<(const unsigned long &value)
{
   cpyValue<unsigned long>(&value);
}

void SerializationBase::operator >>(unsigned long &value)
{
   getValue<unsigned long>(&value);
}

void SerializationBase::operator <<(const bool &value)
{
   cpyValue<bool>(&value);
}

void SerializationBase::operator >>(bool &value)
{
   getValue<bool>(&value);
}

void SerializationBase::operator <<(const char &value)
{
   cpyValue<char>(&value);
}

void SerializationBase::operator >>(char &value)
{
   getValue<char>(&value);
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

void SerializationBase::setPackedString(const char *packedString)
{
   mPackedBytes.clear();
   mTotalLength = -1;

   memmove(&mTotalLength, packedString, sizeof(mTotalLength));

   size_t currentPtr = sizeof(mTotalLength);

   while(currentPtr != mTotalLength + sizeof(mTotalLength))
   {
      SerializeContent * serializeContent = new SerializeContent();
      memmove(&(serializeContent->length), &(packedString[currentPtr]), SIZE_T_LENGTH);

      char * payload = new char[serializeContent->length];
      memmove(payload, &(packedString[currentPtr + SIZE_T_LENGTH]), serializeContent->length);

      serializeContent->content = payload;

      mPackedBytes.push_back(serializeContent);

      currentPtr += SIZE_T_LENGTH + serializeContent->length;
   }

   assert(currentPtr == mTotalLength + sizeof(mTotalLength));
}


int SerializationBase::getTotalLength()
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
