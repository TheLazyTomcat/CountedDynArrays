unit CountedDynArraysUInt64;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

interface

uses
  AuxTypes,
  CountedDynArrays;

type
  TUInt64CountedDynArray = record
    Arr:    array of UInt64;
    Count:  Integer;
    Data:   PtrInt;
  end;
  PUInt64CountedDynArray = ^TUInt64CountedDynArray;

  TBaseType = UInt64;
  TArrayType = TUInt64CountedDynArray;

{$DEFINE CDA_Interface}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Interface}

implementation

uses
  SysUtils,
  ListSorters;

Function CDA_CompareFunc(A,B: UInt64): Integer;
begin
Result := Integer(A - B);
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}

end.
