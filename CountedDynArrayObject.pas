{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Counted Dynamic Arrays

    Counted dynamic array of TObject values

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
unit CountedDynArrayObject;

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
  TCDABaseType = TObject;
  PCDABaseType = ^TCDABaseType;

  TCountedDynArrayObject = record
  {$DEFINE CDA_Structure}
    {$INCLUDE '.\CountedDynArrays.inc'}
  {$UNDEF CDA_Structure}
  end;
  PCountedDynArrayObject = ^TCountedDynArrayObject;

  TCDAArrayType = TCountedDynArrayObject;
  PCDAArrayType = PCountedDynArrayObject;

  // aliases
  TCountedDynArrayOfObject = TCountedDynArrayObject;
  PCountedDynArrayOfObject = PCountedDynArrayObject;

  TObjectCountedDynArray = TCountedDynArrayObject;
  PObjectCountedDynArray = PCountedDynArrayObject;

  TCDAOfObject = TCountedDynArrayObject;
  PCDAOfObject = PCountedDynArrayObject;

  TCDAObject = TCountedDynArrayObject;
  PCDAObject = PCountedDynArrayObject;

  TObjectCDA = TCountedDynArrayObject;
  PObjectCDA = PCountedDynArrayObject;

{$DEFINE CDA_Interface}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Interface}

implementation

uses
  SysUtils,
  ListSorters, StrRect, BinaryStreaming;

{$INCLUDE '.\CountedDynArrays_msgdis.inc'}

const
  CDA_DEFAULT_VALUE = TCDABaseType(nil);

  CDA_ARRAY_NAME = 'AoObject';

//------------------------------------------------------------------------------

Function CDA_ItemCompare(A,B: TCDABaseType): Integer; {$IFDEF CanInline} inline; {$ENDIF}
begin
{$IFDEF FPCDWM}{$PUSH}W4055{$ENDIF}
If PtrUInt(Pointer(A)) < PtrUInt(Pointer(B)) then
  Result := -1
else If PtrUInt(Pointer(A)) > PtrUInt(Pointer(B)) then
  Result := +1
else
  Result := 0;
{$IFDEF FPCDWM}{$POP}{$ENDIF}
end;

//------------------------------------------------------------------------------

procedure CDA_ItemWrite(Item: TCDABaseType; Stream: TStream);
begin
// utterly pointless, but here you go...
{$IFDEF FPCDWM}{$PUSH}W4055{$ENDIF}
Stream_WriteUInt64(Stream,UInt64(PtrUInt(Pointer(Item))));
{$IFDEF FPCDWM}{$POP}{$ENDIF}
end;

//------------------------------------------------------------------------------

Function CDA_ItemRead(Stream: TStream): TCDABaseType;
begin
{$IFDEF FPCDWM}{$PUSH}W4055{$ENDIF}
Result := TObject(Pointer(PtrUInt(Stream_GetUInt64(Stream))));
{$IFDEF FPCDWM}{$POP}{$ENDIF}
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}   

end.
