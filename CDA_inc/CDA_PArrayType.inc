{$IF Defined(CDA_TypeBool)}
PBooleanCountedDynArray
{$ELSEIF Defined(CDA_TypeInteger)}
PIntegerCountedDynArray
{$ELSEIF Defined(CDA_TypeDateTime)}
PDateTimeCountedDynArray
{$ELSEIF Defined(CDA_TypeString)}
PStringCountedDynArray
{$ELSEIF Defined(CDA_TypePointer)}
PPointerCountedDynArray
{$ELSEIF Defined(CDA_TypeObject)}
PObjectCountedDynArray 
{$ELSEIF Defined(CDA_TypeInt8)}
PInt8CountedDynArray
{$ELSEIF Defined(CDA_TypeUInt8)}
PUInt8CountedDynArray
{$ELSEIF Defined(CDA_TypeInt16)}
PInt16CountedDynArray
{$ELSEIF Defined(CDA_TypeUInt16)}
PUInt16CountedDynArray
{$ELSEIF Defined(CDA_TypeInt32)}
PInt32CountedDynArray
{$ELSEIF Defined(CDA_TypeUInt32)}
PUInt32CountedDynArray
{$ELSEIF Defined(CDA_TypeInt64)}
PInt64CountedDynArray
{$ELSEIF Defined(CDA_TypeUInt64)}
PUInt64CountedDynArray
{$ELSEIF Defined(CDA_TypeFloat32)}
PFloat32CountedDynArray
{$ELSEIF Defined(CDA_TypeFloat64)}
PFloat64CountedDynArray 
{$ELSE}
  {$MESSAGE FATAL 'Unknown array type.'}
{$IFEND}