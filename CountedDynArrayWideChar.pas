{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Counted Dynamic Arrays

    Counted dynamic array of WideChar values

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
unit CountedDynArrayWideChar;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

{$DEFINE CDA_CaseSensitiveBaseType}

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
  TCDABaseType = WideChar;
  PCDABaseType = ^TCDABaseType;

  TCountedDynArrayWideChar = record
  {$DEFINE CDA_Structure}
    {$INCLUDE '.\CountedDynArrays.inc'}
  {$UNDEF CDA_Structure}
  end;
  PCountedDynArrayWideChar = ^TCountedDynArrayWideChar;

  TCDAArrayType = TCountedDynArrayWideChar;
  PCDAArrayType = PCountedDynArrayWideChar;

  // aliases
  TCountedDynArrayOfWideChar = TCountedDynArrayWideChar;
  PCountedDynArrayOfWideChar = PCountedDynArrayWideChar;

  TWideCharCountedDynArray = TCountedDynArrayWideChar;
  PWideCharCountedDynArray = PCountedDynArrayWideChar;

  TCDAOfWideChar = TCountedDynArrayWideChar;
  PCDAOfWideChar = PCountedDynArrayWideChar;

  TCDAWideChar = TCountedDynArrayWideChar;
  PCDAWideChar = PCountedDynArrayWideChar;

  TWideCharCDA = TCountedDynArrayWideChar;
  PWideCharCDA = PCountedDynArrayWideChar;

{$DEFINE CDA_Interface}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Interface}

implementation

uses 
  SysUtils,
  ListSorters, StrRect, BinaryStreaming;

const
  CDA_DEFAULT_VALUE = TCDABaseType(#0);

  CDA_ARRAY_NAME = 'AoWideChar';

//------------------------------------------------------------------------------

Function CDA_ItemCompare(A,B: TCDABaseType; CaseSensitive: Boolean): Integer;{$IFDEF CanInline} inline;{$ENDIF}
begin
Result := WideStringCompare(A,B,CaseSensitive);
end;

//------------------------------------------------------------------------------

Function CDA_ItemSame(const A,B: TCDABaseType; CaseSensitive: Boolean): Boolean;{$IFDEF CanInline} inline;{$ENDIF}
begin
Result := WideStringSame(A,B,CaseSensitive);
end;

//------------------------------------------------------------------------------

procedure CDA_ItemWrite(Item: TCDABaseType; Stream: TStream);
begin
Stream_WriteWideChar(Stream,Item);
end;

//------------------------------------------------------------------------------

Function CDA_ItemRead(Stream: TStream): TCDABaseType;
begin
Result := Stream_GetWideChar(Stream);
end;

//------------------------------------------------------------------------------

Function CDA_ItemDecode(const Item: TVarRec; out Value: TCDABaseType): Boolean;
begin
Result := True;
case Item.VType of
  vtWideChar: Value := TCDABaseType(Item.VWideChar);
else
  Result := False;
end;
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}

end.
