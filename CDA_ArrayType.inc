{$IF Defined(CDA_TypeBool)}
TBooleanCountedDynArray
{$ELSEIF Defined(CDA_TypeInteger)}
TIntegerCountedDynArray
{$ELSEIF Defined(CDA_TypeDateTime)}
TDateTimeCountedDynArray
{$ELSEIF Defined(CDA_TypeString)}
TStringCountedDynArray
{$ELSEIF Defined(CDA_TypePointer)}
TPointerCountedDynArray
{$ELSEIF Defined(CDA_TypeObject)}
TObjectCountedDynArray 
{$ELSEIF Defined(CDA_TypeInt8)}
TInt8CountedDynArray
{$ELSEIF Defined(CDA_TypeUInt8)}
TUInt8CountedDynArray
{$ELSEIF Defined(CDA_TypeInt16)}
TInt16CountedDynArray
{$ELSEIF Defined(CDA_TypeUInt16)}
TUInt16CountedDynArray
{$ELSEIF Defined(CDA_TypeInt32)}
TInt32CountedDynArray
{$ELSEIF Defined(CDA_TypeUInt32)}
TUInt32CountedDynArray
{$ELSEIF Defined(CDA_TypeInt64)}
TInt64CountedDynArray
{$ELSEIF Defined(CDA_TypeUInt64)}
TUInt64CountedDynArray
{$ELSEIF Defined(CDA_TypeFloat32)}
TFloat32CountedDynArray
{$ELSEIF Defined(CDA_TypeFloat64)}
TFloat64CountedDynArray 
{$ELSE}
  {$MESSAGE FATAL 'Unknown array type.'}
{$IFEND}