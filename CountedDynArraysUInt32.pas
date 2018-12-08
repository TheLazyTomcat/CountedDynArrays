unit CountedDynArraysUInt32;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

interface

uses
  AuxTypes,
  CountedDynArrays;

type
  TUInt32CountedDynArray = record
    Arr:    array of UInt32;
    Count:  Integer;
    Data:   PtrInt;
  end;
  PUInt32CountedDynArray = ^TUInt32CountedDynArray;

  TBaseType = UInt32;
  TArrayType = TUInt32CountedDynArray;

{$DEFINE CDA_Interface}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Interface}

implementation

uses
  SysUtils,
  ListSorters;

Function CDA_CompareFunc(A,B: UInt32): Integer;
begin
Result := Integer(A - B);
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}

end.
