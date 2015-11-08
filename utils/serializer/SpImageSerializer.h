#ifndef SPIMAGESERIALIZER_HH
#define SPIMAGESERIALIZER_HH

#include "utils/serializer/serializationbase.h"

class SpImageSerializer : public SerializationBase
{
public:
   SpImageSerializer();

   typedef enum
   {
      ARRAY_START = 0,
      ARRAY_END
   }ArrayIndicator;

   typedef enum
   {
      STRUCT_START = 0,
      STRUCT_END
   }StructIndicator;


   void packSpMatrixes(StructIndicator)
   {
   }

   template<typename...Argus>
   void packSpMatrixes(StructIndicator, Argus... argus)
   {
      packSpMatrixes(argus...);
   }

   template<typename BasicType, typename...Argus>
   void packSpMatrixes(BasicType value, Argus... argus)
   {
      cpyValue<BasicType>(&value);
      packSpMatrixes(argus...);
   }

   template<typename ArrayType, typename...Argus>
   void packSpMatrixes(ArrayIndicator /*indicator*/, unsigned long value, ArrayType* payload, ArrayIndicator /*indicator*/, Argus... argus)
   {
      packPureArray<ArrayType>(value, payload);
      packSpMatrixes(argus...);
   }

   void unpackSpMatrix(StructIndicator)
   {
   }

   template<typename...Argus>
   void unpackSpMatrix(StructIndicator, Argus... argus)
   {
      unpackSpMatrix(argus...);
   }

   template<typename BasicType, typename...Argus>
   void unpackSpMatrix(BasicType * value, Argus... argus)
   {
      getValue<BasicType>(value);      
      unpackSpMatrix(argus...);
   }

   template<typename ArrayType, typename...Argus>
   void unpackSpMatrix(ArrayType ** value, Argus... argus)
   {
      unpackPureArray<ArrayType>(*value);      
      unpackSpMatrix(argus...);
   }

private:
   bool mIsArrayStart;
   int mArrayLength;

};

#endif // SPIMAGESERIALIZER_HH
