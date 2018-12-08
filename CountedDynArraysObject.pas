unit CountedDynArraysObject;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

interface

uses
  AuxTypes,
  CountedDynArrays;

type
  TObjectCountedDynArray = record
    Arr:    array of TObject;
    Count:  Integer;
    Data:   PtrInt;
  end;
  PObjectCountedDynArray = ^TObjectCountedDynArray;

  TBaseType = TObject;
  TArrayType = TObjectCountedDynArray;

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

Function CDA_CompareFunc(A,B: TObject): Integer;
begin
{$IFDEF FPCDWM}{$PUSH}W4055{$ENDIF}
Result := Integer(PtrUInt(Pointer(A)) - PtrUInt(Pointer(B)));
{$IFDEF FPCDWM}{$POP}{$ENDIF}
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}


end.
