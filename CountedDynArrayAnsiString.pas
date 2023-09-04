{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Counted Dynamic Arrays

    Counted dynamic array of AnsiString values

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
unit CountedDynArrayAnsiString;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

{$DEFINE CDA_ConstBaseType}
{$DEFINE CDA_CaseSensitiveBaseType}

{$DEFINE CDA_FuncOverride_ItemUnique}
{$DEFINE CDA_FuncOverride_ItemCompare}
{$DEFINE CDA_FuncOverride_ItemWrite}
{$DEFINE CDA_FuncOverride_ItemRead}

interface

uses
  Classes,
  AuxTypes,
  CountedDynArrays;

type
  TCDABaseType = AnsiString;
  PCDABaseType = ^TCDABaseType;

  TCountedDynArrayAnsiString = record
  {$DEFINE CDA_Structure}
    {$INCLUDE '.\CountedDynArrays.inc'}
  {$UNDEF CDA_Structure}
  end;
  PCountedDynArrayAnsiString = ^TCountedDynArrayAnsiString;

  TCDAArrayType = TCountedDynArrayAnsiString;
  PCDAArrayType = PCountedDynArrayAnsiString;  

  // aliases
  TCountedDynArrayOfAnsiString = TCountedDynArrayAnsiString;
  PCountedDynArrayOfAnsiString = PCountedDynArrayAnsiString;

  TAnsiStringCountedDynArray = TCountedDynArrayAnsiString;
  PAnsiStringCountedDynArray = PCountedDynArrayAnsiString;

  TCDAOfAnsiString = TCountedDynArrayAnsiString;
  PCDAOfAnsiString = PCountedDynArrayAnsiString;

  TCDAAnsiString = TCountedDynArrayAnsiString;
  PCDAAnsiString = PCountedDynArrayAnsiString;

  TAnsiStringCDA = TCountedDynArrayAnsiString;
  PAnsiStringCDA = PCountedDynArrayAnsiString;

{$DEFINE CDA_Interface}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Interface}

implementation

uses
  SysUtils,
  ListSorters, StrRect, BinaryStreaming;

{$INCLUDE '.\CountedDynArrays_msgdis.inc'}

const
  CDA_DEFAULT_VALUE = TCDABaseType('');

  CDA_ARRAY_NAME = 'AoAnsiString';

//------------------------------------------------------------------------------

procedure CDA_ItemUnique(var Item: TCDABaseType);{$IFDEF CanInline} inline;{$ENDIF}
begin
UniqueString(Item);
end;

//------------------------------------------------------------------------------

Function CDA_ItemCompare(const A,B: TCDABaseType; CaseSensitive: Boolean): Integer;{$IFDEF CanInline} inline;{$ENDIF}
begin
Result := AnsiStringCompare(A,B,CaseSensitive);
end;

//------------------------------------------------------------------------------

procedure CDA_ItemWrite(const Item: TCDABaseType; Stream: TStream);
begin
Stream_WriteAnsiString(Stream,Item);
end;

//------------------------------------------------------------------------------

Function CDA_ItemRead(Stream: TStream): TCDABaseType;
begin
Result := Stream_GetAnsiString(Stream);
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}

end.
