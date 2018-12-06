{$IF Defined(CDA_TypeBool)}
Boolean
{$ELSEIF Defined(CDA_TypeInteger)}
Integer         
{$ELSEIF Defined(CDA_TypeDateTime)}
TDateTime
{$ELSEIF Defined(CDA_TypeString)}
String
{$ELSEIF Defined(CDA_TypePointer)}
Pointer
{$ELSEIF Defined(CDA_TypeObject)}
TObject 
{$ELSEIF Defined(CDA_TypeInt8)}
Int8
{$ELSEIF Defined(CDA_TypeUInt8)}
UInt8
{$ELSEIF Defined(CDA_TypeInt16)}
Int16
{$ELSEIF Defined(CDA_TypeUInt16)}
UInt16
{$ELSEIF Defined(CDA_TypeInt32)}
Int32
{$ELSEIF Defined(CDA_TypeUInt32)}
UInt32
{$ELSEIF Defined(CDA_TypeInt64)}
Int64
{$ELSEIF Defined(CDA_TypeUInt64)}
UInt64
{$ELSEIF Defined(CDA_TypeFloat32)}
Float32
{$ELSEIF Defined(CDA_TypeFloat64)}
Float64 
{$ELSE}
  {$MESSAGE FATAL 'Unknown base type.'}
{$IFEND}