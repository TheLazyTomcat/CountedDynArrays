unit CountedDynArraysBool;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

interface

uses
  AuxTypes,
  CountedDynArrays;

type
  TBooleanCountedDynArray = record
    Arr:    array of Boolean;
    Count:  Integer;
    Data:   PtrInt;
  end;
  PBooleanCountedDynArray = ^TBooleanCountedDynArray;

  TBaseType = Boolean;
  TArrayType = TBooleanCountedDynArray;

{$DEFINE CDA_Interface}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Interface}

implementation

uses
  SysUtils,
  ListSorters;

Function CDA_CompareFunc(A,B: Boolean): Integer;
begin
Result := Ord(A) - Ord(B);
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}

end.
