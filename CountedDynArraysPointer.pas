unit CountedDynArraysPointer;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

interface

uses
  AuxTypes,
  CountedDynArrays;

type
  TPointerCountedDynArray = record
    Arr:    array of Pointer;
    Count:  Integer;
    Data:   PtrInt;
  end;
  PPointerCountedDynArray = ^TPointerCountedDynArray;

  TBaseType = Pointer;
  TArrayType = TPointerCountedDynArray;

{$DEFINE CDA_Interface}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Interface}

implementation

uses
  SysUtils,
  ListSorters;

{$IFDEF FPC_DisableWarns}
  {$DEFINE FPCDWM}
  {$DEFINE W4055:={$WARN 4055 OFF}} // Conversion between ordinals and pointers is not portable
{$ENDIF}

Function CDA_CompareFunc(A,B: Pointer): Integer;
begin
{$IFDEF FPCDWM}{$PUSH}W4055{$ENDIF}
Result := Integer(PtrUInt(A) - PtrUInt(B));
{$IFDEF FPCDWM}{$POP}{$ENDIF}
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}

end.
