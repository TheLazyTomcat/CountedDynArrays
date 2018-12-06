{$IFDEF FPC}
  {$MODE ObjFPC}{$H+}
  {$INLINE ON}
  {$DEFINE CanInline}
{$ELSE}
  {$IF CompilerVersion >= 17 then}  // Delphi 2005+
    {$DEFINE CanInline}
  {$ELSE}
    {$UNDEF CanInline}
  {$IFEND}
{$ENDIF}

{$UNDEF CDA_TypeBool}
{$UNDEF CDA_TypeInteger}
{$UNDEF CDA_TypeDateTime}
{$UNDEF CDA_TypeString}
{$UNDEF CDA_TypePointer}
{$UNDEF CDA_TypeObject}

{$UNDEF CDA_TypeInt8}
{$UNDEF CDA_TypeUInt8}
{$UNDEF CDA_TypeInt16}
{$UNDEF CDA_TypeUInt16}
{$UNDEF CDA_TypeInt32}
{$UNDEF CDA_TypeUInt32}
{$UNDEF CDA_TypeInt64}
{$UNDEF CDA_TypeUInt64}
{$UNDEF CDA_TypeFloat32}
{$UNDEF CDA_TypeFloat64}

