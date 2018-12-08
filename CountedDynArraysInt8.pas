unit CountedDynArraysInt8;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

interface

uses
  AuxTypes,
  CountedDynArrays;

type
  TInt8CountedDynArray = record
    Arr:    array of Int8;
    Count:  Integer;
    Data:   PtrInt;
  end;
  PInt8CountedDynArray = ^TInt8CountedDynArray;

  TBaseType = Int8;
  TArrayType = TInt8CountedDynArray;

{$DEFINE CDA_Interface}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Interface}

implementation

uses
  SysUtils,
  ListSorters;

Function CDA_CompareFunc(A,B: Int8): Integer;
begin
Result := Integer(A - B);
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}

end.
