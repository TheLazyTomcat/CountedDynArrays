{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Counted Dynamic Arrays

    Counted dynamic array of PtrInt values

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
unit CountedDynArrayPtrInt;

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
  TCDABaseType = PtrInt;
  PCDABaseType = ^TCDABaseType;

  TCountedDynArrayPtrInt = record
  {$DEFINE CDA_Structure}
    {$INCLUDE '.\CountedDynArrays.inc'}
  {$UNDEF CDA_Structure}
  end;
  PCountedDynArrayPtrInt = ^TCountedDynArrayPtrInt;

  TCDAArrayType = TCountedDynArrayPtrInt;
  PCDAArrayType = PCountedDynArrayPtrInt;

  // aliases
  TCountedDynArrayOfPtrInt = TCountedDynArrayPtrInt;
  PCountedDynArrayOfPtrInt = PCountedDynArrayPtrInt;

  TPtrIntCountedDynArray = TCountedDynArrayPtrInt;
  PPtrIntCountedDynArray = PCountedDynArrayPtrInt;

  TCDAOfPtrInt = TCountedDynArrayPtrInt;
  PCDAOfPtrInt = PCountedDynArrayPtrInt;

  TCDAPtrInt = TCountedDynArrayPtrInt;
  PCDAPtrInt = PCountedDynArrayPtrInt;

  TPtrIntCDA = TCountedDynArrayPtrInt;
  PPtrIntCDA = PCountedDynArrayPtrInt;

{$DEFINE CDA_Interface}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Interface}

implementation

uses
  SysUtils,
  ListSorters, StrRect, BinaryStreaming;

const
  CDA_DEFAULT_VALUE = 0;

  CDA_ARRAY_NAME = 'AoPtrInt';

//------------------------------------------------------------------------------

Function CDA_ItemCompare(A,B: TCDABaseType): Integer;
begin
If A < B then
  Result := -1
else If A > B then
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
begin
Stream_WriteInt64(Stream,Int64(Item));
end;

//------------------------------------------------------------------------------

Function CDA_ItemRead(Stream: TStream): TCDABaseType;
begin
Result := PtrInt(Stream_GetInt64(Stream));
end;

//------------------------------------------------------------------------------

Function CDA_ItemDecode(const Item: TVarRec; out Value: TCDABaseType): Boolean;
begin
Result := True;
case Item.VType of
  vtInteger:  Value := TCDABaseType(Item.VInteger);
  vtInt64:    Value := TCDABaseType(Item.VInt64^);
else
  Result := False;
end;
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}

end.
