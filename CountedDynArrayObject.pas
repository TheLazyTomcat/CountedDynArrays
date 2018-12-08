{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Counted dynamic arrays

    Counted dynamic array of objects

  ©František Milt 2018-12-08

  Version 1.0

  Dependencies:
    AuxTypes    - github.com/ncs-sniper/Lib.AuxTypes
    ListSorters - github.com/ncs-sniper/Lib.ListSorters

===============================================================================}
unit CountedDynArrayObject;

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
