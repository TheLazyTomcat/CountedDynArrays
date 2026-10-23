{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Counted Dynamic Arrays

    Counted dynamic array of UInt64 values

  Version 1.5.7 (2026-10-23)

  Last changed 2026-10-23

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
unit CountedDynArrayUInt64;

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
  TCDABaseType = UInt64;
  PCDABaseType = ^TCDABaseType;

  TCountedDynArrayUInt64 = record
  {$DEFINE CDA_Structure}
    {$INCLUDE '.\CountedDynArrays.inc'}
  {$UNDEF CDA_Structure}
  end;
  PCountedDynArrayUInt64 = ^TCountedDynArrayUInt64;

  TCDAArrayType = TCountedDynArrayUInt64;
  PCDAArrayType = PCountedDynArrayUInt64;

  // aliases
  TCountedDynArrayOfUInt64 = TCountedDynArrayUInt64;
  PCountedDynArrayOfUInt64 = PCountedDynArrayUInt64;

  TUInt64CountedDynArray = TCountedDynArrayUInt64;
  PUInt64CountedDynArray = PCountedDynArrayUInt64;

  TCDAOfUInt64 = TCountedDynArrayUInt64;
  PCDAOfUInt64 = PCountedDynArrayUInt64;

  TCDAUInt64 = TCountedDynArrayUInt64;
  PCDAUInt64 = PCountedDynArrayUInt64;

  TUInt64CDA = TCountedDynArrayUInt64;
  PUInt64CDA = PCountedDynArrayUInt64;

{$DEFINE CDA_Interface}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Interface}

implementation

uses
  SysUtils,
  ListSorters, StrRect, BinaryStreaming;

const
  CDA_DEFAULT_VALUE = 0;

  CDA_ARRAY_NAME = 'AoUInt64';

//------------------------------------------------------------------------------

Function CDA_ItemCompare(A,B: TCDABaseType): Integer;
begin
If Int64Rec(A).Hi < Int64Rec(B).Hi then
  Result := -1
else If Int64Rec(A).Hi > Int64Rec(B).Hi then
  Result := +1
else
  begin
    If Int64Rec(A).Lo < Int64Rec(B).Lo then
      Result := -1
    else If Int64Rec(A).Lo > Int64Rec(B).Lo then
      Result := +1
    else
      Result := 0;
  end;
end;

//------------------------------------------------------------------------------

Function CDA_ItemSame(A,B: TCDABaseType): Boolean; {$IFDEF CanInline} inline; {$ENDIF}
begin
Result := A = B;
end;

//------------------------------------------------------------------------------

procedure CDA_ItemWrite(Item: TCDABaseType; Stream: TStream);
begin
Stream_WriteUInt64(Stream,Item);
end;

//------------------------------------------------------------------------------

Function CDA_ItemRead(Stream: TStream): TCDABaseType;
begin
Result := Stream_GetUInt64(Stream);
end;

//------------------------------------------------------------------------------

Function CDA_ItemDecode(const Item: TVarRec; out Value: TCDABaseType): Boolean;
begin
Result := True;
case Item.VType of
  vtInteger:  Value := TCDABaseType(Item.VInteger);
  vtInt64:    Value := TCDABaseType(Item.VInt64^);
{$IF Declared(vtQWord)}
  vtQWord:    Value := TCDABaseType(Item.VQWord^);
{$IFEND}
else
  Result := False;
end;
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}

end.
