{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Counted Dynamic Arrays

    Counted dynamic array of Pointer values

  Version 1.4.1 (2023-01-27)

  Last changed 2023-09-04

  ©2018-2023 František Milt

  Contacts:
    František Milt: frantisek.milt@gmail.com

  Support:
    If you find this code useful, please consider supporting its author(s) by
    making a small donation using the following link(s):

      https://www.paypal.me/FMilt

  Changelog:
    For detailed changelog and history please refer to this git repository:

      github.com/TheLazyTomcat/CountedDynArrays

  Dependencies:
    AuxClasses      - github.com/TheLazyTomcat/Lib.AuxClasses
    AuxTypes        - github.com/TheLazyTomcat/Lib.AuxTypes
    BinaryStreaming - github.com/TheLazyTomcat/Lib.BinaryStreaming
    ListSorters     - github.com/TheLazyTomcat/Lib.ListSorters
    StrRect         - github.com/TheLazyTomcat/Lib.StrRect

===============================================================================}
unit CountedDynArrayPointer;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

{$DEFINE CDA_FuncOverride_ItemCompare}
{$DEFINE CDA_FuncOverride_ItemWrite}
{$DEFINE CDA_FuncOverride_ItemRead}

interface

uses
  Classes,
  AuxTypes,
  CountedDynArrays;

type
  TCDABaseType = Pointer;
  PCDABaseType = ^TCDABaseType;

  TCountedDynArrayPointer = record
  {$DEFINE CDA_Structure}
    {$INCLUDE '.\CountedDynArrays.inc'}
  {$UNDEF CDA_Structure}
  end;
  PCountedDynArrayPointer = ^TCountedDynArrayPointer;

  TCDAArrayType = TCountedDynArrayPointer;
  PCDAArrayType = PCountedDynArrayPointer;

  // aliases
  TCountedDynArrayOfPointer = TCountedDynArrayPointer;
  PCountedDynArrayOfPointer = PCountedDynArrayPointer;

  TPointerCountedDynArray = TCountedDynArrayPointer;
  PPointerCountedDynArray = PCountedDynArrayPointer;

  TCDAOfPointer = TCountedDynArrayPointer;
  PCDAOfPointer = PCountedDynArrayPointer;

  TCDAPointer = TCountedDynArrayPointer;
  PCDAPointer = PCountedDynArrayPointer;

  TPointerCDA = TCountedDynArrayPointer;
  PPointerCDA = PCountedDynArrayPointer;

{$DEFINE CDA_Interface}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Interface}

implementation

uses
  SysUtils,
  ListSorters, StrRect, BinaryStreaming;

{$INCLUDE '.\CountedDynArrays_msgdis.inc'}

const
  CDA_DEFAULT_VALUE = nil;

  CDA_ARRAY_NAME = 'AoPointer';

//------------------------------------------------------------------------------

Function CDA_ItemCompare(A,B: TCDABaseType): Integer;{$IFDEF CanInline} inline; {$ENDIF}
begin
{$IFDEF FPCDWM}{$PUSH}W4055{$ENDIF}
If PtrUInt(A) < PtrUInt(B) then
  Result := -1
else If PtrUInt(A) > PtrUInt(B) then
  Result := +1
else
  Result := 0;
{$IFDEF FPCDWM}{$POP}{$ENDIF}
end;

//------------------------------------------------------------------------------

procedure CDA_ItemWrite(Item: TCDABaseType; Stream: TStream);
begin
// pointless, but whatever
{$IFDEF FPCDWM}{$PUSH}W4055{$ENDIF}
Stream_WriteUInt64(Stream,UInt64(PtrUInt(Item)));
{$IFDEF FPCDWM}{$POP}{$ENDIF}
end;

//------------------------------------------------------------------------------

Function CDA_ItemRead(Stream: TStream): TCDABaseType;
begin
{$IFDEF FPCDWM}{$PUSH}W4055{$ENDIF}
Result := Pointer(PtrUInt(Stream_GetUInt64(Stream)));
{$IFDEF FPCDWM}{$POP}{$ENDIF}
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}

end.
