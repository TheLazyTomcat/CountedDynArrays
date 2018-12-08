unit CountedDynArraysInteger;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

interface

uses
  AuxTypes,
  CountedDynArrays;

type
  TIntegerCountedDynArray = record
    Arr:    array of Integer;
    Count:  Integer;
    Data:   PtrInt;
  end;
  PIntegerCountedDynArray = ^TIntegerCountedDynArray;

  TBaseType = Integer;
  TArrayType = TIntegerCountedDynArray;

{$DEFINE CDA_Interface}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Interface}

implementation

uses
  SysUtils,
  ListSorters;

Function CDA_CompareFunc(A,B: TBaseType): Integer;
begin
Result := Ord(A) - Ord(B);
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}

end.
