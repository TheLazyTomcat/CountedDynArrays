unit CountedDynArraysExt;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

interface

uses
  AuxTypes,
  CountedDynArrays;

{$DEFINE CDA_TypeInt8}
type
  {$INCLUDE '.\CDA_ArrayType.inc'} = record
    Arr:    array of {$INCLUDE '.\CDA_BaseType.inc'};
    Count:  Integer;
    Data:   PtrInt;
  end;
  {$INCLUDE '.\CDA_PArrayType.inc'} = ^{$INCLUDE '.\CDA_ArrayType.inc'};

{$INCLUDE '.\CDA_Interface.inc'} 
{$UNDEF CDA_TypeInt8}

{$DEFINE CDA_TypeUInt8}
type
  {$INCLUDE '.\CDA_ArrayType.inc'} = record
    Arr:    array of {$INCLUDE '.\CDA_BaseType.inc'};
    Count:  Integer;
    Data:   PtrInt;
  end;
  {$INCLUDE '.\CDA_PArrayType.inc'} = ^{$INCLUDE '.\CDA_ArrayType.inc'};

{$INCLUDE '.\CDA_Interface.inc'} 
{$UNDEF CDA_TypeUInt8}

{$DEFINE CDA_TypeInt16}
type
  {$INCLUDE '.\CDA_ArrayType.inc'} = record
    Arr:    array of {$INCLUDE '.\CDA_BaseType.inc'};
    Count:  Integer;
    Data:   PtrInt;
  end;
  {$INCLUDE '.\CDA_PArrayType.inc'} = ^{$INCLUDE '.\CDA_ArrayType.inc'};

{$INCLUDE '.\CDA_Interface.inc'}
{$UNDEF CDA_TypeInt16}

{$DEFINE CDA_TypeUInt16}
type
  {$INCLUDE '.\CDA_ArrayType.inc'} = record
    Arr:    array of {$INCLUDE '.\CDA_BaseType.inc'};
    Count:  Integer;
    Data:   PtrInt;
  end;
  {$INCLUDE '.\CDA_PArrayType.inc'} = ^{$INCLUDE '.\CDA_ArrayType.inc'};

{$INCLUDE '.\CDA_Interface.inc'}
{$UNDEF CDA_TypeUInt16}

{$DEFINE CDA_TypeInt32}
type
  {$INCLUDE '.\CDA_ArrayType.inc'} = record
    Arr:    array of {$INCLUDE '.\CDA_BaseType.inc'};
    Count:  Integer;
    Data:   PtrInt;
  end;
  {$INCLUDE '.\CDA_PArrayType.inc'} = ^{$INCLUDE '.\CDA_ArrayType.inc'};

{$INCLUDE '.\CDA_Interface.inc'}
{$UNDEF CDA_TypeInt32}

{$DEFINE CDA_TypeUInt32}
type
  {$INCLUDE '.\CDA_ArrayType.inc'} = record
    Arr:    array of {$INCLUDE '.\CDA_BaseType.inc'};
    Count:  Integer;
    Data:   PtrInt;
  end;
  {$INCLUDE '.\CDA_PArrayType.inc'} = ^{$INCLUDE '.\CDA_ArrayType.inc'};

{$INCLUDE '.\CDA_Interface.inc'}
{$UNDEF CDA_TypeUInt32}

{$DEFINE CDA_TypeInt64}
type
  {$INCLUDE '.\CDA_ArrayType.inc'} = record
    Arr:    array of {$INCLUDE '.\CDA_BaseType.inc'};
    Count:  Integer;
    Data:   PtrInt;
  end;
  {$INCLUDE '.\CDA_PArrayType.inc'} = ^{$INCLUDE '.\CDA_ArrayType.inc'};

{$INCLUDE '.\CDA_Interface.inc'}
{$UNDEF CDA_TypeInt64}

{$DEFINE CDA_TypeUInt64}
type
  {$INCLUDE '.\CDA_ArrayType.inc'} = record
    Arr:    array of {$INCLUDE '.\CDA_BaseType.inc'};
    Count:  Integer;
    Data:   PtrInt;
  end;
  {$INCLUDE '.\CDA_PArrayType.inc'} = ^{$INCLUDE '.\CDA_ArrayType.inc'};

{$INCLUDE '.\CDA_Interface.inc'}
{$UNDEF CDA_TypeUInt64}

{$DEFINE CDA_TypeFloat32}
type
  {$INCLUDE '.\CDA_ArrayType.inc'} = record
    Arr:    array of {$INCLUDE '.\CDA_BaseType.inc'};
    Count:  Integer;
    Data:   PtrInt;
  end;
  {$INCLUDE '.\CDA_PArrayType.inc'} = ^{$INCLUDE '.\CDA_ArrayType.inc'};

{$INCLUDE '.\CDA_Interface.inc'}
{$UNDEF CDA_TypeFloat32}

{$DEFINE CDA_TypeFloat64}
type
  {$INCLUDE '.\CDA_ArrayType.inc'} = record
    Arr:    array of {$INCLUDE '.\CDA_BaseType.inc'};
    Count:  Integer;
    Data:   PtrInt;
  end;
  {$INCLUDE '.\CDA_PArrayType.inc'} = ^{$INCLUDE '.\CDA_ArrayType.inc'};

{$INCLUDE '.\CDA_Interface.inc'}
{$UNDEF CDA_TypeFloat64}

implementation

uses
  SysUtils;

{$DEFINE CDA_TypeInt8}
  {$INCLUDE '.\CDA_Implementation.inc'}
{$UNDEF CDA_TypeInt8}

{$DEFINE CDA_TypeUInt8}
  {$INCLUDE '.\CDA_Implementation.inc'}
{$UNDEF CDA_TypeUInt8}

{$DEFINE CDA_TypeInt16}
  {$INCLUDE '.\CDA_Implementation.inc'}
{$UNDEF CDA_TypeInt16}

{$DEFINE CDA_TypeUInt16}
  {$INCLUDE '.\CDA_Implementation.inc'}
{$UNDEF CDA_TypeUInt16}

{$DEFINE CDA_TypeInt32}
  {$INCLUDE '.\CDA_Implementation.inc'}
{$UNDEF CDA_TypeInt32}

{$DEFINE CDA_TypeUInt32}
  {$INCLUDE '.\CDA_Implementation.inc'}
{$UNDEF CDA_TypeUInt32}

{$DEFINE CDA_TypeInt64}
  {$INCLUDE '.\CDA_Implementation.inc'}
{$UNDEF CDA_TypeInt64}

{$DEFINE CDA_TypeUInt64}
  {$INCLUDE '.\CDA_Implementation.inc'}
{$UNDEF CDA_TypeUInt64}

{$DEFINE CDA_TypeFloat32}
  {$INCLUDE '.\CDA_Implementation.inc'}
{$UNDEF CDA_TypeFloat32}

{$DEFINE CDA_TypeFloat64}
  {$INCLUDE '.\CDA_Implementation.inc'}
{$UNDEF CDA_TypeFloat64}

end.
