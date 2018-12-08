unit CountedDynArraysUInt8;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

interface

uses
  AuxTypes,
  CountedDynArrays;

type
  TUInt8CountedDynArray = record
    Arr:    array of UInt8;
    Count:  Integer;
    Data:   PtrInt;
  end;
  PUInt8CountedDynArray = ^TUInt8CountedDynArray;

  TBaseType = UInt8;
  TArrayType = TUInt8CountedDynArray;

{$DEFINE CDA_Interface}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Interface}

implementation

uses
  SysUtils,
  ListSorters;

Function CDA_CompareFunc(A,B: UInt8): Integer;
begin
Result := Integer(A - B);
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}

end.

