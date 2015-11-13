#ifndef SERIALIZATIONBASE_H
#define SERIALIZATIONBASE_H

#include <cstring>
#include <string>
#include <deque>
#include <stdio.h>
#include "GlobalClassId.hh"

class SerializationBase
{
public:
   enum SerializerTypeId
   {
      BASE_SERIALIZER = 0,
      SPIMAGE
   };

   SerializationBase();
   SerializationBase(SerializerTypeId typeId);

   virtual ~SerializationBase() {}

   virtual void operator <<(const std::string& value);
   virtual void operator >>(std::string &value);

   virtual void operator <<(const int& value);
   virtual void operator >>(int &value);

   virtual void operator <<(const float& value);
   virtual void operator >>(float& value);

   virtual void operator <<(const bool& value);
   virtual void operator >>(bool& value);

   virtual void operator <<(const char& value);
   virtual void operator >>(char& value);

   virtual void operator <<(const double &value);
   virtual void operator >>(double &value);

   virtual void operator <<(const unsigned long &value);
   virtual void operator >>(unsigned long &value);

   virtual void operator <<(const unsigned int &value);
   virtual void operator >>(unsigned int &value);

   virtual void operator <<(const GlobalClassId::ClassId &value);
   virtual void operator >>(GlobalClassId::ClassId &value);

   template<typename ArrayType>
   void packPureArray(const int arrayLength, const ArrayType *payload)
   {
      SerializeContent *content = new SerializeContent();

      content->length = (size_t)(arrayLength * sizeof(ArrayType));
      char* byteArray = new char[content->length];

      memmove(byteArray, payload, content->length);
      content->content = byteArray;

      mPackedBytes.push_back(content);

      mTotalLength += SIZE_T_LENGTH + content->length;
   }

   template<typename ArrayType>
   size_t unpackPureArray(ArrayType * &value)
   {
      unsigned int length = mPackedBytes.front()->length/sizeof(ArrayType);

      ArrayType* returnInstance = new ArrayType[length];

      memmove(returnInstance, mPackedBytes.front()->content, mPackedBytes.front()->length);
      mTotalLength -= (SIZE_T_LENGTH + mPackedBytes.front()->length);
      mPackedBytes.pop_front();

      value = returnInstance;

      return length;
   }

   virtual const char *getPackedString() const;
   virtual void setPackedString(const char* packedString, int offset = 0);

   virtual int getTotalLength() const;
   virtual int getHeadLength() const  { return sizeof(mTotalLength); }

   virtual int getSize() const { return getTotalLength() + getHeadLength(); }

   virtual void clearContent();

   virtual SerializerTypeId getTypeId() const { return mTypeId; }


protected:

   SerializerTypeId mTypeId;

   int SIZE_T_LENGTH;

   size_t mTotalLength;

   typedef struct
   {
      size_t length;
      char * content;
   }SerializeContent;

   std::deque<SerializeContent *> mPackedBytes;

   template <typename T>
   void cpyValue(const T* value)
   {
      size_t eleLength = sizeof(*value);
      SerializeContent *content = new SerializeContent();
      content->length = eleLength;

      char *byteArray = new char[eleLength];
      memmove(byteArray, value, eleLength);

      content->content = byteArray;

      mPackedBytes.push_back(content);
      mTotalLength += SIZE_T_LENGTH + eleLength;
   }

   template <typename T>
   void getValue(T* value)
   {
      memset(value, 0, sizeof(*value));
      memmove(value, mPackedBytes.front()->content, sizeof(*value));

      mTotalLength -= (SIZE_T_LENGTH + mPackedBytes.front()->length);
      mPackedBytes.pop_front();
   }
};

#endif // SERIALIZATIONBASE_H
