unit CountedDynArraysUInt16;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

interface

uses
  AuxTypes,
  CountedDynArrays;

type
  TUInt16CountedDynArray = record
    Arr:    array of UInt16;
    Count:  Integer;
    Data:   PtrInt;
  end;
  PUInt16CountedDynArray = ^TUInt16CountedDynArray;

  TBaseType = UInt16;
  TArrayType = TUInt16CountedDynArray;

{$DEFINE CDA_Interface}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Interface}

implementation

uses
  SysUtils,
  ListSorters;

Function CDA_CompareFunc(A,B: UInt16): Integer;
begin
Result := Integer(A - B);
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}

end.
