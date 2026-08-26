{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Counted Dynamic Arrays

    Counted dynamic array of TObject values

  Version 1.5.6 (2026-08-25)

  Last changed 2026-08-27

  ©2018-2026 František Milt

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
  * AuxExceptions   - github.com/TheLazyTomcat/Lib.AuxExceptions
    AuxTypes        - github.com/TheLazyTomcat/Lib.AuxTypes
    BinaryStreaming - github.com/TheLazyTomcat/Lib.BinaryStreaming
    ListSorters     - github.com/TheLazyTomcat/Lib.ListSorters
    ListUtils       - github.com/TheLazyTomcat/Lib.ListUtils
    StrRect         - github.com/TheLazyTomcat/Lib.StrRect

  Library AuxExceptions is required only when rebasing local exception classes
  (see symbol CountedDynArrays_UseAuxExceptions for details).

  Library AuxExceptions might also be required as an indirect dependency.

  Indirect dependencies:
    AuxClasses  - github.com/TheLazyTomcat/Lib.AuxClasses
    SimpleCPUID - github.com/TheLazyTomcat/Lib.SimpleCPUID
    UInt64Utils - github.com/TheLazyTomcat/Lib.UInt64Utils
    WinFileInfo - github.com/TheLazyTomcat/Lib.WinFileInfo

===============================================================================}
unit CountedDynArrayObject;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

{$DEFINE CDA_FuncOverride_ItemCompare}
{$DEFINE CDA_FuncOverride_ItemSame}
{$DEFINE CDA_FuncOverride_ItemWrite}
{$DEFINE CDA_FuncOverride_ItemRead}
{$DEFINE CDA_FuncOverride_ItemDecode}

interface

uses
  Classes,
  AuxTypes, ListUtils,
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

const
  CDA_DEFAULT_VALUE = TCDABaseType(nil);

  CDA_ARRAY_NAME = 'AoObject';

//------------------------------------------------------------------------------

Function CDA_ItemCompare(A,B: TCDABaseType): Integer; {$IFDEF CanInline} inline; {$ENDIF}
var
  AInt: PtrUInt absolute A;
  BInt: PtrUInt absolute B;
begin
If AInt < BInt then
  Result := -1
else If AInt > BInt then
  Result := +1
else
  Result := 0;
end;

//------------------------------------------------------------------------------

Function CDA_ItemSame(A,B: TCDABaseType): Boolean; {$IFDEF CanInline} inline; {$ENDIF}
begin
Result := A = B;
end;

//------------------------------------------------------------------------------

procedure CDA_ItemWrite(Item: TCDABaseType; Stream: TStream);
var
  ItemInt: PtrUInt absolute Item;
begin
// utterly pointless, but here you go...
Stream_WriteUInt64(Stream,UInt64(ItemInt));
end;

//------------------------------------------------------------------------------

Function CDA_ItemRead(Stream: TStream): TCDABaseType;
var
  ResultInt: PtrUInt absolute Result;
begin
ResultInt := PtrUInt(Stream_GetUInt64(Stream));
end;

//------------------------------------------------------------------------------

Function CDA_ItemDecode(const Item: TVarRec; out Value: TCDABaseType): Boolean;
begin
Result := True;
case Item.VType of
  vtObject: Value := TCDABaseType(Item.VObject);
else
  Result := False;
end;
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}   

end.
