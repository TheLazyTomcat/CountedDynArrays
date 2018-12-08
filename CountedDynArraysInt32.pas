unit CountedDynArraysInt32;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

interface

uses
  AuxTypes,
  CountedDynArrays;

type
  TInt32CountedDynArray = record
    Arr:    array of Int32;
    Count:  Integer;
    Data:   PtrInt;
  end;
  PInt32CountedDynArray = ^TInt32CountedDynArray;

  TBaseType = Int32;
  TArrayType = TInt32CountedDynArray;

{$DEFINE CDA_Interface}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Interface}

implementation

uses
  SysUtils,
  ListSorters;

Function CDA_CompareFunc(A,B: Int32): Integer;
begin
Result := Integer(A - B);
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}

end.
