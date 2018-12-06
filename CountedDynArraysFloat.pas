unit CountedDynArraysFloat;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

interface

uses
  AuxTypes,
  CountedDynArrays;

{$DEFINE Interface}

{$DEFINE CDA_TypeFloat32}
type
  {$INCLUDE '.\CDA_inc\CDA_ArrayType.inc'} = record
    Arr:    array of {$INCLUDE '.\CDA_inc\CDA_BaseType.inc'};
    Count:  Integer;
    Data:   PtrInt;
  end;
  {$INCLUDE '.\CDA_inc\CDA_PArrayType.inc'} = ^{$INCLUDE '.\CDA_inc\CDA_ArrayType.inc'};

{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_TypeFloat32}

{$DEFINE CDA_TypeFloat64}
type
  {$INCLUDE '.\CDA_inc\CDA_ArrayType.inc'} = record
    Arr:    array of {$INCLUDE '.\CDA_inc\CDA_BaseType.inc'};
    Count:  Integer;
    Data:   PtrInt;
  end;
  {$INCLUDE '.\CDA_inc\CDA_PArrayType.inc'} = ^{$INCLUDE '.\CDA_inc\CDA_ArrayType.inc'};

{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_TypeFloat64}

{$UNDEF Interface}

implementation

uses
  SysUtils;

{$DEFINE Implementation}

{$DEFINE CDA_TypeFloat32}
  {$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_TypeFloat32}

{$DEFINE CDA_TypeFloat64}
  {$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_TypeFloat64}

{$UNDEF Implementation}

end.
