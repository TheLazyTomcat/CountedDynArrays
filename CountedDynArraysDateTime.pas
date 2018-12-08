unit CountedDynArraysDateTime;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

interface

uses
  AuxTypes,
  CountedDynArrays;

type
  TDateTimeCountedDynArray = record
    Arr:    array of TDateTime;
    Count:  Integer;
    Data:   PtrInt;
  end;
  PDateTimeCountedDynArray = ^TDateTimeCountedDynArray;

  TBaseType = TDateTime;
  TArrayType = TDateTimeCountedDynArray;

{$DEFINE CDA_Interface}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Interface}

implementation

uses
  SysUtils,
  ListSorters;

Function CDA_CompareFunc(A,B: TDateTime): Integer;
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
