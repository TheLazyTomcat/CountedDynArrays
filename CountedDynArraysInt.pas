unit CountedDynArraysInt;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

interface

uses
  AuxTypes,
  CountedDynArrays;

{$DEFINE Interface}

{$DEFINE CDA_TypeInt8}
type
  {$INCLUDE '.\CDA_inc\CDA_ArrayType.inc'} = record
    Arr:    array of {$INCLUDE '.\CDA_inc\CDA_BaseType.inc'};
    Count:  Integer;
    Data:   PtrInt;
  end;
  {$INCLUDE '.\CDA_inc\CDA_PArrayType.inc'} = ^{$INCLUDE '.\CDA_inc\CDA_ArrayType.inc'};

{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_TypeInt8}

{$DEFINE CDA_TypeUInt8}
type
  {$INCLUDE '.\CDA_inc\CDA_ArrayType.inc'} = record
    Arr:    array of {$INCLUDE '.\CDA_inc\CDA_BaseType.inc'};
    Count:  Integer;
    Data:   PtrInt;
  end;
  {$INCLUDE '.\CDA_inc\CDA_PArrayType.inc'} = ^{$INCLUDE '.\CDA_inc\CDA_ArrayType.inc'};

{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_TypeUInt8}

{$DEFINE CDA_TypeInt16}
type
  {$INCLUDE '.\CDA_inc\CDA_ArrayType.inc'} = record
    Arr:    array of {$INCLUDE '.\CDA_inc\CDA_BaseType.inc'};
    Count:  Integer;
    Data:   PtrInt;
  end;
  {$INCLUDE '.\CDA_inc\CDA_PArrayType.inc'} = ^{$INCLUDE '.\CDA_inc\CDA_ArrayType.inc'};

{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_TypeInt16}

{$DEFINE CDA_TypeUInt16}
type
  {$INCLUDE '.\CDA_inc\CDA_ArrayType.inc'} = record
    Arr:    array of {$INCLUDE '.\CDA_inc\CDA_BaseType.inc'};
    Count:  Integer;
    Data:   PtrInt;
  end;
  {$INCLUDE '.\CDA_inc\CDA_PArrayType.inc'} = ^{$INCLUDE '.\CDA_inc\CDA_ArrayType.inc'};

{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_TypeUInt16}

{$DEFINE CDA_TypeInt32}
type
  {$INCLUDE '.\CDA_inc\CDA_ArrayType.inc'} = record
    Arr:    array of {$INCLUDE '.\CDA_inc\CDA_BaseType.inc'};
    Count:  Integer;
    Data:   PtrInt;
  end;
  {$INCLUDE '.\CDA_inc\CDA_PArrayType.inc'} = ^{$INCLUDE '.\CDA_inc\CDA_ArrayType.inc'};

{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_TypeInt32}

{$DEFINE CDA_TypeUInt32}
type
  {$INCLUDE '.\CDA_inc\CDA_ArrayType.inc'} = record
    Arr:    array of {$INCLUDE '.\CDA_inc\CDA_BaseType.inc'};
    Count:  Integer;
    Data:   PtrInt;
  end;
  {$INCLUDE '.\CDA_inc\CDA_PArrayType.inc'} = ^{$INCLUDE '.\CDA_inc\CDA_ArrayType.inc'};

{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_TypeUInt32}

{$DEFINE CDA_TypeInt64}
type
  {$INCLUDE '.\CDA_inc\CDA_ArrayType.inc'} = record
    Arr:    array of {$INCLUDE '.\CDA_inc\CDA_BaseType.inc'};
    Count:  Integer;
    Data:   PtrInt;
  end;
  {$INCLUDE '.\CDA_inc\CDA_PArrayType.inc'} = ^{$INCLUDE '.\CDA_inc\CDA_ArrayType.inc'};

{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_TypeInt64}

{$DEFINE CDA_TypeUInt64}
type
  {$INCLUDE '.\CDA_inc\CDA_ArrayType.inc'} = record
    Arr:    array of {$INCLUDE '.\CDA_inc\CDA_BaseType.inc'};
    Count:  Integer;
    Data:   PtrInt;
  end;
  {$INCLUDE '.\CDA_inc\CDA_PArrayType.inc'} = ^{$INCLUDE '.\CDA_inc\CDA_ArrayType.inc'};

{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_TypeUInt64}

{$UNDEF Interface}

implementation

uses
  SysUtils;

{$DEFINE Implementation}

{$DEFINE CDA_TypeInt8}
  {$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_TypeInt8}

{$DEFINE CDA_TypeUInt8}
  {$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_TypeUInt8}

{$DEFINE CDA_TypeInt16}
  {$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_TypeInt16}

{$DEFINE CDA_TypeUInt16}
  {$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_TypeUInt16}

{$DEFINE CDA_TypeInt32}
  {$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_TypeInt32}

{$DEFINE CDA_TypeUInt32}
  {$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_TypeUInt32}

{$DEFINE CDA_TypeInt64}
  {$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_TypeInt64}

{$DEFINE CDA_TypeUInt64}
  {$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_TypeUInt64}

{$UNDEF Implementation}

end.
