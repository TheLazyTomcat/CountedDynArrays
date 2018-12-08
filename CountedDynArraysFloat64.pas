unit CountedDynArraysFloat64;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

interface

uses
  AuxTypes,
  CountedDynArrays;

type
  TFloat64CountedDynArray = record
    Arr:    array of Float64;
    Count:  Integer;
    Data:   PtrInt;
  end;
  PFloat64CountedDynArray = ^TFloat64CountedDynArray;

  TBaseType = Float64;
  TArrayType = TFloat64CountedDynArray;

{$DEFINE CDA_Interface}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Interface}


implementation

uses
  SysUtils,
  ListSorters;

Function CDA_CompareFunc(A,B: Float64): Integer;
begin
If A > B then Result := 1
  else If A < B then Result := -1
    else Result := 0;
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}

end.

