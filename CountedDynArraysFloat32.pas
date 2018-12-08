unit CountedDynArraysFloat32;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

interface

uses
  AuxTypes,
  CountedDynArrays;

type
  TFloat32CountedDynArray = record
    Arr:    array of Float32;
    Count:  Integer;
    Data:   PtrInt;
  end;
  PFloat32CountedDynArray = ^TFloat32CountedDynArray;

  TBaseType = Float32;
  TArrayType = TFloat32CountedDynArray;

{$DEFINE CDA_Interface}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Interface}


implementation

uses
  SysUtils,
  ListSorters;

Function CDA_CompareFunc(A,B: Float32): Integer;
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
